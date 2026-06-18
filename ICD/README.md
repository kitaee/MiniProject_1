# ICD (외부 통신 메시지)

모의기별 ICD는 엑셀 파일(시트/페이지 per 모의기)로 관리합니다.

## 작업 순서

1. 엑셀 ICD를 이 폴더에 배치
2. 메시지 name, id, struct 필드를 각 모의기 `UDPCommunicationManager.xml` 및 업무 Manager XML에 반영
3. 공통 struct/enum은 `common/SchemaRegistryData.xml`에 정의
