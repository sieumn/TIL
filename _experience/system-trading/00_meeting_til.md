# 오늘 스터디에서 배운 것 (TIL)

> 매주 스터디 당일 배우고 느낀 점을 간단히 기록합니다. (매주 업데이트)

## 1회차 미팅 (9/14)

오늘 첫 미팅을 가졌다. 각자 스터디를 통해 얻고 싶은 것을 이야기하고, 다음 스터디 시간까지 무엇을 공부해올지 정했다.

- 자동매매 프로그램을 개발하면 어떤 역량을 기를 수 있는지 알게 되었다.
  
  - 어떤 공부를 시작하기 목표를 분명히 하는 것이 중요하다는 것을 새삼 깨달았다.

- 프로그램을 개발할 때 단순히 기능을 구현하는 것 외에 고민해야만 하는 요소에 대해 인지하게 되었다.

  - 클린 아키텍처 적용, 객체 지향 코드, 디자인 패턴 등을 공부하고 고민해야겠다는 생각을 했고, 클린 아키텍처 책을 구입했다. 우선 아키텍처에 대해 학습해볼 예정이다.

- 스터디를 마칠 때 쯤에는 많은 것을 얻고 배울 수 있을 것 같다. 열심히 해야겠다.

## 2회차 미팅 (9/28)

오늘 개발 스터디에서는 각자 작성한 시스템 아키텍처를 공유하는 시간을 가졌다. 다른 분들이 작성한 아키텍처를 보며 다음 것을 배웠다.

- 데이터 크롤링의 중요성에 대해 알게 되었다.

    - 데이터를 얻을 때 여러 증권사의 API를 사용하여 정보의 양을 늘릴 수 있음을 알게 되었다.
    - 증권사 API가 아닌 일반 웹을 통한 데이터 축적도 가능할 수 있음을 인지하게 되었다.
  
- API와 DB를 추상화해야한다는 말에 공감했고, 그렇게 구현하고 싶다.
- 스터디를 준비할 때 각 모듈의 우선순위를 고려하는 과정이 필요했다. (부족했다.)
    - 각 모듈이 동작을 위한 필수 요소인지 또는 옵션인지를 정의하고, 실제 개발을 할 때 어떤 모듈부터 만들기 시작해야할지에 대한 고민을 했어야 했다.
    - 작은 단위로 `동작`하는 프로그램을 먼저 만들고, 점점 기능을 `확장`하는 방식으로 개발 흐름을 가져가자는 것에 동의했다.

## 3회차 미팅 (10/5)

오늘 개발 스터디에서는 각자 작성한 API 구현 코드를 소개하고, 코드를 작성하며 고려한 점 또는 느낀 점을 공유했다. 추가로, 앞으로 진행할 코드 리뷰 방식을 결정하고, 개발 로드맵을 작성했다. 금일 스터디에서는 다음 것들을 배웠다.

- 지난 과제를 하며 궁금했던 점을 해결했다.
  + Python의 abstract class를 사용하여 API를 추상화할 수 있었다.
  + 디렉토리 구조는 아키텍처 구조와 일치시키는 것이 좋다.
  
- 함수를 구현하기 전 interface를 먼저 작성해 보는 과정이 필요함을 알게 되었다.
  + interface는 함수의 이름, 입력 데이터, 반환 데이터 등을 포함한다.
  + 보다 정돈된 함수 구조를 만드는 데 도움이 많이 될 것 같다.
  
- git으로 협업하는 방법(github-flow)에 대해 배웠다.
  + branch 생성부터 PR 생성, 코드 리뷰, merge까지 git을 사용하여 협업하는 전체 flow를 배우고 정리할 수 있었다.
  + github desktop 애플리케이션을 사용하면 git을 보다 편리하게 사용할 수 있음을 알게 되었다.
  
- 개발 로드맵을 작성했다.
  + 대략적인 개발 로드맵을 결정하니 스터디 계획을 세우는 것이 수월해졌다.

## 4회차 미팅 (10/12)

오늘 개발 스터디에서는 실시간 체결 데이터 수신 API를 구현한 결과와 트레이딩 알고리즘을 조사한 결과를 공유했다. 추가로, 첫 코드 리뷰 후기를 공유하고 리뷰 방식을 구체화했다. 금일 스터디에서는 다음 것들을 배웠다.

- 실시간 체결 데이터 수신 API의 동작 방식을 이해했다.
- 이번 주 과제로 구현한 Real_S3 외에 Real_K3 기능을 추가로 구현해야한다는 것을 알게 되었다.
- 다양한 트레이딩 알고리즘에 대해 알게 되었다.
  + 내가 조사한 기본적인 알고리즘 외에도 돌파 전략, VWAP 전략 등의 매매 알고리즘을 알게 되었다.
- 트레이딩 효율을 높이기 위해 모든 종목의 실시간 데이터가 필요할 수 있다는 것을 인지했다.
  + 가능한 많은 종목의 실시간 체결 데이터를 받기 위한 방법을 찾는 것이 숙제로 남았다.
  + 사전 필터링, 멀티 프로세싱 등의 아이디어를 얻었다.
- 스터디 내 코드 리뷰 문화를 만들기 시작했다.
  + 첫 코드 리뷰 후기를 공유했다. 코드 리뷰가 서로에게 도움이 되는 것 같아 만족스러웠다.
  + 리뷰 사이클, PR 범위, 리뷰 내용 등의 초안을 함께 정했다. 스터디를 진행하며 더 좋은 리뷰 문화를 만들고 싶다.

## 5회차 미팅 (10/19)

오늘 개발 스터디에서는 매수, 매도 기능을 구현한 결과를 공유하고 개발하며 고민한 부분에 대해 함께 논의했다. 또한, 새로운 코드 리뷰 문화를 제안하고, 다음 주제를 선정하며 스터디 진행 방식을 조금 더 구체화했다. 오늘 스터디에서는 다음 것들을 배우고 느꼈다.

- XAQuery에서 클래스마다 다른 종류의 InBound와 OutBound를 사용하는 것을 처리하는 방법에 대해 이야기했다. 
  + 우선은 현재 구현한 것처럼 get_result 함수의 세부 구현을 각 기능 클래스에서 영역에서 함으로써, 원하는 변수를 사용하도록 둘 생각이다.
  + 더 좋은 방법이 있을지 고민이 필요하다.
- 매수/매도 기능 구현 시 input, output 인자를 어떻게 처리할지에 대해 이야기했다.
  + input, output 인자 중 꼭 필요한 내용을 구분해두는 작업이 필요하겠다고 생각했다.
- 리뷰 마니또라는 새로운 코드 리뷰 문화를 도입했다.
- 다음 과제로 구현할 클래스들의 정의와 인터페이스 일부를 함께 작성했다.
  + 클래스의 개요와 인터페이스를 같이 이야기하고 정하는 과정을 함께 함으로써, 모두가 같은 관점으로 프로그램과 클래스를 바라볼 수 있게 되었다.
  + 기능 구현 및 코드 리뷰에도 도움이 많이 될 것 같다.

## 6회차 미팅 (10/26)

오늘 개발 스터디에서는 지난 과제를 공유하고, 버퍼 기간에 대해 논의했다. 오늘 스터디에서는 다음과 같은 것들을 배웠다.

- 과제 범위를 작게 잡는 것이 중요함을 알게 되었다.
    + 이번 과제는 스케줄러와 트레이더 클래스를 만드는 것이었는데, 모든 멤버들이 과제를 다 끝내지 못했다. 시간은 부족한데 과제 양이 많으니, 단순히 과제를 못하는 것을 넘어 의욕이 꺾이는 기분마저 들기도 했다.
    + 일주일간 무엇을 해야 할지 명확하게 보일 만큼만 과제 범위를 잡기로 했다.
- 버퍼 기간을 도입했다.
    + 매주 미팅을 하고 과제를 한 지 5-6주차가 되니 다들 지쳐하는 기색이 있었다.
    + 스터디 4주를 진행하면 1주는 버퍼 기간으로 둠으로써, 쉬거나 지난 스터디 내용을 보완하는 시간을 갖기로 결정했다.
    + 시스템 트레이딩의 경우 꽤 장기 프로젝트가 될 수도 있으므로, 장기적인 관점에서 버퍼ㅁ 기간은 필요하다는 것을 이번 주에 특히 느낄 수 있었다.
- chart, trader, scheduler 세 클래스가 중요하다는 것을 알게 되었다.
    + 버퍼 기간 이후에는 세 클래스 구현을 중심으로 진행될 것으로 예상된다.

## 7회차 미팅 (11/2)

오늘 개발 스터디에서는 지난 일주일간의 근황을 공유하고, 앞으로의 4주를 계획했다. 기존에는 매주 다음 일주일간 할 과제를 논의하는 방식으로 스터디를 운영했는데, 스터디 효율을 높이기 위해 조금 더 장기적인 계획을 세워보기로 했다. 오늘 스터디에서는 다음과 같은 것들을 배웠다.

- 버퍼 기간을 도입하기를 정말 잘했다.
    + 한주 쉬고 나니 에너지 충전이 되었다. 다음 4주는 더 열심히 할 수 있을 것 같다는 생각이 든다.
    + 버퍼 기간 덕분에 지금까지의 스터디 진행을 돌아보고, 방향을 새롭게 결정할 수 있었다.
- 중장기적인 목표를 세우는 것이 중요하다는 것을 알게 되었다.
    + 중기: 4주 뒤의 목표를 세우고 나니, 앞으로 무엇을 하면 좋을지 결정하는 것이 쉬워졌다.
    + 장기: 완성 본의 형태를 직접 보니, 결과물에 대한 막연함이 해소되고 동기부여가 잘 된다.
- 일부 기능은 분담해서 구현하는 것을 고려해 보기로 했다. 선택과 집중을 하는 것도 좋은 선택지라고 생각했다.

## 8회차 미팅 (11/9)

오늘 개발 스터디에서는 지난 일주일간의 근황을 공유하고, 지난 과제였던 DB 조사 내용과 스케줄러 구현 내용을 공유했다.

- 미팅 시작할 때 체크인 시간을 갖는 것이 만족스럽다. 오늘은 체크인으로 현재 컨디션에 별점을 매겨보고 그 이유를 공유했다. 자연스럽게 근황을 알게 되고 스몰 톡을 나눌 수 있어 좋았다.
    - 체크인은 태영님이 알려주신 문화로, 미팅 시작 전 간단히 한 가지 주제에 대해 이야기하며 분위기를 푸는 과정이다.
    - 다른 미팅에서도 적용해 보고 싶다.
- 데이터베이스에 대해 공부하고 배울 수 있었다.
    - SQL과 NoSQL의 차이를 알게 되었다.
    - SQL 중에서도 server/client DB와 serverless DB의 개념과 특징에 대해 알게 되었다.
- scheduler와 program을 결합하는 여러 방법에 대해 알게 되었다.
    - scheduler 클래스 내에 시간대별(장 시작 전, 장 중, 장 마감 후) 함수를 두어, 해당 함수에서 필요한 program을 호출하는 방법
    - program 클래스를 만들고, 클래스 내에 run()이라는 함수를 두어 해당 program을 실행하는 방법
- 백테스팅할 때 과거 데이터를 사용하는 방법에 대해 알게 되었다.
    - 과거 데이터의 모든 틱을 저장하는 것에는 한계가 있기 때문에, 과거 데이터를 분봉으로 저장한 후에 해당 데이터를 틱으로 재현하는 방법을 사용할 수 있다.
    - 백테스팅을 잘 하기 위해서는 봉가정오류 등 과거 데이터를 재현하는 방법에 대한 고민이 필요하다는 것을 알게 되었다.

## 9회차 미팅 (11/16)

오늘 개발 스터디에서는 차트 구현 및 각자 추가로 구현한 코드를 공유하고, 실시간 틱 데이터를 받는 것에 대해 이야기했다.

- 실시간 틱 데이터 수신과 관련된 주의 사항 및 의견을 공유했다.
  + 장 중에 실시간 틱 데이터를 수신하기 위해서는 while Ture 내에서 데이터를 끊임없이 받아오는 동작을 실행시켜야 한다. 만약, 데이터 수신 외에 매매, 차트 저장, 전략 확인 등 다른 함수 호출이 필요하다면, 해당 함수들 또한 동일한 while 문 내에서 호출해야 하는 구조다.
  + 실시간 데이터를 수신하는 것과 다른 기능들을 분리할 수 있는 방안이 있는지 고민과 테스트가 필요하다.
- 다른 스터디원들의 작업량에 반성했다. 더 열심히 해야지.

## 10회차 미팅 (11/23)

오늘 개발 스터디에서는 실시간 데이터 수신 결과와 데이터를 차트에 연결한 결과를 공유했다. 트레이더의 속도와 효율 측면에서 태영님이 테스트한 내용도 공유 받을 수 있었다. 오늘 스터디에서는 다음 것들을 배웠다.

- stock_code 별로 chart를 따로 그리는 방법에 대해 이야기했다.
  + 이번 과제에서는 chart 클래스 내에서 stock_code를 나누어 데이터를 저장하는 방법을 사용했었는데, 애초에 stock_code 별로 chart 클래스를 따로 생성하면 더 깔끔하게 처리할 수 있음을 알게 되었다.
- 실시간 데이터를 수신하는 Real 클래스와 Trader의 관계를 다시 정리할 수 있었다.
  + 실시간 데이터를 수신할 때, OnReceiveRealData() 함수가 callback 함수를 호출하고, callback 함수가 trading을 하는 형태로 구현해야 하는 것으로 정리가 되었다.
  + Real과 Trader를 완전히 분리한 채로 프로그램을 동작시킬 수 있을지에 대한 고민과 연구가 필요하다는 것을 인지했다.
- 실전 트레이딩을 위해 앞으로 고민해야 하는 중요한 문제들에 대해 인지했다.
  + 프로그램이 실시간으로 받아야 할 데이터의 양과 트레이딩 연산에 소요되는 시간 등을 체크하는 것이 필요하다.
  + 기본 동작에 대한 구현과 검증을 완료하면, 퍼포먼스를 높이는 방법에 대한 리서치를 더 많이 진행해야겠다고 생각했다.
