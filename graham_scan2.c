#include <stdio.h>
#include "graham_scan2.h"
#include "stack.h"
#include "sort.h"

coordinate lowest_anchor(coordinate *points, int n) {
    int low_index = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[low_index].y ||
            (points[i].y == points[low_index].y && points[i].x < points[low_index].x)) {
            low_index = i;
        }
    }
    coordinate temp = points[0];
    points[0] = points[low_index];
    points[low_index] = temp;
    return points[0];
}

double cross_multiply(coordinate p1, coordinate p2, coordinate p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

int compare_polar(coordinate *a, coordinate *b, coordinate anchor) {
    double x = cross_multiply(anchor, *a, *b);

    if (x > 0) {
        return -1;
    }
    if (x < 0) {
        return 1;
    }

    double da = (a->x - anchor.x) * (a->x - anchor.x) + (a->y - anchor.y) * (a->y - anchor.y);
    double db = (b->x - anchor.x) * (b->x - anchor.x) + (b->y - anchor.y) * (b->y - anchor.y);
    if (da < db) {
        return -1;
    }
    if (da > db) {
        return 1;
    }
    return 0;
}

static int remove_anchor_duplicates(coordinate *points, int n) {
    int k = 1;
    for (int i = 1; i < n; i++) {
        if (points[i].x != points[0].x || points[i].y != points[0].y) {
            points[k++] = points[i];
        }
    }
    return k;
}

static int remove_adjacent_duplicates(coordinate *points, int n) {
    if (n < 2) {
        return n;
    }
    int k = 1;
    for (int i = 1; i < n; i++) {
        if (points[i].x != points[k - 1].x || points[i].y != points[k - 1].y) {
            points[k++] = points[i];
        }
    }
    return k;
}

int graham_scan_fast(coordinate *points, int n, coordinate *hull) {
    int n_input = n;
    int hull_size = 0;

    if (n > 0) {
        coordinate anchor = lowest_anchor(points, n);
        n = remove_anchor_duplicates(points, n);

        if (n > 1) {
            quicksort(points + 1, anchor, n - 1);
            n = 1 + remove_adjacent_duplicates(points + 1, n - 1);
        }

        if (n <= 2) {
            for (int i = 0; i < n; i++) {
                hull[i] = points[i];
            }
            hull_size = n;
        } else {
            static stack s;
            initialize_stack(&s);
            push(&s, anchor);
            push(&s, points[1]);

            for (int i = 2; i < n; i++) {
                while (s.top >= 1 && cross_multiply(next_to_top(&s), top(&s), points[i]) <= 0) {
                    pop(&s);
                }
                push(&s, points[i]);
            }

            hull_size = s.top + 1;
            for (int i = 0; i < hull_size; i++) {
                hull[i] = s.data[i];
            }
        }
    }

    printf("Graham scan (fast, quicksort): n = %d, hull = %d\n",
           n_input, hull_size);

    return hull_size;
}
