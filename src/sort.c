#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void display_numbers(int *num, size_t len);
void shuffle_array(int *num, size_t len);
void bubble_sort(int *num, size_t len);
void selection_sort(int *num, size_t len);
void insertion_sort(int *num, size_t len);
void merge_sort(int *num, size_t left, size_t right);

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int num[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    size_t len = sizeof(num) / sizeof(num[0]);

    printf("\nBubble Sort:\n");
    display_numbers(num, len);
    bubble_sort(num, len);
    printf("Result:\n");
    display_numbers(num, len);
    shuffle_array(num, len);
    printf("\n");

    printf("Selection Sort:\n");
    display_numbers(num, len);
    selection_sort(num, len);
    printf("Result:\n");
    display_numbers(num, len);
    shuffle_array(num, len);
    printf("\n");

    printf("Insertion Sort:\n");
    display_numbers(num, len);
    selection_sort(num, len);
    printf("Result:\n");
    display_numbers(num, len);
    shuffle_array(num, len);
    printf("\n");

    printf("Merge Sort:\n");
    display_numbers(num, len);
    merge_sort(num, 0, len - 1);
    printf("Result:\n");
    display_numbers(num, len);
    shuffle_array(num, len);
    printf("\n");

    return 0;
}

void shuffle_array(int *num, size_t len)
{
    for (size_t i = len - 1; i > 0; i--)
    {
        size_t j = rand() % (i + 1);

        int temp = num[i];
        num[i] = num[j];
        num[j] = temp;
    }
}

void display_numbers(int *num, size_t len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%i ", num[i]);
    }
    printf("\n");
}

void bubble_sort(int *num, size_t len)
{
    if (len < 2)
        return;

    for (size_t i = 0; i < len - 1; i++)
    {
        int swapped = 0;
        for (size_t j = 0; j < len - i - 1; j++)
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

void selection_sort(int *num, size_t len)
{
    if (len < 2)
        return;

    for (size_t i = 0; i < len - 1; i++)
    {
        size_t min = i;
        for (size_t j = i + 1; j < len; j++)
        {
            if (num[j] < num[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            int temp = num[i];
            num[i] = num[min];
            num[min] = temp;
        }
    }
}

void insertion_sort(int *num, size_t len)
{
    if (len < 2)
        return;

    for (size_t i = 1; i < len; i++)
    {
        int key = num[i];
        size_t j = i - 1; // unsigned
        while (j >= 0 && num[j] > key)
        {
            num[j + 1] = num[j];
            j = j - 1;
        }
        num[j + 1] = key;
    }
}

void merge_sort(int *num, size_t left, size_t right)
{
    if (left < right)
    {
        size_t mid = left + (right - left) / 2;

        merge_sort(num, left, mid);
        merge_sort(num, mid + 1, right);

        size_t n1 = mid - left + 1;
        size_t n2 = right - mid;

        int *L = (int *)malloc(n1 * sizeof(int));
        int *R = (int *)malloc(n2 * sizeof(int));

        if (L == NULL || R == NULL)
        {
            free(L);
            free(R);
            printf("Memory allocation failed\n");
            exit(1);
        }

        for (size_t i = 0; i < n1; i++)
            L[i] = num[left + i];
        for (size_t i = 0; i < n2; i++)
            R[i] = num[mid + 1 + i];

        size_t i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
            num[k++] = L[i] <= R[j] ? L[i++] : R[j++];
        while (i < n1)
            num[k++] = L[i++];
        while (j < n2)
            num[k++] = R[j++];

        free(R);
        free(L);
    }
}
