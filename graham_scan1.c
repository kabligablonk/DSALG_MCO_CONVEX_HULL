#include <stdio.h>
#include "stack.h"
#include "graham_scan1.h"
#include "sort.h"

//Find Lowest Point (Separate by lowest x val if y values are same)
int FindAnchor(coordinate *points, int n){
	int i, min, index_min;
	int lowest_x;
	
	lowest_x = points[0].x;
	min = points[0].y; 
	index_min = 0;

	
	//Gets index of lowest val
	for(i = 0; i < n; i++){
		if(points[i].y < min || points[i].y == min && points[i].x < lowest_x){
			min = points[i].y;
			lowest_x = points[i].x;
			index_min = i;
		}
	}
	
	return index_min;
}

//Puts the anchor point into the first index
void SetAnchor(coordinate *points, int index){
	coordinate temp;

	temp = points[index];
	points[index] = points[0];
	points[0] = temp;
}


//Calculates the angle 
double IsCounterClockwise(coordinate p1, coordinate p2, coordinate p3){
	return (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);
}

//Compares polar angles
//Majority of function body is lifted from graham_scan2.c's "compare_polar" function
int compare(coordinate anchor, coordinate *a, coordinate *b){
	double x = IsCounterClockwise(anchor, *a, *b);
	
	if(x > 0){
		return -1;
	}
	if(x < 0){
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

//Implement Graham Sort
int slow_graham_scan(coordinate *points, int n, coordinate *hull){
	int n_input = n;
    int hull_size = 0;

    if (n > 0) {
        int index_anchor = FindAnchor(points, n);
        SetAnchor(points, index_anchor);
        coordinate anchor = points[0];
        

        if (n > 1) {
            bubblesort(points + 1, anchor, n - 1);
            
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
                while (s.top >= 1 && IsCounterClockwise(next_to_top(&s), top(&s), points[i]) <= 0) {
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

    printf("Graham scan (slow, bubblesort): n = %d, hull = %d\n",
           n_input, hull_size);

    return hull_size;
}
 

