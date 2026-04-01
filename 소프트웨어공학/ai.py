import ollama

# 단발 생성
response = ollama.generate(
    model='qwen2.5',
    prompt='파이썬으로 피보나치 수열을 출력하는 함수를 작성해줘'
)

print(response['response'])
