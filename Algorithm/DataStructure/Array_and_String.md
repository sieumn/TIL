# Array and String

## 이 페이지를 읽으면 알 수 있는 것

- 배열, 동적 배열, 문자열의 개념과 그 차이점은 무엇인가?
- 배열, 동적 배열, 문자열을 초기화하는 방법에는 무엇이 있는가?
- 동적 메모리 할당이란 무엇인가?
- 동적 배열 및 문자열의 기본 함수에는 어떤 것들이 있는가?

## 배열 (Array)

배열이란 같은 타입의 변수들을 하나의 묶음으로 만든 것이다.

### 배열의 생성

자료형 배열이름[배열크기] 의 형태로 배열을 선언하여 생성한다.

```C++
int a[5]; // 크기가 5인 int형 배열 생성
int a[2][3]; // 2행 3열의 int형 2차원 배열 생성
```

배열이 선언되면 각 배열의 요소들은 메모리 상에 연속된 주소로 저장된다. 다차원 배열의 경우 뒤에 있는 대괄호를 우선으로 메모리에 배치된다. 즉, a[0][0], a[0][1], a[0][2], a[1][0], a[1][1] .. 순서로 메모리에 저장된다는 것이다.

### 배열 초기화

위의 예제처럼 배열을 선언만 했을 경우에는, 각 배열의 주소에는 임의의 쓰레기 값이 들어있다. 배열을 특정 값으로 채우고 싶을 경우 다음 방법으로 배열을 초기화할 수 있다.

참고로, 배열의 이름은 해당 배열이 할당된 메모리의 시작 주소를 의미한다. 즉, 1차원 배열 arr는 &arr[0]와 같은 의미이다. 다른 원소의 주소에 순차적으로 접근하고 싶은 경우, arr+'offset'으로 표현할 수 있다. 예를 들면, arr[2]의 주소 값은 arr+2로 표현할 수 있다.

- 선언 시 초기화

    배열을 다 채우지 않고 0으로 끝내면, 이후 원소들은 자동으로 모두 0으로 초기화된다. 참고로, 자동 초기화는 0으로만 가능하다.

    ```C++
    int arr1[5] = {1, 2, 3, 4, 5}; //배열의 생성과 초기화
    int arr2[5] = {0, }; // 전체 원소를 0으로 초기화
    int arr3[5] = {1, 2, 0}; // {1, 2, 0 , 0, 0}으로 초기화

    int arr[2][3] = {1, 2, 3, 4, 5, 6}; // 2차원 배열 초기화도 동일
    ```

- fill_n(void* start, int num, int value);
    - void* start: 변경하려는 배열의 시작 주소
    - int num: 변경하려는 원소의 갯수
    - int value: 변경 값

    ```C++
    int arr[10];

    //첫 번째 원소부터 10개의 원소를 -1로 지정
    fill_n(arr, 10, -1);

    //두 번째 원소부터 5개의 원소를 2로 지정
    fill_n(arr+1, 5, 2);
    ```

- fill(void* start, void* end, int value);
    - void* start: 변경하려는 배열의 시작 주소
    - void* end: 변경하려는 배열의 종료 주소
    - value: 변경 값

    ```C++
    int arr[10];
    int arr2[5][3];

    //첫 번째 원소부터 10개의 원소를 -1로 초기화
    fill(arr, arr+10, -1);

    //두 번째 원소부터 5개의 원소를 2로 초기화
    fill(arr+1, arr+6, 2);

    //2차원 배열 전체를 5로 초기화
    fill(&arr2[0][0], &arr2[4][2], 5);
    ```

- memset(void* start, int value, size_t num);
    - void* start: 변경하려는 배열의 시작 주소
    - int value: 변경 값 **(0과 -1으로만 초기화 가능)**
    - size_t num: 변경하려는 배열의 크기. sizeof(데이터타입)으로 표현.

    ```C++
    int arr[10];
    int arr2[5][3];

    //첫 번째 원소부터 10개의 원소를 -1로 지정
    memset(arr, -1, sizeof(arr));

    //두 번째 원소부터 5개의 원소를 0로 지정
    memset(arr+1, 0, 5*sizeof(int));

    //2차원 배열 전체를 0으로 초기화
    memset(arr2, 0, sizeof(arr2));
    ```

### 접근

arr[0], arr[2] 등 원하는 index를 대괄호 안에 넣어 원소에 접근할 수 있다.

### 동적 메모리 할당

지금까지 예시로 살펴본 배열은 고정 배열이다. 고정 배열은 컴파일할 때 크기가 지정되기 때문에, 실행하는 동안 크기를 늘리거나 줄일 수 없다. 컴파일 이후에 배열의 크기를 결정하기 위해 동적 메모리 할당이라는 개념을 사용할 수 있다.

동적 메모리 할당이란, 실행 시간에 정적으로 변수의 크기를 정해서 메모리를 할당한다. 주로 malloc 함수를 이용해서 heap 영역의 메모리를 할당받은 후, free 명령어로 메모리를 해제해 준다.

```C++
// 배열의 크기가 5인 동적 메모리 할당
int* arr = (int*)malloc(sizeof(int) * 5);
cout << _msize(a); // 20
free(a);
cout << _msize(a); // error
```

sizeof로 a의 크기를 측정하려 하면 int* 형인 주소의 크기가 나오기 때문에, 실제 heap에서 사용한 메모리 크기를 측정하려면 _msize를 이용한다.

## 동적 배열 (Vector)

C++에서는 별도 라이브러리를 포함하면 쉽게 길이를 조절할 수 있는 동적 배열인 vector를 사용할 수 있다. vector는 길이를 조절할 수 있는 것을 제외하면 배열과 거의 유사한 개념을 갖고 있다.

vector는 실행 시간 중 요소를 추가할 수 있고, 배열 사이즈가 늘어나면 새로운 배열을 할당한 후 모든 요소를 이동시키는 방법으로 배열을 확장한다. 요소 이동으로 인해 발생하는 오버헤드를 최소화하기 위해 배열 할당 시 여유 공간을 둔다.

### vector의 생성

vector를 사용하기 위해서는 vector 라이브러리를 반드시 포함해야 한다.

```C++
#include<vector>

//기본 선언 후에는 크기도 값도 없는 빈 공간이다.
vector<int> vec;

//크기 3인 벡터 생성. 값은 기본 0으로 초기화
vector<int> vec(3);

//2차원 vector 선언
vector< vector<int>> vec2;

//3x2의 2차원 vector 생성. 값은 기본 0으로 초기화
vector<vector<int>> vec2(3, vector<int>(2));
```

### vector 초기화

- 선언 시 초기화

    ```C++
    #include<vector>

    //크기 3인 백터 생성. 값은 기본 0으로 초기화
    vector<int> vec(3);

    //크기 3, 값 1로 초기화
    vector<int> vec = {1, 1, 1};
    vector<int> vec(3, 1);

    //3x2 크기의 벡터를 -1로 초기화
    vector<vector<int>> vec2(3, vector<int>(2,-1));
    ```

- fill(void* start, void* end, int value);
    - void* start: 변경하려는 배열의 시작 주소
    - void* end: 변경하려는 배열의 종료 주소
    - value: 변경 값

    ```C++
    #include<vector>
    vector<int> vec(10);
    vector<vector<int>> vec2(3, vector<int>(2));

    //vec 값을 -1로 초기화
    fill(vec.begin(), vec.end(), -1);

    //3x2 크기의 벡터를 -1로 초기화
    fill(vec2.begin(), vec2.end(), vector<int>(3, -1));    
    ```

- vector.assign(int size, int value)

    ```C++
    #include<vector>
    vector<int> vec;

    //크기 3, 값 1로 초기화
    vec.assign(3, -1);
    ```

- 배열을 사용해서 초기화
    - 배열의 첫 번째 주소와 마지막 주소를 전달함으로써 배열과 동일하게 vector를 초기화해줄 수 있다.
    - 만약 배열의 크기를 모른다면 sizeof(arr)/sizeof(int) 와 같은 방법으로 배열의 크기를 넘겨줄 수 있다.

    ```C++
    int arr[3];
    memset(arr, -1, sizeof(arr));
    vector<int> vec(arr, arr + 3);
    ```

- vector를 사용해서 초기화
  - 다음과 같이 기존 vector를 사용하여 초기화할 수 있다.
  
    ```C++
    vector<int> vec1(3, -1);
    vector<int> vec2(vec1);
    ```

### vector 기본 사용

vector 라이브러리의 내장 함수를 사용하여 배열의 크기를 쉽게 조절할 수 있다. 동적 배열 개념과 관련된 기본 함수들을 몇 가지 알아보자.

- push_back(value): 배열의 끝에 원소 추가
- pop_back(): 배열의 가장 끝 원소 제거

    ```C++
    vector<int> vec;
    vec.push_back(1); //vec: {1}
    vec.push_back(2); //vec: {1, 2}
    vec.push_back(3); //vec: {1, 2, 3}
    vec.pop_back(); //vec: {1, 2}
    vec.pop_back(); //vec: {1}
    ```

- insert(index, value): 해당 index에 원소 추가
- insert(index, iter, value): 해당 index에 iter개의 value값 추가
- erase(index): 해당 index에 있는 원소 제거

    ```C++
    vector<int> vec = {1, 2, 3};

    vec.insert(0, 4); //vec: {4, 1, 2, 3}
    vec.insert(2, 5); //vec: {4, 1, 5, 2, 3}
    vec.erase(1); //vec: {4, 5, 2, 3}
    vec.erase(0); //vec: {5, 2, 3}
    vec.insert(1, 3, 7) //vec: {5, 7, 7, 7, 2, 3}
    ```

- resize(size, value): 배열의 크기를 size로 조절하고, 만약 배열이 늘어날 경우 value값으로 채운다.

    ```C++
    vector<int> vec = {1, 2, 3};

    vec.resize(5, -1); // {1, 2, 3, -1, -1}
    vec.resize(2); // {1, 2}
    ```

## 문자열 (String)

배열 중에서도 char 데이터 타입의 배열을 문자열(string)이라고 한다.

### String 선언 및 초기화

char형 배열을 선언함으로써 다음과 같이 문자열을 선언 및 초기화할 수 있다.

```C++
char str1[100];
char str2[] = "hello";
char *str3 = "world";
```

배열과 마찬가지로, 각 str1, str2, str3 변수명은 배열의 시작 주소를 담고 있다. 따라서 우리는 대괄호 또는 포인터를 사용하여 각 문자열 값에 접근할 수 있다.

### String 주의 사항

"hello"라는 문자열을 저장하기 위해 우리는 크기가 몇인 문자열을 선언해야 할까? "hello"의 원소가 5개이기 때문에 크기가 5인 문자열을 선언해야 한다고 생각할 수 있지만, 정답은 6 이상의 배열이 필요하다. 문자열에서는 가장 마지막 입력 값 다음 자리에 NULL(\0) 값이 자동으로 지정되기 때문에, 늘 NULL 공간을 고려하여 문자열 크기를 지정해야 함을 주의하자. 

### String 라이브러리

C++에서는 string 라이브러리를 사용하여 string 데이터 타입을 쉽게 사용할 수 있다.

```C++
#include<string>
string str;

string str1 = "hello";
string str2("world");
string str3(str1);
string str4(10, 'a') //aaaaaaaaaa
```

### String 기본 함수

- strlen(str): str 문자의 길이 반환 (NULL값 제외)
- strcpy(str1, str2): str1에 str2 값을 복사
- strcmp(str1, str2): str1과 str2 값을 비교
  - 사전순으로 str1이 str2보다 앞설 때: -1 반환
  - 사전순으로 str2이 str1보다 앞설 때: 1 반환
  - str1과 str2가 동일할 때: 0 반환
- strcat(str1, str2): str1에 str2 값을 이어붙여 저장

```C++
#include<string>
char[] str = "hello"
char[10] str2;

int len = strlen(str) //len = 5
strcpy(str2, str) //str2에 "hello" 저장
int diff = strcmp(str1, str2) //diff = 0
strcpy(str, str2) //str에 "hellohello" 저장
```
