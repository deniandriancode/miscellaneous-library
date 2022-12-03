/*
 * Time Complexity:
 *
 * Best Case : O(n)
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

void display (int *arr);
void swap (int *arr, int src, int dst);
void bubblesort (int *arr);
int array_length (int *arr);

int
main ()
{
    int arr[9] = {4,8,5,1,6,7,9,2,3};
    display (arr);
    bubblesort (arr);
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
 * bubblesort: sort an array
 */
void
bubblesort (int *arr)
{
    int l, i;
    int counter; // pass counter

    l = array_length (arr);
    for (counter = 0; counter < l; ++counter) {
        for (i = 0; i < l-1; ++i) {
            if (arr[i] > arr[i+1]) {
                swap (arr, i, i+1);
            }
        }
    }
}

/*
 * array_length: find the length of an array
 */
int
array_length (int *arr)
{
    int i;

    for (i = 0; arr[i]; ++i)
        ; // do nothing

    return i;
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
