# Python Code Style

## Python Code Style Guide

Python Code Style은 흔히 PEP8 또는 Google 가이드를 따른다. 본 게시물은 PEP8 가이드를 기준으로 정리할 예정이다.

- [PEP8 Code Style Guide](https://www.python.org/dev/peps/pep-0008/)
- [Google Code Style Guide](https://google.github.io/styleguide/pyguide.html)

## Python Naming Convention

### 모듈, 패키지

- 모듈명은 가능한 짧은 소문자로 이름 짓는다.
- 모듈명은 가독성을 위해 밑줄문자(_)를 사용한다.
- 패키지명은 밑줄문자를 사용하지 않는다.

### 클래스

- UpperCamelCase 형식으로 이름 짓는다.
- 밑줄을 사용하지 않는다.
- exception은 "Error"로 끝내는것을 권장한다.

### 변수, 함수, 메서드

- 소문자가 원칙이며 가독성을 위해 밑줄 사용을 권장한다.
- 보호 속성일 때 맨앞에 '_'를 붙여준다.
- 키워드와 동일 변수일 때는 맨뒤에 '_'를 추가 한다.
- 비공개 속성일 때는 맨앞에 '__' 더블언더를 추가한다.
- 스폐셜 속성일 때는 앞과 뒤에 '__' 더블언더를 추가한다.
- 인스턴스 메서드는 자신을 가리킬 때 self를 사용한다.
- 클래스 메서드는 자신을 가리킬 때 cls를 사용한다.

### 상수

- 모듈에서 정의되는 상수는 대문자로 작성 한다.
- 단어마다 밑줄로 연결하는 ALL_CAPS 포맷으로 명명한다.
