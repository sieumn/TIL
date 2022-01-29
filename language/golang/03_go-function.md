# #3 Go 함수

## 함수

- Go에서 함수는 func 키워드를 사용하여 정의한다.
- func 뒤에 함수 명을 적고, ()에 전달할 parameter를 적으며, () 뒤에 리턴 타입을 적는다.

   ```go
  func test(msg string) int {
    println(msg)
    return 0
  }
  ```

### Pass by Value/Reference

- Go에서 parameter를 전달하는 방식은 크게 Pass by Value와 Pass by Reference가 있다.

#### Pass by Value

- parameter 값을 복사하여 함수에 전달하는 방식이다.
- parameter 값이 함수 내에서 변경되더라도 호출 함수의 변수 값에는 영향이 없다.

#### Pass by Reference

- parameter 를 전달할 때 앞에 &를 붙이면 변수의 주소를 전달하게 된다.
- 이 경우 함수 내에서 값이 변경될 경우 호출 함수의 변숟도 함께 변경된다.

  ```go  
  func main() {
    val := 3
    add(&val)
    println(val)   // 5
  }

  func add(val *int) {
    *val += 2
  }
  ```

### 가변 인자 함수

- 함수에 고정된 수의 인자가 아닌, 다양한 수의 인자를 전달하고자 할 때 가변 인자를 나타내는 `...`를 사용한다.
- 예를 들어, ...string과 같이 인자를 표현하면, N개의 string 타입 인자를 전달할 수 있음을 의미한다.

  ```go
  package main
  
  func main() {
    println(sum(1, 2, 3, 4))
    println(sum(1, 2))
  }

  func sum(num ...int) int {
    sum := 0
    for _, n := range num {
      sum += n
    }
    return sum
  }
  ```


### 함수 return

- Go에서 복수 개의 값을 리턴하기 위해서는 해당 리턴 타입들을 괄호 안에 적어준다.

  ```go
  func main() {
    count, total := sum(1, 2, 3)
  }

  func sum(nums ...int) (int, int) {
    sum := 0
    count := 0

    for _, n := range nums {
      sum += n
      count++
    }

    return count, sum
  }
  ```

- Go에서 Named Return Parameter를 사용하여 리턴값에 이름을 붙일 수 있다. 리턴하는 값이 여러 개일 경우 코드 가독성을 높일 수 있다.

  ```go
  func main() {
    count, total := sum(1, 2, 3)
  }

  func sum(nums ...int) (count int, sum int) {
    sum := 0
    count := 0

    for _, n := range nums {
      sum += n
      count++
    }
    return
  }
  ```

## 익명함수

### 익명함수 (Anonymous Function)

- 함수명을 갖지 않는 함수를 익명 함수라고 부른다. 일반적으로 익명 함수는 그 함수 전체를 변수에 할당하거나, 다른 함수의 인자로 직접 정의되며 사용된다.

```go
func main() {
    sum := func(n ...int) int {
        sum := 0
        for _, i := range n {
            sum += i
        }
        return sum
    }
    result := sum(1, 2, 3)
}
```

### 일급 함수

- Go에서 함수는 일급 함수로서 기본 데이터 타입과 동일하게 취급된다. 따라서 다른 함수의 인자나 리턴으로도 사용될 수 있다.
- 함수를 다른 함수의 인자로 전달하기 위해서는 익명함수를 변수에 할당하거나, 인자에 직접 정의하는 방법이 있다.

```go
func main() {
  add := func(i int, j int) int {
      return i + j
  }
  a := calculate(add, 1, 2)
  b := calculate(func(x int, y int) int { return x + y }, 1, 2)
}
 
func calculate(f func(int, int) int, a int, b int) int {
    result := f(a, b)
    return result
}
```

### Type문을 사용한 함수 원형 정의

- Type문은 struct, 인터페이스 등 user defined type을 정의하기 위해 사용되는데, 함수 원형을 정의하기 위해서도 사용된다.
- 이렇게 함수의 원형을 정의하고 함수를 다른 메서드에 전달하는 것을 흔히 delegate라고 표현한다.

```go
type calculator func(int, int) int

func calc(f calculator, a int, b int) int {
  result := f(a, b)
  return result
}
```

## 클로저 (Closure)

- Closure란 함수 바깥의 변수를 참조하는 함수 값이다. 함수는 바깥의 변수를 함수 안에 있는 것처럼 참조할 수 있다.
- Clousure을 사용할 경우 함수가 소멸되더라도 함수 내 지역 변수를 계속 참조할 수 있다는 장점이 있다.

```go
package main
 
func nextInt() func() int {
    i := 0
    return func() int {
        i++
        return i
    }
}
 
func main() {
    next := nextInt()
 
    println(nextInt())  // 1
    println(nextInt())  // 2
    println(nextInt())  // 3
 
    nextInt2 := nextInt()
    println(nextInt2()) // 1 다시 시작
    println(nextInt2()) // 2
}
```

- 위 예제에서 nextValue()는 익명함수를 리턴하는데, nextValue가 참조하는 변수 i는 함수 밖에 있는 변수다. 익명함수가 i를 로컬 변수로 갖는 것이 아니므로, 외부 변수 i가 유지하는 그 값을 증가하는 기능을 하게 된다.
- nextValue()를 한 번 next라는 변수에 할당하면, next는 내부 변수 i를 가진 것처럼 i 값을 계속 1씩 증가시킨다. 하지만, anotherNext에 새로운 closure 함수 값을 생성한다면 i 값은 다시 초기 0 값으로 돌아간다.

## Reference

- [예제로 배우는 Go 프로그래밍 - Go 함수](http://golang.site/go/article/9-Go-함수)
- [예제로 배우는 Go 프로그래밍 - Go 익명함수](http://golang.site/go/article/10-Go-익명함수)
- [예제로 배우는 Go 프로그래밍 - Go 클로저](http://golang.site/go/article/11-Go-클로저)
