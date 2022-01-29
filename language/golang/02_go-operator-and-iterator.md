# #2 Go 연산자, 조건문, 반복문

## 연산자

#### 산술 연산자

- 산술 연산자는 사칙연산자(+, -, *, /, %)와 증감연산자(++, --)를 사용한다.

  ```go
  c = (a + b) / 2 * 5
  i++
  ```

#### 관계 연산자

- 관계 연산자는 서로의 크기를 비교하거나 동일함을 체크할 때 사용한다.

  ```go
  a == b
  a > b
  a != b
  ```

#### 논리 연산자

- 논리 연산자는 AND, OR, NOT 을 표현하는 데 사용한다.

  ```go
  A && B
  !A || B
  ```

#### Bitwise 연산자

- Bitwise 연산자는 비트 단위의 연산을 위해 사용한다.

  ```go
  c = a << 5
  ```

#### 할당 연산자

- 할당 연산자는 값을 할당하는 = 연산자 외에 사칙연산, 비트연산 등을 축약한 +=, &=, <<= 같은 연산자들이 있다.

  ```dart
  a = 1
  a += 2
  a <<= 3
  a /= 4
  ```

#### 포인터 연산자

- 포인터 연산자는 & 또는 *를 사용하여 해당 변수의 주소를 알아내거나 참조할 때 사용한다.
- Go는 포인터 연산자를 제공하지만, 포인터에 더하고 빼는 기능은 제공하지 않는다.

```dart
var k int = 10
var p  = &k     // k의 주소를 할당
println(*p)     // p가 가리키는 주소의 실제 내용 출력
```

## 조건문

### if문

- Go에서 if 조건문은 괄호로 둘러싸지 않아도 된다.
- 다만, 반드시 조건의 시작 괄호 { 를 if문과 같은 라인에 두어야 한다는 것을 주의해야 한다.
- if 조건문은 반뜨시 Boolean으로 표현되어야 한다. 다른 언어처럼 조건식에 0, 1 등의 숫자를 사용할 수는 없다.

  ```go
  if v == 1 {
    ...
  } else if v == 2 {
    ...
  } else {
    ...
  }
  ```

- if문에서 조건식을 사용할 때 optional statement를 함께 실행할 수 있다.

  ```go
  if val := i + 1; val < max {
    ...
  }
  ```

  + 이때 정의된 변수 val은 if문 블럭 안에서만 사용할 수 있다.

### Switch문

- 여러 값을 비교할 경우 switch문을 사용한다. 
- Go에서는 break를 사용하지 않아도 다음 case로 자동으로 넘어가지 않는다.
  + 만약 C언어처럼  계속 다음 case 블럭을 실행하게 만들려면 `fallthrough`를 넣어주면 된다.  

  ```go
  switch number {
    case 1:
      ...
    case 2:
      ...
    case 3, 4:
      ...
      fallthrough
    default:
      ...
  }
  ```

- Go에서는 변수의 값뿐 아니라 타입에 따라서도 case로 분기할 수 있다.

  ```go
  switch data.(type) {
  case int:
    ...
  case bool:
    ...
  case string:
    ...
  default:
    ...
  }
  ```

- Go에서는 switch 뒤에 조건을 적지 않는 것도 가능하다. 대신 case 조건문을 검사하여 조건에 맞는case 블럭을 실행하고 switch문을 빠져나온다.

  ```go
  func grade(score int) {
    switch {
    case score >= 90:
      println("A")
    case score >= 80:
      println("B")
    case score >= 70:
      println("C")
    case score >= 60:
      println("D")
    default:
      println("F")
    }
  }
  ```

## 반복문

### for문

- Go 언어에서 반복문은 for문만 사용할 수 있다. for문에서도 조건에 괄호는 사용하지 않는다.

  ```go
  sum := 0
  for i:= 1; i <= 5; i++ {
    sum += i
  }
  ```

- Go언에서 for문은 초기값과 증감식을 제외하고 가운데 조건식만을 사용하여 표현할 수 있다. 이 경우 for문은 while문처럼 동작한다.

  ```go
  n := 1
  for n < 500 {
    n *= 3
  }
  ```

- 조건식까지 생략하면 for문으로 무한 루프를 구현할 수 있다.

  ```go
  for {
    println("Infinite Loop")
  }
  ```

- for range 구문은 데이터구조 내의 요소들을 차례로 순회하는 문법이다. range를 배열에서 사용하면 각 원소의 index와 값을 반환한다.

  ```go
  nums := []int{1, 2, 3, 4, 5}

  for _, num := range nums {
    print(num)
  }

  for index, num := range nums {
    if num == 4 {
      println(index, num)
    }
  }
  ```

## Reference

- [예제로 배우는 Go 프로그래밍 - Go 연산자](http://golang.site/go/article/6-Go-연산자)
- [예제로 배우는 Go 프로그래밍 - Go 조건문](http://golang.site/go/article/7-Go-조건문)
- [예제로 배우는 Go 프로그래밍 - Go 반복문](http://golang.site/go/article/8-Go-반복문)
