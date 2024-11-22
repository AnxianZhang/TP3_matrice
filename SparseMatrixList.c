//
// Created by gadan on 11/22/2024.
//
#include "SparseMatrixList.h"

#include <stdlib.h>

int isSelectedMatrixSame(const SparseMatrixList *list, unsigned int numberM1, unsigned int numberM2) {
    const SparseMatrix *m1 = list->list[numberM1];
    const SparseMatrix *m2 = list->list[numberM2];

    return m1->maxColumns != m2->maxColumns && m1->maxLines != m2->maxLines;
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

void addMatrixInList(SparseMatrixList *list, unsigned int line, unsigned colum) {
    manageMatrixArray(list);
    list->list[list->usedSpace] = malloc(sizeof(SparseMatrix));

    if (!list->list[list->usedSpace]) return;

    populateMatrix(list->list[list->usedSpace++], line, colum);
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

void freeMatrixArray(const SparseMatrixList **list, const unsigned int usedSize) {
    for (unsigned int i = 0; i < usedSize; i++)
        freeMatrix((*list)->list[i]);
    free(list);
}