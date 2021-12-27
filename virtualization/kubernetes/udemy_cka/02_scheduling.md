# [Udmey_CKA] #2 Scheduling

> Udemy의 CKA with Practical Test 강의를 듣고 정리합니다.

## Manual scheduling

- 만약 스케줄러가 없다면, Pod를 정의할 때 spec.nodeName에서 직접 노드를 지정해야 한다.

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: nginx
  labels:
    name: nginx
spec:
  containers:
    - name: nginx
      image: nginx
      ports:
        - containerPort: 8080
  nodeName: node02
```

- 스케줄러가 없는데 nodeName도 없을 경우 Pod가 생성되지 않고 pending 상태로 남는다.
    + pending 중인 pod를 node에 배치하기 위해서는 binding 오브젝트를 생성해야 한다.
        
        ```yaml
        apiVersion: v1
        kind: Binding
        metadata:
          name: nginx
        target:
          apiVersion: v1
          kind: Node
          name: node02
        ```
        

## Labels and Selectors

### Labels

- 오브젝트, 리소스 등에 label을 설정해두면 label을 기준으로 수 많은 자원들을 그룹화하고 검색하는 것이 용이해진다.
- manifest 파일의 metadata 영역에서 key-value 형태로 정의된다.

### Selectors

- 특정 Label을 가진 자원을 검색하거나 사용할 때 사용하는 개념이다.
- 다음과 같이 app=App1 label을 갖는 pod를 검색할 수 있다.
    
    ```yaml
    kubectl get pods --selector app=App1                 # --selector 대신 --l 써도 됨
    kubectl get pods --selector app=App1,tier=frontend.  # 여러 label 검색
    ```
    
- replicaset에서는 selector와 label을 모두 사용하는데, selector에서 사용하는 matchLabels 영역과 template의 label 영역이 일치해야 여러 pod 배포가 가능하다.

## Taints and Tolerations

### Taints

- node에 taint를 설정하면 해당 node가 오염되어 특정 pod만 스케줄링할 수 있다.
- container가 특정 node가 가진 taint 속성에 대해 toleration이 없는 경우 해당 taint에 스케줄링될 수 없다.

```yaml
kubectl taint nodes node-name key=value:taint-effect
kubectl taint nodes node1 app=blue:NoSchedule
```

- taint-effect
    + NoSchedule: 해당 node에 새로운 pod가 스케줄되지 않는다.
    + PreferNoSchedule: 최대한 스케줄을 피하나 보장하지는 않는다.
    + NoExecute: 새로운 pod 스케줄되지 않고, 기존에 실행중이던 pod도 이동시킨다.
- Kubernetes를 초기 설정하면 master node는 자동으로 NoSchedule 속성을 갖도록 설정된다.

### Tolerations

- pod가 특정 taint에 대해 toleration을 갖고 있다면 taint가 있는 node에도 스케줄링될 수 있다.
- POD를 생성할 때 다음과 같이 속성을 넣어 tolerance를 설정할 수 있다. “” 을 사용해야 한다.

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: myapp-pod
spec:
  containers:
  - name: nginx-container
    image: nginx
  tolerations:
  - key: "app"
    operator: "Equal"
    value: "blue"
    effect: "NoSchedule"
```

## Node Selectors and Affinity

### Node Selector

- 만약 자원이 많이 필요한 pod를 자원이 많은 node에 자동으로 배정하고 싶다면?
- 두 가지 방법이 있는데 첫 번째로는 node selector를 사용하는 것이다. nodeSelector에서 원하는 node 특성을 label을 사용하여 지정할 수 있다.

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: myapp-pod
spec:
  containers:
  - name: data-processor
    image: data-processor
  nodeSelector:
    size: Large
```

- node에 label 지정하는 방법은 다음과 같다.

```yaml
kubectl label nodes <node-name> <key>=<value>
kubectl label nodes node01 size=Large
```

- 한계
    + 여러 개의 label을 지정하거나, 특정 label을 제외한 node에 배포하는 등 복잡한 배포 조건을 설정할 수 없다.
    + 복잡한 설정을 위해 node-affinity 속성을 사용해야 한다.

### Node Affinity

- Node affinity도 pod가 특정 속성을 가진 node에 배정될 수 있도록 지원하는 기능을 한다.

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: myapp-pod
spec:
  containers:
  - name: data-processor
    image: data-processor
  affinity:
    nodeAffinity:
      requiredDuringSchedulingIgnoredDuringExecution:
        nodeSelectorTerms:
        - matchExpressions:
          - key: size
            operator: In
            values:
            - Large
            - Medium
```

- operator에 In, NotIn, Exists 등 다양한 조건을 설정할 수 있다.
- nodeAffinity Types에도 다양한 속성이 있다.
    + requiredDuringSchedulingIgnoredDuringExecution
    + preferredDuringSchedulingIgnoredDuringExecution
    + requiredDuringSchedulingRequiredDuringExecution
    + During Scheduling: pod를 생성하고 스케줄링할 때 조건
        * Required: 스케줄링 당시에 반드시 해당 node에만 pod를 생성할 수 있다. node가 없을 경우 pod는 pending 상태로 남는다.
        * Preferred: 해당 node가 없을 경우 다른 사용가능한 node에 스케줄링된다.
    + During Execution: pod가 이미 실행되고 있는데 node에 label이 사라진다면?
        * Ignored: 이미 실행중인 pod에는 전혀 영향을 주지 않는다.
        * Required: 실행 중에 node의 label 정보가 바뀐다면 pod를 재배치한다.

## Resource Requirements and Limits

```yaml
apiVersion: v1
kind: Pod
metadata:
  app: myApp
spec:
  containers:
    - image: nginx
      name: nginx
      resources:
        requests:
          memory: "1Gi"
          cpu: 1
        limits:
          memory: "4Gi"
          cpu: 2
```

### Resource Unit

- CPU
    + 0.1 CPU = 100m CPU
    + 1 CPU = 1 AWS vCPU = 1 GCP Core = 1 Azure Core = 1 Hyperthread
- MEM
    + 1G (Gigabyte) = 1,000,000,000 bytes
    + 1M (Megabyte) = 1,000,000 bytes
    + 1K (Kilobyte) = 1,000 bytes
    + 1Gi (Gibibyte) = (1 << 9) bytes
    + 1Mi (Mibibyte) = (1 << 6) bytes
    + 1Ki (Kibibyte) = (1 << 3) bytes

### Resource Requirements

- Pod가 생성될 때 기본적으로 0.5CPU, 256Mi 메모리를 최소값으로 부여받는다.
- 최솟값으로 더 많은 자원이 필요할 경우 POD manifest 파일에 기입해줄 수 있다.

### Resource Limits

- container가 사용할 수 있는 자원의 최댓값을 설정할 수 있다.
- container가 limit 보다 많은 자원을 사용하면 pod가 종료된다.

### LimitRange

- resource 최소, 최대값 default를 다음과 같이 설정할 수 있다.

```yaml
apiVersion: v1
kind: LimitRange
metadata:
  name: mem-limit-range
spec:
  limits:
  - default:
      memory: 512Mi
    defaultRequest:
      memory: 256Mi
    type: Container
```

- https://kubernetes.io/docs/tasks/administer-cluster/manage-resources/memory-default-namespace/

## DaemonSets

- DaemonSet은 replicaset처럼 pod를 여러 개 복제하여 배포하는 역할을 한다. 차이는, daemonset은 클러스터 내의 모든 노드에 하나씩 pod를 배치하는 역할을 한다.
    + 새로운 node가 추가되면 pod도 하나 추가되고, node가 삭제되면 pod도 삭제된다.
- 모니터링 솔루션, 로그 콜렉터 등을 daemonSet으로 사용하면 편하다.
- replicaSet 정의서와 kind 빼고 동일하다.

```yaml
apiVersion: v1
kind: DaemonSets
metadata:
. 
```

- DaemonSet이 동작하는 방식
    - k8s v1.12까지는 각 pod마다 nodeName을 붙여서 노드를 지정
    - k8s v1.12 부터는 nodeAffinity와 default scheduler를 사용하여 노드 배치

## Static Pods

- 만약 클러스터에 kube-apiserver를 포함한 master node가 없고 worker node만 존재한다면, 혼자서 있는 worker node는 독립적으로 pod를 생성할 수 있을까?
    + kube-apiserver가 없으니 kubectl을 사용할 수는 없다.
- 이 경우 /etc/kubernetes/manifests 폴더에 yaml 파일을 넣어두면, kubelet이 주기적으로 해당 디렉터리를 체크하여 pod를 생성할 수 있다.
    + 디렉터리는 kubelet.service 에서 변경할 수 있다.  (/var/lib/kubelet/config.yaml)
    + 이 폴더에서 내용을 변경하거나 삭제하면 변경, 삭제 내용이 반영된다.
- 다만, pod만 이러한 방식으로 생성할 수 있고, deployments, service 등의 다른 오브젝트들은 여기서 설명할 수 없다.
- static pod를 생성하면  mirror object가 kube-apiserver에 전달되어 kube-apiserver가 알 수 있다. 다만, 삭제나 수정은 kubectl 등을 사용하여 할 수 없다. (디렉터리 접근을 통해서만 가능)
- node를 여러개 배포할 때 기본적인 config 파일들을 manifest에 넣어둔 채로 배포하면 직접 배포하지 않아도 기본 애플리케이션들이 존재하는 node를 셋업할 수 있다.

### Daemon Sets vs. Static PODs

| DaemonSets | Static Pods |
| --- | --- |
| kube-api server에 의해 생성 | kubelet에 의해 생성 |
| monitoring agent, logging agent 등 배포 | control plane 컴포넌트들을 배포 |
| kube-scheduler에 의해 무시됨 | kube-scheduler에 의해 무시됨 |

## Multiple Scheduler

- 만약 내가 필요한 스케줄링 알고리즘을 갖는 스케줄러가 필요하다면? Kubernetes에서는 새로운 스케줄러를 디자인하여 default 스케줄러로서 사용하거나, 기본 default 스케줄러에 추가하여 여러 개의 스케줄러를 사용할 수 있다.
- POD나 Deployment를 배포할 때 어떤 스케줄러를 사용할 것인지 명시할 수 있다.
- kube-scheduler.service 에서 default-scheduler를 변경할 수도 있다.

```yaml
# /etc/kubernetes/manifests/kube-scheduler.yaml
apiVersion: v1
kind: Pod
metadata:
  name: kube-scheduler
  namespace: kube-system
spec:
  containers:
  - command:
    - kube-scheduler
    - --address=127.0.0.1
    - --kubeconfig=/etc/kubernetes/scheduler.conf
    - --leader-elect=true
    image: k8s.gcr.io/kube-scheduler-amd64:v1.11.3
    name: kube-scheduler
```

- leader-elect 옵션은 scheduler 여러 개가 복사되어 사용될 때, 어떤 것이 메일으로 사용될지를 결정하는 옵션이다. (HA를 높이기 위해 여러 대 배포할 경우)
- POD나 Deployment에 다음과 같이 스케줄러를 명시해준다.
    
    ```yaml
    apiVersion: v1
    kind: Pod
    metadata:
      name: nginx
    spec:
      containers:
      - image: nginx
        name: nginx
      schedulerName: my-custom-scheduler
    ```