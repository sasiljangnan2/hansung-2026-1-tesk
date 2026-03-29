import pandas as pd

df = pd.read_csv("데이터마이닝/학생건강검사.csv", encoding='cp949')

# DataFrame을 리스트로 변환
a = df.values.tolist()

print(a[0])  # 0행 데이터 확인
print(a[1])  # 1행 데이터 확인
print(a[2])  # 2행 데이터 확인

print("총 행의 수는", len(a))

count=0
for i in range(len(a)):
    if a[i][1] == '초':
        count+=1

print("초등학생의 총 인원수는", count)

