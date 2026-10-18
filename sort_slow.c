#include "sort_slow.h"
#include "stack.h"
#include "graham_scan1.h"

//slow algo
void bubblesort(coordinate *points, coordinate anchor, int n){
	int i, j;
    int swapped;
    coordinate temp;

    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {

            if (compare(anchor, &points[j], &points[j + 1]) > 0) {
                temp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        }
    }
}



