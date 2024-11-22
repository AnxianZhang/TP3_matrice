//
// Created by gadan on 11/22/2024.
//

#ifndef SPARSEMATRIXLIST_H
#define SPARSEMATRIXLIST_H

#include "SparseMatrix.h"

typedef struct SparseMatrixList {
    SparseMatrix **list;
    unsigned int availableSpace;
    unsigned int usedSpace;
} SparseMatrixList;

SparseMatrixList *createSparseMatrixList(unsigned int initialSize, unsigned int usedSpace);

void addMatrixInList(SparseMatrixList *list, unsigned int line, unsigned colum);

void manageMatrixArray(SparseMatrixList *list);

int isSelectedMatrixSame(const SparseMatrixList *list, unsigned int numberM1, unsigned int numberM2);

void freeMatrixArray(const SparseMatrixList **list, unsigned int usedSize);

#endif
