#include <stdio.h>
#include <stdlib.h>
#include "SparseMatrix.h"
#include "Utile.h"

int getNumberOfMatrix(unsigned int currentNumberOfMatrix) {
    int value = getUserNumber("Which matrix you want to use for ?");
    if (value <= 0 || value > currentNumberOfMatrix) return -1;
    return value;
}

void manageMatrixArray(SparseMatrix ***m, unsigned int *max, const unsigned int *current) {
    if (*current == *max) {
        *max += 5;
        SparseMatrix **newM = malloc(sizeof(SparseMatrix *) * *max);

        for (unsigned int i = 0; i < *current; ++i)
            newM[i] = (*m)[i];

        // TODO: freeMatrix();
        free(*m);

        *m = newM;
    }
}

int main() {
    unsigned int maxSize = 2, usedSize = 0;

    SparseMatrix **m = malloc(sizeof(SparseMatrix *) * maxSize);

    // ============= UI ============= */
    char choice = '0';
    while (choice != '8') {
        unsigned int line = 0, column = 0;
        int selectedMatrix;


        printf("\n================ MENU ================");
        printf("\n1. Populate matrix");
        printf("\n2. Show matrix");
        printf("\n3. Show line array matrix");
        printf("\n4. Search value");
        printf("\n5. Affect value");
        printf("\n6. Sum 2 matrix");
        printf("\n8. Leave");
        printf("\n======================================");
        printf("\nYour choice ?");

        choice = getchar();

        switch (choice) {
            case '1':
                line = getUserNumber("Please enter the number of lines for the matrix:");
                column = getUserNumber("Please enter the number of columns for the matrix:");

                manageMatrixArray(&m, &maxSize, &usedSize);
                m[usedSize] = malloc(sizeof(SparseMatrix));
                populateMatrix(m[usedSize++], line, column);
                break;

            case '2':
                selectedMatrix = getNumberOfMatrix(usedSize);

                if (selectedMatrix == -1)
                    printf("Invalid value, please retry");
                else {
                    printf("\n-----> Matrix number %d <-----\n", selectedMatrix);
                    showMatrix(m[selectedMatrix - 1]);
                }
                break;

            case '3':
                break;

            case '4':
                selectedMatrix = getNumberOfMatrix(usedSize);
                if (selectedMatrix == -1)
                    printf("Invalid value, please retry");
                else {
                    line = getUserNumber("Please enter the number of line that you searching for:");
                    column = getUserNumber("Please enter the number of column that you searching for:");

                    const int value = searchValue(m[selectedMatrix - 1], line, column);
                    if (value == -1)
                        printf("The value doesn't exist for line %d, column %d! \n", line, column);
                    else
                        printf("Value at line %d, column %d = %d\n", line, column, value);
                }
                break;

            case '5':
                unsigned int i,j,val;
                printf("enter the ligne: ");
                scanf("%d", &i);
                printf("enter the column: ");
                scanf("%d", &j);
                printf("enter the value: ");
                scanf("%d", &val);
                affectValue(&m, i, j, val);
                break;

            case '6':
                selectedMatrix = getNumberOfMatrix(usedSize);
                int secondSelectedMatrix = getNumberOfMatrix(usedSize);
                if (selectedMatrix == -1 || secondSelectedMatrix == -1)
                    printf("The number of one of the matrix isn't valid, please retry");
                else if (m[selectedMatrix - 1]->maxColumns != m[secondSelectedMatrix - 1]->maxColumns && m[
                             selectedMatrix - 1]->maxLines != m[secondSelectedMatrix - 1]->maxLines)
                    printf("Both matrix should have the same number of line and column, please retry");
                else {
                    sumMatrix(m[selectedMatrix - 1], m[secondSelectedMatrix - 1]);
                    printf("The result us in the first selected matrix:\n-----> Matrix number %d <-----\n", selectedMatrix);
                    showMatrix(m[selectedMatrix - 1]);
                }
                break;

            case '7':
                break;

            case '8':
                printf("\n======== PROGRAM FINISHED ========\n");
                break;

            default:
                printf("\n\nERREUR : votre choix n'est valide ! ");
        }
        emptyBuffer();
    }

    // TODO freeMatrix();
    free(m);

    return 0;
}
