# [Udmey_CKA] #8 Network

> Udemy의 CKA with Practical Test 강의를 듣고 정리합니다.

## Network Basic

### Switching/Routing

- Switching: 같은 네트워크 대역에서 MAC 주소를 사용하여 데이터 전송
- Routing: 다른 네트워크 대역 사이에서 IP 주소를 사용하여 데이터 전송

### DNS

- DNS(Domain Name System)은 호스트의 도메인 이름을 호스트의 네트워크 주소로 바꾸거나 그 반대의 변환을 수행
- Linux 환경에서 DNS를 사용하는 방법은 /etc/hosts 파일에 DNS 정보를 저장하는 것이다. 시스템은 도메인 이름으로 IP를 검색할 때 이 파일을 가장 먼저 열어본다.
- 만약 host 파일에 원하는 DNS 정보가 없을 경우, 시스템은 /etc/resolv.conf 파일을 열어 도메인을 검색할 도메인 서버의 주소를 찾는다. 도메인 서버에서 원하는 DNS 레코드를 검색한다.

### CoreDNS

- CoreDNS는 CNCF에서 관리하는 프로젝트로, 쿠버네티스에서 사용을 권장하는 도메인 서버 서비스다.
- CoreDNS는 클러스터를 모니터링하며, 새로운 Service 또는 Pod이 추가되는 경우 도메인 서버에 이를 업데이트한다.

### Network Namespace

- 네트워크 네임스페이스는 네트워크 인터페이스, 라우팅, 방화벽 규칙 등을 격리한다.
- `veth`: 가상 이더넷 인터페이스(virtual ethernet interface)로, 항상 쌍으로 생성되어 연결된 상태를 유지하며, network namespace간 터널 역할을 한다.
- `ip link list` 를 입력하면 네트워크 인터페이스를 출력할 수 있다.
- `Bridge` : 네트워크를 segment 단위로 분할하여 네트워크 세그먼트 사이에서 트래픽을 전달하는 역할을 한다.

### CNI(Container Network Interface)

- Pod가 생성, 삭제될 때 호출되는 네트워크 API 의 구격과 인터페이스 정의
    - IPAM(IP Address Management): Pod 생성, 삭제 시 IP 주소 할당 및 해제
    - Network: Pod 생성, 삭제 시 네트워크 연결을 구현