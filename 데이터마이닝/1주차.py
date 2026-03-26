import pandas as pd
import numpy as np

df = pd.read_csv("학생건강검사.csv", encoding='cp949')
a = df.values.tolist()
#불리언 마스크로  고등학생 남학생과 여학생을 추출한 후, 학년별로 평균 키를 계산하여 출력
man = np.array(a)[(np.array(a)[:, 3] == '남') & (np.array(a)[:, 1] == '고')] # 남학생 , 고등학생 추출
woman = np.array(a)[(np.array(a)[:, 3] == '여') & (np.array(a)[:, 1] == '고')] # 여학생 , 고등학생 추출

for i in range(1, 4): # 1학년부터 3학년까지 반복
    # 학년별로 남학생과 여학생을 추출하여 평균 키 계산
    grade_man = man[man[:, 2].__eq__(str(i))] #연산자 오버로딩 연습
    grade_woman = woman[woman[:, 2].__eq__(str(i))]
    # 4번째 열을 추출
    m_heights = grade_man[:, 4].astype(float)
    w_heights = grade_woman[:, 4].astype(float)
    print(f"고등학생 {i}학년 남학생 평균 키: {m_heights.mean():.2f}cm")
    print(f"고등학생 {i}학년 여학생 평균 키: {w_heights.mean():.2f}cm")  
print("고등학생 남학생은 평균 키가 학년별로 증가하지만, 여학생은 증가 폭이 매우 작습니다. ")
print("남학생은 아직 성장이 진행중이지만, 여학생은 이미 성장이 거의 완료된 상태로 보입니다. ")