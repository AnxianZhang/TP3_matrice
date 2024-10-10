//
// Created by gadan on 10/10/2024.
//

#ifndef ELEMENT_H
#define ELEMENT_H

typedef struct Element {
    int value;
    unsigned int column;
    struct Element *next;
} Element;

typedef Element *LineArray;

#endif //ELEMENT_H
