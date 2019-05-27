import random

# 몬테카를로 계산을 반복할 횟수
loop = 10**7


inside=0
for _ in range(loop):
    a,b=random.random(), random.random()
    inside += 1 if ( (a*a) + (b*b) ) < 1.0 else 0
print( (inside*4.0)/loop )