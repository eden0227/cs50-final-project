#include <stdlib.h>

typedef struct
{
    char *key;
    int value;
} key_value_pair;

int compare_values(const void *a, const void *b)
{
    return ((key_value_pair *)a)->value - ((key_value_pair *)b)->value;
}

void sort_by_value(key_value_pair *pairs, int len)
{
    qsort(pairs, len, sizeof(key_value_pair), compare_values);
}
