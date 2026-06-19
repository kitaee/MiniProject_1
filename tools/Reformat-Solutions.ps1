# Reformat SimulatorSuite .sln to MiniProject folder layout (UTF-8)
$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot -Parent

function Write-Utf8($path, $content) {
    [System.IO.File]::WriteAllText($path, $content, [System.Text.UTF8Encoding]::new($false))
}

function New-HeadlessSln($simUpper, $iniName, $projects) {
    # projects: array of @{ Name; Guid; Path; Kind = 'main'|'manager'|'udp' }
    $folderConsole = '{8AB46294-6251-4E0B-A535-C30AC8A5AA40}'
    $folderPlugIn = '{190E9A0A-A577-4E01-8462-5B3DBBD41D28}'
    $folderComm = '{0FA14B51-DE65-4B73-B867-98E01E6727D3}'

    $sln = @"
Microsoft Visual Studio Solution File, Format Version 12.00
# Visual Studio Version 17
VisualStudioVersion = 17.0.31903.59
MinimumVisualStudioVersion = 10.0.40219.1
Project("{2150E333-8FDC-42A3-9474-1A3956D46DE8}") = "PlugInManager", "PlugInManager", "$folderPlugIn"
EndProject
Project("{2150E333-8FDC-42A3-9474-1A3956D46DE8}") = "ConsoleMain", "ConsoleMain", "$folderConsole"
	ProjectSection(SolutionItems) = preProject
		bin\$iniName = bin\$iniName
		bin\SchemaRegistryData.xml = bin\SchemaRegistryData.xml
	EndProjectSection
EndProject
Project("{2150E333-8FDC-42A3-9474-1A3956D46DE8}") = "Communication", "Communication", "$folderComm"
EndProject
"@
    foreach ($p in $projects) {
        $sln += "`r`nProject(`"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}`") = `"$($p.Name)`", `"$($p.Path)`", `"$($p.Guid)`"`r`nEndProject"
    }
    $sln += "`r`nGlobal`r`n`tGlobalSection(SolutionConfigurationPlatforms) = preSolution`r`n`t`tDebug|x64 = Debug|x64`r`n`t`tRelease|x64 = Release|x64`r`n`tEndGlobalSection`r`n`tGlobalSection(ProjectConfigurationPlatforms) = postSolution"
    foreach ($p in $projects) {
        $g = $p.Guid
        $sln += "`r`n`t`t$g.Debug|x64.ActiveCfg = Debug|x64`r`n`t`t$g.Debug|x64.Build.0 = Debug|x64`r`n`t`t$g.Release|x64.ActiveCfg = Release|x64`r`n`t`t$g.Release|x64.Build.0 = Release|x64"
    }
    $sln += "`r`n`tEndGlobalSection`r`n`tGlobalSection(SolutionProperties) = preSolution`r`n`t`tHideSolutionNode = FALSE`r`n`tEndGlobalSection`r`n`tGlobalSection(NestedProjects) = preSolution"
    foreach ($p in $projects) {
        $parent = switch ($p.Kind) {
            'main' { $folderConsole }
            'udp' { $folderComm }
            default { $folderPlugIn }
        }
        $sln += "`r`n`t`t$($p.Guid) = $parent"
    }
    $sln += "`r`n`tEndGlobalSection`r`nEndGlobal`r`n"
    Write-Utf8 (Join-Path $root "$simUpper\$simUpper.sln") $sln
}

# ATS
New-HeadlessSln 'ats' 'ATS.ini' @(
    @{ Name='SimulatorMain'; Guid='{DE3CD81E-490E-4F44-A17B-5F222CF5625D}'; Path='src\Main\SimulatorMain\SimulatorMain.vcxproj'; Kind='main' }
    @{ Name='SimulationManager'; Guid='{B5DFC520-B35D-488E-AC77-68632C034DF0}'; Path='src\Managers\SimulationManager\SimulationManager.vcxproj'; Kind='manager' }
    @{ Name='ATSModelManager'; Guid='{91FB3C06-45EE-4DD5-91EE-875F0BD9406C}'; Path='src\Managers\ATSModelManager\ATSModelManager.vcxproj'; Kind='manager' }
    @{ Name='UDPCommunicationManager'; Guid='{9B625DB5-DA6D-4D6A-A3A4-235255FEF91F}'; Path='src\Communication\UDPCommunicationManager\UDPCommunicationManager.vcxproj'; Kind='udp' }
)

# LCS
New-HeadlessSln 'lcs' 'LCS.ini' @(
    @{ Name='SimulatorMain'; Guid='{EE033075-403D-45C4-8FBF-6EEAA8F54432}'; Path='src\Main\SimulatorMain\SimulatorMain.vcxproj'; Kind='main' }
    @{ Name='SimulationManager'; Guid='{28830F74-6D12-4474-B9B1-417DC1AD3527}'; Path='src\Managers\SimulationManager\SimulationManager.vcxproj'; Kind='manager' }
    @{ Name='LaunchManager'; Guid='{A8A89DFD-F1AB-4D81-A0CA-82DB24664C4D}'; Path='src\Managers\LaunchManager\LaunchManager.vcxproj'; Kind='manager' }
    @{ Name='LCSModelManager'; Guid='{CB605800-5F5A-49BE-99A0-0D37D65D7FCC}'; Path='src\Managers\LCSModelManager\LCSModelManager.vcxproj'; Kind='manager' }
    @{ Name='UDPCommunicationManager'; Guid='{EF6D9400-CBA4-4121-BB15-1ED456822274}'; Path='src\Communication\UDPCommunicationManager\UDPCommunicationManager.vcxproj'; Kind='udp' }
)

# MFRS
New-HeadlessSln 'mfrs' 'MFRS.ini' @(
    @{ Name='SimulatorMain'; Guid='{100E3855-BDB5-4159-8EE8-6C26296D6336}'; Path='src\Main\SimulatorMain\SimulatorMain.vcxproj'; Kind='main' }
    @{ Name='SimulationManager'; Guid='{D97FD16B-E48D-4B7A-B94E-3A5232BD116C}'; Path='src\Managers\SimulationManager\SimulationManager.vcxproj'; Kind='manager' }
    @{ Name='DetectManager'; Guid='{7ECB7D9A-9F58-4AC6-9B27-98FC5B9AD238}'; Path='src\Managers\DetectManager\DetectManager.vcxproj'; Kind='manager' }
    @{ Name='DataLinkManager'; Guid='{449BBA45-F5D7-4D08-ADEA-5E8B9CC854B6}'; Path='src\Managers\DataLinkManager\DataLinkManager.vcxproj'; Kind='manager' }
    @{ Name='MFRSModelManager'; Guid='{39C7347D-7831-48FC-B279-2D72491580BB}'; Path='src\Managers\MFRSModelManager\MFRSModelManager.vcxproj'; Kind='manager' }
    @{ Name='UDPCommunicationManager'; Guid='{B661C6FE-03E9-42A2-AAFB-97F0697D70F9}'; Path='src\Communication\UDPCommunicationManager\UDPCommunicationManager.vcxproj'; Kind='udp' }
)

# MSS
New-HeadlessSln 'mss' 'MSS.ini' @(
    @{ Name='SimulatorMain'; Guid='{D5059ED9-AC27-43B1-BC8E-ED2DC901DDB7}'; Path='src\Main\SimulatorMain\SimulatorMain.vcxproj'; Kind='main' }
    @{ Name='SimulationManager'; Guid='{596F045A-F2CE-4515-96F9-07A7BC5473B6}'; Path='src\Managers\SimulationManager\SimulationManager.vcxproj'; Kind='manager' }
    @{ Name='LaunchManager'; Guid='{C3ABE6BC-C339-4F6A-A215-A7418C9F4DC2}'; Path='src\Managers\LaunchManager\LaunchManager.vcxproj'; Kind='manager' }
    @{ Name='DataLinkManager'; Guid='{4E84EDA9-3839-4044-AB30-8043350FC317}'; Path='src\Managers\DataLinkManager\DataLinkManager.vcxproj'; Kind='manager' }
    @{ Name='MSSModelManager'; Guid='{4958B541-81ED-42DD-BB77-5D643AA211D6}'; Path='src\Managers\MSSModelManager\MSSModelManager.vcxproj'; Kind='manager' }
    @{ Name='DetonationManager'; Guid='{FDF776C5-1CDB-4FB2-B033-333B06AE021F}'; Path='src\Managers\DetonationManager\DetonationManager.vcxproj'; Kind='manager' }
    @{ Name='UDPCommunicationManager'; Guid='{1E7D469B-A0C3-4D82-80A6-2248EAB2F549}'; Path='src\Communication\UDPCommunicationManager\UDPCommunicationManager.vcxproj'; Kind='udp' }
)

Write-Host 'Reformatted ATS/LCS/MFRS/MSS solutions (TCC.sln updated separately).'
