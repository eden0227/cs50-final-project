import csv
import sys


def main():
    if len(sys.argv) != 2:
        print('Usage: python main.py output.csv')
        sys.exit(1)

    if not sys.argv[1].endswith('.csv'):
        print('Usage: Data must be a CSV file')
        sys.exit(2)

    filename = sys.argv[1]
    with open(filename, 'w', newline='') as file:
        writer = csv.DictWriter(file, fieldnames=["key", "value"])
        writer.writeheader()
        for i in range(30, 0, -1):
            writer.writerow({"key": 'a', "value": i})

    rows = []
    with open(filename, 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)

    for row in rows:
        print(f'{row['key']}, {row['value']}')


if __name__ == "__main__":
    main()
