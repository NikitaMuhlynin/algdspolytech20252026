#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "nqueens.h"

static int abs_int(int x) { return x < 0 ? -x : x; }

static void verify_solution(int n, const Queen *q) {
    if (n == 0) return;

    int *col_used = (int*)calloc((size_t)n, sizeof(int));
    assert(col_used);

    for (int r = 0; r < n; r++) {
        assert(q[r].row == r);
        assert(q[r].col >= 0 && q[r].col < n);
        assert(col_used[q[r].col] == 0);
        col_used[q[r].col] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dr = abs_int(q[i].row - q[j].row);
            int dc = abs_int(q[i].col - q[j].col);
            assert(dr != dc); /* диагонали */
        }
    }

    free(col_used);
}

static void test_small_known(void) {
    Queen q[10];

    assert(nqueens_construct(1, q) == 1);
    verify_solution(1, q);

    assert(nqueens_construct(2, q) == 0);
    assert(nqueens_construct(3, q) == 0);

    assert(nqueens_construct(4, q) == 1);
    verify_solution(4, q);
}

static void test_range(int from, int to) {
    for (int n = from; n <= to; n++) {
        Queen *q = (Queen*)malloc((size_t)n * sizeof(Queen));
        assert(q);

        int ok = nqueens_construct(n, q);
        if (n == 2 || n == 3) {
            assert(ok == 0);
        } else {
            assert(ok == 1);
            verify_solution(n, q);
        }

        free(q);
    }
}

int main(void) {
    test_small_known();
    test_range(1, 200);

    puts("OK");
    return 0;
}