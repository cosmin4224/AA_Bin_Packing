#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool check_for_overflow(int *items, int items_placed, int c, int **bins, int current_bins, int *bins_capacity) {
    // when creating a new bin, it is guaranteed that it doesn't overflow
    int current_bin_capacity;
    for (int bin = 0; bin < current_bins; bin++) {
        current_bin_capacity = c;
        current_bin_capacity -= items[bins[bin][0]];
        for (int item = 1; item < bins_capacity[bin]; item++) {
            current_bin_capacity -= items[bins[bin][item]];
        }
        if (current_bin_capacity < 0) {
            return true;
        }
    }
    return false;
}

void backtracking(int *items, int items_placed, int n, int c, int **bins, int current_bins, int *bins_capacity, int **best_sol, int *max_bins) {
    if (items_placed == n) {
        // printf("max_bins: %d\n", *max_bins);
        if (current_bins < *max_bins) {
            // new best sol
            *max_bins = current_bins;
            for (int bin = 0; bin < current_bins; bin++) {
                memcpy(best_sol[bin], bins[bin], sizeof(int) * n);
            }
        }
    } else {
        // for each bin, add current value
        // if state is valid, backtracking(...)
        // !!! then remove value from bin
        if (current_bins < *max_bins) {
            // printf("current bins: %d\n", current_bins);
            for (int bin = 0; bin <= current_bins; bin++) {
                // add index, not item itself
                bins[bin][bins_capacity[bin]] = items_placed;
                bins_capacity[bin] += 1;
                // valid means no overflow
                if (!check_for_overflow(items, items_placed + 1, c, bins, current_bins, bins_capacity)) {
                    if (bin < current_bins) {
                        backtracking(items, items_placed + 1, n, c, bins, current_bins, bins_capacity, best_sol, max_bins);
                    }
                    else {
                        backtracking(items, items_placed + 1, n, c, bins, current_bins + 1, bins_capacity, best_sol, max_bins);
                    }
                }
                // remove added item
                bins_capacity[bin] -= 1;
                bins[bin][bins_capacity[bin]] = 0;
            }
        }
    }
}

int main(int argc, char **argv) {

    if (argc < 3) {
        printf("usage: ./backtracking input.in output.out max_bins\n");
        printf("max_bins is an optional variable which decides at \nwhat bin size to begin pruning\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    // read N and C
    int n, c;
    fscanf(input, "%d %d", &n, &c);

    int *items = malloc(sizeof(int) * n);

    // read items
    for (int i = 0; i < n; i++) {
        fscanf(input, "%d", &items[i]);
    }

    int max_bins;
    if (argc >= 4) {
        max_bins = atoi(argv[3]);
    } else {
        max_bins = n;
    }

    int **bins = malloc(sizeof(int *) * n);
    int *bins_capacity = malloc(sizeof(int) * n);

    int **best_sol = malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++) {
        bins[i] = calloc(n, sizeof(int));
        bins_capacity[i] = 0;

        best_sol[i] = malloc(sizeof(int) * n);
    }

    backtracking(items, 0, n, c, bins, 0, bins_capacity, best_sol, &max_bins);

    int item = 1;

    fprintf(output, "%d\n", max_bins);

    for (int bin = 0; bin < max_bins; bin++) {
        fprintf(output, "%d ", best_sol[bin][0]);
        // we know that each bin has at least 1 item
        // so we print the first item outside of the loop,
        // allowing us to use the condition index != 0 to
        // stop printing
        while (best_sol[bin][item] != 0 && item < n) {
            fprintf(output, "%d ", best_sol[bin][item]);
            item++;
        }
        fprintf(output, "\n");
        item = 1;
    }

    fclose(input);
    fclose(output);

    return 0;
}
