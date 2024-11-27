#include <stdio.h>

#include "SparseMatrix.h"
#include "SparseMatrixList.h"
#include "Utile.h"

#define INITIAL_MATRIX_SIZE 2

int getNumberOfMatrix(unsigned int currentNumberOfMatrix) {
    int value = getUserNumber("Which matrix you want to use for ?");
    if (value <= 0 || value > currentNumberOfMatrix) return -1;
    return value;
}

int main() {
    SparseMatrixList *sparseMatrixList = createSparseMatrixList(INITIAL_MATRIX_SIZE, 0);

    // ============= UI ============= */
    char choice = '0';
    while (choice != '9') {
        unsigned int line = 0, column = 0;
        int selectedMatrix;

        printf("\n================ MENU ================");
        printf("\n1. Populate matrix");
        printf("\n2. Show matrix");
        printf("\n3. Show line array matrix");
        printf("\n4. Search value");
        printf("\n5. Affect value");
        printf("\n6. Sum 2 matrix");
        printf("\n7. Get number of gained octet");
        printf("\n8. drop value");
        printf("\n9. Leave");
        printf("\n======================================");
        printf("\nYour choice ?: ");

        choice = getchar();

        switch (choice) {
            case '1':
                line = getUserNumber("Please enter the number of lines for the matrix: ");
                column = getUserNumber("Please enter the number of columns for the matrix: ");
                addMatrixInList(sparseMatrixList, line, column);
                break;

            case '2':
                selectedMatrix = getNumberOfMatrix(sparseMatrixList->usedSpace);

                if (selectedMatrix == -1)
                    printf("Invalid value, please retry");
                else {
                    printf("\n-----> Matrix number %d <-----\n", selectedMatrix);
                    showMatrix(sparseMatrixList->list[selectedMatrix - 1]);
                }
                break;

            case '3':
                selectedMatrix = getNumberOfMatrix(sparseMatrixList->usedSpace);

                if (selectedMatrix == -1)
                    printf("Invalid value, please retry");
                else {
                    printf("\n-----> Matrix number %d <-----\n", selectedMatrix);
                    showMatrixArray(sparseMatrixList->list[selectedMatrix - 1]);
                }
                break;

            case '4':
                selectedMatrix = getNumberOfMatrix(sparseMatrixList->usedSpace);
                if (selectedMatrix == -1)
                    printf("Invalid value, please retry");
                else {
                    line = getUserNumber("Please enter the number of line that you searching for: ");
                    column = getUserNumber("Please enter the number of column that you searching for: ");

                    const int value = searchValue(sparseMatrixList->list[selectedMatrix - 1], line, column);
                    if (value == -1)
                        printf("The value doesn't exist for line %d, column %d! \n", line, column);
                    else
                        printf("Value at line %d, column %d = %d\n", line, column, value);
                }
                break;

            case '5':
                selectedMatrix = getNumberOfMatrix(sparseMatrixList->usedSpace);
                if (selectedMatrix == -1)
                    printf("Invalid value, please retry");
                else {
                    line = getUserNumber("Please enter the number of line that you want to affect value : ");
                    column = getUserNumber("Please enter the number of column that you want to affect value : ");
                    int value = getUserNumber("Please enter the number you want to insert : ");
                    if (line > sparseMatrixList->list[selectedMatrix - 1]->maxLines ||
                        column > sparseMatrixList->list[selectedMatrix - 1]->maxColumns) {
                        printf("Invalid value, please retry");
                        break;
                    }
                    addValueAt(sparseMatrixList->list[selectedMatrix - 1], line - 1, column - 1, value);
                }
                break;

            case '6':
                selectedMatrix = getNumberOfMatrix(sparseMatrixList->usedSpace);
                int secondSelectedMatrix = getNumberOfMatrix(sparseMatrixList->usedSpace);
                if (selectedMatrix == -1 || secondSelectedMatrix == -1)
                    printf("The number of one of the matrix isn't valid, please retry");
                else if (isSelectedMatrixSame(sparseMatrixList->list[selectedMatrix - 1],
                                              sparseMatrixList->list[secondSelectedMatrix - 1]))
                    printf("Both matrix should have the same number of line and column, please retry");
                else {
                    sumMatrix(sparseMatrixList->list[selectedMatrix - 1],
                              sparseMatrixList->list[secondSelectedMatrix - 1]);
                    printf("The result us in the first selected matrix:\n-----> Matrix number %d <-----\n",
                           selectedMatrix);
                    showMatrix(sparseMatrixList->list[selectedMatrix - 1]);
                }
                break;

            case '7':
                selectedMatrix = getNumberOfMatrix(sparseMatrixList->usedSpace);
                if (selectedMatrix == -1)
                    printf("Invalid value, please retry");
                else {
                    printf("\n-----> Matrix number %d <-----\n");
                    printf("\nNumber of octet without 0 is: %d",
                           getNumberOfGainedOctet(sparseMatrixList->list[selectedMatrix - 1]));
                    printf("\nNumber of octet if all 0 are stored: %d\n",
                           getNumberOfGainedOctetWith_0(sparseMatrixList->list[selectedMatrix - 1]));
                }
                break;
            case '8':
                selectedMatrix = getNumberOfMatrix(sparseMatrixList->usedSpace);
                if (selectedMatrix == -1)
                    printf("Invalid value, please retry");
                else {
                    line = getUserNumber("Please enter the number of line that you want to drop value : ");
                    column = getUserNumber("Please enter the number of column that you want to drop value : ");
                    if (line > sparseMatrixList->list[selectedMatrix - 1]->maxLines ||
                        column > sparseMatrixList->list[selectedMatrix - 1]->maxColumns) {
                        printf("Invalid value, please retry");
                        break;
                    }
                    delete_value(sparseMatrixList->list[selectedMatrix - 1], line - 1, column - 1);
                }
                break;

            case '9':
                printf("\n======== PROGRAM FINISHED ========\n");
                break;

            default:
                printf("\n\nERROR : INVALID CHOICE ! ");
        }
        emptyBuffer();
    }

    freeMatrixArray(sparseMatrixList);

    return 0;
}
