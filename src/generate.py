import argparse
import csv
import random


def generate_rows(length, state):
    values = [random.randint(1, length) for _ in range(length)]

    if state == "unsorted":
        pass

    elif state == "sorted":
        values.sort()

    elif state == "reversed":
        values.sort(reverse=True)

    elif state == "partially_unsorted":
        split = int(length * 0.85)
        values[:split] = sorted(values[:split])
        random.shuffle(values[split:])
    
    value_count = {}
    for value in values:
        count = value_count.get(value, 0) + 1;
        value_count[value] = count

        key = f"{1000 + count}"
        yield key, value


def write_csv(filename, rows):
    with open(filename, 'w', newline='') as file:
        writer = csv.DictWriter(file, fieldnames=["key", "value"])
        writer.writeheader()

        for key, value in rows:
            writer.writerow({"key": key, "value": value})


def main():
    parser = argparse.ArgumentParser(
        description='Generate CSV file with stable key ordering for duplicate values'
    )

    parser.add_argument(
        '--length',
        type=int,
        required=True,
        choices=[10000, 250000, 1000000, 10000000],
        help='Number of rows to generate'
    )
    parser.add_argument(
        '--state',
        type=str,
        required=True,
        choices=['unsorted', 'sorted', 'reversed', 'partially_unsorted'],
        help='Data ordering state'
    )
    parser.add_argument(
        '--output',
        type=str,
        default='./tests/data.csv',
        help='Output CSV filename'
    )

    args = parser.parse_args()
    rows = generate_rows(args.length, args.state)
    write_csv(args.output, rows)


if __name__ == "__main__":
    main()
