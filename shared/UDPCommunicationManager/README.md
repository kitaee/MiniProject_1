# UDPCommunicationManager (공유 소스)

선택 사항: 모의기별 `UDPCommunicationManager` 소스를 한 벌로 공유할 때 이 폴더에 배치합니다.

MiniProject 예제의 `UDPCommunicationManager`를 복사한 뒤 ICD에 맞게 XML·CommLinkInfo.ini만 모의기별로 분리하는 패턴을 권장합니다.

## 역할

- UDP 패킷 ↔ NOM 변환 (외부 통신 전담)
- BaseManager 상속 DLL
- 업무 Manager는 UDP 소켓을 직접 다루지 않음
