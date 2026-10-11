#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

double mean(const int *values, size_t n) {
    double total = 0;
    for (size_t i = 0; i < n; ++i) total += values[i];
    return total / n;
}

double median(const int *sorted, size_t n) {
    if (n % 2) return sorted[n / 2];
    return ((double)sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
}

void print_modes(const int *sorted, size_t n) {
    size_t max_count = 0;
    for (size_t i = 0; i < n;) {
        size_t j = i + 1;
        while (j < n && sorted[j] == sorted[i]) ++j;
        if (j - i > max_count) max_count = j - i;
        i = j;
    }
    if (max_count == 1) { puts("Mode: none (all values occur once)"); return; }
    printf("Mode(s): ");
    int first = 1;
    for (size_t i = 0; i < n;) {
        size_t j = i + 1;
        while (j < n && sorted[j] == sorted[i]) ++j;
        if (j - i == max_count) {
            printf("%s%d", first ? "" : ", ", sorted[i]);
            first = 0;
        }
        i = j;
    }
    putchar('\n');
}

int main(void) {
    const int input[] = {4, 2, 7, 2, 9, 4, 2};
    const size_t n = sizeof(input) / sizeof(input[0]);
    if (!n) { fputs("Input cannot be empty.\n", stderr); return 1; }
    int *sorted = malloc(n * sizeof(*sorted));
    if (!sorted) { fputs("Memory allocation failed.\n", stderr); return 1; }
    for (size_t i = 0; i < n; ++i) sorted[i] = input[i];
    qsort(sorted, n, sizeof(*sorted), compare_ints);
    printf("C (Procedural) | Count: %zu\n", n);
    printf("Mean: %.2f\nMedian: %.2f\n", mean(input, n), median(sorted, n));
    print_modes(sorted, n);
    free(sorted);
    return 0;
}
