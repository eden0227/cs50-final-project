#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INSERTION_THRESHOLD 16
#define D 4
#define BITS 32

typedef struct
{
    char *key;
    int value;
} key_value_pair;

void c_qsort(key_value_pair *arr, int len);
int compare(const void *a, const void *b);
void merge_sort(key_value_pair *arr, int len);
void merge_sort_helper(key_value_pair *arr, int left, int right, key_value_pair *temp);
void insertion_sort_helper(key_value_pair *arr, int left, int right);
void quick_sort(key_value_pair *arr, int len);
void quick_sort_helper(key_value_pair *arr, int low, int high);
void swap(key_value_pair *a, key_value_pair *b);
void heap_sort(key_value_pair *arr, int len);
void heap_sort_helper(key_value_pair *arr, int len, int parent);
void radix_sort(key_value_pair *arr, int len);

void c_qsort(key_value_pair *arr, int len)
{
    qsort(arr, len, sizeof(key_value_pair), compare);
}

int compare(const void *a, const void *b)
{
    return ((key_value_pair *)a)->value - ((key_value_pair *)b)->value;
}

void merge_sort(key_value_pair *arr, int len)
{
    if (len < 2)
        return;

    key_value_pair *temp = malloc(len * sizeof(key_value_pair));
    if (temp == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    merge_sort_helper(arr, 0, len - 1, temp);
    free(temp);
}

void merge_sort_helper(key_value_pair *arr, int left, int right, key_value_pair *temp)
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

    if (arr[mid].value <= arr[mid + 1].value)
        return;

    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
        temp[k++] = arr[i].value <= arr[j].value ? arr[i++] : arr[j++];
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    memcpy(arr + left, temp, k * sizeof(key_value_pair));
}

void insertion_sort_helper(key_value_pair *arr, int left, int right)
{
    if (right - left < 1)
        return;

    for (int i = left + 1; i <= right; i++)
    {
        key_value_pair min = arr[i];
        int j = i - 1;
        while (j >= left && arr[j].value > min.value)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = min;
    }
}

void quick_sort(key_value_pair *arr, int len)
{
    if (len < 2)
        return;

    quick_sort_helper(arr, 0, len - 1);
}

void quick_sort_helper(key_value_pair *arr, int low, int high)
{
    if (high - low < INSERTION_THRESHOLD)
    {
        insertion_sort_helper(arr, low, high);
        return;
    }

    while (low < high)
    {
        int mid = (low + high) / 2;
        if (arr[high].value < arr[low].value)
            swap(&arr[high], &arr[low]);
        if (arr[mid].value < arr[low].value)
            swap(&arr[mid], &arr[low]);
        if (arr[high].value < arr[mid].value)
            swap(&arr[high], &arr[mid]);

        int pivot = arr[mid].value;
        int i = low - 1;
        int j = high + 1;

        while (1)
        {
            do
                i++;
            while (arr[i].value < pivot);

            do
                j--;
            while (arr[j].value > pivot);

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

void swap(key_value_pair *a, key_value_pair *b)
{
    key_value_pair temp = *a;
    *a = *b;
    *b = temp;
}

void heap_sort(key_value_pair *arr, int len)
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

void heap_sort_helper(key_value_pair *arr, int len, int parent)
{
    while (1)
    {
        int max = parent;

        for (int k = 0; k < D; k++)
        {
            int child = D * parent + (k + 1);
            if (child < len && arr[child].value > arr[max].value)
                max = child;
        }

        if (max == parent)
            break;

        swap(&arr[max], &arr[parent]);
        parent = max;
    }
}

void radix_sort(key_value_pair *arr, int len)
{
    if (len < 2)
        return;

    if (len <= INSERTION_THRESHOLD)
    {
        insertion_sort_helper(arr, 0, len - 1);
        return;
    }

    int bucket_count[256];
    key_value_pair *temp = malloc(len * sizeof(key_value_pair));
    if (temp == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int max = arr[0].value;
    for (int i = 1; i < len; i++)
    {
        if (arr[i].value > max)
            max = arr[i].value;
    }

    for (int shift = 0; shift < BITS; shift += 8)
    {
        memset(bucket_count, 0, sizeof(bucket_count));

        for (int i = 0; i < len; i++)
        {
            int digit = (arr[i].value >> shift) & 0xff;
            bucket_count[digit]++;
        }

        for (int i = 1; i < 256; i++)
            bucket_count[i] += bucket_count[i - 1];

        for (int i = len - 1; i >= 0; i--)
        {
            int digit = (arr[i].value >> shift) & 0xff;
            temp[--bucket_count[digit]] = arr[i];
        }

        memcpy(arr, temp, len * sizeof(key_value_pair));

        if (max >> (shift + 8) == 0 && shift < BITS - 8)
            break;
    }

    free(temp);
}
