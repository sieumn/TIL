# #5 Container Configuration

## Pod Status (Phase)

- Pod의 상태 중 `phase`는 pod가 라이프사이클 중 어느 단계에 해당하는지 표현하는 간단한 요약이다.
- pod의 phase는 다음 값들을 가질 수 있다.

### Pending

- Pod가 Kubernetes cluster에 의해 승인되었지만, 하나 이상의 컨테이너가 설정되지 않아 실행할 준비가 되지 않은 상태
- 여기에는 Pod가 스케줄 되기 이전까지의 시간뿐만 아니라 네트워크를 통한 컨테이너 이미지 다운로드 시간도 포함된다.

### Running

- Pod가 node에 바인딩 되었고, 모든 컨테이너가 생성되었다.
- 적어도 하나의 컨테이너가 아직 실행 중이거나, 시작 또는 재시작 중에 있다.

### Succeeded

- Pod에 있는 모든 컨테이너들이 성공적으로 종료되었고, 재시작되지 않을 것이다.

### Failed

- Pod에 있는 모든 컨테이너가 종료된 상태
- 또는 적어도 하나 이상의 컨테이너가 실패로 종료된 상태

### Unknown

- 어떤 이유에 의해서 Pod의 상태를 얻을 수 없는 상태.
- 이 단계는 일반적으로 Pod가 실행되어야 하는 노드와의 통신 오류로 인해 발생한다.

## Container Status

- Kubernetes는 전체 Pod의 phase뿐 아니라, pod 내부의 각 컨테이너의 상태도 추적한다.
- 파드 내의 각 컨테이너의 상태는 `kubectl describe pod <pod_name>` 명령어를 사용하여 확인할 수 있다.
- 스케줄러가 node에 pod를 할당하면, kubelet은 container runtime을 사용하여 컨테이너 생성을 시작한다. 이 때 표현될 수 있는 컨테이너의 상태는 3가지로 다음과 같다.

### Waiting

- `Waiting` 상태의 컨테이너는 시작 전에 컨테이너 이미지를 가져오거나, 시크릿 데이터를 적용하는 등의 필요한 작업을 실행하는 상태이다.
- kubectl을 사용하면 필드에 컨테이너가 waiting 상태에 있는 이유를 확인할 수 있다.

### Running

- `Running` 상태는 컨테이너가 문제 없이 실행되고 있음을 나타낸다.
- kubectl을 사용하여 해당 컨테이너가 running 상태에 진입한 시기를 확인할 수 있다.

### Terminated

- `Terminated` 상태는 컨테이너가 실행 후에 완료되어 종료되었거나, 어떤 이유로 실패했음을 나타낸다.
- kubectl을 사용하여 컨테이너가 종료된 이유와 종료 코드, 실행 시간 등을 확인할 수 있다.

## Container Restart Policy

- Pod를 생성할 때 spec에는 `restartPolicy` 필드가 있으며, 이는 컨테이너의 재시작할 정책을 의미한다. Pod에 선언된 restartPolicy는 pod 내의 모든 컨테이너에 적용된다.
- 이 필드에서 사용 가능한 값은 Always, OnFailure, Never이 있으며, 기본값은 Always이다.

## Container Probes

- 컨테이너 probe란 컨테이너에서 kubelet에 의해 주기적으로 수행되는 진단(diagnostic)이다.

### Probe 종류

kubelet은 실행 중인 컨테이너들에 대해 3가지 종류의 Probe를 수행할 수 있다.

#### livenessProbe

- 컨테이너가 동작 중인지 여부를 진단한다.
- livenessProbe에 실패하면 kubelet은 컨테이너를 죽이고, 해당 컨테이너는 재시작 정책에 따라 동작한다.

#### readinessProbe

- 컨테이너가 요청을 처리할 준비가 되어 있는지 여부를 진단한다.
- probe가 성공한 경우에만 pod에 트래픽 전송을 시작하려고 한다면 readinessProbe를 지정해야 한다.
- readinessProbe에 실패하면 엔드포인트 컨트롤러는 pod에 연관된 모든 서비스들의 엔드 포인트에서 pod의 IP 주소를 제거한다.

#### startupProbe

- 컨테이너 내의 애플리케이션이 시작되었는지 여부를 진단한다.
- startupProbe가 주어진 경우, startupProbe가 성공할 때까지 다른 probe들은 활성화되지 않는다.
- startupProbe는 서비스를 시작하는 데 오래 걸리는 컨테이너가 있는 pod에서 유용하다. 활성 간격을 길게 설정하는 대신, startupProbe를 설정하면 더 긴 시간을 안전하게 허용할 수 있다.
- startupProbe에 실패하면 kubelet은 컨테이너를 죽이고, 해당 컨테이너는 재시작 정책에 따라 동작한다.

### Probe Results

Probe 결과로는 다음 셋 중 하나의 값을 가진다.

- `Success`: 컨테이너가 진단을 통과
- `Failure`: 컨테이너가 진단에 실패
- `Unknown`: 진단 자체가 실패하여 아무런 액션도 수행되면 안됨

### Probe Handlers

kubelet은 컨테이너에 의해 구현된 핸들러를 호출하여 진단을 수행한다.

- `ExecAction`
  + 컨테이너 내에서 지정된 명령어를 실행하는 방식이다.
  + 성공 기준: 명령어가 상태 코드 0으로 종료
- `TCPSocketAction`
  + 지정된 포트에서 컨테이너의 IP 주소에 대한 TCP 검사를 수행한다.
  + 성공 기준: 포트가 활성화되어 연결 성공
- `HTTPGetAction`
  + 지정한 포트 및 경로에서 컨테이너의 IP 주소에 대한 HTTP GET 요청을 수행한다.
  + 성공 기준: 응답의 상태 코드가 200~399

### Probe Options

- `initialDelaySeconds`
  + 컨테이너가 시작되고 몇 초 뒤에 진단을 수행할지 지정한다.
- `periodSeconds`
  + 얼마나 자주 진단을 수행할지 지정한다. 기본값은 10s이다.
- `timeoutSeconds`
  + 타임 아웃의 기준을 지정한다. 기본값은 1s이다.
- `successThreshold`
  + 진단이 성공으로 간주되기 위해서 몇 번 연속으로 성공해야 하는지 지정한다. 기본값은 1이다.
- `failureThreshold`
  + 진단이 실패로 간주되기 위해서 몇 번 연속으로 실패해야 하는지 지정한다. 기본값은 3이다.

## Container Resources

- Pod를 생성할 때 컨테이너에 필요한 리소스의 양을 지정할 수 있다. request를 통해 최소 리소스 양을 지정하거나, limit을 통해 최대 리소스를 지정한다.
- 지정하는 리소스에는 CPU, 메모리, 네트워크 등이 있다.
- 만약 리소스 limit은 있으나 request는 지정되지 않은 경우, kuberneets는 limit과 일치하는 request를 자동으로 할당한다.

### Resource Requests

- Pod에서 리소스 request를 지정하면, 스케줄러는 이 요청을 사용하여 pod가 배치될 node를 결정한다.
- pod가 실행 중인 node에 리소스 자원이 충분하다면, 컨테이너는 지정한 request 리소스보다 더 많은 리소스를 사용할 수 있다.

### Resource Limit

- Pod에서 리소스 limit을 설정하면, kubelet은 pod가 설정한 limit보다 더 많은 리소스를 사용할 수 없도록 제한을 적용한다.
- 만약 컨테이너가 limit 이상으로 자원을 할당하려고 시도한다면, 해당 컨테이너는 종료된다.

### resource.yaml

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: frontend
spec:
  containers:
  - name: app
    image: images.my-company.example/app:v4
    resources:
      requests:
        memory: "64Mi"
        cpu: "250m"
      limits:
        memory: "128Mi"
        cpu: "500m"
```

## Reference

- [Kubernetets Documentation](https://kubernetes.io/ko/docs/concepts/workloads/pods/pod-lifecycle/)