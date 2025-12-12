#include "nqueens.h"
#include <stdlib.h>

static void push_row(int *rows_by_col_1based, int *idx, int r1) {
    rows_by_col_1based[(*idx)++] = r1;
}

int nqueens_construct(int n, Queen *out) {
    if (n < 0 || !out) return 0;
    if (n == 0) return 1;
    if (n == 1) { out[0].row = 0; out[0].col = 0; return 1; }
    if (n == 2 || n == 3) return 0;

    int *rows = (int*)malloc((size_t)n * sizeof(int)); /* rows[col] = row (1-based) */
    if (!rows) return 0;

    int idx = 0;
    int rem = n % 6;

    if (rem != 2 && rem != 3) {
        for (int r = 2; r <= n; r += 2) push_row(rows, &idx, r);
        for (int r = 1; r <= n; r += 2) push_row(rows, &idx, r);

    } else if (rem == 2) {
        for (int r = 2; r <= n; r += 2) push_row(rows, &idx, r);
        push_row(rows, &idx, 3);
        push_row(rows, &idx, 1);
        for (int r = 7; r <= n; r += 2) push_row(rows, &idx, r);
        push_row(rows, &idx, 5);

    } else { /* rem == 3 */
        for (int r = 4; r <= n - 1; r += 2) push_row(rows, &idx, r);
        push_row(rows, &idx, 2);
        for (int r = 5; r <= n; r += 2) push_row(rows, &idx, r);
        push_row(rows, &idx, 1);
        push_row(rows, &idx, 3);
    }

    /* Инверсия: rows[col] = row => out[row].col = col */
    for (int r = 0; r < n; r++) {
        out[r].row = r;
        out[r].col = -1;
    }
    for (int c = 0; c < n; c++) {
        int r0 = rows[c] - 1;      /* 0-based row */
        out[r0].row = r0;
        out[r0].col = c;
    }

    free(rows);
    return 1;
}