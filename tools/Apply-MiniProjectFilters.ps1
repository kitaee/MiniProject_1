# Apply MiniProject-style Solution Explorer filters to headless simulators (ATS, LCS, MFRS, MSS).
# Idempotent: safe to re-run.
$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot -Parent
$commonSchema = Join-Path $root 'common\SchemaRegistryData.xml'
$filterTemplate = Join-Path $root 'tcc\src\Managers\ControlManager\ControlManager.vcxproj.filters'

function Write-Utf8($path, $content) {
    $dir = Split-Path $path -Parent
    if ($dir -and -not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
    [System.IO.File]::WriteAllText($path, $content, [System.Text.UTF8Encoding]::new($false))
}

function Get-KoreanFilterNames {
    $tpl = [System.IO.File]::ReadAllText($filterTemplate, [System.Text.UTF8Encoding]::new($false))
    @{
        Source   = ([regex]::Match($tpl, 'Filter Include="([^"]+)"').Groups[1].Value)
        Header   = ([regex]::Match($tpl, '<Filter Include="[^"]+">.*?</Filter>\s*<Filter Include="([^"]+)"').Groups[1].Value)
        Resource = ([regex]::Match($tpl, '<Filter Include="[^"]+">.*?</Filter>\s*<Filter Include="[^"]+">.*?</Filter>\s*<Filter Include="([^"]+)"').Groups[1].Value)
    }
}

function Get-FilterHeader($names) {
@'
<?xml version="1.0" encoding="utf-8"?>
<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup>
    <Filter Include="{0}"><UniqueIdentifier>{{4FC737F1-C7A5-4376-A066-2A32D752A2FB}}</UniqueIdentifier></Filter>
    <Filter Include="{1}"><UniqueIdentifier>{{93995380-89BD-4b04-88EB-625FBE52EBFC}}</UniqueIdentifier></Filter>
    <Filter Include="{2}"><UniqueIdentifier>{{67DA6AB6-F800-4c08-8B7A-83BB121AAD02}}</UniqueIdentifier></Filter>
  </ItemGroup>
'@ -f $names.Source, $names.Header, $names.Resource
}

function Get-VcxprojIncludes([string]$content, [string]$tag) {
    $pattern = "<$tag Include=`"([^`"]+)`""
    [regex]::Matches($content, $pattern) | ForEach-Object { $_.Groups[1].Value }
}

function Add-VcxprojItemIfMissing([string]$content, [string]$tag, [string]$include) {
    $escaped = [regex]::Escape($include)
    if ($content -match "<$tag Include=`"$escaped`"") { return @{ Content = $content; Changed = $false } }
    $line = "    <$tag Include=`"$include`" />"
    if ($tag -in @('None', 'Xml') -and $content -match '(?s)(<ItemGroup>\r?\n(?:\s*<(?:None|Xml) Include="[^"]+"\s*/>\r?\n)+)') {
        $content = [regex]::Replace($content, '(?s)(<ItemGroup>\r?\n(?:\s*<(?:None|Xml) Include="[^"]+"\s*/>\r?\n)+)', "`$1$line`r`n", 1)
    } elseif ($content -match "(?s)(<ItemGroup>\r?\n(?:\s*<$tag Include=`"[^`"]+`"\s*/>\r?\n)+)") {
        $content = [regex]::Replace($content, "(?s)(<ItemGroup>\r?\n(?:\s*<$tag Include=`"[^`"]+`"\s*/>\r?\n)+)", "`$1$line`r`n", 1)
    } else {
        $content = $content -replace '(  <Import Project="\$\(VCTargetsPath\)\\Microsoft\.Cpp\.targets")', "  <ItemGroup>`r`n$line`r`n  </ItemGroup>`r`n  `$1"
    }
    return @{ Content = $content; Changed = $true }
}

function Write-StandardFilters([string]$filtersPath, [string[]]$sources, [string[]]$headers, [string[]]$xmlItems, [string[]]$noneItems, $names) {
    $sb = New-Object System.Text.StringBuilder
    [void]$sb.Append((Get-FilterHeader $names))
    [void]$sb.AppendLine('')
    if ($sources.Count -gt 0) {
        [void]$sb.AppendLine('  <ItemGroup>')
        foreach ($s in $sources) {
            [void]$sb.AppendLine("    <ClCompile Include=`"$s`"><Filter>$($names.Source)</Filter></ClCompile>")
        }
        [void]$sb.AppendLine('  </ItemGroup>')
    }
    if ($headers.Count -gt 0) {
        [void]$sb.AppendLine('  <ItemGroup>')
        foreach ($h in $headers) {
            [void]$sb.AppendLine("    <ClInclude Include=`"$h`"><Filter>$($names.Header)</Filter></ClInclude>")
        }
        [void]$sb.AppendLine('  </ItemGroup>')
    }
    if ($xmlItems.Count -gt 0 -or $noneItems.Count -gt 0) {
        [void]$sb.AppendLine('  <ItemGroup>')
        foreach ($x in $xmlItems) {
            [void]$sb.AppendLine("    <Xml Include=`"$x`"><Filter>$($names.Resource)</Filter></Xml>")
        }
        foreach ($n in $noneItems) {
            [void]$sb.AppendLine("    <None Include=`"$n`"><Filter>$($names.Resource)</Filter></None>")
        }
        [void]$sb.AppendLine('  </ItemGroup>')
    }
    [void]$sb.AppendLine('</Project>')
    Write-Utf8 $filtersPath $sb.ToString()
}

function Update-SlnConsoleMain([string]$slnPath, [string]$iniName) {
    $content = [System.IO.File]::ReadAllText($slnPath)
    if ($content -notmatch 'SchemaRegistryData\.xml') {
        $content = $content -replace "(bin\\$([regex]::Escape($iniName)) = bin\\$([regex]::Escape($iniName)))", "`$1`r`n`t`tbin\SchemaRegistryData.xml = bin\SchemaRegistryData.xml"
        Write-Utf8 $slnPath $content
    }
}

function Ensure-SchemaRegistry([string]$simDir) {
    $dest = Join-Path $simDir 'bin\SchemaRegistryData.xml'
    if (-not (Test-Path $dest) -and (Test-Path $commonSchema)) {
        Copy-Item $commonSchema $dest -Force
    }
}

function Merge-ResourceItemGroups([string]$content) {
    $xmlItems = Get-VcxprojIncludes $content 'Xml'
    $noneItems = Get-VcxprojIncludes $content 'None'
    if ($xmlItems.Count -eq 0 -and $noneItems.Count -eq 0) { return $content }
    $content = [regex]::Replace($content, '(?s)\s*<ItemGroup>\s*<Xml Include="[^"]+"\s*/>\s*</ItemGroup>', '')
    $content = [regex]::Replace($content, '(?s)\s*<ItemGroup>\s*(?:<None Include="[^"]+"\s*/>\s*)+</ItemGroup>', '')
    $lines = @('  <ItemGroup>')
    foreach ($x in $xmlItems) { $lines += "    <Xml Include=`"$x`" />" }
    foreach ($n in $noneItems) { $lines += "    <None Include=`"$n`" />" }
    $lines += '  </ItemGroup>'
    $block = ($lines -join "`r`n") + "`r`n"
    return [regex]::Replace($content, '(  <Import Project="\$\(VCTargetsPath\)\\Microsoft\.Cpp\.targets")', ($block + '$1'), 1)
}

function Update-VcxprojAndFilters([string]$projPath, [string]$filtersPath, [scriptblock]$patchItems, $names) {
    $content = [System.IO.File]::ReadAllText($projPath)
    $result = & $patchItems $content
    if ($result.Changed) { $content = $result.Content }
    $merged = Merge-ResourceItemGroups $content
    if ($merged -ne $content) { Write-Utf8 $projPath $merged; $content = $merged }
    Write-StandardFilters $filtersPath `
        (Get-VcxprojIncludes $content 'ClCompile') `
        (Get-VcxprojIncludes $content 'ClInclude') `
        (Get-VcxprojIncludes $content 'Xml') `
        (Get-VcxprojIncludes $content 'None') `
        $names
}

$names = Get-KoreanFilterNames
$headless = @{
    ats  = 'ATS.ini'
    lcs  = 'LCS.ini'
    mfrs = 'MFRS.ini'
    mss  = 'MSS.ini'
}

foreach ($simKey in $headless.Keys) {
    $iniName = $headless[$simKey]
    $simDir = Join-Path $root $simKey
    $simUpper = $simKey.ToUpper()

    Ensure-SchemaRegistry $simDir
    Update-SlnConsoleMain (Join-Path $simDir "$simUpper.sln") $iniName

    Update-VcxprojAndFilters `
        (Join-Path $simDir 'src\Main\SimulatorMain\SimulatorMain.vcxproj') `
        (Join-Path $simDir 'src\Main\SimulatorMain\SimulatorMain.vcxproj.filters') `
        {
            param($c)
            $r = Add-VcxprojItemIfMissing $c 'None' "..\..\..\bin\$iniName"
            $r2 = Add-VcxprojItemIfMissing $r.Content 'Xml' '..\..\..\bin\SchemaRegistryData.xml'
            @{ Content = $r2.Content; Changed = ($r.Changed -or $r2.Changed) }
        } $names

    Update-VcxprojAndFilters `
        (Join-Path $simDir 'src\Communication\UDPCommunicationManager\UDPCommunicationManager.vcxproj') `
        (Join-Path $simDir 'src\Communication\UDPCommunicationManager\UDPCommunicationManager.vcxproj.filters') `
        {
            param($c)
            $r = Add-VcxprojItemIfMissing $c 'None' '..\..\..\bin\UDPCommunicationManager\CommLinkInfo.ini'
            $r2 = Add-VcxprojItemIfMissing $r.Content 'None' '..\..\..\bin\UDPCommunicationManager\NOM.xsd'
            @{ Content = $r2.Content; Changed = ($r.Changed -or $r2.Changed) }
        } $names

    Get-ChildItem (Join-Path $simDir 'src\Managers') -Directory | ForEach-Object {
        $mgrName = $_.Name
        $mgrProj = Join-Path $_.FullName "$mgrName.vcxproj"
        if (-not (Test-Path $mgrProj)) { return }
        Update-VcxprojAndFilters $mgrProj (Join-Path $_.FullName "$mgrName.vcxproj.filters") {
            param($c)
            Add-VcxprojItemIfMissing $c 'None' "..\..\..\bin\$mgrName\NOM.xsd"
        } $names
    }

    Write-Host "Applied MiniProject filters: $simUpper"
}

Write-Host 'Done. Reload .sln in Visual Studio to see Solution Explorer changes.'
