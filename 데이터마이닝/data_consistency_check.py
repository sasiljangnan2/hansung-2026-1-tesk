import pandas as pd
import numpy as np

# CSV 파일 읽기
file_path = 'Teen_Mental_Health_Dataset (1).csv'
df = pd.read_csv(file_path)

print("=" * 80)
print("데이터셋 일관성 검사 리포트")
print("=" * 80)

# 1. 기본 정보
print("\n[1] 기본 정보")
print(f"행 개수: {df.shape[0]}")
print(f"열 개수: {df.shape[1]}")
print(f"\n컬럼명: {list(df.columns)}")

# 2. 데이터 타입
print("\n[2] 데이터 타입")
print(df.dtypes)

# 3. 결측값 검사
print("\n[3] 결측값 검사")
missing_data = df.isnull().sum()
if missing_data.sum() == 0:
    print("✓ 결측값 없음")
else:
    print(f"⚠ 결측값 있음:\n{missing_data[missing_data > 0]}")

# 4. 수치형 컬럼 범위 검사
print("\n[4] 수치형 컬럼 범위 검사")
numeric_cols = ['age', 'daily_social_media_hours', 'sleep_hours', 'screen_time_before_sleep', 
                'academic_performance', 'physical_activity', 'stress_level', 'anxiety_level', 'addiction_level']

for col in numeric_cols:
    if col in df.columns:
        min_val = df[col].min()
        max_val = df[col].max()
        print(f"\n{col}:")
        print(f"  범위: {min_val} ~ {max_val}")
        
        # 이상치 감지
        issues = []
        if col == 'age' and (min_val < 13 or max_val > 19):
            issues.append(f"⚠ 나이 범위 이상: {min_val}~{max_val} (13~19 예상)")
        elif col == 'sleep_hours' and (min_val < 0 or max_val > 12):
            issues.append(f"⚠ 수면 시간 이상: {min_val}~{max_val} (0~12 예상)")
        elif col == 'daily_social_media_hours' and (min_val < 0 or max_val > 24):
            issues.append(f"⚠ SNS 사용 시간 이상: {min_val}~{max_val} (0~24 예상)")
        elif col == 'screen_time_before_sleep' and (min_val < 0 or max_val > 10):
            issues.append(f"⚠ 수면 전 화면 시간 이상: {min_val}~{max_val} (0~10 예상)")
        elif col in ['academic_performance', 'physical_activity'] and (min_val < 0 or max_val > 5):
            issues.append(f"⚠ {col} 범위 이상: {min_val}~{max_val} (0~5 예상)")
        elif col in ['stress_level', 'anxiety_level', 'addiction_level'] and (min_val < 0 or max_val > 10):
            issues.append(f"⚠ {col} 범위 이상: {min_val}~{max_val} (0~10 예상)")
        
        if issues:
            for issue in issues:
                print(f"  {issue}")
        else:
            print(f"  ✓ 범위 정상")

# 5. 범주형 컬럼 검사
print("\n[5] 범주형 컬럼 검사")

categorical_cols = {
    'gender': ['male', 'female'],
    'platform_usage': ['Instagram', 'TikTok', 'Both'],
    'social_interaction_level': ['low', 'medium', 'high'],
    'depression_label': [0, 1]
}

for col, expected_values in categorical_cols.items():
    if col in df.columns:
        unique_vals = df[col].unique()
        print(f"\n{col}:")
        print(f"  고유값: {sorted(unique_vals)}")
        
        # 예상값과 비교
        unexpected = set(unique_vals) - set(expected_values)
        if unexpected:
            print(f"  ⚠ 예상치 못한 값: {unexpected}")
        else:
            print(f"  ✓ 모든 값 유효함")
        
        print(f"  개수: {df[col].value_counts().to_dict()}")

# 6. 중복행 검사
print("\n[6] 중복행 검사")
duplicate_rows = df.duplicated().sum()
if duplicate_rows == 0:
    print("✓ 중복 행 없음")
else:
    print(f"⚠ 중복 행: {duplicate_rows}개")
    print("\n중복 행 상세:")
    print(df[df.duplicated(keep=False)].sort_values(by=list(df.columns)))

# 7. 논리적 일관성 검사
print("\n[7] 논리적 일관성 검사")

# SNS 사용 시간과 화면 시간 검사
sns_gt_screen = (df['daily_social_media_hours'] < df['screen_time_before_sleep']).sum()
if sns_gt_screen > 0:
    print(f"⚠ SNS 사용 시간 < 수면 전 화면 시간: {sns_gt_screen}개 행")
    print(df[df['daily_social_media_hours'] < df['screen_time_before_sleep']][['daily_social_media_hours', 'screen_time_before_sleep']].head())
else:
    print("✓ SNS 사용 시간과 수면 전 화면 시간 일관성 정상")

# 스트레스/불안/중독 레벨 검사 (높으면 depression_label=1일 가능성)
print("\n[8] 통계 요약")
print(df.describe())

# 결론
print("\n" + "=" * 80)
print("검사 완료")
print("=" * 80)
