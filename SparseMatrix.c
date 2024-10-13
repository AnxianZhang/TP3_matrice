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
        printf("\nEnter you %d line:", i);

        fgets(buffer, sizeof(buffer), stdin);

        m->matrix[i] = populateLineArray(buffer, 0);
    }
}
