#include <stdio.h>
#include <stdlib.h>
#include "nqueens.h"
#pragma warning(disable: 4996)

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    if (n == 0) return 0;

    Queen *q = (Queen*)malloc((size_t)n * sizeof(Queen));
    if (!q) return 0;

    if (!nqueens_construct(n, q)) {
        puts("-1");
        free(q);
        return 0;
    }

    for (int r = 0; r < n; r++) {
        printf("%d %d\n", q[r].row, q[r].col);
    }

    free(q);
    return 0;
}