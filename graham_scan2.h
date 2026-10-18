#ifndef DSALG_MCO_CONVEX_HULL_GRAHAM_SCAN2_H
#define DSALG_MCO_CONVEX_HULL_GRAHAM_SCAN2_H

#include "stack.h"

coordinate lowest_anchor(coordinate *points, int n);
double cross_multiply(coordinate p1, coordinate p2, coordinate p3);
int compare_polar(coordinate *a, coordinate *b, coordinate anchor);
int graham_scan_fast(coordinate *points, int n, coordinate *hull);

#endif //DSALG_MCO_CONVEX_HULL_GRAHAM_SCAN2_H