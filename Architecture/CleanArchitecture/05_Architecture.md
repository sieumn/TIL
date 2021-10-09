# #5 아키텍처의 역할과 결합 분리 모드

<!-- 2021.10.06 -->

> Clean Architecture(Martin, Robert C.) 5부 15-16장 정리

## 이 페이지를 읽으면 알 수 있는 것

- 개발, 배포, 운영, 유지보수, 측면에서 아키텍처의 역할은 무엇인가?
- 아키텍처에서 정책과 세부사항은 어떤 관계를 가져야 하는가?
- 유스케이스 측면에서 아키텍처의 역할은 무엇인가?
- 아키텍처에서 각 컴포넌트의 결합은 어떻게 분리될 수 있는가?

## 15장. 아키텍처란?

아키텍처의 주된 목적은 시스템의 생명주기를 지원하는 것이다. 좋은 아키텍처는 시스템을 쉽게 이해하고, 쉽게 개발하며, 쉽게 유지보수하고, 또 쉽게 배포하게 해준다. 아키텍처의 궁극적인 목표는 시스템의 수명과 관련된 비용은 최소화하고, 프로그래머의 생산성은 최대화하는 데 있다.

### 개발

아키텍처는 개발 팀의 구조에 따라 달라질 수 있다. 개발 팀이 아주 작다면, 잘 정의된 아키텍처 없이도 서로 효율적으로 협력하여 모노리틱 시스템을 개발할 수 있다. 이러한 팀에서는 아키텍처 관련 제약이 오히려 방해가 된다고 여길 가능성이 높다. 수많은 시스템에서 좋은 아키텍처가 결여되는 바로 이 때문이다.

반면 개발 팀이 매우 크다면, 시스템을 잘 설계된 컴포넌트 단위로 분리하지 않으면 개발을 진척하기가 힘들 것이다. 따라서 시스템을 구성하는 컴포넌트는 개발 그룹에 따라 분리될 것이고, 그것이 시스템의 아키텍처로 발전될 가능성이 높다. 하지만, 이러한 개발 그룹별 컴포넌트 아키텍처가 최적의 아키텍처일 가능성은 거의 없다.

### 배포

소프트웨어 시스템이 사용될 수 있으려면 반드시 배포할 수 있어야 한다. 따라서 소프트웨어 아키텍처는 시스템을 단 한 번에 쉽게 배포할 수 있도록 만드는 데 목표를 둔다.

하지만 대부분의 사람들이 초기 개발 단계에서는 배포 전략을 고려하지 않는다. 이로 인해 개발하기는 쉽더라도 배포하기는 상당히 어려운 아키텍처가 만들어지는 것이다. 훌륭한 아키텍트는 배포 문제를 초기에 고려하여 컴포넌트간 상호 연결을 관리해야 한다.

### 운영

비용 관점에서 아키텍처는 운영보다는 개발, 배포, 유지보수 쪽으로 더 기운다. 하지만, 좋은 소프트웨어 아키텍처는 시스템의 운영 방식을 잘 드러내 준다는 특징을 갖는다. 시스템 아키텍처는 유스케이스, 기능, 시스템의 필수 행위를 최상급 엔티티로 격상시키고, 이 요소들을 개발자에게 주요 목표로 인식 시킨다. 이를 통해 시스템을 이해하기 쉬워지고, 개발과 유지보수에 큰 도움이 된다.

### 유지보수

유지보수는 소프트웨어 시스템에서 비용이 가장 많이 드는 요소다. 유지보수의 가장 큰 비용은 탐사에 있다. 탐사란 기존 소프트퉤어에 새로운 기능을 추가하거나 결함을 수정할 때 소프트웨어를 파헤쳐서 어떤 전략으로 어디를 고쳐야 할지 결정할 때 드는 비용이다. 이러한 변경에서 의도하지 않은 결함이 발생할 가능성은 항상 존재하며, 이로 인한 위험부담 비용이 추가된다. 따라서, 신중하게 설계된 아키텍처는 탐사 비용을 크게 줄이는 데 기여한다.

### 선택사항 열어 두기

모든 소프트웨어 시스템은 두 가지 주요 구성요소로 분해될 수 있는데, 바로 정책과 세부사항이다. 정책이란 시스템의 모든 업무 규칙과 절차를 구체화하는 요소이며, 세부사항은 사람, 외부 시스템, 프로그래머가 정책과 소통할 때 필요한 요소를 말한다. 입출력 장치, 데이터베이스, 웹, 서버, 프레임워크 등이 세부사항에 해당되며, 세부사항은 정책이 가진 행위에는 전혀 영향을 주지 않는다.

훌륭한 아키텍트는 정책을 시스템에서 가장 핵심적인 요소로 식별하고, 동시에 세부사항은 정책에 무관하게 동작하도록 구성한다. 예를 들면 다음과 같다.

- 개발 초기에는 DB 시스템을 선택할 필요가 없다. 고수준의 정책은 어떤 종류의 DB를 사용하는지 신경 써서는 안 된다.
- 개발 초기에는 웹 서버를 선택할 필요가 없다. 고수준의 정책은 자신이 웹을 통해 전달된다는 사실을 알아서는 안 된다.
- 개발 초기에는 REST를 적용할 필요가 없다. 고수준의 정책은 외부 세계로의 인터페이스에 독립적이어야 한다.
- 개발 초기에는 의존성 주입 프레임워크를 적용할 필요가 없다. 고수준의 정책은 의존성을 해석하는 방식에 대해 신경 써서는 안 된다.

위의 예시처럼 세부사항에 대한 결정을 가능한 오래 참을 수 있어야 한다. 좋은 아키텍트는 결정되지 않은 사항의 수를 최대화한다.

### 결론

좋은 아키텍트는 세부사항을 정책으로부터 신중하게 가려내고 분리한다. 이를 통해 정책은 세부사항에 관한 어떠한 지식도 갖지 못하게 되며, 어떤 경우에도 세부사항에 의존하지 않게 된다. 좋은 아키텍트는 세부사항에 대한 결정을 가능한 한 오랫동안 미룰 수 있는 방향으로 정책을 설계한다.

## 16장. 독립성

좋은 아키텍처는 다음 4가지 요소(유스케이스, 운영, 개발, 배포)를 지원해야 한다.

### 유스케이스

시스템 아키텍처는 시스템의 의도를 지원해야 한다. 만약 시스템이 장바구니 애플리케이션이라면, 이 아키텍처는 장바구니와 관련된 유스케이스를 지원해야 한다. 아키텍처에서 최우선은 유스케이스이며, 아키텍처는 반드시 유스케이스를 지원해야 한다.

아키텍처는 시스템의 행위에 큰 영향을 주지 않는다. 하지만, 좋은 아키텍처는 시스템의 행위를 명확히 정의하고 외부로 드러내며, 이를 통해 시스템이 지닌 의도를 아키텍처 수준에서 알아볼 수 있게 만든다. 좋은 아키텍처는 유스케이스를 시스템 구조에서 한눈에 드러낸다.

### 운영

운영의 관점에서 아키텍처는 더 실질적인 역할을 맡는다. 아키텍처는 시스템이 요구하는 처리량과 응답시간을 보장해야 하며, 필요한 운영 작업을 허용하는 형태로 구조화되어야 한다. 하지만, 이러한 결정은 열어 두어야 하는 선택사항 중 하나다. 아키텍처에서 컴포넌트 간 통신 방식을 특정 형태로 제한하지 않는다면, 시간이 지나 운영에 필요한 요구 사항이 바뀌더라도 스레드, 프로세스, 서비스 구성을 전환하는 일이 어렵지 않게 된다.

### 개발

아키텍처는 개발 환경에서 핵심적인 역할을 수행한다. 많은 팀으로 구성된 조직에서 어떤 시스템을 개발한다면, 각 팀이 독립적으로 개발 가능한 아키텍처를 반드시 확보해야 한다.

### 배포

아키텍처는 배포 용이성을 결정하는 데 중요한 역할을 하며, 이 때의 목표는 '즉각적인 배포'다. 좋은 아키텍처는 시스템이 빌드된 후 즉각 배포할 수 있도록 지원해야 한다. 이러한 아키텍처를 위해서는 시스템을 컴포넌트 단위로 적절하게 분할하고 격리시켜야 한다. 또한 마스터 컴포넌트는 시스템 전체를 하나로 묶고, 각 컴포넌트를 올바르게 구동하고 통합하고 관리해야 한다.

### 계층 결합 분리

아키텍트는 시스템에서 필요한 모든 유스케이스를 알지는 못하더라도, 시스템의 기본적인 의도는 분명히 알 수 있다. 즉, 아키텍트는 유스케이스에 단일 책임 원칙과 공통 폐쇄 원칙을 적용하여, 맥락에 따라 서로 다른 이유로 변경되는 것들은 분리하고 동일한 이유로 변경되는 것들을 묶어야 한다.

예를 들어, 사용자 인터페이스가 변경되는 이유는 업무 규칙과는 아무런 관련이 없다. 만약 유스케이스가 두 가지 요소를 모두 포함한다면, 유스케이스는 UI와 업무 규칙을 분리해야만 한다. 이렇게, 아키텍트는 변경 단위에 따라 시스템을 수평적인 계층으로 분리해야 한다. 이러한 수평적인 계층의 예로는 UI, 애플리케이션 특화 업무 규칙, 독립적인 업무 규칙, 데이터베이스 등이 있다.

### 유스케이스 결합 분리

유스케이스 자체에서도 결합과 분할이 자주 이루어진다. 예를 들어, 주문 입력 시스템에서 주문을 추가하는 유스케이스는 주문을 삭제하는 유스케이스와는 분명히 다른 이유로 변경 된다. 따라서 주문이라는 유스케이스 내에서도 주문 입력과 주문 삭제는 서로 분리되어야 한다. 

정리하면 아키텍트는 시스템을 수평적 계층으로 분할하는 동시에, 해당 계층을 가로지르는 수직적인 유스케이스 분할을 추가해야 한다. 즉, UI 를 구성하는 유스케이스 내에서도 주문 추가 유스케이스 UI와 주문 삭제 유스케이스 UI를 수직으로 분할해야 한다는 것이다.

이렇게 시스템에서 서로 다른 이유로 변경되는 요소들의 결합을 분리하면, 기존 요소에 영향을 주지 않고도 새로운 유스케이스를 추가하거나 수정할 수 있다.

### 결합 분리 모드

이러한 결합 분리는 운영 측면에서도 유용하다. 유스케이스에서 서로 다른 관점이 분리된다면, 높은 처리량을 보장해야 하는 유스케이스와 낮은 처리량으로도 충분한 유스케이스는 이미 분리되어 있을 가능성이 높다. 또, UI와 데이터베이스가 분리되어 있다면 두 유스케이스는 서로 다른 서버에서 실행될 수 있다.

다만 이렇게 분리된 컴포넌트를 서로 다른 서버에서 실행하는 상황이라면, 분리된 컴포넌트는 반드시 독립된 서비스어야만 한다. 이렇게 서비스에 기반한 아키텍처를 흔히 서비스 지향 아키텍처(SOA, Service-Oriented Architecture)라고 부른다. 이렇게, 때때로 아키텍처는 컴포넌트를 서비스 수준까지도 분리될 수도 있다.

### 개발 및 배포 독립성

개발 독립성 측면에서 컴포넌트가 완전히 분리되면 팀 사이의 간섭은 줄어든다. 또 유스케이스와 계층의 결합이 분리되면 배포 측면에서도 고도의 유연성이 생긴다. 결합을 제대로 분리했다면 운영 중인 시스템에서도 계층과 유스케이스를 쉽게 교체할 수 있다.

### 진짜 중복과 우발적 중복

소프트웨어에서 중복은 일반적으로 나쁜 것이지만, 우리는 진짜 중복과 우발적인 중복을 구분할 수 있어야 한다. 중복처럼 보이는 두 코드 영역이 서로 다른 속도와 다른 이유로 변경된다면 두 코드는 진짜 중복이 아니다. 따라서, 자동반사적으로 중복을 제거해버리는 잘못을 저지르지 않도록 주의하자.

### 결합 분리 모드 (다시)

계층과 유스케이스의 결합을 분리하는 방법은 다양하다.

#### 소스 수준 분리 모드

소스 코드 모듈 사이의 의존성을 제어할 수 있다. 이를 통해 하나의 모듈이 변하더라도 다른 모듈을 변경하거나 재컴파일하지 않도록 만들 수 있다. 이 모드에서는 모든 컴포넌트가 같은 주소 공간에서 실행되고, 각 컴포넌트는 간단한 함수 호출을 통해 통신한다. 컴퓨터 메모리에는 하나의 실행 파일만이 로드된다. 이 구조는 흔히 모노리틱 구조라고 불린다.

#### 배포 수준 분리 모드

jar 파일, DLL, 공유 라이브러리와 같이 배포 가능한 단위들 사이의 의존성을 제어할 수 있다. 많은 컴포넌트가 여전히 같은 주소 공간에 상주하며, 단순한 함수 호출을 통해 통신할 수 있다. 이 모드의 중요한 특징은 결합이 분리된 컴포넌트가 jar, GEM, DLL과 같이 독립적으로 배포할 수 있는 단위로 분할되어 있다는 것이다.

#### 서비스 수준 분리 모드

각 컴포넌트의 의존 수준을 데이터 구조 단위까지 낮추고, 순전히 네트워크 패킷을 통해서만 통신하도록 만들 수 있다. 이를 통해 실행 가능한 단위는 소스 변경에 대해 서로 완전히 독립적이게 된다.

### 결론

시스템의 결합 분리 모드는 시간이 지나면서 바뀌기 쉬우며, 뛰어난 아키텍트는 이러한 변경을 예측하여 큰 무리 없이 반영할 수 있도록 만들어야 한다.

좋은 아키텍처는 시스템이 모노리틱 구조로 태어나서 단일 파일로 배포되더라도, 이후에는 독립적으로 배포 가능한 단위들의 집합으로 성장하고, 또 독립적인 서비스 수준으로 성장할 수 있도록 만들어져야 한다. 또한, 좋은 아키텍처라면 나중에 상황이 바뀌었을 때 이 진행 방향을 거꾸로 돌려 원래 형태인 모노리틱 구조로 되돌릴 수도 있어야 한다. 즉, 결합 분리 모드는 선택사항으로 남겨져야 한다.