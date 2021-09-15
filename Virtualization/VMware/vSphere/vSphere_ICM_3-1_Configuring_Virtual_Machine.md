# [vSphere] Configuring Virtual Machines

> vSphere Install, Configure, Manage [V7] Lecture Note <br>
> Module 3. Virtual Machines

이번 장은 VM 생성, 프로비저닝, 삭제 등에 관한 내용을 다루는데, 주로 실습 위주라서 필요한 것만 정리

## 가상 머신 프로비저닝 방법
- VMware Host Client 에서 생성
- vSphere Client 에서 생성
- vSphere Client를 사용해야만 하는 경우
    - VM 템플릿을 사용하여 새 VM을 생성하거나 복제할 때
    - OVF(Open VM Format)으로 VM을 배포할 때

## VMware Tools란?

VMware Tools란 VM의 게스트 OS의 성능을 향상시키기 위해 필요한 항목들의 집합으로, 아래 항목을 포함한다.

- Device drivers
    - SVGA display
    - VMXNET/VMXNET3
    - Balloon driver for memory management
    - Sync driver for quiescing I/O
- Increased graphics performance
- Improved mouse performance
- Guest OS heartbeat service
- Time synchronization
- Ability to shut down the VM

VNware Tools 없이도 게스트 OS가 동작은 하지만, 일부 기능에 제한이 있기 때문에 가급적 설치하는 것을 권장한다.

