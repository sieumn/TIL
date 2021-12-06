# #1 Linux System Access

## Command Line Access

### Bash Shell 소개

- 명령 줄(command line)이란 컴퓨터 시스템에 명령을 입력하는 데 사용하는 텍스트 기반의 인터페이스다. Linux의 명령행은 shell이라는 프로그램에서 제공된다.

- Red Hat Enterprise Linux(이하 RHEL)에서 사용자의 기본 shell은 GNU Bourne-Again Shell(bash)이며, bash는 UNIX 계열 시스템에 사용되는 가장 성공적인 shell 중 하나인 Bourne Shell(sh)의 향상된 버전이다.

- 대화형 shell을 사용하면 사용자의 명령 입력을 기다리는 동안 다음과 같은 문자열이  표시되며, 이것을 shell prompt라고 한다. 일반 사용자가 shell을 시작할 때 기본 프롬프트는 다음과 같이 $로 끝난다.

    ```bash
    [user@host ~]$
    ```

- Shell이 root 사용자로서 실행되는 경우에는 $ 문자가 # 문자로 바뀌어 표시된다. 이렇게 하면 root shell 임을 쉽게 알 수 있다.

    ```bash
    [user@host ~]#
    ```

### Shell 기본 구성

- Shell 프롬프트에서 입력되는 명령은 세 가지 기본 부분으로 구성된다.

    ```bash
    $ <COMMAND> <option> <명령어>
    # example
    $ usermod -L user01
    ```

### Virtual Console

- 가상 콘솔(Virtual Console)이란 한 대의 컴퓨터로 여러 대의 컴퓨터를 동시에 사용하는 것과 같은 효과를 볼 수 있는 가상의 시스템 분할 환경이다.

- Linux는 총 6개의 가상 콘솔을 제공한다. 즉, linux에는 6개의 서로 다른 화면이 있다는 것이다. 각 가상 콘솔은 독립적인 로그인 세션을 지원한다. Ctrl + Alt + F1~6 단축키를 사용하면 가상 콘솔 간 화면을 전환할 수 있다.
  
- Linux나 Unix는 multi-user system이다. 즉, 하나의 linux 서버에 다수의 사용자가 접속하는 것이 가능하다. multi-user system을 이용하면 가상 콘솔 1에는 root 계정으로 접속하고, 가상 콘솔 2에는 사용자 계정으로 접속하는 등의 상황을 만들 수 있다.

- tty는 표준 출력에 해당하는 터미널의 장치 이름을 출력해 주는 명령어다. 일반적으로 현재 사용 중인 터미널의 파일명을 확인할 때 사용한다. 만약 tty 명령어를 입력했을 때 'tty1'이라는 결과값이 나왔다면, 현재 첫 번째 가상 콘솔을 사용하고 있다는 뜻이다.

### 네트워크를 통한 로그인 - SSH

- Linux를 사용하다 보면 네트워크를 통해 원격 시스템에 대한 shell 접근 권한을 얻어야 하는 경우가 많다. 특히, cloud 환경을 사용하면 실제 하드웨어 콘솔이 없어 무조건 원격으로 접속해야 하는 경우가 발생한다.

- Linux에서 원격 시스템의 shell 프롬프트를 가져오는 가장 일반적인 방법이 SSH(보안 shell)을 사용하는 것이다. 다음과 같이 ssh 명령어를 사용하여 원격 콘솔에 접속할 수 있다. 아래 경우에서는 원격 콘솔의 비밀번호를 입력하여 접속했다.

    ```bash
    [user@host ~]$ ssh remoteuser@remotehost
    remoteuser@remotehost\'s password: password
    [remoteuser@remotehost ~]$
    ```

### 네트워크를 통한 로그인 - 공개 키

- 일부 보안이 강화된 시스템에서는 원격 콘솔의 암호를 사용하여 ssh 로그인하는 것이 불가능하다. 암호를 사용하지 않고 원격 시스템에 인증할 수 있는 다른 방법은 공개 키 인증을 사용하는 것이다. 공개 키는 암호와 동등한 효과를 가지며, 사용자가 생성한 공개 키가 원격 서버의 계정에도 설치되어 있을 경우, 암호를 확인하지 않고 로그인이 가능하다.

- mylab.pem 라는 공개 키를 가지고 있다면, 다음과 같은 방식으로 공개 키를 사용하여 원격 콘솔에 로그인할 수 있다.

    ```bash
    [user@host ~]$ ssh -i mylab.pem remoteuser@remotehost
    [remoteuser@remotehost ~]$
    ```

### 로그아웃

- exit 명령어 또는 Ctrl+D 단축키를 통해 shell 세션을 종료할 수 있다.

    ```bash
    [remoteuser@remotehost ~]$ exit
    logout
    Connection to remotehost closed
    [user@host ~]$ 
    ```

## SSH 키 기반 인증 설정

### SSH 키 생성

- 앞서 살펴 본 공개 키 기반 인증에 대해 자세히 살펴보자. 사용자는 개인-공개 키 체계를 기반으로 암호 없이 SSH 서버에 인증이 가능하다.
  
- 사용자는 한 쌍의 암호화 키 파일을 생성해야 하는데, 하나는 개인 키 파일이고 다른 하나는 공개 키 파일이다. 개인 키 파일은 인증 자격으로 사용되며, 이는 암호와 마찬가지로 비밀로 유지해야 한다. 공개 키는 사용자가 연결하려는 서버에 복사되며, 개인 키를 확인하는 용도로 사용된다. 공개 키는 굳이 비밀로 유지할 필요는 없다.

- 개인 키 및 공개 키를 만들기 위해서는 ssh-keygen 명령을 사용한다.

    ```bash
    [user@host ~]$ ssh-keygen -t rsa -N '' -f ~/.ssh/testkey
    # -t <key_format> : key 파일 암호화 알고리즘 방식 (rsa 형식)
    # -N <passwd> : 패스워드 설정. 비울 경우 비밀번호 없음
    # -f <dir> : 파일 저장 위치 (default: ~/.ssh/id_rsa)
    # 인증 키를 여러 개 만들 경우, 계속 동일 위치의 rsa 파일 덮어쓰므로 저장 위치와 키 이름을 구분하는 것이 좋다.
    ```

- 위 명령어를 사용하여 키를 생성하면 ~/.ssh 폴더에 testkey와 testkey.pub 두 개의 키가 생성되어 있을 것이다. 확장자가 없는 testkey가 개인 키이며, testkey.pub가 공개 키다.

### 공개 키 공유

- 생성한 공개 키를 원하는 대상 시스템에 복사해 보자. 공개키 복사에는 ssh-copy-id 라는 명령이 사용된다.

    ```bash
    # <PUB_KEYNAME.pub> 파일을 다른 user에게 전달
    $ ssh-copy-id -i ~/.ssh/<PUB_KEYNAME.pub> <USERNAME>@<HOST>
    ```

- 공개 키를 복사하고 나면, 사용자는 해당 콘솔에 별도의 콘솔 암호 입력 없이 로그인할 수 있다. 개인 키에 암호가 설정되어 있을 경우, 개인 키 암호를 입력하여 접속이 가능하다.

- 만약 한 번에 여러 서버에 공개 키를 공유하고 싶다면, 다음과 같이 명령어를 사용해 볼 수 있다.

    ```bash
    $ for host in node1 node2 node3 node4 node5 ; do ssh-copy-id -o StrictHostKeyChecking=no root@$host ;
    # -o StrictHostKeyChecking : finger-print key 검사 무시
    ```

### 비대화형 인증을 위해 ssh-agent 사용하기

- 개인 키에 암호가 걸려있는 경우, ssh-agent라는 프로그램을 사용하면 임시로 암호를 메모리에 캐시할 수 있다.
  
- ssh-agent는 경우에 따라 자동으로 시작될 수도 있고 그렇지 않을 수도 있는데, 만약 ssh-agent를 수동으로 시작해야 한다면 다음 명령어를 사용하면 된다.

    ```bash
    [user@host ~]$ eval $(ssh-agent)
    Agent pid 10155
    [user@host ~]$
    ```

- ssh-agent가 실행 중이라면, ssh-add 명령어를 사용하여 개인 키에 대한 암호를 저장할 수 있다.

    ```bash
    # 별도 경로가 없을 경우 /.ssh/id_rsa 파일을 사용한다.
    [user@host ~]$ ssh-add
    Identity added

    # 개인 키에 암호가 설정된 경우 다음과 같이 암호 입력을 받는다.
    [user@host ~]$ ssh-add /.ssh/key-with-pass
    Enter passphrase for .ssh/key-with-pass: redhatpass
    Identity added
    ```

- ssh-agent에 암호를 저장하고 나면, 이제 개인 키를 따로 등록하지 않아도 원격 콘솔에 ssh 명령어만 입력하여 접속할 수 있다.

    ```bash
    # default 개인 키를 사용할 경우
    [user@host ~]$ ssh user@remotehost
    [user@remostehost ~]$

    # 특정 경로의 개인 키를 사용할 경우 (비밀번호는 생략 가능)
    [user@host ~]$ ssh -i .ssh/key-with-pass user@remotehost
    [user@remostehost ~]$
    ```
