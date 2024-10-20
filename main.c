#include <stdio.h>
#include <stdlib.h>
#include "SparseMatrix.h"
#include "Utile.h"

int getUserNumber(const char *message) {
    unsigned int number = 0;

    printf(message);
    scanf("%d", &number);
    emptyBuffer();

    return number;
}

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
    int selectedMatrix;
    unsigned int maxSize = 2, usedSize = 0;

    SparseMatrix **m = malloc(sizeof(SparseMatrix *) * maxSize);

    // ============= UI ============= */
    char choice = '0';
    while (choice != '8') {
        unsigned int line = 0, column = 0;

        printf("\n======================================");
        printf("\n1. Populate matrix");
        printf("\n2. Show matrix");
        printf("\n3. Show line array matrix");
        printf("\n4. Search value");
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
                break;

            case '6':
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
