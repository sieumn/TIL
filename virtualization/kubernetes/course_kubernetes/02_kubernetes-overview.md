# #1 Kubernetes Overview

### Kubernetes Overview

#### Kubernetes

- 애플리케이션(컨테이너)의 배포, 관리 및 확장을 지원하는 도구이다.
- 베어메탈, 하이퍼바이저, 클라우드 서비스 등 다양한 환경에서 동작한다.
- Declarative configuration을 사용하며, 특정 명령을 내리는 것 대신 '바라는 상태'를 정의함으로써 시스템을 동작시킨다.

#### Docker vs. Kubernetes

Docker는 단일 호스트에서 컨테이너를 관리할 때 유용하다. 하지만, 다중 호스트에서 여러 대의 컨테이너를 관리해야 한다면, Docker는 다음과 같은 문제를 해결하지 못한다.

- 대규모의 컨테이너 관리
- 실패한 컨테이너 재실행
- 용량에 따라 컨테이너 스케일링
- 네트워킹 및 로드 밸런싱

Kubernetes는 컨테이너 orchestration 계층을 제공함으로써 이러한 문제를 해결한다.

#### yaml 파일

- Kubernetes에서 Pod를 포함한 모든 자원들은 yaml 파일을 통해 정의된다.
- yaml 파일에는 다음과 같이 리소스의 바라는 상태가 정의되어 있다.

    ```yaml
    apiVersion: v1
    kind: Pod
    metadata:
      name: my-nginx
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx
        image: nginx:1.7.9
        ports:
          - containerPort: 80
    ```

### Kubernetes Building Blocks

Kubernetes는 크게 Pods, nodes, 그리고 clusters로 구성되어 있다.

![](images/2021-12-14-01-09-40.png)

#### Pods

- Kubernetes에서 Pod는 컨테이너를 배포하는 최소 단위이다. 컨테이너를 생성하기 위해서는 Pod를 생성해야만 한다.
- 하나의 Pod에는 하나의 컨테이너가 있거나, 면밀하게 연결된 여러 개의 컨테이너가 포함된다. Pod 내의 컨테이너들은 동일한 생성 및 소멸 주기를 갖는다.

#### Nodes

- Pod가 실행되는 일종의 컨테이너 호스트다. 실제 물리 서버 또는 VM을 사용한다.
- Node는 master node와 worker node 두 종류가 있다.
  + master node는 클러스터 내부의 이벤트에 반응하며, 클러스터와 관련된 글로벌한 결정을 내린다.
  + worker node는 Pod를 실제로 생성하는 역할을 한다.

#### Cluster

![](images/2021-12-14-01-11-49.png)

- Master node에 의해 관리되는 worker node들의 집합을 의미한다.
- Cluster는 control plane과 data plane으로 구분된다. 
  + control plane에는 master node가 위치하며 클러스터에 고가용성을 제공하는 역할을 한다.
  + data plane에는 여러 개의 worker node들이 위치해 있다.

### Kubernetes Architecture

Kubernetes는 다양한 component들로 구성되어 있다.

![](images/2021-12-14-00-22-11.png)

#### kubectl

- kubectl은 Kubernetes API를 사용하는 CLI이다.
- kubectl 명령어를 사용하여 Kubernetes API 서버에 접근한다.

#### kube-apiServer (master node)

- Kubernetes 시스템의 진입 포인트로, 모든 요청을 받아 처리한다.
- REST API로 요청을 받아 JSON 파일로 상태를 정보를 반환한다.

#### etcd (master node)

- Kubernetes에서 데이터베이스 역할을 하는 component다.
- 클러스터의 상태와 설정 등 모든 정보를 key-value 형태로 저장한다.
- apiServer를 통해 노드와 통신하며 노드의 현재 상태를 파악한다. 그리고 현재 상태와 데이터 스토어에 저장된 바라는 상태 사이의 차이점을 찾아낸다.

#### kube-controller-manager (master node)

- apiserver를 관찰함으로써 클러스터 내의 변화를 감지한다.
- 클러스터 내에 변화가 있을 경우, 바라는 상태에 도달하도록 다양한 컨트롤러들을 실행시키고 관리한다.

#### kube-scheduler (master node)

- 정책을 기반으로 각 노드에 workload를 분산하는 역할을 한다.
- Pod 배치를 결정할 때는 affinity, 자원 상태 등이 고려된다.

#### kubelet (worker node)

- kubelet은 node agent로, node 내에서 컨테이너들이 잘 실행되고 있는지 관찰한다.
- kubelet은 apiServer와 통신하며 node 내 컨테이너 실행 상태를 전달하고, 새로운 work를 부여받는다.

#### kube-proxy (worker node)

- 트래픽을 컨테이너로 라우팅하기 위해 네트워크 규칙을 설정한다.
- 로드 밸런싱을 하거나 가상 IP 주소를 만드는 등의 역할을 한다.

#### docker (worker node)

- docker(containerd)가 위치하며, kubelet의 요청에 의해 컨테이너를 생성한다.