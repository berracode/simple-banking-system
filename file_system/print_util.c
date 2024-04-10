#include <stdio.h>
#include <string.h>

#include "print_util.h"

void print_separator_line(int *column_widths, int num_columns) {
    int total_width = (num_columns-1)+num_columns*2;
    for (int i = 0; i < num_columns; ++i) {
        total_width += column_widths[i];
    }
    printf("+");
    for (int i = 0; i < total_width; ++i) {
        printf("-");
    }
    printf("+\n");
}

void print_row(int *column_widths, char **data, int num_columns) {
    printf("|");
    for (int i = 0; i < num_columns; i++) {
        //printf("col %d tam: %d", i, column_widths[i]);
        printf(" %-*s |", column_widths[i], data[i]);
    }
    printf("\n");
}
