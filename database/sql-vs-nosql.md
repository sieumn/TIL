# SQL vs NoSQL

## SQL(Structed Query Language)
+ RDBMS(관계형 데이터베이스 관리 시스템)의 데이터를 관리하기 위해 설계된 프로그래밍 언어다.
+ SQL을 사용하는 DB는 MySQL, PostgreSQL 등이 있다.
+ SQL을 사용하는 DB들은 데이터 저장 구조를 엄격하게 관리하기 때문에 스키마에 맞지 않는 형식의 데이터는 저장할 수 없다. 예를 들어, 일부 칼럼이 빈 경우 해당 데이터는 DB에 저장할 수 없다.
+ 관계 지정이 쉽다. SQL은 각 테이블 간의 관계 지정을 통해 테이블을 접근할 수 있고, 따라서 중복 없이 해당 데이터만을 다룰 수 있다.
+ 일반적으로 수직적 확장을 제공한다.

## NoSQL
+ SQL보다 덜 제한적인 모델을 이용해 데이터의 저장 및 검색 메커니즘을 제공한다.
+ NoSQL을 사용하는 DB에는 mongoDB, redis 등이 있다.
+ NoSQL은 데이터의 구조가 같을 필요가 없다. 
+ 관계 지정 대신 각 테이블이 필요한 모든 정보를 갖고 있다. 이런 방식은 중복 데이터를 만든다.
+ 일반적으로 수평적 확장을 제공한다.


## Reference

- [SQL vs NoSQL (MySQL vs MongoDB)](https://parkadd.tistory.com/41)
- [[DB] SQL vs NoSQL(mySQL vs MongoDB) 비교, 차이점](https://mjmjmj98.tistory.com/43)
  
