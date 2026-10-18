#ifndef DSALG_MCO_CONVEX_HULL_STACK_H
#define DSALG_MCO_CONVEX_HULL_STACK_H

#include <stdbool.h>

#define STACK_SIZE 32768

typedef struct {
    double x;
    double y;
} coordinate;

typedef struct {
    coordinate data[STACK_SIZE];
    int top;
} stack;

void initialize_stack(stack *s);
bool is_empty(stack *s);
bool is_full(stack *s);
coordinate top(stack *s);
coordinate next_to_top(stack *s);
void push(stack *s, coordinate value);
coordinate pop(stack *s);

#endif //DSALG_MCO_CONVEX_HULL_STACK_H
