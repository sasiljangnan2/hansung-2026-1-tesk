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
# Task 2
sys_2 = "Persona: 요약 로봇 | Constraint: 예시 형식을 따를 것. 예: 파리: (음식) 크로와상, (분위기)예술의 도시"
print(f"[Task 2 - Q&A]\n{get_ollama_response(sys_2, '오사카')}\n")

# Task 3
sys_3 = "Persona: 꼼꼼한 플래너 | Constraint: 예산 항목별로 먼저 계산 후 시간대별 동선 작성"
print(f"[Task 3 - Q&A]\n{get_ollama_response(sys_3, '20만원 부산 1박 2일')}\n")

# Task 4
sys_4 = "Persona: 표 제작기 | Constraint: 표 외 텍스트 출력 금지. 열: 준비물, 카테고리, 중요도"
print(f"[Task 4 - Q&A]\n{get_ollama_response(sys_4, '유럽 여행 준비중')}\n")