# nFramework SDK

SDK는 `frameworks/nFramework_sdk` junction으로 연결됩니다.

```
nFramework_sdk/   →  c:\LIG\nFrameworkv1.8.2\
├── include/
├── lib/
└── bin/
```

junction 재생성:

```bat
mklink /J frameworks\nFramework_sdk c:\LIG\nFrameworkv1.8.2
```
