#include "sort_fast.h"
#include "graham_scan2.h"

// fast algo
void quicksort(coordinate *points, coordinate anchor, int n) {
    while (n > 1) {
        coordinate p;
        int middle = n / 2;

        if (compare_polar(&points[middle], &points[0], anchor) < 0) {
            p = points[middle];
            points[middle] = points[0];
            points[0] = p;
        }
        if (compare_polar(&points[n - 1], &points[0], anchor) < 0) {
            p = points[n - 1];
            points[n - 1] = points[0];
            points[0] = p;
        }
        if (compare_polar(&points[n - 1], &points[middle], anchor) < 0) {
            p = points[n - 1];
            points[n - 1] = points[middle];
            points[middle] = p;
        }

        coordinate pivot = points[middle];
        int i = 0;
        int j = n - 1;

        while (i <= j) {
            while (compare_polar(&points[i], &pivot, anchor) < 0) {
                i++;
            }
            while (compare_polar(&points[j], &pivot, anchor) > 0) {
                j--;
            }
            if (i <= j) {
                p = points[i];
                points[i] = points[j];
                points[j] = p;
                i++;
                j--;
            }
        }

        if (j + 1 < n - i) {
            quicksort(points, anchor, j + 1);
            points += i;
            n -= i;
        } else {
            quicksort(points + i, anchor, n - i);
            n = j + 1;
        }
    }
}