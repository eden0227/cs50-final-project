#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define INSERTION_THRESHOLD 8
#define D 4

void test_sort(char *name, void (*func)(int *, int), int *num, int len);
void display_numbers(int *num, int len);
void compare_array(int *num, int len);
void shuffle_array(int *num, int len);
void bubble_sort(int *num, int len);
void swap(int *a, int *b);
void selection_sort(int *num, int len);
void insertion_sort(int *num, int len);
void merge_sort(int *num, int len);
void merge_sort_helper(int *num, int left, int right, int *temp);
void insertion_sort_helper(int *num, int left, int right);
void quick_sort(int *num, int len);
void quick_sort_helper(int *num, int low, int high);
void heap_sort(int *num, int len);
void heap_sort_helper(int *num, int len, int parent);
void radix_sort(int *num, int len);

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int num[] = {30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
                 20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
                 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int len = sizeof(num) / sizeof(num[0]);

    test_sort("Bubble Sort", bubble_sort, num, len);
    test_sort("Selection Sort", selection_sort, num, len);
    test_sort("Insertion Sort", insertion_sort, num, len);
    test_sort("Merge Sort", merge_sort, num, len);
    test_sort("Quick Sort", quick_sort, num, len);
    test_sort("Heap Sort", heap_sort, num, len);
    test_sort("Radix Sort", radix_sort, num, len);

    return 0;
}

void test_sort(char *name, void (*func)(int *, int), int *num, int len)
{
    printf("%s:\n", name);
    display_numbers(num, len);
    func(num, len);
    printf("Result:\n");
    display_numbers(num, len);
    compare_array(num, len);
    shuffle_array(num, len);
    printf("\n");
}

void display_numbers(int *num, int len)
{
    for (int i = 0; i < len; i++)
        printf("%i ", num[i]);
    printf("\n");
}

void compare_array(int *num, int len)
{
    int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                    21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
    for (int i = 0; i < len; i++)
    {
        if (num[i] != sorted[i])
        {
            printf("Not Sorted\n");
            return;
        }
    }
    printf("Sorted!\n");
}

void shuffle_array(int *num, int len)
{
    for (int i = len - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = num[i];
        num[i] = num[j];
        num[j] = temp;
    }
}

void bubble_sort(int *num, int len)
{
    if (len < 2)
        return;

    for (int i = 0; i < len - 1; i++)
    {
        int swapped = 0;
        for (int j = 0; j < len - i - 1; j++)
        {
            if (num[j] > num[j + 1])
            {
                swap(&num[j], &num[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int *num, int len)
{
    if (len < 2)
        return;

    for (int i = 0; i < len - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < len; j++)
        {
            if (num[j] < num[min])
                min = j;
        }
        if (min != i)
            swap(&num[i], &num[min]);
    }
}

void insertion_sort(int *num, int len)
{
    if (len < 2)
        return;

    for (int i = 1; i < len; i++)
    {
        int key = num[i];
        int j = i - 1;
        while (j >= 0 && num[j] > key)
        {
            num[j + 1] = num[j];
            j--;
        }
        num[j + 1] = key;
    }
}

void merge_sort(int *num, int len)
{
    if (len < 2)
        return;

    int *temp = malloc(len * sizeof(int));
    if (temp == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    merge_sort_helper(num, 0, len - 1, temp);
    free(temp);
}

void merge_sort_helper(int *num, int left, int right, int *temp)
{
    if (left >= right)
        return;

    if (right - left < INSERTION_THRESHOLD)
    {
        insertion_sort_helper(num, left, right);
        return;
    }

    int mid = left + (right - left) / 2;

    merge_sort_helper(num, left, mid, temp);
    merge_sort_helper(num, mid + 1, right, temp);

    if (num[mid] <= num[mid + 1])
        return;

    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
        temp[k++] = num[i] <= num[j] ? num[i++] : num[j++];
    while (i <= mid)
        temp[k++] = num[i++];
    while (j <= right)
        temp[k++] = num[j++];

    memcpy(num + left, temp, k * sizeof(int));
}

void insertion_sort_helper(int *num, int left, int right)
{
    if (right - left < 1)
        return;

    for (int i = left + 1; i <= right; i++)
    {
        int key = num[i];
        int j = i - 1;
        while (j >= left && num[j] > key)
        {
            num[j + 1] = num[j];
            j--;
        }
        num[j + 1] = key;
    }
}

void quick_sort(int *num, int len)
{
    if (len < 2)
        return;

    quick_sort_helper(num, 0, len - 1);
}

void quick_sort_helper(int *num, int low, int high)
{
    if (high - low < INSERTION_THRESHOLD)
    {
        insertion_sort_helper(num, low, high);
        return;
    }

    while (low < high)
    {
        int mid = (low + high) / 2;
        if (num[high] < num[low])
            swap(&num[high], &num[low]);
        if (num[mid] < num[low])
            swap(&num[mid], &num[low]);
        if (num[high] < num[mid])
            swap(&num[high], &num[mid]);

        int pivot = num[mid];
        int i = low - 1;
        int j = high + 1;

        while (1)
        {
            do
                i++;
            while (num[i] < pivot);

            do
                j--;
            while (num[j] > pivot);

            if (i >= j)
                break;

            swap(&num[i], &num[j]);
        }

        if (j - low < high - j)
        {
            quick_sort_helper(num, low, j);
            low = j + 1;
        }
        else
        {
            quick_sort_helper(num, j + 1, high);
            high = j;
        }
    }
}

void heap_sort(int *num, int len)
{
    if (len < 2)
        return;

    if (len <= INSERTION_THRESHOLD)
    {
        insertion_sort_helper(num, 0, len - 1);
        return;
    }

    for (int i = (len - 2) / D; i >= 0; i--)
        heap_sort_helper(num, len, i);

    for (int i = len - 1; i >= 0; i--)
    {
        swap(&num[0], &num[i]);

        if (i < INSERTION_THRESHOLD)
        {
            insertion_sort_helper(num, 0, i);
            break;
        }

        heap_sort_helper(num, i, 0);
    }
}

void heap_sort_helper(int *num, int len, int parent)
{
    while (1)
    {
        int largest = parent;

        for (int k = 0; k < D; k++)
        {
            int child = D * parent + (k + 1);
            if (child < len && num[child] > num[largest])
                largest = child;
        }

        if (largest == parent)
            break;

        swap(&num[largest], &num[parent]);
        parent = largest;
    }
}

void radix_sort(int *num, int len)
{
    if (len < 2)
        return;

    if (len <= INSERTION_THRESHOLD)
    {
        insertion_sort_helper(num, 0, len - 1);
        return;
    }

    int bucket_count[10];
    int *temp = malloc(len * sizeof(int));
    if (temp == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int divisor = 1;
    int largest = num[0];

    for (int i = 1; i < len; i++)
    {
        if (num[i] > largest)
            largest = num[i];
    }

    while (largest / divisor > 0)
    {
        memset(bucket_count, 0, sizeof(bucket_count));

        for (int i = 0; i < len; i++)
        {
            int digit = (num[i] / divisor) % 10;
            bucket_count[digit]++;
        }

        for (int i = 1; i < 10; i++)
            bucket_count[i] += bucket_count[i - 1];

        for (int i = len - 1; i >= 0; i--)
        {
            int digit = (num[i] / divisor) % 10;
            temp[--bucket_count[digit]] = num[i];
        }

        memcpy(num, temp, len * sizeof(int));
        divisor *= 10;
    }

    free(temp);
}
