#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define INSERTION_THRESHOLD 8
#define D 4
#define BITS 32

void test_sort(char *name, void (*func)(int *, int), int *arr, int len);
void display_numbers(int *arr, int len);
void compare_array(int *arr, int len);
void shuffle_array(int *arr, int len);
void bubble_sort(int *arr, int len);
void swap(int *a, int *b);
void selection_sort(int *arr, int len);
void insertion_sort(int *arr, int len);
void merge_sort(int *arr, int len);
void merge_sort_helper(int *arr, int left, int right, int *temp);
void insertion_sort_helper(int *arr, int left, int right);
void quick_sort(int *arr, int len);
void quick_sort_helper(int *arr, int low, int high);
void heap_sort(int *arr, int len);
void heap_sort_helper(int *arr, int len, int parent);
void radix_sort(int *arr, int len);

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int arr[] = {30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
                 20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
                 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int len = sizeof(arr) / sizeof(arr[0]);

    test_sort("Bubble Sort", bubble_sort, arr, len);
    test_sort("Selection Sort", selection_sort, arr, len);
    test_sort("Insertion Sort", insertion_sort, arr, len);
    test_sort("Merge Sort", merge_sort, arr, len);
    test_sort("Quick Sort", quick_sort, arr, len);
    test_sort("Heap Sort", heap_sort, arr, len);
    test_sort("Radix Sort", radix_sort, arr, len);

    return 0;
}

void test_sort(char *name, void (*func)(int *, int), int *arr, int len)
{
    printf("%s:\n", name);
    display_numbers(arr, len);
    func(arr, len);
    printf("Result:\n");
    display_numbers(arr, len);
    compare_array(arr, len);
    shuffle_array(arr, len);
    printf("\n");
}

void display_numbers(int *arr, int len)
{
    for (int i = 0; i < len; i++)
        printf("%i ", arr[i]);
    printf("\n");
}

void compare_array(int *arr, int len)
{
    int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                    21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
    for (int i = 0; i < len; i++)
    {
        if (arr[i] != sorted[i])
        {
            printf("Not Sorted\n");
            return;
        }
    }
    printf("Sorted!\n");
}

void shuffle_array(int *arr, int len)
{
    for (int i = len - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void bubble_sort(int *arr, int len)
{
    if (len < 2)
        return;

    for (int i = 0; i < len - 1; i++)
    {
        int swapped = 0;
        for (int j = 0; j < len - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
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

void selection_sort(int *arr, int len)
{
    if (len < 2)
        return;

    for (int i = 0; i < len - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }
        if (min != i)
            swap(&arr[i], &arr[min]);
    }
}

void insertion_sort(int *arr, int len)
{
    if (len < 2)
        return;

    for (int i = 1; i < len; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge_sort(int *arr, int len)
{
    if (len < 2)
        return;

    int *temp = malloc(len * sizeof(int));
    if (temp == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    merge_sort_helper(arr, 0, len - 1, temp);
    free(temp);
}

void merge_sort_helper(int *arr, int left, int right, int *temp)
{
    if (left >= right)
        return;

    if (right - left < INSERTION_THRESHOLD)
    {
        insertion_sort_helper(arr, left, right);
        return;
    }

    int mid = left + (right - left) / 2;

    merge_sort_helper(arr, left, mid, temp);
    merge_sort_helper(arr, mid + 1, right, temp);

    if (arr[mid] <= arr[mid + 1])
        return;

    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
        temp[k++] = arr[i] <= arr[j] ? arr[i++] : arr[j++];
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    memcpy(arr + left, temp, k * sizeof(int));
}

void insertion_sort_helper(int *arr, int left, int right)
{
    if (right - left < 1)
        return;

    for (int i = left + 1; i <= right; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void quick_sort(int *arr, int len)
{
    if (len < 2)
        return;

    quick_sort_helper(arr, 0, len - 1);
}

void quick_sort_helper(int *arr, int low, int high)
{
    if (high - low < INSERTION_THRESHOLD)
    {
        insertion_sort_helper(arr, low, high);
        return;
    }

    while (low < high)
    {
        int mid = (low + high) / 2;
        if (arr[high] < arr[low])
            swap(&arr[high], &arr[low]);
        if (arr[mid] < arr[low])
            swap(&arr[mid], &arr[low]);
        if (arr[high] < arr[mid])
            swap(&arr[high], &arr[mid]);

        int pivot = arr[mid];
        int i = low - 1;
        int j = high + 1;

        while (1)
        {
            do
                i++;
            while (arr[i] < pivot);

            do
                j--;
            while (arr[j] > pivot);

            if (i >= j)
                break;

            swap(&arr[i], &arr[j]);
        }

        if (j - low < high - j)
        {
            quick_sort_helper(arr, low, j);
            low = j + 1;
        }
        else
        {
            quick_sort_helper(arr, j + 1, high);
            high = j;
        }
    }
}

void heap_sort(int *arr, int len)
{
    if (len < 2)
        return;

    if (len <= INSERTION_THRESHOLD)
    {
        insertion_sort_helper(arr, 0, len - 1);
        return;
    }

    for (int i = (len - 2) / D; i >= 0; i--)
        heap_sort_helper(arr, len, i);

    for (int i = len - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);

        if (i < INSERTION_THRESHOLD)
        {
            insertion_sort_helper(arr, 0, i);
            break;
        }

        heap_sort_helper(arr, i, 0);
    }
}

void heap_sort_helper(int *arr, int len, int parent)
{
    while (1)
    {
        int largest = parent;

        for (int k = 0; k < D; k++)
        {
            int child = D * parent + (k + 1);
            if (child < len && arr[child] > arr[largest])
                largest = child;
        }

        if (largest == parent)
            break;

        swap(&arr[largest], &arr[parent]);
        parent = largest;
    }
}

void radix_sort(int *arr, int len)
{
    if (len < 2)
        return;

    if (len <= INSERTION_THRESHOLD)
    {
        insertion_sort_helper(arr, 0, len - 1);
        return;
    }

    int bucket_count[256];
    int *temp = malloc(len * sizeof(int));
    if (temp == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int largest = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] > largest)
            largest = arr[i];
    }

    for (int shift = 0; shift < BITS; shift += 8)
    {
        memset(bucket_count, 0, sizeof(bucket_count));

        for (int i = 0; i < len; i++)
        {
            int digit = (arr[i] >> shift) & 0xff;
            bucket_count[digit]++;
        }

        for (int i = 1; i < 256; i++)
            bucket_count[i] += bucket_count[i - 1];

        for (int i = len - 1; i >= 0; i--)
        {
            int digit = (arr[i] >> shift) & 0xff;
            temp[--bucket_count[digit]] = arr[i];
        }

        memcpy(arr, temp, len * sizeof(int));

        if (largest >> (shift + 8) == 0 && shift < BITS - 8)
            break;
    }

    free(temp);
}
