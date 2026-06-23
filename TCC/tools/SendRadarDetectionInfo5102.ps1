param(
    [string]$Address = "224.0.0.100",
    [int]$Port = 10000,
    [uint32]$TargetID = 1,
    [float]$TargetVelocity = 250.0,
    [float]$StartLatitude = 37.50,
    [float]$StartLongitude = 127.00,
    [int]$RepeatPerFlag = 5,
    [int]$IntervalMs = 1000,
    [ValidateSet("Little", "Big")]
    [string]$Endian = "Little"
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$MessageID = [uint32]5102
$MessageLength = [uint32]28

function ConvertTo-EcefXY {
    param(
        [double]$Latitude,
        [double]$Longitude
    )

    $earthSemiMajorAxisMeters = 6378137.0
    $earthFlattening = 1.0 / 298.257223563
    $earthEccentricitySquared = $earthFlattening * (2.0 - $earthFlattening)

    $latitudeRadians = $Latitude * [Math]::PI / 180.0
    $longitudeRadians = $Longitude * [Math]::PI / 180.0
    $sinLatitude = [Math]::Sin($latitudeRadians)
    $cosLatitude = [Math]::Cos($latitudeRadians)
    $radius = $earthSemiMajorAxisMeters /
        [Math]::Sqrt(1.0 - $earthEccentricitySquared * $sinLatitude * $sinLatitude)

    return @{
        X = [float]($radius * $cosLatitude * [Math]::Cos($longitudeRadians))
        Y = [float]($radius * $cosLatitude * [Math]::Sin($longitudeRadians))
    }
}

function ConvertTo-TargetEndian {
    param(
        [byte[]]$Bytes
    )

    $wantBigEndian = $Endian -eq "Big"
    if (($wantBigEndian -and [BitConverter]::IsLittleEndian) -or
        (-not $wantBigEndian -and -not [BitConverter]::IsLittleEndian)) {
        [Array]::Reverse($Bytes)
    }

    return $Bytes
}

function Add-UInt32Value {
    param(
        [System.Collections.Generic.List[byte]]$Buffer,
        [uint32]$Value
    )

    $bytes = ConvertTo-TargetEndian -Bytes ([BitConverter]::GetBytes($Value))
    $Buffer.AddRange($bytes)
}

function Add-FloatValue {
    param(
        [System.Collections.Generic.List[byte]]$Buffer,
        [float]$Value
    )

    $bytes = ConvertTo-TargetEndian -Bytes ([BitConverter]::GetBytes($Value))
    $Buffer.AddRange($bytes)
}

function New-RadarDetectionPacket {
    param(
        [uint32]$DetectedFlag,
        [float]$Latitude,
        [float]$Longitude
    )

    $ecef = ConvertTo-EcefXY -Latitude $Latitude -Longitude $Longitude
    $buffer = [System.Collections.Generic.List[byte]]::new()

    Add-UInt32Value -Buffer $buffer -Value $MessageID
    Add-UInt32Value -Buffer $buffer -Value $MessageLength
    Add-UInt32Value -Buffer $buffer -Value $TargetID
    Add-FloatValue -Buffer $buffer -Value $ecef.X
    Add-FloatValue -Buffer $buffer -Value $ecef.Y
    Add-UInt32Value -Buffer $buffer -Value $DetectedFlag
    Add-FloatValue -Buffer $buffer -Value $TargetVelocity

    return @{
        Bytes = $buffer.ToArray()
        X = $ecef.X
        Y = $ecef.Y
    }
}

$udpClient = [System.Net.Sockets.UdpClient]::new()
$udpClient.MulticastLoopback = $true
$udpClient.Client.SetSocketOption(
    [System.Net.Sockets.SocketOptionLevel]::IP,
    [System.Net.Sockets.SocketOptionName]::MulticastTimeToLive,
    1)

$remoteEndpoint = [System.Net.IPEndPoint]::new([System.Net.IPAddress]::Parse($Address), $Port)

try {
    foreach ($flag in 0, 1, 2) {
        for ($index = 0; $index -lt $RepeatPerFlag; $index++) {
            $latitude = [float]($StartLatitude + ($flag * 0.12) + ($index * 0.01))
            $longitude = [float]($StartLongitude + ($flag * 0.15) + ($index * 0.01))
            $packet = New-RadarDetectionPacket -DetectedFlag ([uint32]$flag) -Latitude $latitude -Longitude $longitude

            [void]$udpClient.Send($packet.Bytes, $packet.Bytes.Length, $remoteEndpoint)

            Write-Host ("Sent 5102 RadarDetectionInfo endian={0} flag={1} seq={2}/5 lat={3:F5} lon={4:F5} x={5:F1} y={6:F1}" -f `
                $Endian, $flag, ($index + 1), $latitude, $longitude, $packet.X, $packet.Y)

            Start-Sleep -Milliseconds $IntervalMs
        }
    }
}
finally {
    $udpClient.Dispose()
}
