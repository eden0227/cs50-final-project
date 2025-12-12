#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define INSERTION_THRESHOLD 16

void test_sort(char *name, void (*func)(int *, int), int *num, int len);
void display_numbers(int *num, int len);
void shuffle_array(int *num, int len);
void bubble_sort(int *num, int len);
void selection_sort(int *num, int len);
void insertion_sort(int *num, int len);
void merge_sort(int *num, int len);
void merge_sort_helper(int *num, int left, int right, int *temp);
void insertion_sort_helper(int *num, int left, int right);

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int num[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int len = sizeof(num) / sizeof(num[0]);

    test_sort("Bubble Sort", bubble_sort, num, len);
    test_sort("Selection Sort", selection_sort, num, len);
    test_sort("Insertion Sort", insertion_sort, num, len);
    test_sort("Merge Sort", merge_sort, num, len);

    return 0;
}

void test_sort(char *name, void (*func)(int *, int), int *num, int len)
{
    printf("%s:\n", name);
    display_numbers(num, len);
    func(num, len);
    printf("Result:\n");
    display_numbers(num, len);
    shuffle_array(num, len);
    printf("\n");
}

void display_numbers(int *num, int len)
{
    for (int i = 0; i < len; i++)
        printf("%i ", num[i]);
    printf("\n");
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
                int temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
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
        {
            int temp = num[i];
            num[i] = num[min];
            num[min] = temp;
        }
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
