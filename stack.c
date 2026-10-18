#include "stack.h"
#include  <stdio.h>
#include  <stdbool.h>

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
    return s->data[s->top];
}

coordinate next_to_top(stack *s) {
    return s->data[s->top - 1];
}

void push(stack *s, coordinate value) {
    s->data[++s->top] = value;
    printf("Pushed coordinates: %i %i\n", value.x, value.y);
}

coordinate pop(stack *s) {
    coordinate pop_value = s->data[s->top];
    s->top--;
    printf("Popped coordinates: %i %i\n", pop_value.x, pop_value.y);
    return pop_value;
}