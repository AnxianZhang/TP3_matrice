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

/**
 * Create a new list of sparse matrix
 *
 * @param initialSize initial length of the list
 * @param usedSpace remaining slot in the list
 * @return
 */
SparseMatrixList *createSparseMatrixList(unsigned int initialSize, unsigned int usedSpace);

/**
 *  Add a new matrix in the list of matrix, by calling populateMatrix function
 *
 * @param list list of matrix
 * @param line number of line of the new matrix
 * @param colum number of column of the new matrix
 */
void addMatrixInList(SparseMatrixList *list, unsigned int line, unsigned colum);

/**
 * Compare the 2 matrix
 *
 * @param M1
 * @param M2
 * @return 1 if it is the same 0 otherwise
 */
int isSelectedMatrixSame(const SparseMatrix *M1, const SparseMatrix *M2);

/**
 * Free the entire list of atrix
 *
 * @param list
 */
void freeMatrixArray(SparseMatrixList *list);

#endif
