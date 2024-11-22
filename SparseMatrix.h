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

/**
 * Function that fills a hollow matrix, representing a matrix of size 𝑁×𝑀,
 * from a user input using the keyboard (the user will therefore have to
 * enter successively 𝑁×𝑀 positive, negative or zero integers)
 *
 * @param m the matrix which going to be filled up
 * @param line number of line of matrix
 * @param column number of colunm of matrix
 */
void populateMatrix(SparseMatrix *m, unsigned int line, unsigned int column);

/**
 * Show the entire sparse matrix, including 0
 *
 * @param m the matrix to be show
 */
void showMatrix(const SparseMatrix *m);

void showMatrixArray(const SparseMatrix *m);

/**
 * Search a value from the coordinate given by the user
 *
 * @param m the matrix given by the user
 * @param i number of line € [0, n -1]
 * @param j number of column € [0, n -1]
 * @return the value at i j
 */
int searchValue(const SparseMatrix *m, unsigned int i, unsigned int j);

void addValueAt(SparseMatrix *m, unsigned int i, unsigned int j, int val);

/**
 * Make the sum of two matrix, and store the new one in the first matrix
 * @param m1 first matrix
 * @param m2 second matrix
 */
void sumMatrix(SparseMatrix *m1, const SparseMatrix *m2);

int getNumberOfGainedOctet(const SparseMatrix *m);

int getNumberOfGainedOctetWith_0(const SparseMatrix *m);

void freeMatrixArray(SparseMatrix ***m,int usedSize);

void freeMatrix(SparseMatrix *m);

#endif //SPARSEMATRIX_H
