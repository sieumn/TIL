# [Udmey_CKA] #9 Problem Solving

> Udemy의 CKA with Practical Test 강의에 포함된 문제 풀이 정리

## Mock Test 2

1. Take a backup of the etcd cluster and save it to /opt/etcd-backup.db

- Answer
  
    ```bash
    etcdctl --help

    # etcd 미설치시 설치
    sudo apt update
    sudo apt install etcd-client

    # 환경변수 설정
    export ETCDCTL_API=3

    # etcd pod에서 cert 옵션 확인
    kubectl describe pod etcd-controlplne -n kube-system

    # 또는 아래 명령어로도 cert 옵션 확인 가능
    ps -aux | grep -i etcd

    # etcd 백업
    etcdctl snapshot save /opt/etcd-backup.db \
    --cacert="내용" --cert="내용" --key="내용"
    ```

  + etcdctl 옵션 - etcd 프로세스 옵션 매칭
      * —cacert : —trusted-ca-file
      * —cert : —cert-file
      * —key : —key-file
        
    
2. Create a Pod called redis-storage with image: redis:alpine with a Volume of type emptyDir that lasts for the life of the Pod. Specs on the below
   
   - Pod named ‘redis-storage’ created
   - Pod ‘redis-storage’ uses Volume type of emptyDir
   - Pod ‘redis-storage’ uses volumeMount with mountPath = /data/redis

- Answer

    ```bash
    kubectl run redis-storage --image=redis:alpine --dry-run=client -o yaml > redis-storage.yaml

    vi redis-storage.yaml
    ```

    ```yaml
    # redis-storage.yaml

    apiVersion: v1
    kind: Pod
    metadata:
    name: redis-storage
    labels:
        run: redis-storage
    spec:
    containers:
    - name: redis-storage
        image: redis:alpine
        resources: {}
        volumeMounts:
        - name: redis-storage
        mountPath: /data/redis
    voluems:
    - name: redis-storage
        emptyDir: {} 
    ```
        
    
3. Create a new pod called super-user-pod with image busybox:1.28. Allow the pod to be able to set system system_time. The container should sleep for 4800 seconds.

   - Pod: super-user-pod
   - Container Image: busybox:1.28
   - SYS_TIME capabilities for the container?

- Answer
   
    ```bash
    kubectl run super-user-pod --image busybox:1.28 --dry-run=client -o yaml super-user-pod.yaml

    vi super-user-pod.yaml
    ```

    ```yaml
    # super-user-pod.yaml

    apiVersion: v1
    kind: Pod
    metadata:
        name: super-user-pod
        labels:
        run: super-user-pod
    spec:
        containers:
        - name: super-user-pod
        image: busybox:1.28
        commmand: ["sleep", "4800"]
        securityContext:
            capabilities:
            add: ["SYS_TIME"]
    ```
        

4. A pod definition file is created at /root/CKA/use-pv.yaml. Make use of this manifest file and mount the persistent volume called pv-1. Ensure the pod is running and the PV is bounded.

   - mountPath: /data
   - persistentVolumeClaim Name: my-pvc
   - persistentVolumeClaim configured correctly
   - pod using the correct moundPath
   - pod using persistent volume claim?

- Answer

    ```bash
    $ kubectl get pv
    NAME   CAPACITY   ACCESS MODES   RECLAIM POLICY   STATUS     ...
    pv-1   10Mi       RWO            Retain           Available  
    ```

    ```yaml
    # my-pvc.yaml

    apiVersion: v1
    kind: PersistentVolumeClaim
    metadata:
    name: my-pvc
    spec:
    resources:
    requests:
    storage: 10Mi
    accessModes:
    - ReadWriteOnce

    # use-pv.yaml

    apiVersion: v1
    kind: Pod
    metadata:
    name: use-pv
    labels:
    run: use-pv
    spec:
    containers:
    - name: use-pv
    image: nginx
    volumeMounts:
    - name: my-pvc
    mountPath: /data
    volumes:
    - name: my-pvc
    persistentVolumeClaim:
    claimName: my-pvc
    ```
        

5. Create a new development called nginx-deploy, with image nginx:1.16 and 1 replicas. Next upgrade the deployment to version 1.17 using rolling update.

   - Deployment: nginx-deploy
   - Image: nginx:1.16
   - Task: Upgrade the version of the deployment to 1.17
   - Task: Record the changes for the image upgrade

- Answer
        
    ```bash
    # deployment 배포
    kubectl create deployment nginx-deploy --image=nginx:1.16 --replicas=1
    
    # rolling update
    kubectl set image deployment nginx-deploy nginx=nginx:1.17 --record
    ```
        
    
6. Create a new user called john. Grant him access to the cluster. John should have permission to create, list, get, update and delete pods in the development namespace. The private key exists in the location: /root/CKA/john.key and csr at /root/CKA/john.csr.
   
    *Important Note: As of kubernetes 1.19, the CertificateSigningRequest object expects a signerName*

    - CSR: john-developer  Status: Approved
    - Role Name: developer, namespace: development, Resources: Pods
    - Access: User ‘john’ has appropriate permissions

- Answer
        
    ```bash
    # get encoded value of the CSR file
    cat /root/CKA/john.csr | base64 | tr -d "\n"
    ```

    ```bash
    # john-csr.yaml

    apiVersion: certificates.k8s.io/v1
    kind: CertificateSigningRequest
    metadata:
        name: john-developer
    spec:
        request: # encoded of the CSR file
        signerName: kubernetes.io/kube-apiserver-client
        usages:
        - client auth
    ```

    ```bash
    kubectl apply -f john-csr.yaml

    # get the list of CSRs
    kubectl get csr

    # Approve the CSR
    kubectl certificate approve john-developer

    # Create Role
    kubectl create role developer \
                    --verb=create --verb=list --verb=get --verb=update \
                    --verb=delete --resource=pods --n development

    # Create RoleBinding
    kubectl create rolebinding developer-binding-myuser \
            --role=developer --user=john -n development

    # Check
    kubectl -n development describe rolebinding developer-role-binding
    kubectl auth can-i update pods --namespace=development --as=john

    ```
        
    
7. Create a nginx pod called nginx-resolver using image nginx, expose it internally with a service called nginx-resolver-service. Test that you are able to look up the service and pod names from within the cluster. User the image: busybox:1.28 for dns lookup. Record results in /root/CKA/nginx.svc and /root/CKA/nginx.pod

   - Pod: nginx-resolver created
   - Service DNS Resolution recorded correctly
   - Pod DNS Resolution recorded correctly

- Answer
        
    ```bash
    # create a pod called nginx-resolver
    kubectl run nginx-resolver --image=nginx
    
    # expose the pod internally
    kubectl expose pod nginx-resolver \
                --name nginx-resolver-service --type=ClusterIP \
                --port=80 --target-port=80
    
    # create a pod test-nslookup and test nslookup
    # --rm : 실행이 끝나면 자동으로 pod 삭제
    # --restart=Never 을 같이 붙여줘야 정상 작동
    kubectl run test-nslookup --image=busybox:1.28 --restart=Never \
                --rm -it -- nslookup nginx-resolver-service \
                > /root/CKA/nginx.svc
    
    # pod를 검색할때는 POD_IP.default.pod 로 검색
    kubectl run test-nslookup --image=busybox:1.28 --restart=Never \
                --rm -it -- nslookup <POD-IP>.default.pod \
                > /root/CKA/nginx.pod
    ```
        
    
8. Create a static pod on node01 called nginx-critical with image nginx and make sure that it is recreated/restarted automatically in case of a failure.
    
    Use /etc/kubernetes/manifests as the Static Pod path for example.
    
   - static pod configured under /etc/kubernetes/manifests ?
   - Pod nginx-critical-node01 is up and running

- Answer
    
    ```bash
    kubectl run nginx-critical --image=nginx --dry-run=client -o yaml > nginx-critical.yaml
    
    scp nginx-critical.yaml node01:/root/
    
    ssh <IP of node01>
    
    cp /root/nginx-critical.yaml /etc/kubernetes/manifests/
    ```
        

## Mock Test 3

1. Create a new service account with the name `pvviewer`. Grant this Service account access to `list` all PersistentVolumes in the cluster by creating an appropriate cluster role called `pvviewer-role` and ClusterroleBinding called `pvviewer-role-binding`. 
    
    Next, create a pod called `pvviewer` with the image: redis and serviceAccount: `pvviewer` in the default namespace.
    
   - ServiceAccount: pvviewer
   - ClusterRole: pvviewer-role
   - ClusterRoleBinding: pvviewer-role-binding
   - Pod: pvviewer
   - Pod configured to user ServiceAccount pvviewer?
  
- Answer
        
    ```bash
    # create a service account
    kubectl create serviceaccount pvviewer

    # create a clusterRole
    kubectl create clusterrole pvviewer-role --verb=list --resource=pv

    # create a clusterRoleBinding
    kubectl create clusterrolebinding pvviewer-role-binding \
            --clusterrole=pvviewer-role --serviceaccount=default:pvviewer

    # create a pod called pvviewer
    kubectl run pvviewer --image=redis --dry-run=client -o yaml > pvviewer.yaml

    vi pvviewer.yaml
    ```

    ```yaml
    apiVersion: v1
    kind: Pod
    metadata:
        name: pvviewer
        labels:
        run: pvviewer
    spec:
        containers:
        - name: pvviewer
        image: redis
        serviceAccountName: pvviewer
    ```
        
    
2. List the InternalIP of all nodes of the cluster. Save the result to a file /root/CKA/node_ips.
    
    Answer should be in the format: `InternalIP of controlplane` <space> `InternalIP of node01` (in a single line)
    
- Answer
  
    ```bash
    kubectl get nodes -o jsonpath="{items[*].status.addresses[?(@.type=='InternalIP')].address}" > /root/CKA/nodes_ips
    ```
        
    
3. Create a pod called `multi-pod` with two containers.
    
    Container 1, name: `alpha`, image: `nginx`

    Container 2, name: `beta`, image: `busybox`, command: `sleep 4800`

    Environment Variables:

    container 1: `name: alpha`

    container 2: `name: beta`

    - Pod Name: multi-pod
    - Container 1: alpha
    - Container 2: beta
    - Container beta commands set correctly?
    - Container 1 Environment Value Set
    - Container 2 Environment Value Set

- Answer
        
    ```yaml
    # multi-pod.yaml

    apiVersion: v1
    kind: Pod
    metadata:
        name: multi-pod
    spec:
        containers:
        - name: alpha
        image: nginx
        env:
        - name: name
            value: alpha
        - name: beta
        image: busybox
        command: ["sleep", "4800"]
        env:
        - name: name
            value: beta   
    ```
        

4. Create a Pod called `non-root-pod`, image: `redis:alpine`
    
    runAsUser: 1000

    fsGroup: 2000

    - Pod non-root-pod fsGroup configured
    - Pod non-root-pod runAsUser configured
  
- Answer

    ```yaml
    # non-root-pod.yaml

    apiVersion: v1
    kind: Pod
    metadata:
        name: non-root-pod
    spec:
        containers:
        - image: redis:alpine
        name: non-root-pod
        securityContext:
        runAsUser: 1000
        fsGroup: 2000 
    ```
        
    
5. We have deployed a new pod called np-test-1 and a service called np-test-service. Incoming connections to this service are not working. Troubleshoot and fix it
    
    Create NetworkPolicy, by the name ingress-to-nptest that allows incoming connections to the service over port 80.

    Important: Don’t delete any current objects deployed.

    - Important: Don’t Alter Existing Objects!
    - NetworkPolicy: Applied to All sources (Incoming traffic from all pods) ?
    - NetworkPolicy: Correct Port?
    - NetworkPolicy: Applied to correct Pod?

- Answer
        
    ```yaml
    apiVersion: networking.k8s.io/v1
    kind: NetworkPolicy
    metadata:
        name: ingress-to-nptest
    spec:
        podSelector:
        matchLabels:
            run: np-test-1
        policyTypes:
        - Ingress
        ingress:
        - ports:
        - protocol: TCP
            port: 80
    ```
        
    
6. Taint the worker node node01 to be Unschedulable. Once done, create a pod called `dev-redis`, image `redis:alpine`, to ensure workloads are not scheduled to this worker node. Finally, create a new pod called `prod-redis` and image: `redis:alpine` with toleration to be scheduled on node01.
    
    key: `env_type`, value: `production`, operator: `Equal` and effect: `NoSchedule`

    - Key = env_type
    - Value = production
    - Effect - NoSchedule
    - pod ‘dev-redis’ (no tolerations) is not scheduled on node01 ?
    - Create a pod ‘prod-redis’ to run on node01

- Answer
        
    ```bash
    # taint node01
    kubectl taint node node01 env_type=production:NoSchedule

    # create a pod called dev-redis
    kubectl run dev-redis --image=redis:alpine

    # create a pod called prod-redis
    kubectl run prod-redis --image=redis:alpine --dry-run=client -o yaml > prod-redis.yaml
    ```

    ```yaml
    apiVersion: v1
    kind: Pod
    metadata:
        name: prod-redis
        labels:
        run: prod-redis
    spec:
        containers:
        - image: redis:alpine
        name: prod-redis
        tolerations:
        - key: "env_type"
        value: "production"
        effect: "NoSchedule"
        operator: "Equal"
    ```
        
7. Create a pod called `hr-pod` in hr namespace belonging to the `production` environment and `frontend` tier
    
    image: `redis:alpine`

    User appropriate labels and create all the required objects if it does not exist in the system already.

    - hr-pod labeled with environment production?
    - hr-pod labeled with tier fronted?

- Answer
   
    ```bash
    kubectl run hr-pod -n hr --image=redis:alpine --labels="environment=production,tier=frontend"
    ```
        

8. A kubeconfig file called super.kubeconfig has been created under /root/CKA. There is something wrong with the configuration. Troubleshoot and fix it.

    - Fix /root/CKA/super.kubeconfig

- Answer
   
   + Server 주소에서 port 번호 6443
        
    
9.  We have created a new deployment called nginx-deploy. Scale the deployment to 3 replicas. Has the replica’s increased? Troubleshoot the issue and fix it.

    - deployment has 3 replicas

- Answer
  
    ```bash
    kubectl get pods -A
    # 결과를 보면 controller 이름이 contro1ler으로 되어 있음
    # /etc/kubernetes/manifests 폴더에서 이름 수정하기

    kubectl scale deployment nginx-deploy --replicas=3
    ```