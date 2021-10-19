# [Git] GitHub 원격 저장소에서 .pyc 파일 모두 지우기

다음과 같이 remove, commit, push 과정을 진행하면 된다.

```vim
git rm -f "*.pyc"
git commit -a -m "all pyc files removed"
git push
```

그리고 로컬 저장소에 있는 .gitignore 파일 가장 아래에 `*.pyc`를 추가해 두자. 그러면 git에서 .pyc 확장자를 가진 파일들을 무시하여 원격 저장소에 저장하지 않는다.