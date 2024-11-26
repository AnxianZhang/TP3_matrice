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
 * Function that fills a hollow sparse matrix, representing a sparse matrix of size 𝑁×𝑀,
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

/**
 * Show the sparse matrix in a form af array, without exposing 0 values
 *
 * @param m the provided matrix
 */
void showMatrixArray(const SparseMatrix *m);

/**
 * Search a value from the coordinate given by the user, in a sparse matrix
 *
 * @param m the matrix given by the user
 * @param i number of line € [0, n -1]
 * @param j number of column € [0, n -1]
 * @return the value at i j
 */
int searchValue(const SparseMatrix *m, unsigned int i, unsigned int j);

/**
 * Used to modify a value in a sparse matrix at position (i,j)
 *
 * @param m the matrix given by the user
 * @param i number of line € [0, n -1]
 * @param j number of column € [0, n -1]
 * @param val new value at (i,j) position
 */
void addValueAt(SparseMatrix *m, unsigned int i, unsigned int j, int val);

/**
 * Make the sum of two sparse matrix, and store the new one in the first sparse matrix
 *
 * @param m1 first matrix
 * @param m2 second matrix
 */
void sumMatrix(const SparseMatrix *m1, const SparseMatrix *m2);

/**
 * Calculate the number of octet used by a sparse matrix
 *
 * @param m
 * @return
 */
int getNumberOfGainedOctet(const SparseMatrix *m);

/**
 * Calculate the number of octet used by a matrix that containing 0 value
 *
 * @param m
 * @return
 */
int getNumberOfGainedOctetWith_0(const SparseMatrix *m);

/**
 * Free a sparseMatrix
 *
 * @param m
 */
void freeMatrix(SparseMatrix *m);

/**
 * drop value
 *
 * @param m
 */
void delete_value(SparseMatrix *m, unsigned int i, unsigned int j);

#endif //SPARSEMATRIX_H
