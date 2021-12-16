# #7 Stateful Application

## Volume

- 컨테이너 내의 디스크는 임시적이며, 컨테이너가 사라지면 파일도 손실된다. 또한 Pod 내에서 컨테이너끼리 데이터를 공유하기도 어렵다. 따라서 쿠버네티스에서는 volume이라는 추상 오브젝트를 사용한다.
- 쿠버네티스는 다양한 유형의 volume을 지원한다. 임시 volume 유형은 pod의 수명 주기를 가지며 peresistent volume은 pod의 수명을 넘어 존재한다. 
- 일반적으로 스토리지 volume은 pod 레벨에서 정의된다. 따라서 volume 종류와 관계없이 pod 내에서 컨테이너가 재시작되어도 데이터는 보존된다.

### emptyDir

- Volume의 기본값은 임시 volume인 emptyDir이다. emptyDir volume은 처음에 비어 있다.
- emptyDir volume은 pod가 노드에 할당될 때 처음 생성되며, 해당 노드에 pod가 존재하는 동안에만 유지된다.
- pod 내 모든 컨테이너는 emptyDir volume의 파일에 접근할 수 있으며, 해당 volume은 각 컨테이너에 마운트 될 수도 있다.
- 어떤 이유로든 pod가 노드에서 제거되면 emptyDir의 데이터는 영구적으로 삭제된다.

#### emptyDir 구성 예시

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: test-pd
spec:
  containers:
  - image: k8s.gcr.io/test-webserver
    name: test-container
    volumeMounts:
    - mountPath: /cache
      name: cache-volume
  volumes:
  - name: cache-volume
    emptyDir: {}
```

### Persistent Volume (PV)

- Pod의 라이프 사이클과 독립적인 스토리지를 사용하기 위해서는 Persistent Volume이라는 클러스터 리소스를 사용한다.
- Persistent Volume(PV)는 관리자가 프로비저닝하거나 스토리지 클래스를 사용하여 동적으로 프로비저닝한 클러스터 스토리지다.
- PV는 클러스터의 리소스이며, PV를 사용하는 pod와는 독립적인 라이프 사이클을 가진다.
- PV 오브젝트는 스토리지 구현에 대한 세부 정보를 담고 있다.

### Persistent Volume Claim(PVC)

- Persistent Volume Claim(PVC)는 사용자의 스토리지에 대한 요청이다.
- pod가 노드 리소스를 사용하는 것처럼 PVC는 PV의 리소스를 사용한다. pod가 CPU, 메모리 등을 요청한다면, PVC는 특정 크기 및 접근 모드 등을 요청한다.

### Using PV

다음과 같이 PVC를 생성하고, pod에서 PVC를 연결할 수 있다.

#### PersistentVolumeClaim

```yaml
kind: PersistentVolumeClaim
apiVersion: v1
metadata:
  name: mysql-pvc
spec:
  accessModes:
    - ReadWriteOnce
  volumeMode: Filesystem
  resources:
    requests:
      storage: 8Gi
  storageClassName: slow
```

#### PVC in a Pod

```yaml
kind: Pod
apiVersion: v1
metadata:
  name: mypod
spec:
  container:
    - name: my-mysql
      image: mysql:5.6
      volumeMounts:
      - mountPath: "/var/lib/mysql"
        name: mysql-pd
  volumes:
    - name: mysql-pd
      persistentVolumeClaim:
        claimName: mysql-pvc
```

## PV와 PVC의 상호작용

PV와 PVC 간의 상호 작용은 다음 라이프 사이클을 따른다.

### 프로비저닝

PV를 프로비저닝하는 방법에는 정적 프로비저닝, 동적 프로비저닝 두 가지 방법이 있다.

#### 정적(staic) 프로비저닝

- 정적 프로비저닝은 사용자가 여러 PV를 만들고, 사용자가 사용할 수 있는 세부사항을 제공하는 것이다.

#### 동적(dynamic) 프로비저닝

- PVC의 요청이 관리자가 생성한 PV와 일치하지 않다면, 동적 프로비저닝에서는 PVC를 위해 새로운 볼륨을 동적으로 프로비저닝하려고 시도한다.
- 동적 프로비저닝은 스토리지 클래스를 기반으로 하며, PVC는 스토리지 클래스를 요청해야 한다.
  + 만약 PVC가 `""` 클래스를 요청한다면 동적 프로비저닝은 비활성화된다. 

### 바인딩

- master-control-loop는 새로운 PVC를 감시하고 일치하는 PV를 찾아 서로 바인딩 한다.
- 만약 어떤 PV가 PVC에 의해 동적으로 프로비저닝된 경우, loop는 해당 PV를 항상 PVC에 바인딩 한다.
- PVC와 PV는 1 대 1 매핑으로, `ClaimRef`라는 양방향 바인딩을 사용한다.
- 만약 일치하는 PV가 없다면, PVC는 일치하는 볼륨이 제공될 때까지 바인딩 되지 않은 상태로 남아 있다.

### 사용중

- pod는 PVC를 볼륨으로 사용한다. 클러스터는 PVC를 검사하여 바인딩 된 볼륨을 찾고 해당 볼륨을 pod에 마운트 한다.
- 사용자는 pod의 `volumes` 블록에 `persistentVolumeClaim`을 포함하여 pod를 스케줄링하고, 클레임한 PV에 접근한다.

### 사용 중인 스토리지 오브젝트 보호

- PVC가 사용 중인 PV와 pod에 바인딩 된 PVC가 시스템에서 삭제되지 않도록 하기 위해 오브젝트 보호 기능을 사용한다.
- 사용자가 pod에서 활발하게 사용하고 있는 PVC를 삭제한다면 PVC는 즉시 삭제되지 않는다. pod가 더 이상 PVC를 적극적으로 사용하지 않을 때까지 PVC 삭제가 연기된다.
- 마찬가지로, PVC에 바인딩 된 PV를 삭제하려고 시도하더라도 PV는 즉시 삭제되지 않는다. PV가 더 이상 PVC에 바인딩 되지 않을 때까지 PV 삭제가 연기된다.

### 반환(Reclaiming)

- 사용자가 volume을 다 사용하고 나면 리소스 반환 API를 사용하여 PVC 오브젝트를 삭제할 수 있다.
- 반환할 때는 volume에서 클레임을 해제한 후에 volume에 수행할 작업을 알려줘야 하는데, 반환 정책에는 다음 두 가지가 있다.

#### Retain(보존)

- Retain은 리소스를 수동으로 반환할 수 있게 한다. PVC가 삭제되더라도 PV는 released 된 것으로 간주되며 여전히 남아있다.
- 다만 이전 사용자의 데이터가 volume에 남아 있기 때문에, 다른 요청에는 아직 사용할 수 없다.

#### Delete(삭제)

- Delete는 PV와 외부 인프라(AWS EBS, GCE PD 등) 관련 모든 스토리지 자산을 삭제한다.
- 동적으로 프로비저닝된 volume의 경우 반환의 기본값이 delete이다.

## StorageClass

- 스토리지 클래스는 관리자가 제공하는 스토리지의 기본 정보를 담고 있다.
- 각 스토리지 클래스에는 해당 스토리지 클래스에 속하는 PV를 동적으로 프로비저닝할 때 사용되는 `provisioner`, `parameters`, `reclaimPolicy` 필드가 있다.
- 사용자는 스토리지 클래스의 이름을 사용하여 특정 클래스를 요청한다. 특정 클래스에 바인딩을 요청하지 않는 경우 기본 스토리지 클래스를 지정할 수 있다.

### Storage Class 생성하기

```yaml
apiVersion: storage.k8s.io/v1
kind: StorageClass
metadata:
  name: standard
provisioner: kubernetes.io/aws-ebs
parameters:
  type: gp2
reclaimPolicy: Retain
allowVolumeExpansion: true
mountOptions:
  - debug
volumeBindingMode: Immediate
```

#### Provisioner

- provisioner는 각 스토리지 클래스에서 PV 프로비저닝에 사용되는 volume 플러그인을 결정한다. (필수 필드)
- AWSElasticBlockStore, AzureFile, GCEPersistentDisk 등을 사용할 수 있다.
- 내부 privisioner도 지정할 수 있는데, 이는 `kubernetes.io`가 접두사로 시작한다.

#### Parameters

- privisoner에 따라 다른 parameter 값을 사용할 수 있다.

#### reclaimPolicy

- 스토리지 클래스에 의해 동적으로 생성된 PV는 클래스의 reclaimPolicy에 의해 제거 정책이 결정된다.
- Delete 또는 Retain을 선택할 수 있으며, 기본값은 Delete이다.

#### allowVolumeExpansion

- PV는 volume을 확ㅈ아하도록 구성할 수 있다. 이 기능을 true로 설정하면 해당 PVC를 편집하여 volume 크기를 조정할 수 있다.

#### mountOptions

- 동적으로 생성된 PV는 mountOptions 필드에 지정된 마운트 옵션을 가진다.
- 마운트 옵션은 클래스나 PV에서 검증되지 않으므로, 볼륨 플러그인이 마운트 옵션을 지원하는지 확인이 필요하다. PV 마운트가 유효하지 않으면 프로비저닝은 실패한다.

#### volumeBindingMode

- volumeBindingMode는 volume 바인딩과 동적 프로비저닝 시작 시기를 제어한다. 기본값은 `Immediate` 모드이다.
- `Immediate` 모드는 PVC가 생성되는 즉시 볼륨 바인딩과 동적 프로비저닝이 시작되는 것을 의미한다.
- `WaitForFirstConsumer` 모드는 PVC를 사용하는 pod가 생성될 때까지 PV의 바인딩과 동적 프로비저닝을 지연시킨다.

## StatefulSets

- StatefulSets은 deployment와 유사하게 여러 pod들을 관리하지만, deployment와 달리 각 pod의 독자성을 유지한다.
- statefulSets에서 각 pod는 동일한 spec을 갖더라도 서로 교체될 수 없다.
- statefulSets은 안정적인 PV를 사용해야 한다는 특징을 갖는다.

### StatefulSets 예시

```yaml
apiVersion: apps/v1
kind: StatetfulSet
metadata:
  name: web
spec:
  selector:
    matchLabels:
      app: my-mysql
  serviceName: my-mysql
  replicas: 1
  template:
    metadata:
      labels:
        app: my-mysql
    containers:
    - name: mysql
      image: mysql:5.6
      volumeMounts:
      - name: mysql-pd
        mountPath: /var/lib/mysql
  volumeClaimTemplates:
  - metadata:
      name: mysql-pd
    spec:
      accessModes: [ "ReadWriteOnce" ]
      storageClassName: "my-storage-class"
      resources:
        requests:
          storage: 8Gi
```

## Reference

- [Kubernetes Documentation - Storage](https://kubernetes.io/ko/docs/concepts/storage/)
- Kubernetes Fundamentals and Cluster Operations Lecture notes
