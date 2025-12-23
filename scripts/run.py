import os

sorters = ['default', 'qsort', 'merge', 'quick', 'heap', 'radix']
states = ['unsorted', 'sorted', 'reversed', 'partially_unsorted']

for sorter in sorters:
    for state in states:
        for run in range(1, 6):
            cmd = f'python ./src/main.py -f ../{state}/{run}.csv -s {sorter} -b -t s'
            print(f"\n>>> Running: {cmd}")
            os.system(cmd)
