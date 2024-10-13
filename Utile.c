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
