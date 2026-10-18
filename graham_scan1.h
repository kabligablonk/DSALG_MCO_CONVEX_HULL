#ifndef DSALG_MCO_CONVEX_HULL_GRAHAM_SCAN1_H
#define DSALG_MCO_CONVEX_HULL_GRAHAM_SCAN1_H

#include "stack.h"

int FindAnchor(coordinate *points, int n);
void SetAnchor(coordinate *points, int index);
double IsCounterClockwise(coordinate p1, coordinate p2, coordinate p3);
int compare(coordinate anchor, coordinate *a, coordinate *b);
int slow_graham_scan(coordinate *points, int n, coordinate *hull);

#endif //DSALG_MCO_CONVEX_HULL_GRAHAM_SCAN1_H
