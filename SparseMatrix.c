//
// Created by gadan on 10/10/2024.
//

#include "stdio.h"
#include "SparseMatrix.h"

#include <stdlib.h>
#include <string.h>

/**
 * Get the substring before the first of ' '
 * and convert it into an integer
 *
 * @param src original string
 * @param substring
 * @return the converted substring into integer
 */
int getNumber(const char *src, const char *substring) {
    char destination[100] = {0};

    if (substring == NULL)
        return atoi(src);

    const unsigned int length = substring - src;
    strncpy(destination, src, length);
    destination[length] = '\0';

    return atoi(destination);
}

/**
 * Create a linked list with a line which was entered by the user.
 * The linked list contains only non-zero values
 *
 * @param buffer entered line
 * @param idx index of the first element in the line
 * @return all a linked list of all value != 0
 */
LineArray populateLineArray(const char *buffer, unsigned short idx) {
    if (buffer == NULL || buffer[0] == '\0') {
        return NULL;
    }

    char *subBuffer = strchr(buffer, ' ');

    if (subBuffer != NULL)
        subBuffer = subBuffer + 1;

    const int value = getNumber(buffer, subBuffer);
    Element *next = populateLineArray(subBuffer, idx + 1);

    if (value == 0)
        return next;

    Element *current = malloc(sizeof(Element));
    current->column = idx;
    current->value = value;
    current->next = next;

    return current;
}

void populateMatrix(SparseMatrix *m, const unsigned int line, const unsigned int column) {
    m->maxColumns = column;
    m->maxLines = line;
    m->matrix = malloc(sizeof(LineArray) * m->maxLines);

    for (unsigned int i = 0; i < m->maxLines; ++i) {
        char buffer[100];
        printf("Enter you %d line:", i + 1);

        fgets(buffer, sizeof(buffer), stdin);

        m->matrix[i] = populateLineArray(buffer, 0);
    }
}

/**
 * Show an entire line of a sparse matrix, including 0
 *
 * @param line a line of the matrix
 * @param maxColumn max column of the matrix
 * @param columnGap gap between the first and the next value of a line
 */
void showPLainLine(const LineArray line, unsigned int maxColumn, int columnGap) {
    if (columnGap > 0)
        for (unsigned int i = 0; i < columnGap; i++)
            printf("0 ");

    if (!line)
        return;

    const unsigned int newGap = (line->next ? line->next->column - line->column : maxColumn - line->column) - 1;

    printf("%d ", line->value);
    showPLainLine(line->next, maxColumn, newGap);
}

void showMatrix(const SparseMatrix *m) {
    for (unsigned int i = 0; i < m->maxLines; ++i) {
        const int firstGap = !m->matrix[i] ? m->maxColumns : m->matrix[i]->column;

        showPLainLine(m->matrix[i], m->maxColumns, firstGap);
        printf("\n");
    }
}
