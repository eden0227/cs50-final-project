import argparse
import csv
import ctypes

dll_path = r'C:\Users\USER\Desktop\cs50-final-project\src\program.dll'
lib = ctypes.CDLL(dll_path)

class KeyValuePair(ctypes.Structure):
    _fields_ = [("key", ctypes.c_char_p),
                ("value", ctypes.c_int)]

lib.sort_by_value.argtypes = [ctypes.POINTER(KeyValuePair), ctypes.c_int]

def is_stable(rows):
    for (id1, val1), (id2, val2) in zip(rows[1:], rows[2:]):
        if val1 == val2 and id1 > id2:
            return False
    return True

def main():
    parser = argparse.ArgumentParser(
        description='Python controller for sorting CSV data file with integrated C sorting algorithms'
    )

    parser.add_argument(
        '-f',
        '--file',
        type=str,
        required=True,
        help='CSV data file to sort'
    )
    parser.add_argument(
        '-s',
        '--sorter',
        choices=['default', 'merge', 'radix'],
        default='default',
        help='Sorting algorithm to choose'
    )
    parser.add_argument(
        '-b',
        '--benchmark',
        action='store_true',
        help='Enable benchmarking'
    )

    args = parser.parse_args()
    
    with open(args.file, 'r', newline='') as file:
        reader = csv.reader(file)
        rows = list(reader)

    sort_column = 1
    has_header = True

    header = None
    if has_header and rows:
        header = rows[0]
        data_rows = rows[1:]
    else:
        data_rows = rows

    def sort_key(row):
        if sort_column < len(row):
            try:
                return float(row[sort_column])
            except ValueError:
                return row[sort_column]
        return ""
    
    if args.sorter == 'default':
        print('qsort')

        length = len(data_rows)
        c_array = (KeyValuePair * length)()

        for i, (key, value) in enumerate(data_rows):
            c_array[i].key = key.encode('utf-8')
            c_array[i].value = int(value)

        lib.sort_by_value(c_array, length)
    
        sorted_rows = []
        for i in range(length):
            key_bytes = None
            if c_array[i].key:
                try:
                    key_bytes = ctypes.string_at(c_array[i].key)
                    key = key_bytes.decode('utf-8')
                except:
                    key = f'key_{i}'
            else:
                key = f'key_{i}'

            value = c_array[i].value
            sorted_rows.append([key, value])

    elif args.sorter == 'merge':
        print('Merge')
        sorted_rows = sorted(data_rows, key=sort_key)
    elif args.sorter == 'radix':
        print('Radix')
        sorted_rows = sorted(data_rows, key=sort_key)

    output_file = args.file.replace('.csv', '_sorted.csv')
    with open(output_file, 'w', newline='') as file:
        writer = csv.writer(file)
        if header:
            writer.writerow(header)
        writer.writerows(sorted_rows)
        stable = is_stable(sorted_rows)

    if args.benchmark:
        if stable:
            print('Stable')
        else:
            print('Not stable')


if __name__ == "__main__":
    main()
