## 👨‍👩‍👧‍👦 구성원
| 이름                 | 담당 모의기    
| -------------------- | ------------ | 
|  **이기태** 연구원 | `발사대 모의기`       |    
|  **박수빈** 연구원 | `운용통제기` |      
|  **김동민** 연구원 | `공중위협 모의기` |
|  **김우림** 연구원 | `운용통제기`       |
|  **김주성** 연구원 | `유도탄 모의기` |
|  **김도현** 연구원 | `레이다 모의기`       |       |

## 이해관계자 식별
<img width="782" height="421" alt="image" src="https://github.com/user-attachments/assets/032c1d51-57d4-4926-a170-82d58bbac53d" />

## 요구사항 도출 및 분석
### 인터페이스 및 시스템, 연관 관계의 정의
<img width="752" height="425" alt="image" src="https://github.com/user-attachments/assets/f54b2818-881e-4e8d-b56e-064cf45582f0" />
<img width="756" height="426" alt="image" src="https://github.com/user-attachments/assets/bdec4e75-e107-4368-bafc-7962cca90534" />

## Git Convention

본 프로젝트는 브랜치 관리는 **Git Flow**를 기반으로 하며, 커밋 메시지는 **Conventional Commits** 형식을 참고하여 작성한다.

---

## Branch Strategy

본 프로젝트는 Git Flow 기반으로 브랜치를 관리한다.

| Branch       | 설명                |
| ------------ | ----------------- |
| `main`       | 배포 가능한 안정 버전 관리   |
| `develop`    | 개발 통합 브랜치         |
| `feature/*`  | 기능 개발 브랜치         |
| `fix/*`      | 버그 수정 브랜치         |
| `refactor/*` | 코드 구조 개선 브랜치      |
| `chore/*`    | 설정, 문서, 기타 작업 브랜치 |

### Branch Naming

브랜치 이름은 아래 형식을 따른다.

```text
<type>/<description>
```

### Branch Naming 예시

```bash
feature/scenario-receive
fix/missile-inventory-count
refactor/launcher-status-manager
chore/update-readme
```

---

## Commit Message Convention

본 프로젝트는 커밋 메시지를 **Conventional Commits** 형식을 참고하여 아래 형식에 맞춰 작성한다.

```text
<type>: <message>
```

### Commit Type

| Type       | 설명                | 예시                           |
| ---------- | ----------------- | ---------------------------- |
| `feat`     | 새로운 기능 추가         | `feat: 발사 명령 처리 기능 추가`       |
| `fix`      | 버그 수정             | `fix: 유도탄 재고 차감 오류 수정`       |
| `refactor` | 기능 변경 없이 코드 구조 개선 | `refactor: 발사대 상태 관리 로직 분리`  |
| `chore`    | 빌드, 설정, 문서, 기타 작업 | `chore: README 커밋 메시지 규칙 추가` |

### 작성 예시

```bash
feat: 시나리오 수신 기능 추가
fix: 유효하지 않은 유도탄 ID 예외처리 오류 수정
refactor: 유도탄 관리 모듈 구조 개선
chore: Git ignore 파일 정리
```

### 작성 규칙

* 커밋 메시지는 한글로 작성한다.
* 메시지는 변경 내용을 간결하게 표현한다.
* 하나의 커밋에는 하나의 목적만 포함한다.
* 기능 추가, 버그 수정, 구조 개선, 기타 작업을 구분하여 작성한다.
* 커밋 타입은 `feat`, `fix`, `refactor`, `chore` 중 하나를 사용한다.

### 데모 영상
https://drive.google.com/file/d/18SFCia1ubFUV9EBApbzGk7VSPSii51Qx/view?usp=drive_link
