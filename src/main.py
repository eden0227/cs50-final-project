import argparse
import csv
import ctypes
import time


dll_path = r'C:\Users\USER\Desktop\cs50-final-project\src\program.dll'
lib = ctypes.CDLL(dll_path)

class KeyValuePair(ctypes.Structure):
    _fields_ = [("key", ctypes.c_char_p),
                ("value", ctypes.c_int)]

argtypes = [ctypes.POINTER(KeyValuePair), ctypes.c_int]
restype = None

for func_name in ('c_qsort', 'merge_sort', 'quick_sort', 'heap_sort', 'radix_sort'):
    getattr(lib, func_name).argtypes = argtypes
    getattr(lib, func_name).restype = restype


def sort_key(row):
    sort_column = 1
    if sort_column < len(row):
        try:
            return float(row[sort_column])
        except ValueError:
            return row[sort_column]
    return ""


def default_sorted(data_rows):
    start = time.perf_counter_ns()
    sorted_rows = sorted(data_rows, key=sort_key)
    end = time.perf_counter_ns()
    return sorted_rows, start, end


def c_sorted(data_rows, sorter):
    start = time.perf_counter_ns()
    length = len(data_rows)
    c_array = (KeyValuePair * length)()
    for i, (key, value) in enumerate(data_rows):
        c_array[i].key = key.encode('utf-8')
        c_array[i].value = int(value)

    c_start = time.perf_counter_ns()
    if sorter == 'qsort':
        lib.c_qsort(c_array, length)
    elif sorter == 'merge':
        lib.merge_sort(c_array, length)
    elif sorter == 'quick':
        lib.quick_sort(c_array, length)
    elif sorter == 'heap':
        lib.heap_sort(c_array, length)
    elif sorter == 'radix':
        lib.radix_sort(c_array, length)
    c_end = time.perf_counter_ns()

    sorted_rows = []
    for i in range(length):
        value = c_array[i].value
        c_pointer = c_array[i].key
        if c_pointer:
            try:
                c_string_bytes = ctypes.string_at(c_pointer)
                key = c_string_bytes.decode('utf-8')
            except:
                key = f'key_{i}'
        else:
            key = f'key_{i}'
        sorted_rows.append([key, value])

    end = time.perf_counter_ns()
    return sorted_rows, start, end, c_start, c_end


def check_rows_header(rows, has_header):
    if has_header and rows:
        return rows[0], rows[1:]
    else:
        return None, rows


def get_time_multiplier(time):
    if time == 's':
        return 1e9
    elif time == 'ms':
        return 1e6


def check_stability(rows):
    for (id1, val1), (id2, val2) in zip(rows[1:], rows[2:]):
        if val1 == val2 and id1 > id2:
            return False
    return True


def main():
    parser = argparse.ArgumentParser(
        description='Python CLI with Integrated C Sorting Algorithms for Practical, Large-Scale Data and Performance Benchmarking'
    )
    parser.add_argument(
        '-f',
        '--file',
        type=str,
        required=True,
        help='Select data file (.csv)'
    )
    parser.add_argument(
        '-s',
        '--sorter',
        choices=['default', 'qsort', 'merge', 'quick', 'heap', 'radix'],
        default='default',
        help='Select sorting algorithm'
    )
    parser.add_argument(
        '-b',
        '--benchmark',
        action='store_true',
        help='Enable benchmarking'
    )
    parser.add_argument(
        '-t',
        '--time',
        choices=['s', 'ms'],
        default='ms',
        help='Select time unit'
    )
    args = parser.parse_args()


    with open(args.file, 'r', newline='') as file:
        reader = csv.reader(file)
        rows = list(reader)
    header, data_rows = check_rows_header(rows, True)


    if args.sorter == 'default':
        print('sorted')
        sorted_rows, start, end = default_sorted(data_rows)

    elif args.sorter == 'qsort':
        print('qsort')
        sorted_rows, start, end, c_start, c_end = c_sorted(data_rows, args.sorter)

    elif args.sorter == 'merge':
        print('merge')
        sorted_rows, start, end, c_start, c_end = c_sorted(data_rows, args.sorter)

    elif args.sorter == 'quick':
        print('quick')
        sorted_rows, start, end, c_start, c_end = c_sorted(data_rows, args.sorter)
    
    elif args.sorter == 'heap':
        print('heap')
        sorted_rows, start, end, c_start, c_end = c_sorted(data_rows, args.sorter)
    
    elif args.sorter == 'radix':
        print('radix')
        sorted_rows, start, end, c_start, c_end = c_sorted(data_rows, args.sorter)


    output_file = args.file.replace('.csv', '_sorted.csv')
    with open(output_file, 'w', newline='') as file:
        writer = csv.writer(file)
        if header:
            writer.writerow(header)
        writer.writerows(sorted_rows)


    if args.benchmark:
        ns_conversion = get_time_multiplier(args.time)
        stable = check_stability(sorted_rows)

        print(f"{(end - start) / ns_conversion:.4f}{args.time}")
        if args.sorter != 'default':
            print(f"{(c_end - c_start) / ns_conversion:.4f}{args.time}")
        if stable:
            print('stable')
        else:
            print('not stable')


if __name__ == "__main__":
    main()
