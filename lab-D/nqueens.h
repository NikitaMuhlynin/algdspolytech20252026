#ifndef NQUEENS_H
#define NQUEENS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int row;
    int col;
} Queen;

int nqueens_construct(int n, Queen *out);

#ifdef __cplusplus
}
#endif

#endif
