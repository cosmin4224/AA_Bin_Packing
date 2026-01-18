#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    // number of bins required
    int k = 1;

    // initialize bin with capacity
    int *current_bin = malloc(sizeof(int) * n);
    int current_bin_size = 0;
    int remaining_capacity = c;

    fprintf(output, "%d\n", k);

    for (int i = 0; i < n; i++) {
        if (items[i] < remaining_capacity) {
            current_bin[current_bin_size] = i;
            current_bin_size += 1;
            remaining_capacity -= items[i];
        } else {
            // write to file

            for (int j = 0; j < current_bin_size; j++) {
                fprintf(output, "%d ", current_bin[j]);
                // printf("%d ", current_bin[j]);
            }
            fprintf(output, "\n");
            // printf("\n");

            memset(current_bin, 0, sizeof(int) * n);
            current_bin_size = 0;
            remaining_capacity = c;
            k++;

            current_bin[current_bin_size] = i;
            current_bin_size += 1;
            remaining_capacity -= items[i];
        }
    }

    for (int j = 0; j < current_bin_size; j++) {
        fprintf(output, "%d ", current_bin[j]);
        // printf("%d ", current_bin[j]);
    }
    fprintf(output, "\n");
    // printf("\n");

    fseek(output, 0, SEEK_SET);
    fprintf(output, "%d\n", k);

    fclose(input);
    fclose(output);

    return 0;
}
