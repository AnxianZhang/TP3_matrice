#include <stdio.h>
#include "SparseMatrix.h"
#include "Utile.h"

int getUserNumber(const char *message) {
    unsigned int number = 0;

    printf(message);
    scanf("%d", &number);
    emptyBuffer();

    return number;
}

int main() {
    SparseMatrix m;

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

                populateMatrix(&m, line, column);
                break;
            case '2':
                // TODO: enable the possibility to créate severa matrix and chose which one to show
                showMatrix(&m);

                break;

            case '3':
                break;

            case '4':
                line = getUserNumber("Please enter the number of line that you searching for:");
                column = getUserNumber("Please enter the number of column that you searching for:");

                const int value = searchValue(&m, line, column);
                if (value == -1)
                    printf("The value doesn't exist for line %d, column %d! \n", line, column);
                else
                    printf("Value at line %d, column %d = %d\n", line, column, value);

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

    return 0;
}
