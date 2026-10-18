#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void initialize_stack(stack *s) {
    s->top = -1;
}

bool is_empty(stack *s) {
    return s->top == -1;
}

bool is_full(stack *s) {
    return s->top >= STACK_SIZE - 1;
}

coordinate top(stack *s) {
    if (is_empty(s)) {
        fprintf(stderr, "Error: TOP on an empty stack\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top];
}

coordinate next_to_top(stack *s) {
    if (s->top < 1) {
        fprintf(stderr, "Error: NEXT-TO-TOP needs at least 2 elements\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top - 1];
}

void push(stack *s, coordinate value) {
    if (is_full(s)) {
        fprintf(stderr, "Error: PUSH on a full stack\n");
        exit(EXIT_FAILURE);
    }
    s->data[++s->top] = value;
}

coordinate pop(stack *s) {
    if (is_empty(s)) {
        fprintf(stderr, "Error: POP on an empty stack\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top--];
}
