# 4장. 주석

> Clean Code(Martin, Robert C.) 4장 정리

우리는 코드로 의도를 표현하지 못해, 그러니까 실패를 만회하기 위해 주석을 사용한다. 주석은 언제나 실패를 의미한다. 그러므로 주석이 필요한 상황에 처하면 곰곰이 생각하기를 바란다. 상황을 역전해 코드로 의도를 표현할 방법은 없을까? 코드만이 정확한 정보를 제공하는 유일한 출처다. 그러므로 우리는 주석을 가능한 줄이도록 꾸준히 노력해야 한다.

### 주석은 나쁜 코드를 보완하지 못한다

- 코드에 주석을 추가하는 일반적인 이유는 코드 품질이 나쁘기 때문이다.
- 표현력이 풍부하고 깔끔하며 주석이 거의 없는 코드가, 복잡하고 어수선하며 주석이 많이 달린 코드보다 훨씬 좋다.

### 코드로 의도를 표현하라!

- 주석으로 달려는 설명을 함수로 만들어 표현할 수 있다. 다음 코드는 나쁜 코드다.

    ```C++
    // 직원에게 복지 혜택을 받을 자격이 있는지 검사한다.
    if ((employee.flags & HOURLY_FLAG) && (employee.age > 65))
    ```

- 위 코드 대신 아래 코드를 사용해라

    ```C++
    if (employee.isEligibleForFullBenefits())
    ```

### 좋은 주석

어떤 주석은 필요하거나 유익하다.

#### 1. 법적인 주석

- 소스 파일 첫 머리에 주석으로 들어가는 저작권 정보와 소유권 정보
        
    ```C++
    // Copyright (C) 2003, 2004, 2005 by Object Mentor, Inc. all rightts reserved.
    ```

#### 2. 정보를 제공하는 주석

- 때로는 기본적인 정보를 주석으로 제공해 주면 편리하다.
- 하지만, 이것도 이왕이면 코드에 담는 것이 좋다.

    ```C++
    // kk:mm:ss EEE, MMM dd, yyyy gudtlrdlek.
    Pattern timeMatcher = Pattern.compile(
        "\\d*:\\d*:\\d* \\w*, \\w* \\d*, \\d*"
    );
    ```

#### 3. 의도를 설명하는 주석

- 주석은 때때로 결정에 깔린 의도까지 설명한다.

#### 4. 의미를 명료하게 밝히는 주석

- 모호한 인수나 반환값은 그 의미를 읽기 좋게 표현하면 이해하기 쉬워진다.
- 인수나 반환값이 표준 라이브러리 등 변경하지 못하는 코드에 속한다면 특히 유용하다.

    ```C++
    assertTrue(a.compareTo(a) == 0);  // a == a
    assertTrue(a.compareTo(b) != 0);  // a != b
    assertTrue(a.compareTo(b) == -1); // a < b
    ```

- 다만 이 경우 그릇된 주석을 달아놓을 위험이 상당히 높다. 이것이 주석이 위험한 이유이기도 하다.

#### 5. 결과를 경고하는 주석

- 때로 다른 프로그래머에게 결과를 경고할 목적으로 주석을 사용한다.

    ```C++
    // 여유 시간이 충분하지 않다면 실행하지 마십시오.
    public void _testWithReallyBigFile(){
        ...
    }
    ```

#### 6. TODO 주석

- '앞으로 할 일'을 //TODO 주석으로 남기면 편하다. TODO 주석은 프로그래머가 필요하다 여기지만 당장 구현하기 어려운 업무를 기술한다.
  
    ```C++
    //TODO
    protected VersionInfo makeVersion() throws Exception{
        return null;
    }
    ```

#### 7. 중요성을 강조하는 주석

- 자칫 대수롭지 않다고 여겨질 뭔가의 중요성을 강조하기 위해서도 주석을 사용한다.

    ```C++
    String listItemContent = match.group(3).trim();
    // 여기서 trim은 정말 중요하다. trim 함수는 문자열에서 시작 공백을 제거한다.
    // 문자열에 시작 공백이 있으면 다른 문자열로 인식되기 때문이다.
    ```

### 나쁜 주석

대다수 주석이 이 범주에 속한다. 

#### 1. 주절거리는 주석

- 특별한 이유 없이 의무감으로 주석을 다는 것은 시간 낭비다.
- 이해가 안 되어 다른 모듈까지 뒤져야 하는 주석은 독자와 소통하지 못하는 주석이다.

#### 2. 같은 이야기를 중복하는 주석

- 주석이 코드 내용을 그대로 중복하는 경우 주석은 코드를 지저분하게 할 뿐이다.
- 아래 주석은 아무 의미가 없다.

    ```C++
    // 이 컴포넌트의 프로세스 지연값
    protected int backgroundProcessorDelaay = -1;

    // 컨테이너와 관련된 Loader 구현
    protected Loader loader = null;
    ```

#### 3. 오해할 여지가 있는 주석

- 주석에 오해할 여지가 있다면, 프로그래머는 함수를 경솔하게 호출할 수 있다.

#### 4. 의무적으로 다는 주석

- 의무적으로 다는 주석은 코드를 복잡하게 만들며, 잘못된 정보를 제공할 여지만 만든다.

#### 5. 이력을 기록하는 주석

- 소스 코드 관리 시스템이 없었을 때에는 모듈 첫 머리에 변경 이력을 기록하고 관리하는 관례가 바람직했다.
- 하지만 이제는 혼란만 가중할 뿐으로, 완전히 제거하라.

#### 6. 있으나 마나 한 주석

- 너무나 당연한 사실을 언급하며 새로운 정보를 제공하지 못하는 주석은 개발자가 주석을 무시하는 습관에 빠지게 한다.

#### 7. 함수나 변수로 표현할 수 있다면 주석을 달지 마라

- 다음 코드를 보자

    ```C++
    // 전역 목록 <smodule>에 속하는 모듈이 우리가 속한 하위 시스템에 의존하는가?
    if (smodule.getDependSubsystems().contains(subSysMod.getSubSystem()))
    ```

- 이 코드에서 주석을 없애고 다시 표현하면 다음과 같이 작성할 수 있다.

    ```C++
    ArrayList moduleDependees = smodule.getDependSubsystems();
    String ourSubSystem = subSysMod.getSubSystem();
    if (moduleDependees.contains(ourSubSystem))
    ```

#### 8. 위치를 표현하는 주석

- 너무 자주 사용하지 않는다면 배너는 눈에 띄며 주의를 환기한다.

    ```C++
    // Actions /////////////////////////////
    ```

- 다만 일반적으로 배너는 가독성만 낮추므로 제거해야 마땅하다.

#### 9. 닫는 괄호에 다는 주석

- 닫는 괄호에 주석을 다는 대신 함수를 줄이려 시도하자.

#### 10. 공로를 돌리거나 저자를 표시하는 주석

- 이런 정보는 소스 코드 관리 시스템에 저장해라.

    ```C++
    /* 릭이 추가함 */
    ```

#### 11. 주석으로 처리한 코드

- 주석으로 처리한 코드만큼 밉상인 관행도 드물다. 어차피 소스 코드 관리 시스템이 코드를 기억해준다. 그냥 코드를 삭제하라.

    ```C++
    this.bytePos = writeBytes(pngIdBytes, 0);
    //hdrPos = bytePos;
    writeHeader();
    writeResolution();
    //dataPos = bytePos;
    ```

#### 12. HTML 주석

- 소스 코드에서 HTML 주석은 혐오 그 자체다. HTML 주석은 편집기에서조차 읽기 어렵다.

    ```C++
    /*
    * <p/>
    * &lt; taskdef claasspathref=&quot;
    * </p>
    */ 
    ```

#### 13. 전역 정보

- 주석을 달아야 한다면 근처에 있는 코드만 기술하라. 코드 일부에 주석을 달면서 시스템의 전반적인 정보를 기술하지 마라.

#### 14. 너무 많은 정보

- 주석에다 흥미로운 역사나 관련 없는 정보를 장황하게 늘어놓지 마라.

#### 15. 모호한 관계

- 주석과 주석이 설명하는 코드는 둘 사이 관계가 명백해야 한다.
- 주석 자체가 다시 설명을 요구하는 것은 안타깝기 그지없다.

#### 16. 함수 헤더

- 짧은 함수는 긴 설명이 필요 없다.
- 짧고 한 가지만 수행하며 이름을 잘 붙인 함수가 주석으로 헤더를 추가한 함수보다 훨씬 좋다.
