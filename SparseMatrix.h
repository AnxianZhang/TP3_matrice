//
// Created by gadan on 10/10/2024.
//

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "Element.h"

typedef struct SparseMatrix {
    LineArray *matrix;
    unsigned int maxLines;
    unsigned int maxColumns;
} SparseMatrix;

void populateMatrix(SparseMatrix *m, unsigned int line, unsigned int column);

void showMatrix(const SparseMatrix *m);

void showMatrixArray(const SparseMatrix *m);

int searchValue(const SparseMatrix *m, unsigned int i, unsigned int j);

void addValueAt(SparseMatrix *m, unsigned int i, unsigned int j, int val);

void sumMatrix(SparseMatrix *m1, SparseMatrix *m2);

int getNumberOfGainedOctet(const SparseMatrix *m);

#endif //SPARSEMATRIX_H
