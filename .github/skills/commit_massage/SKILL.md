# Commit Message Generator

Conventional Commits 형식의 Git 커밋 메시지를 생성합니다.
일관성 있는 커밋 히스토리는 코드 리뷰와 이슈 추적을 쉽게 해줍니다.

## 출력 형식

항상 다음 형식을 따릅니다:

```
<type>(<scope>): <subject>

[선택: 본문 – 변경 이유나 주요 내용]
[선택: footer – 이슈 번호, BREAKING CHANGE 등]
```

## type 목록

| type     | 사용 상황                              |
|----------|----------------------------------------|
| feat     | 새로운 기능 추가                        |
| fix      | 버그 수정                              |
| docs     | 문서만 변경                            |
| refactor | 기능 변화 없는 코드 구조 개선          |
| test     | 테스트 추가/수정                        |
| chore    | 빌드 설정, 패키지 업데이트 등 잡무     |
| style    | 포맷, 공백 등 코드 동작 무관한 변경    |
| perf     | 성능 개선                              |

## subject 작성 규칙

- 50자 이내로 작성 (GitHub에서 잘리지 않도록)
- 영어로 작성, 동사 원형으로 시작 (add, fix, update, remove…)
- 마침표 없이 끝냄
- 명령형으로 작성: "Added X" ❌ → "add X" ✅

## 작업 순서

1. 제공된 git diff 또는 설명을 분석해 변경의 핵심을 파악한다
2. 변경 유형에 맞는 type을 선택한다
3. scope는 변경된 모듈/컴포넌트를 나타낸다 (명확하지 않으면 생략)
4. subject를 50자 이내 영어 명령형으로 작성한다
5. 변경 이유가 subject만으로 불충분하면 본문(body)을 추가한다
6. Breaking change나 이슈 참조가 있으면 footer에 추가한다

## 예시

```
feat(auth): add JWT refresh token support

Implements silent token refresh to prevent session expiry.
```

```
fix(api): handle null response from payment gateway
```

## 주의사항

- 여러 독립적인 변경이 섞여 있으면 가장 중요한 하나를 선택하거나, 분리 커밋을 제안한다
- 변경 내용이 불명확하면 추가 설명을 요청한다