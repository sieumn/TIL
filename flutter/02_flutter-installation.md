# #2 Flutter 설치하기

## Prerequisites for Flutter Development

- Android Apps
  + Mac or PC
  +  Android Studio
  +  Android Emulator or physical device

- iOS Apps
  + Mac
  + Android Studio
  + iOS Simulator or physical device

## Overview of the Process

- **If you have a PC**
    
    Outcome: You will be set up to develop Flutter apps for Android.
    
    **Steps:**
    
    1. Install the Flutter SDK
    2. Install Android Studio
    3. Install the Android Emulator
    
    [https://flutter.dev/docs/get-started/install/windows](https://flutter.dev/docs/get-started/install/windows)
    
- **If you have a Mac**
    
    Outcome: You will be set up to develop Flutter apps for both iOS and Android.
    
    **Steps**
    
    1. Install the Flutter SDK
    2. Install Android Studio
    3. Install the Android Emulator
    4. Install Xcode and command-line tools
    5. Test the iOS Simulator
    
    [https://flutter.dev/docs/get-started/install/macos](https://flutter.dev/docs/get-started/install/macos)
    
## Flutter - iOS에 배포하기 위한 환경 설정

- cocoapods 설치

  ```
  sudo gem install cocoapods
  ```

- Xcode 앱을 실행하고, Runner 설정 화면에서 Signing & Capabilities > Team 에서 Apple ID 계정을 추가한다.

  ![](images/2021-11-27-23-39-32.png)

- General > Identity > Bundle Identifier 에서 com.example 부분을 com.{@user_id} 로 변경한다.

## Hello World

- Flutter로 Andriod와 iOS에 각각 기본 앱을 띄워봤다.

    ![](images/2021-11-24-23-14-40.png)
