# [Go] 변수와 상수

## Go 데이터 타입

Go 프로그래밍 언어는 다음과 같은 기본 데이터 타입을 갖는다.

- bool 타입
  + `bool`
- 문자열 타입
  + `string`
  + string은 한 번 생성되면 수정될 수 없는 immutable 타입이다.
- 정수형 타입
  + `int`, `int8`, `int16`, `int32`, `int64`, `uintptr`
  + `uint`, `uint8`, `uint16`, `uint32`, `uint64`, `uintptr`
- Float 및 복소수 타입
  + `float32`, `float64`, `complex64`, `complex128`
- 기타
  + `byte`: uint8과 동일하며 byte 코드에 사용
  + `rune`: int32와 동일하며 유니코드 코드 포인트에 사용

## 문자열

문자열은 `` 또는 ""를 사용하여 표현할 수 있다.

- ``으로 정의한 문자열은 Raw String Literal이라고 불리는데, 이 안에 있는 문자열은 별도로 해석되지 않고 raw string 그대로의 값을 갖는다. 예르 들어, 문자열 안에 \n이 있더라도 줄 바꿈으로 해석되지 않고 \n 라는 문자로 해석된다. 또한, 여러 줄로 문자열을 표현할 때도 자주 사용된다.
- ""으로 정의한 문자열은 Interpreted String Literal이라고 부르는데, 이는 여러 줄에 걸쳐 쓸 수 없으며 문자열 내의 escape 문자열은 특별한 의미로 해석된다. 문자열 안에 \n이 있을 경우 이는 줄바꿈으로 해석되는 것이다. 만약 "" 문자열을 여러 줄로 표현하고 싶은 경우, + 문자열을 이용하여 결합할 수 있다.

```go
func main() {
    rawLiteral := `Hello \n
    World \n
    Good`

    interLiteral := "Hello\nWorld"
    interLiteral := "Hello\n"
                    + "World"

    print(rawLiteral)
    print(interLiteral)

    /* output */
    Hello \n
    World \n
    Good

    Hello
    World
}
```

## 데이터 타입 변환

데이터 타입은 type conversion으로 부르는데, new_type(value)의 형식으로 타입을 변경할 수 있다. go에서는 타입관 변환이 자동으로 일어나지 않으므로, 타입 변환이 필요할 경우 반드시 명시적으로 지정해 주어야 한다.

```go
func main() {
    var i int = 100
    var u uint = uint(i)
    var f float32 = float32(i)

    str := "ABC"
    bytes := []byte(str)
    str2 := string(bytes)
}
```

## 변수

Go 에서 변수는 var을 사용하여 선언한다. var 키워드 뒤에 변수명을 적고, 그 뒤에 변수 타입을 적는다. 변수를 선언할 때 초기 값을 지정할 수도 있으며, 선언된 변수는 그 뒤의 문장에서 값을 재할당할 수도 있다.

```go
var a int
var f float32 = 10.3

a = 5
f = 6.5
```

변수를 선언하면서 초기값을 지정하지 않으면, Go는 Zero Value를 기본적으로 할당한다. 숫자형에는 0, bool 타입에는 false, string 타입에는 ""을 할당한다.

동일한 타입의 변수를 여러개 지정할 경우, 변수를 나열하고 마지막에 한 번만 타입을 지정할 수 있다.

```go
var i, j, k int
var i, j, k int = 1, 2, 3
```

선언할 때 초기값을 지정하는 경우, 변수 타입을 적지 않더라도 go는 할당되는 값을 보고 그 타입을 추론한다.

```go

var i = 1
var s = "Hi"
```

변수를 선언하는 또 다른 방식으로 Short Assignment Statement (:=)를 사용할 수 있다. `var i = 1` 대신 `i := 1`을 사용할 수 있는 것이다. 다만, 이 표현은 함수 내에서만 사용할 수 있으며, 함수 밖에서는 var을 사용해야 한다.

## 상수

Go에서는 const 키워드를 사용하여 상수를 선언한다. const 키워드 뒤에 상수명을 적고, 그 뒤에 상수 타입과 값을 차례로 적는다. 변수와 마찬가지로 선언 시 할당되는 값을 보고 자동으로 타입을 추론할 수도 있다.

```go
const c int = 10
const c = 10

const s string = "Hi"
const s = "Hi"
```

여러 개의 상수를 묶어서 지정할 수도 있는데, 이 경우 괄호를 사용하여 상수를 나열한다.

```go
const (
    a = "Apple"
    b = "Banana"
    c = "Carrot"
)
```

iota라는 identifier를 사용하면 상수값을 0부터 순차적으로 부여할 수 있다. 이 경우 iota가 지정된 첫 번째 값에는 0이 할당되고, 나머지 값에는 차례로 1씩 증가된 값이 할당된다.

```go
const (
    one = iota // 0
    two        // 1
    three      // 2
)
```

참고로 Go에서는 다음과 같이 25개의 키워드를 예약하여 사용하고 있다. 따라서 다음 25개의 키워드는 변수/상수/함수명으로 사용할 수 없다.

```go
break / case / chan / const / continue /
default / defer / else / fallthrough / for /
func / go / goto / if / import /
interface / map / package / range / return /
select / struct / switch / type / var
```

## Reference

- [예제로 배우는 Go 프로그래밍 - Go 변수와 상수](http://golang.site/go/article/4-Go-변수와-상수)
- [예제로 배우는 Go 프로그래밍 - Go 데이타 타입](http://golang.site/go/article/5-Go-데이타-타입)
