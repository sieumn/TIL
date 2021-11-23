# 3장. 함수

> Clean Code(Martin, Robert C.) 3장 정리

읽기 쉽고 이해하기 쉬운 함수는 어떻게 만들 수 있을까? 의도를 분명히 표현하는 함수를 어떻게 구현할 수 있을까? 함수에 어떤 속성을 부여해야 처음 읽는 사람이 프로그램 내부를 직관적으로 파악할 수 있을까?

### 작게 만들어라!

- 함수를 만드는 첫 번째 규칙은 '작게', 둘째 규칙은 '더 작게'다!
- 함수는 가능한 짧아야 한다. 하나의 함수는 하나의 이야기를 표현해야 한다.
- if 문, else 문, while 문에 들어가는 블록은 한 줄이어야 한다. 대게는 그 안에서 새로운 함수를 호출한다. 그렇게 하면 함수가 작아질 뿐 아니라, 코드를 이해하기도 쉬워진다.
- 함수에서 들여쓰기 수준은 1단이나 2단을 넘어서면 안 된다. 중첩 구조가 생길만큼 함수가 커져서는 안 된다는 뜻이다.

### 한 가지만 해라!

- 함수는 한 가지를 해야 한다. 그 한 가지를 잘 해야 한다. 그 한 가지만을 해야 한다.
- 지정된 함수 이름 아래에서 추상화 수준이 하나인 단계만 수행한다면 그 함수는 한 가지 작업만 한다.
- 함수 내에서 의미 있는 이름으로 다른 함수를 추출할 수 있다면 그 함수는 여러 작업을 한다고 판단할 수 있다.

### 함수 당 추상화 수준은 하나로!

- 함수가 확실히 '한 가지' 작업만 하려면 함수 내 모든 문장의 추상화 수준이 동일해야 한다.
- 함수 내에 추상화 수준을 섞으면, 특정 표현이 근본 개념인지 아니면 세부사항인지 구분하기 어렵다.
- 내려가기 규칙
  + 코드는 위에서 아래로 이야기처럼 읽혀야 좋다. 한 함수 다음에는 추상화 수준이 한 단계 낮은 함수가 온다. 즉, 위에서 아래로 프로그램을 읽으면 함수 추상화 수준이 한 번에 한 단계씩 낮아진다.

### Switch 문

- switch 문은 작게 만들기 어렵다. 또한 '한 가지' 작업만 하는 switch 문을 만들기도 어렵다. 하지만, 각 switch 문을 저차원 클래스에 숨기고 절대로 반복하지 않는 방법은 있다.
- 다음 함수의 문제를 보자.
    ```C++
    public Money calculatePay(Employee e)
    throw InvalidEmployeeType {
        switch (e.type) {
            case COMMISSIONED:
                return calculateCommisionedPay(e);
            case HOURLY:
                return calculateHourlyPay(e);
            case SALARIED:
                return calculateSalariedPay(e);
            default:
                throw new InvalidEmployeeType(e.type);
        }
    }
    ```
    + 이 함수는 길고, 여러 작업을 수행한다. 또한 SRP와 OCP를 위반한다. 

- 추상 팩토리에 switch 문을 꽁꽁 숨긴다면 문제를 해결할 수 있다. 추상 팩토리는 switch 문을 사용해 적절한 Employee 파생 클래스의 인스턴스를 생성한다.
  
    ```C++
    public abstract class Employee {
        public abstract boolean isPayday();
        public abstract Money calculatePay();
        public abstract void deliverPay(Money pay);
    }

    public interface EmployeeFactory {
        public Employee makeEmployee(EmployeeRecord r) throws InvalidEmployeeType;
    }

    public class EmployeeFactoryImpl implements EmployeeFactory {
        public Employee makeEmployee(EmployeeRecord r) throws InvalidEmplooyeeType {
            switch (r.type) {
                case COMMISSIONED:
                    return new CommissionEmployee(r);
                case HOURLY:
                    return new HourlyEmployee(r);
                case SALARIED:
                    return new SalariedEmployee(r);
                default:
                    throw new InvalidEmployeeType(r.type);
            }
        }
    }

    ```

    + 이와 같이 switch 문은 다형적 객체를 생성하는 코드 안에서 상속 관계로 숨겨야 한다.

### 서술적인 이름을 사용하라!

- "코드를 읽으면서 짐작했던 기능을 각 루틴이 그대로 수행한다면 깨끗한 코드라 불러도 되겠다."
- 길고 서술적인 이름이 짧고 어려운 이름보다, 서술적인 주석보다 좋다.
- 이름은 일관성이 있어야 한다. 문체가 비슷하면 이야기를 순차적으로 풀어가기도 쉬워진다.

### 함수 인수

- 함수에서 이상적인 인수 개수는 0개(무항)이며, 다음은 1개(단항)고, 다음은 2개(이항)다. 3개(삼항)은 가능한 피하는 편이 좋으며, 4개 이상은 사용하면 안 된다.
- 인수는 개념을 이해하기 어렵게 만든다. `includeSetupPageInto(newPageContent)`보다 `includeSetupPage()`가 이해하기 더 쉽다.
  + `includeSetupPageInto(newPageContent)`는 함수 이름과 인수 사이에 추상화 수준이 다르며, 코드를 읽는 사람이 현 시점에서 별로 중요하지 않은 세부사항을 알아야 한다.

- 많이 쓰는 단항 형식
  + 다음 케이스가 아니라면 단항 형식도 가급적 피하라.
  + 인수에 질문을 던지는 경우
  
    `boolean fileExists("MyFile")`

  + 인수로 뭔가를 변환해 결과를 반환하는 경우

    `InputStream fileOpen("MyFile")`

  + 이벤트 함수

    `passwordAtttempFailedNttimes(int attemps)`

    * 입력 인수만 있고 출력 인수는 없다.
    * 프로그램은 함수 호출을 이벤트로 해석해 입력 인수로 시스템 상태를 바꾼다.
    * 이벤트 함수는 이벤트라는 사실이 코드에 명확하게 드러나야 한다.

- 플래그 인수
  + 플래그 인수는 추하다. 함수에 bool 값을 넘기는 관례는 끔찍하다.
  + render(bool isSuite)는 헷갈리기 십상이다. 이 코드는 renderForSuite()와 renderForSingleTest()로 나눠야 마땅하다.

- 이항 함수
  + 직교 좌표계 점은 일반적으로 인수 2개를 취한다. 두 인수는 하나의 값을 표현한다.
  + 자연적인 순서가 없을 경우, 인수의 순서를 인위적으로 기억해야 한다.
  + 이항 함수는 위험을 수반한다는 것을 기억하고 가능하면 단항 함수로 바꾸도록 애써야 한다.

- 삼항 함수
  + 삼항 함수는 신중히 고려해야 한다.
  + 다음 함수는 멈칫하게 만든다. 인수의 순서와 의미를 계속 상기해야 한다.

    `assertEquals(message, expected, actual)`

- 인수 객체
  + 인수가 여러 개 필요하다면 일부를 독자적인 클래스로 선언할 수 있다.
    
    ```C++
    Circle makeCircle(double x, double y, double radius);
    Circle makeCircle(double center, double radius);
    ```

- 동사와 키워드
  + 단항 함수는 함수와 인수가 동사/명사 쌍을 이뤄야 한다.
  + 함수 이름의 키워드를 추가하면 인수 순서를 기억할 필요가 없어진다.
    ```C++
    assertEquals(expectted, actual)
    assertExpectedEqualsActual(expected, actual)
    ```

### 부수 효과를 일으키지 마라!

- 함수에서 한 가지를 하겠다고 약속하고선 남몰래 다른 일을 하는 거짓말을 하지 마라.
- 부수 효과는 시간 결합이나 순서 종속성을 초래한다.
- checkPassword()는 비밀번호만 확인해야 하지, 그 안에서 비밀번호가 틀릴 경우 비밀번호를 초기화하는 행동을 해서는 안 된다.
- 출력 인수는 피해야 한다. 함수에서 상태를 변경해야 한다면 함수가 속한 객체 상태를 변경하는 방식을 택한다.
  + 첫 번째 방식 대신 두 번째 방식을 사용하라.
    ```C++
    appendFooter(report)
    report.appendFootter()
    ```

