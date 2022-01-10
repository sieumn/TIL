# Python SQLite3 모듈 사용하기

sqlite3 모듈은 파이썬 표준 라이브러리로, SQLite에 대한 인터페이스를 제공한다. 다음과 같이 sqlite3를 import 하면 데이터베이스를 쉽게 이용할 수 있다.

```python
import sqlite3
```

### 데이터베이스 생성

데이터베이스 생성은 sqlite3 모듈의 connect 함수를 사용한다. connect 함수의 인자에 생성할 데이터베이스의 경로 및 이름을 지정하면, Connection 객체가 생성된다.

```python
db = sqlite3.connect('C:\Users\kospi.db')
type(db)    # output: sqlite3.Connection
```

### 데이터베이스에 데이터 삽입

생성된 데이터베이스에 데이터를 넣을 때는 SQL 구문을 사용한다. SQL 구문을 호출하기 위해서는 Cursor 객체가 필요하며, 다음과 같이 이미 생성한 connection 객체를 사용하여 Cursor 객체를 생성할 수 있다.

```python
cursor = db.cursor()
```

이제 데이터를 저장해보자. 데이터를 넣기 전에 먼저 테이블을 생성해야 한다. 테이블을 생성할 때는 각 칼럼에 어떤 데이터가 저장되는지에 대해 함께 기술한다. SQL 구문에서 테이블을 생성하는 방법은 다음과 같다.

```SQL
CREATE TABLE kakao(Date text, Open int, High int, Low int, Closing int, Volume int)
```

SQL 구문을 python 으로 DB에 적용하는 방법은 다음과 같다.

```python
cursor.execute("CREATE TABLE kakao(Date text, Open int, High int, Low int, Closing int, Volume int)")
```

이제 테이블에 데이터를 넣어보자. 마찬가지로 SQL 구문을 만들고 해당 구문을 cursor.execute 메서드를 사용하여 호출하면 된다.

```SQL
INSERT INTO kakao VALUES("16.06.03", 97000, 98600, 96900, 98000, 321405)
```

```python
cursor.execute("INSERT INTO kakao VALUES('16.06.03', 97000, 98600, 96900, 98000, 321405)")
```

작업한 내용을 실제로 데이터베이스에 반영하기 위해서는 commit 메서드를 호출해야 한다. 마지막으로 close 메서드를 통해 데이터베이스 연결을 닫는다.

```python
db.commit()
db.close()
```

### 데이터베이스에서 데이터 읽기

데이터베이스에서 데이터를 읽기 위해서는 먼저 테이블을 선택하는 SQL  구문을 실행해야 한다. 해당 SQL 구문을 cursor.execute 메서드를 사용하여 호출하자.

```SQL
SELECT * FROM kakao
```

```python
cursor.execute("SEELECT * FROM kakao")
```

선택한 테이블로부터 row 단위로 데이터를 읽으려면 fetchone 메서드를 호출한다. fetchone은 첫 번째 row부터 차례로 데이터를 tuple 형으로 반환하고, 모든 row가 반환된 후에는 아무런 값도 반환되지 않는다. 만약 row를 처음부터 다시 읽고 싶다면 tabale을 한번 더 선택하면 된다.

```python
cursor.fetchone()
# output: ('16.06.03', 97000, 98600, 96900, 98000, 321405)
```

만약 row 단위가 아니라 한 번에 모든 row를 읽고 싶담면, fetchall 메서드를 사용한다.

```python
kakao = cursor.fetchall()
print(kakao[0][0])   # '16.06.03'
print(kakao[0][1])   # '97000'
```

### 여러 SQL 명령어를 한 번에 실행하기

만약 cursor.execute 메서드에 여러 SQL 구문을 한 번에 보내고 싶다면, execute 대신 executemany 메서드를 사용할 수 있다. 이때 executemany의 인자에는 enumerable 타입의 변수가 필요하다.

```python
ListTupleData = [('16.06.03', 97000, 98600, 96900, 98000, 321405),
                '16.06.02', 96400, 97400, 95900, 97000, 300000)
                ]

cursor.executemany("INSERT INTO kakao VALUES(?,?,?,?,?,?)", ListTupleData)

cursor.commit()
cursor.close()
```

### Reference

- [파이썬으로 배우는 알고리즘 트레이딩 - SQLite 모듈 기초](https://wikidocs.net/5327)
- [파이썬으로 배우는 알고리즘 트레이딩 - 데이터베이스로부터 데이터 읽기](https://wikidocs.net/5329)
