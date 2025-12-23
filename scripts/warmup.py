import os

for run in range(1, 6):
    cmd = f'python ./src/main.py -f ../warmup/{run}.csv -s merge -b -t s'
    print(f"\n>>> Running: {cmd}")
    os.system(cmd)
