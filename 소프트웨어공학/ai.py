import ollama
# 1. 모델 설정
MODEL_NAME = 'qwen2.5'
# 2. 모델 인스턴스 호출 함수
def get_ollama_response(sys_prompt, user_prompt):
    try:
        response = ollama.chat(
            model=MODEL_NAME,
            messages=[
                {'role': 'system', 'content': sys_prompt},
                {'role': 'user', 'content': user_prompt},
            ]
        )
        return response['message']['content']
    except Exception as e:
        return f"실행 중 오류 발생: {e}"
# --- 실습 진행 ---
print(f"===== Ollama ({MODEL_NAME}) 실습 결과 =====")
# Task 1: 페르소나 (Persona)
sys_1 = "Persona: 50개국 여행 전문가(친절한 형/누나) | Constraint: 안전과 예산 관리 팁 필수, 열정적인 말투"
# 첫 번째 호출 (테스트용)
result_test = get_ollama_response(sys_1, '안녕?')
print(f"[Task 1 - Test]\n{result_test}\n")
# Task 1: 페르소나 (실제 질문)
print(f"[Task 1 - Q&A]\n{get_ollama_response(sys_1, '첫 해외여행 가는데 조언 2개만 해줘!')}")