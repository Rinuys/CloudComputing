import random
import matplotlib.pyplot as plt

# 몬테카를로 계산을 반복할 횟수
loop = 30000000


inside=0
for _ in range(loop):
    a,b=random.random(), random.random()
    inside += 1 if ( (a*a) + (b*b) ) < 1.0 else 0

print( (inside*4.0)/loop )