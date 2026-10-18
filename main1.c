#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "stack.h"
#include "graham_scan1.h"

int main(void) {
    char input_name[256];
    char output_name[256];
    static coordinate points[STACK_SIZE];
    static coordinate hull[STACK_SIZE];
    struct timespec start, end;
    bool is_running = true;
    int n;
    

    while (is_running) {
        printf("Enter the input filename (with extension), or 'qq' to quit: ");
        if (scanf("%255s", input_name) != 1 || input_name[0] == 'q' && input_name[1] == 'q') {
            return 1;
        }

        printf("Enter the output filename (with extension): ");
        if (scanf("%255s", output_name) != 1) {
            is_running = false;
            return 1;
        }

        FILE *fin = fopen(input_name, "r");
        if (fin == NULL) {
            fprintf(stderr, "Error: cannot open input file '%s'\n", input_name);
            return 1;
        }

        if (fscanf(fin, "%d", &n) != 1 || n < 0 || n > STACK_SIZE) {
            fprintf(stderr, "Error: invalid n (must be between 0 and %d)\n", STACK_SIZE);
            fclose(fin);
            return 1;
        }
        for (int i = 0; i < n; i++) {
            if (fscanf(fin, "%lf %lf", &points[i].x, &points[i].y) != 2) {
                fprintf(stderr, "Error: could not read point %d\n", i + 1);
                fclose(fin);
                return 1;
            }
        }

        timespec_get(&start, TIME_UTC);

        int m = slow_graham_scan(points, n, hull);
       	timespec_get(&end, TIME_UTC);

        long seconds = end.tv_sec - start.tv_sec;
    	long nanoseconds = end.tv_nsec - start.tv_nsec;


    	double elapsed_ms = ((double)(end.tv_sec - start.tv_sec) * 1000.0) +
                    		((double)(end.tv_nsec - start.tv_nsec) / 1000000.0);
    	

        FILE *fout = fopen(output_name, "w");
        if (fout == NULL) {
            fprintf(stderr, "Error: cannot open output file '%s'\n", output_name);
            fclose(fin);
            return 1;
        }
        fprintf(fout, "%d\n", m);
        for (int i = 0; i < m; i++) {
            fprintf(fout, "%.6f %.6f\n", hull[i].x, hull[i].y);
        }


        fclose(fin);
        fclose(fout);
        printf("Elapsed time: %.6f milliseconds\n", elapsed_ms);
    }
    return 0;
}
