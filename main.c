#include <stdio.h>
#include "SparseMatrix.h"
#include "Utile.h"

int main() {
    SparseMatrix m;

    // ============= UI ============= */
    char choice = '0';
    while (choice != '8') {
        printf("\n======================================");
        printf("\n1. Populate matrix");
        printf("\n2. Show matrix");
        printf("\n3. Show line array matrix");
        printf("\n8. Leave");
        printf("\n======================================");
        printf("\nYour choice ?");

        choice = getchar();

        switch (choice) {
            case '1':
                unsigned int lines = 0, columns = 0;
                printf("Please enter the number of lines for the matrix:");
                scanf("%d", &lines);
                emptyBuffer();

                printf("Please enter the number of columns for the matrix:");
                scanf("%d", &columns);
                emptyBuffer();

                populateMatrix(&m, lines, columns);
                break;
            case '2':
                break;

            case '3':
                break;

            case '4':
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
