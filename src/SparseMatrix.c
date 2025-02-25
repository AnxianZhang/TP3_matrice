//
// Created by gadan on 10/10/2024.
// Authors: ZHANG Anxian & MIGUEU Brayan
//

#include "stdio.h"
#include "SparseMatrix.h"

#include <stdlib.h>
#include <string.h>

#include "Utile.h"

#define BUFFER_MAX_SIZE 255

/**
 * Get the substring before the first of ' '
 * and convert it into an integer
 *
 * @param src original string
 * @param substring
 * @return the converted substring into integer
 */
int getNumber(const char *src, const char *substring) {
    char destination[BUFFER_MAX_SIZE] = {0};

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
 * @param totalColumn the number of columns of the matrix
 * @param nbColumn index of the first element in the line
 * @return all a linked list of all value != 0
 */
LineArray populateLineArray(const char *buffer, const unsigned short totalColumn, const unsigned short nbColumn) {
    if (buffer == NULL || buffer[0] == '\0' || totalColumn == nbColumn) {
        return NULL;
    }

    char *subBuffer = strchr(buffer, ' ');

    if (subBuffer != NULL)
        subBuffer = subBuffer + 1;

    const int value = getNumber(buffer, subBuffer);
    Element *next = populateLineArray(subBuffer, totalColumn, nbColumn + 1);

    if (value == 0)
        return next;

    Element *current = malloc(sizeof(Element));

    if (current == NULL) return NULL;

    current->column = nbColumn;
    current->value = value;
    current->next = next;

    return current;
}

void populateMatrix(SparseMatrix *m, unsigned int line, unsigned int column) {
    m->maxColumns = column;
    m->maxLines = line;
    m->matrix = malloc(sizeof(LineArray) * m->maxLines);

    if (m->matrix == NULL) return;

    for (unsigned int i = 0; i < m->maxLines; ++i) {
        char buffer[BUFFER_MAX_SIZE];
        printf("Enter you %d line:", i + 1);
        fgets(buffer, sizeof(buffer), stdin);

        char *newBuffer = coverExcessSpace(trim(buffer));

        m->matrix[i] = populateLineArray(newBuffer, m->maxColumns, 0);
        free(newBuffer);
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

void showMatrixArray(const SparseMatrix *m) {
    int i;
    LineArray head;
    for (i = 0; i < m->maxLines; ++i) {
        head = m->matrix[i];
        printf("\n| %d |  ==>  ", i + 1);
        while (head) {
            if (head->value != 0) {
                printf("||val: %d - col: %d||  ==>  ", head->value, head->column + 1);
                head = head->next;
            }
        }
        printf("|x|\n");
    }
}

/**
 * Search the value of a provided column
 *
 * @param line the matrix line
 * @param target the column that we're searching for
 * @return the value at the specified column
 */
int getValueFrom(const LineArray line, unsigned int target) {
    if (line->column > target || (!line->next && line->column < target))
        return 0;

    if (line->column == target)
        return line->value;

    return getValueFrom(line->next, target);
}

int searchValue(const SparseMatrix *m, unsigned int i, unsigned int j) {
    if (i > m->maxLines || j > m->maxColumns || i == 0 || j == 0)
        return -1;

    // if the matrix is null, it means that all the value of line i - 1 are equal to 0
    if (!m->matrix[i - 1]) return 0;

    return getValueFrom(m->matrix[i - 1], j - 1);
}

void addValueAt(SparseMatrix *m, unsigned int i, unsigned int j, int val) {
    if (val != 0 && i < m->maxLines && j < m->maxColumns) {
        int test = 0;
        LineArray head;
        head = m->matrix[i];
        while (head) {
            if (head->column == j) {
                // if element i j exist
                head->value = val;
                test = 1; // element i j exist
                return;
            }
            head = head->next;
        }
        if (test == 0) {
            // element i j does not exist in matrix
            LineArray element = (Element *) malloc(sizeof(Element));

            if (element == NULL) return;

            element->value = val;
            element->column = j;
            head = m->matrix[i];
            if (head == NULL) {
                element->next = NULL;
                m->matrix[i] = element;
            } else {
                if (head->column > j) {
                    element->next = head;
                    m->matrix[i] = element;
                    return;
                }
                while (head->next) {
                    if (head->column < j && (head->next)->column > j) {
                        element->next = head->next;
                        head->next = element;
                        return;
                    }
                    head = head->next;
                }
                // j > all j in matrix
                element->next = NULL;
                head->next = element;
            }
        }
    }
    if (val == 0 && i < m->maxLines && j < m->maxColumns)
        delete_value(m, i, j);
}

void delete_value(SparseMatrix *m, unsigned int line, unsigned int column) {
    if (!m || !m->matrix[line]) return;

    Element *current = m->matrix[line];
    Element *previous = NULL;

    while (current->column != column) {
        previous = current;
        current = current->next;
    }

    if (!previous)
        m->matrix[line] = current->next;
    else {
        previous->next = current->next;
    }

    free(current);
}

int getNumberOfGainedOctet(const SparseMatrix *m) {
    int i, counter = 0;
    counter = sizeof(m);
    LineArray head;
    for (i = 0; i < m->maxLines; ++i) {
        head = m->matrix[i];
        while (head) {
            counter += sizeof(Element);
            head = head->next;
        }
    }
    return counter;
}

int getNumberOfGainedOctetWith_0(const SparseMatrix *m) {
    int counter = 0;
    counter = sizeof(m);
    counter = counter + m->maxColumns * m->maxLines * sizeof(Element);
    return counter;
}

Element *copyElement(const Element *element) {
    Element *copy = malloc(sizeof(Element));

    if (!copy) return NULL;

    copy->column = element->column;
    copy->value = element->value;

    return copy;
}

void sumMatrix(const SparseMatrix *m1, const SparseMatrix *m2) {
    for (unsigned int i = 0; i < m1->maxLines; ++i) {
        Element *headM1 = m1->matrix[i];
        Element *headM2 = m2->matrix[i];
        Element *previousM1 = NULL;

        while (headM1 || headM2) {
            if (headM1 && (!headM2 || headM1->column < headM2->column)) {
                previousM1 = headM1;
                headM1 = headM1->next;
            } else if (!headM1 || headM1->column > headM2->column) {
                Element *copy = copyElement(headM2);

                if (previousM1) {
                    previousM1->next = copy;
                } else {
                    m1->matrix[i] = copy;
                }

                copy->next = headM1;
                previousM1 = copy;

                headM2 = headM2->next;
            } else {
                // headM1->column == headM2->column
                headM1->value += headM2->value;

                previousM1 = headM1;
                headM1 = headM1->next;
                headM2 = headM2->next;
            }
        }
    }
    printf("\n");
}

void freeMatrix(SparseMatrix *m) {
    for (int i = 0; i < m->maxLines; ++i) {
        LineArray head = m->matrix[i];
        while (head) {
            LineArray temp = head;
            head = head->next;
            free(temp);
        }
    }
    free(m);
}
