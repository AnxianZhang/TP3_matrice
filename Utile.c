//
// Created by gadan on 10/13/2024.
//

#include "Utile.h"

#include <stdio.h>

void emptyBuffer() {
    char c = ' ';
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

int getUserNumber(const char *message) {
    unsigned int number = 0;

    printf(message);
    scanf("%d", &number);
    emptyBuffer();

    return number;
}