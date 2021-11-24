# #1 Flutter Overview

## What is Flutter?

1. IOS와 Android를 동시에 개발할 수 있다.

    - App 개발에 대해 생각해보자. 한 명의 개발자가 IOS와 Android를 동시에 개발하는 것은 어렵다.
    - 같은 앱을 완전히 다른 방법으로 공부하고, 개발해서 IOS와 Andriod에 배포해야하며, 유지보수 또한 별도로 진행해야 한다.
  
2. 모든 스크린 사이즈에 배포할 수 있다.
    - 다양한 스크린 사이즈를 가진 기기에 동일한 앱을 배포할 때, 레이아웃에 대해 고민하지 않아도 된다.
    - 앱뿐만 아니라, 윈도우, 웹 등 모든 빈 화면이면 모두 flutter로 구현할 수 있다.

### Why Flutter?

- Flutter: one code base to maintain, one place to debug, and one place to update
    + language: Dart
- 스크린 사이즈가 커지면서 한 화면에 더 많은 것들을 담고 있다. 더 복잡하고, 좋은 화면을 만드는 것은 점점 더 어려워진다.
    + web에서부터 배우자. 웹은 화면이 작아지면 그에 맞게 화면이 최적화되고, 모바일 용, 태블릿 용, PC 용 등 스크린 사이즈에 따라 레이아웃이 쉽게 바뀐다.
- UI를 변경하는 것이 바로 반영된다. 빠르고 쉬운 확인!
- Flutter는 open-source로, 코드가 어떻게 구성되어 있는지 모두 확인할 수 있다.

## The Anatomy of a Flutter app

다음과 같이 UI들을 배치함으로써 화면을 직관적으로 구성할 수 있다.

- Scaffold
    - AppBar
    - Container
        - Column
            - Row
                - Text
                - Icon
            - Text
            - Image