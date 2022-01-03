# [Udmey_CKA] #7 Storage

> Udemy의 CKA with Practical Test 강의를 듣고 정리합니다.

## Volumes

- Docker에서 데이터는 컨테이너의 라이프 사이클과 함께 동작한다. 컨테이너의 동작이 완료되면 사용된 데이터는 컨테이너와 함께 소멸된다. 만약 데이터를 계속 유지하고 싶을 경우에는 volume을 추가하여 컨테이너의 라이프 사이클과 무관하게 데이터를 유지할 수 있다.
- 쿠버네티스에서도 마찬가지로, Pod의 라이프 사이클과 독립적으로 데이터를 보관하기 위해서는 Volume을 사용한다.
    
    ```yaml
    apiVersion: v1
    kind: Pod
    metadata:
      name: random-name-generator
    spec:
      containers:
      - image: alpine
        name: alpine
        ...
        volumeMounts:
        - mountPath: /opt
          name: data-volume
    volumes:
    - name: data-volume
      hostPath:
        path: /data
        type: Directory
    ```
    
    - 컨테이너의 opt 폴더의 데이터들이 노드의 /data 폴더에 저장된다.

## Persistent Volumes (PV)

- Persistent Volumes(PV)는 클러스터에서 Pod가 사용할 수 있는 스토리지를 정의하는 오브젝트다. 다음과 같이 PV를 정의할 수 있다.

```yaml
apiVersion: v1
kind: PersistentVolume
metadata:
  name: pv-vol-1
spec:
  accessModes:
    - ReadWriteOnce
  capacity:
    storage: 1Gi
  hostPath:
    path: /tmp/data
```

- `accessModes` 필드에는 ReadOnlyMany, ReadWriteOnce, ReadWriteMany 옵션이 있다.
- `hostPath` 는 클러스터 내부에 데이터를 저장하는 경우에 사용되며, 외부 스토리지를 사용할 경우 이 필드가 대체된다.

## Persistent Volume Claim (PVC)

- PV를 사용하기 위해서는 PVC를 생성하여 PV를 요청해야 한다. PVC와 PV는 1 대 1으로 매칭된다.
- PVC가 생성되었는데 binding 될 PV가 없다면, 해당 PVC는 pending 상태로 대기한다. 사용할 수 있는 PV가 발생하면 PVC와 PV가 매칭된다.
- 다음과 같이 PVC를 정의할 수 있다.
    
    ```yaml
    # pvc-definition.yaml
    apiVersion: v1
    kind: PersistentVolumeClaim
    metadata:
      name: myclaim
    spec:
      accessModes:
        - ReadWriteOnce
      resources:
        requests:
          storage: 500Mi
    
    ---
    # pv-definition.yaml
    apiVersion: v1
    kind: PersistentVolume
    metadata:
      name: pv-vol-1
    spec:
      accessModes:
        - ReadWriteOnce
      capacity:
        storage: 1Gi
      awsElasticBlockStore:
        volumeID: <volume-id>
        fsType: ext4
    ```
    
- PV에 binding 되어 있던 PVC가 삭제될 경우, 기본값은 PV는 그대로 유지되고 PVC만 삭제된다. 남아 있는 PV는 다른 PVC에 의해 재사용될 수는 없지만, 관리자가 직접 삭제하기 전에는 삭제되지 않는다.
- 만약 PV가 PVC와 함께 삭제되기를 원한다면, `persistentVolumeReclaimPolicy: Delete` 옵션을 사용할 수 있다.

## Storage Class

### Static Provisioning

- Pod에서 PV를 사용하기 위해서는 PV와 PVC를 먼저 정의하고, PVC에서 PV를 호출하고 Pod에서 PVC를 호출해야 한다. 이렇게 모든 PV를 직접 정의하고 프로비저닝하는 것을 static provisioning 이라고 한다.

### Storage Class

- static provisioning 대신 storage class를 사용하면 보다 편하게 PV를 생성할 수 있다. PVC에서 원하는 PV의 형태와 요청 사항을 기입하고 storage class 이름을 호출하면, storage class는 자동으로 필요에 맞는 PV를 생성해준다. 이 경우 사용자가 직접 PV를 생성하지 않아도 되기 때문에 편리하다.

```yaml
# sc-definition.yaml
apiVersion: storage.k8s.io/v1
kind: StorageClass
metadata:
  name: google-storage
provisioner: kubernetes.io/gce-pd

# pvc-definition.yaml
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
  name: myclaim
spec:
  accessModes:
    - ReadWriteOnce
  storageClassName: gogole-storage
  resources:
    requests:
      storage: 500Mi
```