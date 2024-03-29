# #2 MAC 에서 증권사 API 사용하기

> 시스템 트레이딩 개발 스터디 2주차 회고 (2021.09.28 - 10.04)

### AWS Windows 서버를 사용해보자

 자동매매 프로그램을 개발하기 위해서는 증권사 API 연동이 필수적이다. 그리고, 국내 증권사에서 제공하는 OCX, COM 버전의 API를 사용하기 위해서는 반드시 Windows 개발 환경이 필요하다. 이 사실은 별도의 Windows 환경 없이 살아가는 맥 유저에게 큰 고민이 되었다.

 맥북에 Windows를 직접 설치하는 방법은 고려 대상이 아니었으므로, 남은 방법은 Windows 데스크톱을 구매하거나 퍼블릭 클라우드를 이용하는 것뿐이었다. 가급적 퍼블릭 클라우드를 사용해보려고 알아보던 중, AWS에 가입하면 1년간 프리 티어 서버를 사용할 수 있다는 것을 알게 되었다. vCPU 1코어, 1GB 메모리의 프리 티어 사양이 걱정은 됐지만, 다른 방법이 없었으니 우선 사용해보기로 했다.

 AWS 계정을 생성하고, 프리 티어 용으로 제공되는 Windows 서버를 생성했다. 맥에 RDP 애플리케이션을 설치하고, AWS Windows 서버에 정상적으로 접속했다. 서버에 환경 설정을 하고, 이베스트 API와 파이참을 설치했다. 이대로 개발 환경 문제는 잘 해결되는 것처럼 보였다.

### 이렇게 쉬울 리 없지

 안도의 순간도 잠시, RDP로 연결한 AWS 서버에서 파이참을 켜고 코드 작성을 시작하자마자 문제는 다시 원점으로 돌아왔다. 코드를 한 줄 작성할 때마다 몇 초를 기다려야 했고, 코드 실행 버튼을 누르면 RDP 연결이 중단되었다. 약 두 시간의 인내와 시도의 반복 끝에 그만두기로 결정했다. 정신 건강에 해로우니 이 방법은 추천하지 않는다.

 결국 이번 주 API 개발 과제는 본가에 있는 Windows 데스크톱을 사용했다. 데스크톱 덕분에 아주 쾌적하게 API 구현에 성공했다. 제목은 거짓말이다. 본 회고는 MAC에서 증권사 API 사용하기 실패 회고다.

### 다음 시도는?

 우선 다른 스터디원분들이 알려주신 대로, ssh로 AWS 서버에 접속하여 실행시키는 방식을 시도해보려고 한다. 코드 작성은 맥에서 하고 AWS 서버에서 코드 실행만 할 수 있으면, 확실히 RDP를 사용하는 것보다 서버에 무리가 가지 않을 것으로 예상된다. 성공한다면 본 회고에 후기를 덧붙여 두겠다.

 만약 실패한다면, 본가 데스크톱을 계속 원격으로 사용하거나 아예 데스크톱을 하나 구매하는 것도 후보에 올려두었다. 4년째 맥을 사용하면서 처음으로 Windows 없는 게 아쉬워지는 순간이다.

### 이베스트 API 사용하기

 이번 주 과제는 이베스트 Xing API를 사용하여 기본적인 API 동작을 구현하는 것이었다. [Xing API COM 버전 개발 가이드](https://www.ebestsec.co.kr/apiguide/guide.jsp?cno=200)와 [알고리즘 트레이딩 wikidocs](https://wikidocs.net/2871)를 참고하며 동작을 구현했다.

 Xing API의 XASession 을 사용하여 서버에 연결, 로그인 및 계좌 정보 조회 동작을 구현했고, XAQuery를 사용하여 원하는 종목 검색 및 한 달 치 일봉 데이터를 조회했다. 가이드가 잘 되어 있어 단순히 프로그램을 동작시키는 것은 어렵지 않았다.

### 개발하면서 어려웠던 점

프로그램의 각 동작을 개발을 하면서 다음 내용들이 고민이 되고 어려웠다.

- 함수의 기능 및 범위 설정을 어떻게 할 것인가?
    + Login 함수는 단순히 세션 로그인 기능만 할 것인가? 또는 로그인과 동시에 계좌 정보도 저장할 것인가? 이것은 어떤 기준으로 정할 수 있을까?
    + 종목명을 입력했을 때 종목 코드를 반환하는 함수는, 종목에 대한 다른 정보 없이 코드만 반환하는 것으로 충분한가?
- 로그인 정보, 계좌 정보, 주식 정보 등의 데이터는 어떤 컴포넌트가 갖고 있어야 하는가?
    + 증권사 로그인 정보 및 계좌 정보 등은 main 함수가 저장할 것인가? 또는 API class 내부에 저장하는 것으로 충분한가?
    + 종목 정보(이름, 코드 등)는 매번 검색하지 않도록 별도 DB에 저장해두면 편할 것 같다. 만약 관심 있는 종목 개수가 한정적이라면 굳이 DB를 구성하는 것이 맞는 선택일까?
- API는 어떻게 추상화할 수 있는가?
    + 특정 증권사 API, 특정 계좌 정보에 종속되지 않는 코드를 작성하고 싶은 마음은 있었으나, 어떻게 구현해야 할 지 어려웠다.
- 폴더 및 파일 구분은 어떻게 하면 좋을까?

### 다음 시도는?

 이번 주 스터디 진행 후에 몇 차례 코드 수정을 해야 할 것으로 생각한다. 처음부터 완벽한 구성을 할 수는 없겠지만, 코드 수정에 부담이 없는 개발 초기에 최대한 많이 고민하며 깨끗한 구조를 만들어두고 싶다. 예전의 나였으면 프로그램이 원하는 기능을 하는 순간 할 일을 다 했다고 생각했을 텐데, 그래도 이렇게 고민할 기회가 생겨 다행이라는 생각도 든다. 잘해보자.