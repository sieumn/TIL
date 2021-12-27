# [Udmey_CKA] #3 Monitoring and Logging

> Udemy의 CKA with Practical Test 강의를 듣고 정리합니다.

## Monitor Cluster Components

### Monitoring Solution

- 쿠버네티스는 built-in 모티너링 솔루션을 가지고 있지는 않으나, 다양한 오픈소스 메트릭 서버를 사용하여 모니터링 서비스를 만들 수 있다.

### Metrics Server

- 쿠버네티스 클러스터 별로 하나의 메트릭 서버를 가질 수 있다. Metric Server는 in-memory 모니터링 솔루션으로 데이터를 저장하거나 히스토리를 볼 수가 없다.
- kubelet은 cAdvisor 라는 서브-컴포넌트를 가지고 있다. cAdvisor는 pod로부터 성능 메트릭을 받아 kubelet으로 보내 Metric Server에서 해당 정보를 수집할 수 있도록 한다.

### View

```yaml
kubectl top node      # node의 퍼포먼스 메트릭 확인 가능
kubectl top pods      # pod의 퍼포먼스 메트릭 확인 가능
```

## Managing Application Logs

- event-simulator 배포하기

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: event-simulator-pod
spec:
  containers:
  - name: event-simulator
    image: kodekloud/event-simulator
```

- event-simulator에서 발생하는 로그 확인하기

```yaml
kubectl create -f event-simulator.yaml
kubectl logs -f event-simulator-pod       # -f 옵션을 쓰면 live response 확인 가능

# pod 안에 container가 여러개면 지정해서 log 확인 가능
kubectl logs -f event-simulator-pod event-simulator
```