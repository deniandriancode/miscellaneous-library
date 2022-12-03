/*
 * Time Complexity:
 *
 * Best Case : O(n^2)
 * Average Case : O(n^2)
 * Worst Case : O(n^2)
 *
 * Space Complexity:
 *
 * O(1)
 * Stable : true
 *
 */

#include <stdio.h>

void swap (int *arr, int src, int dst);
void selection_sort (int *arr);
int find_smallest (int *arr, int beg);
void display (int *arr);

int
main (int argc, char **argv)
{
    int arr[] = {4,5,8,7,6,1,3,2,9};
    display (arr);
    selection_sort (arr);
    display (arr);

    return 0;
}

/*
 * swap: swap elements inside an array
 */
void
swap (int *arr, int src, int dst)
{
    int tmp;
    tmp = arr[dst];
    arr[dst] = arr[src];
    arr[src] = tmp;
}

/*
 * selection_sort: sort an array
 */
void
selection_sort (int *arr)
{
    int i, base;
    int min;

    base = 0;
    for (i = 0; arr[i]; ++i, ++base) {
        min = find_smallest (arr, base);
        swap (arr, base, min);
    }
}

/*
 * find_smallest: find and return the smallest element in an array
 */
int
find_smallest (int *arr, int beg)
{
    int i, min, index;

    min = arr[beg];
    index = beg;
    for (i = beg; arr[i]; ++i) {
        if (min > arr[i]) {
            min = arr[i];
            index = i;
        }
    }

    return index;
}

/*
 * display: print an array
 */
void
display (int *arr)
{
    int i;

    for (i = 0; arr[i]; ++i) {
        printf ("%d ", arr[i]);
    }
    putchar ('\n');
}
