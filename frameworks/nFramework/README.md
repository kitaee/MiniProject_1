# nFramework SDK (팀 공통 경로)

SDK는 **Git에 포함하지 않습니다.** 팀 전원 동일 경로를 사용합니다.

## 표준 경로

```
C:\LIG\nFrameworkv1.8.2\
├── include\
├── lib\
└── bin\
    ├── NOMHandlerLib.Net8\...
    ├── CS_NOM.Net8\...
    └── *.dll
```

경로는 `frameworks/nFramework.path` 한 줄 파일에 기록되어 있으며,  
MSBuild `NFW_DIR` (`Directory.Build.props`)와 PowerShell 스크립트가 이를 참조합니다.

## 초기 확인 (junction 불필요)

```powershell
Test-Path C:\LIG\nFrameworkv1.8.2\include
Test-Path C:\LIG\nFrameworkv1.8.2\bin\NOMHandlerLib.Net8\Debug\net8.0-windows\NOMHandlerLib.Net8.dll
```

## 런타임 DLL 복사

```powershell
cd <SimulatorSuite>
powershell -ExecutionPolicy Bypass -File tools\Copy-NFrameworkBin.ps1 -Simulator tcc
```

## 다른 PC에 SDK 경로가 다를 때 (예외)

1. `frameworks/nFramework.path` 수정, **또는**
2. 환경 변수 `NFW_ROOT=D:\your\path` 설정, **또는**
3. 루트에 `Directory.Build.props.user` 생성:

```xml
<?xml version="1.0" encoding="utf-8"?>
<Project>
  <PropertyGroup>
    <NFW_DIR>D:\your\nFrameworkv1.8.2\</NFW_DIR>
  </PropertyGroup>
</Project>
```

## (선택) junction — 더 이상 필수 아님

이전 방식: `frameworks\nFramework_sdk` → SDK junction.  
현재는 `NFW_DIR`이 `C:\LIG\nFrameworkv1.8.2`를 직접 가리킵니다.
