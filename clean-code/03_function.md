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
  