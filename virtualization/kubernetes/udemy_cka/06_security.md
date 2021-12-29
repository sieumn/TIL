# [Udmey_CKA] #6 Security

> Udemy의 CKA with Practical Test 강의를 듣고 정리합니다.

## Kubernetes Security Primitives

- 기본적으로 클러스터 내의 pod들을 서로 접근이 가능하다. 네트워크 정책을 사용하여 pod간 접근을 제한할 수 있다.

## Authentication

- 사용자가 kubectl 을 사용하여 명령어를 입력하면, kube-apiserver는 요청을 처리하기 전에 사용자를 인증하는 절차를 거친다.
    - 인증은 다음과 같은 다양한 방식으로 인증할 수 있다.
        - static password file
        - static token file
        - certificates
        - identity service

### Auth Mechanisms - Basic

- 간단하게 Static password file 또는 static token file으로 사용자 인증을 할 수 있지만, 보안상 권장하는 방법은 아니다.
- static password file
    - 다음과 같이 user-detail.csv 파일을 작성한다.
    
    ```bash
    password123,user1,u0001,group1
    password123,user2,u0002,group2
    password123,user3,u0003,group2
    ```
    
    - kube-apiserver.service에 `—-basic-auth-file=user-details.csv` 옵션을 추가한다.
- static token file
    - 다음과 같이 token 파일을 작성한다.
    
    ```bash
    Kpjvdiojr3rwekldsds,user10,u0010,group1
    fjgklajwfemd12wdfdk,user11,u0011,group2
    ```
    
    - kube-apiserver.service에 `—-token-auth-file=user-details.csv` 옵션을 추가한다.
    

## TLS Basic

### TLS Certificate

- 두 그룹간 통신에서 신뢰성을 보장하기 위해 사용하는 것

### Symmetric Encryption (대칭 키 방식)

- 수신 그룹의 암호화와 송신 그룹의 복호화 과정에서 동일한 키를 사용하는 것
- 수신 그룹과 송신 그룹이 동일한 키를 갖기 위해서는 꼭 한 번 키를 교환하는 과정이 필요한데, 키를 교환하는 과정에서 해커가 키를 탈취할 수 있다는 위험성이 있다.

### Asymmetric Encryption (비대칭 키 방식)

- 비대칭 키 방식에서는 두 개의 키를 사용하며, 각각은 private key와 public key 이다. public key는 모든 사람이 갖고 있을 수 있으며, private key는 아무에게도 주지 않고 본인만 가지고 있어야 한다.
    - public key 형식: *.crt, *.pem
    - private key 형식: *.key, *-key.pem
- public key를 가지고 있는 사람은 데이터를 public key로 암호화한 후에 private key를 가진 사용자에게 전송한다. private key를 갖고 있는 사용자는 private key를 사용하여 이를 해독하고 데이터를 얻을 수 있다.
- 예를 들어, 클라이언트가 어떤 서버에 https로 접근하면 해당 서버의 public key를 얻게 된다. 사용자는 얻은 public key를 사용하여 대칭 키를 암호화하여 서버로 보내고, 서버는 자신이 가진 private key를 사용하여 사용자가 보낸 대칭 키를 얻는다. 이 과정에서 데이터를 스니핑 당하더라도 해커는 private key를 갖고 있지 않기 때문에 대칭 키를 얻을 수 없으며, 서버와 클라이언트는 안전하게 통신할 수 있다.
- 이러한 모든 과정을 PKI(Public Key Infrastructure) 라고 부른다.

### CA(Certificate Authorities)

- 서버는 public key를 보낼 때 인증서를 함께 보내게 되는데, 인증서에는 인증서를 발급한 주체와 public key에 대한 정보가 포함되어 있다.
- 만약 인증서가 CA에서 발급을 인정한 정식 인증서가 아닌 경우, 브라우저는 그 사실을 사용자에게 알려줌으로써 해킹을 방지할 수 있다.

## TLS in Kubernetes

![C088BB60-48EB-4554-90D2-251DE1417B41.jpeg](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a809f4ed-f2ce-4eb4-b016-74a54e0bbf2b/C088BB60-48EB-4554-90D2-251DE1417B41.jpeg)

### Server Certificates for Server

- kube-apiserver, etcd, kubelet 서버들은 각각 public key와 private key를 생성한다.

### Client Certificates for Client

- admin, kube-scheduler, kube-controller-manager, kube-proxy는 kube-api 서버와 통신하기 위해 public key와 private key를 생성한다.

### Certificate Creation

- openssl 을 사용하여 ca.key를 발급받을 수 있으며, 통신을 하는 모든 서버는 ca.key 사본을 갖고 있어야 한다.
