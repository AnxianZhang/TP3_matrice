//
// Created by gadan on 10/13/2024.
//

#include "Utile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char *trim(const char *buffer) {
    int start = 0, end = strlen(buffer) - 1;

    while (buffer[start] == ' ' && buffer[start] != '\0') ++start;
    while (end >= start && buffer[end] == ' ') --end;

    int distance = end - start + 1;

    char *newBuffer = malloc(sizeof(char) * (distance + 1));

    if (newBuffer == NULL) {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < distance; ++i)
        newBuffer[i] = buffer[start + i];

    newBuffer[distance] = '\0';

    return newBuffer;
}

char *coverExcessSpace(char *buffer) {
    int i = 0, j = 0;

    while (buffer[i] != '\0') {
        if (buffer[i] == ' ' && (j == 0 || buffer[j - 1] == ' '))
            i++;
        else {
            buffer[j++] = buffer[i++];
        }
    }

    buffer[j] = '\0';
    return buffer;
}