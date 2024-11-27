//
// Created by gadan on 11/22/2024.
//
#include "SparseMatrixList.h"

#include <stdio.h>
#include <stdlib.h>

int isSelectedMatrixSame(const SparseMatrix *M1, const SparseMatrix *M2) {
    return M1->maxColumns != M2->maxColumns && M1->maxLines != M2->maxLines;
}

SparseMatrixList *createSparseMatrixList(const unsigned int initialSize, const unsigned int usedSpace) {
    SparseMatrixList *list = malloc(sizeof(SparseMatrixList));

    if (!list) return NULL;

    list->list = malloc(sizeof(SparseMatrix *) * initialSize);

    if (!list->list) return NULL;

    list->availableSpace = initialSize;
    list->usedSpace = usedSpace;

    return list;
}

void manageMatrixArray(SparseMatrixList *list) {
    if (list->availableSpace == list->usedSpace) {
        list->availableSpace += 5;

        SparseMatrix **newList = malloc(sizeof(SparseMatrix *) * list->availableSpace);

        if (!newList) return;

        for (unsigned int i = 0; i < list->usedSpace; ++i)
            newList[i] = list->list[i];

        free(list->list);
        list->list = newList;
    }
}

void addMatrixInList(SparseMatrixList *list, unsigned int line, unsigned colum) {
    manageMatrixArray(list);
    list->list[list->usedSpace] = malloc(sizeof(SparseMatrix));

    if (!list->list[list->usedSpace]) return;

    populateMatrix(list->list[list->usedSpace++], line, colum);
}

void freeMatrixArray(SparseMatrixList *list) {
    for (unsigned int i = 0; i < list->usedSpace; i++)
        freeMatrix(list->list[i]);
    free(list);
}
