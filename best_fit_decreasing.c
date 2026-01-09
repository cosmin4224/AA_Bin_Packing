#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int decreasing_sort(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int main(int argc, char **argv) {
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

    // sort items
    qsort(items, n, sizeof(int), decreasing_sort);

    /*
     * we are aware that this is inefficient
     * in terms of space complexity
     * O(n^2) as opposed to O(n) worst case;
     * dynamically reallocating bin size when
     * necessary would lead to worse time
     * performace, which would lead to inaccurate
     * time benchmarks
     */

    int **bins = malloc(sizeof(int *) * n);
    int *bins_remaining_capacity = malloc(sizeof(int) * n);
    int *bins_capacity = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        bins[i] = malloc(sizeof(int) * n);
        bins_remaining_capacity[i] = c;
        bins_capacity[i] = 0;
    }

    int k = 1;
    int best_bin;
    int min_space;

    for (int item = 0; item < n; item++) {
        best_bin = -1;
        min_space = INT_MAX;
        for (int bin = 0; bin < k; bin++) {
            if (bins_remaining_capacity[bin] >= items[item] && bins_remaining_capacity[bin] < min_space) {
                best_bin = bin;
                min_space = bins_remaining_capacity[bin];
            }
        }
        if (best_bin != -1) {
            bins[best_bin][bins_capacity[best_bin]] = item;
            bins_capacity[best_bin] += 1;
            bins_remaining_capacity[best_bin] -= items[item];
        } else {
            bins[k][bins_capacity[k]] = item;
            bins_capacity[k] += 1;
            bins_remaining_capacity[k] -= items[item];
            k += 1;
        }
    }

    fprintf(output, "%d\n", k);

    for (int bin = 0; bin < k; bin++) {
        for (int item = 0; item < bins_capacity[bin]; item++) {
            fprintf(output, "%d ", bins[bin][item]);
        }
        fprintf(output, "\n");
    }

    return 0;
}
