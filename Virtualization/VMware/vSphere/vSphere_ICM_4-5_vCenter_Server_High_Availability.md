# [vSphere] vCenter Server High Availability

> vSphere Install, Configure, Manage [V7] Lecture Note
> Module 4. vCenter Server

## vCenter Server HA 유지의 중요성

vCenter Server에 연결되어 있는 솔루션이 많기 때문에, 특히 vCenter Server의 고가용성을 유지하는 것은 매우 중요하다.

![](images/2021-09-14-13-30-21.png)

## vCenter Server High Availavility

 vCenter HA는 장애로부터 vCenter Server를 보호하기 위해 세 개의 노드 클러스터를 구성한다.
 - Active node
 - Passive node
 - Witness node

![](images/2021-09-14-13-31-19.png)


## 장애 시나리오

### 시나리오 1. Active Node 실패

 Active node가 실패하면 Passive node가 작동한다.

### 시나리오 2. Passive Node 실패

 Passive node가 실패하면 active node가 정상적으로 작동하지만 성능 저하 경고가 표시된다.

### 시나리오 3. Witness Node 실패

 Witness node가 ㅏ실패하면 활성 노드가 정상적으로 작동하나, 클러스터 성능이 저하된 상태로 실행되는 것으로 간주된다.

### 시나리오 4. Passive node & Witness Node 모두 실패

 세 개 중 두 개가 장애 나면, read-only 작업만 진행할 수 있다.

## vCenter Server HA의 장점

- 무료다. 추가 License 구입하지 않더라도 사용할 수 있는 vCenter 기본 기능
- 하드웨어, 호스트 및 애플리케이션 장애에 대한 보호 기능이 제공된다.

## vCenter Server HA 설정 방법

 vCenter Server > Configure > vCenter HA 에서 설정 가능하다.

 HA 구성하려면 반드시 해당 vCenter Server가 가진 NIC가 두 개 이상이어야 한다. (Replication용 네트워크 별도 구성)

![](images/2021-09-14-13-38-20.png)