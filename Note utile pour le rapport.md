## Optimisation

#### Optimisation de la fonction manageMatrixArray():
```c
void manageMatrixArray(SparseMatrix ***m, unsigned int *max, const unsigned int *current) {  
    if (*current == *max) {  
        *max += 5;  
        SparseMatrix **newM = malloc(sizeof(SparseMatrix *) * *max);  
  
        for (unsigned int i = 0; i < *current; ++i)  
            newM[i] = *m[i];  
  
        free(*m);  
  
        *m = newM;  
    }  
}
```

>Initialement, le premier paramètre était un pointeur vers un tableau de pointeurs de matrices creuses (`SparseMatrix **`). Cependant, lorsque la liste atteint sa capacité maximale et doit être redimensionnée, cela nécessiterait de copier toutes les matrices dans une nouvelle liste, ce qui est coûteux en termes de p. Afin d'éviter de dupliquer les structures elles-mêmes, il est plus efficace d'utiliser un tableau de pointeurs de pointeurs (`SparseMatrix ***`), ce qui permet de ne copier que les adresses des matrices dans le nouveau tableau. Ainsi, seules les références sont déplacées, et non les données elles-mêmes, ce qui réduit le coût de l'opération


# ==Données de TEST==

#### Création de matrice statiquement:
```c
// ==================== SparceMatrix.h ====================
/**  
 * USED FOR TESTS 
 * 
 * @param m 
 * @param line 
 * @param column 
 * @param predefined_input 
 * */
void populateMatrixTEST(SparseMatrix *m, unsigned int line, unsigned int column, const char *predefined_input[]);



// ==================== SparceMatrix.c ====================
void populateMatrixTEST(SparseMatrix *m, unsigned int line, unsigned int column, const char *predefined_input[]) {  
    m->maxColumns = column;  
    m->maxLines = line;  
    m->matrix = malloc(sizeof(LineArray) * m->maxLines);  
  
    for (unsigned int i = 0; i < m->maxLines; ++i) {  
        m->matrix[i] = populateLineArray(predefined_input[i], 0);  
    }  
}
```

#### Création de plusieurs matrice creuses:
```c
void test() {  
    const char *predefined_input[] = {  
        "0 0 0 0 0",  
        "1 0 3 0 0",  
        "0 0 0 2 5",  
        "100 0 0 -20"  
    };  
  
    const char *predefined_input2[] = {  
        "-3 0 3 -5 0",  
        "1000 25 6 9 4",  
        "0 0 0 0 0",  
        "-9 6 1 8 0"  
    };  
  
    const char *predefined_input3[] = {  
        "-3 0 3",  
        "0 0 0",  
        "0 7 0",  
    };  
  
    unsigned int maxSize = 2;  
    unsigned int usedSize = 0;  
  
    SparseMatrix **m = malloc(sizeof(SparseMatrix *) * maxSize);  
  
    manageMatrixArray(&m, &maxSize, &usedSize);  
    m[usedSize] = malloc(sizeof(SparseMatrix));  
    populateMatrixTEST(m[usedSize], 4, 5, predefined_input);  
    ++usedSize;  
    printf("1rt fill %d %d\n", maxSize, usedSize);  
  
    manageMatrixArray(&m, &maxSize, &usedSize);  
    m[usedSize] = malloc(sizeof(SparseMatrix));  
    populateMatrixTEST(m[usedSize], 4, 5, predefined_input2);  
    ++usedSize;  
    printf("2ed fill %d %d\n", maxSize, usedSize);  
  
    manageMatrixArray(&m, &maxSize, &usedSize);  
    m[usedSize] = malloc(sizeof(SparseMatrix));  
    populateMatrixTEST(m[usedSize], 3, 3, predefined_input3);  
    usedSize++;  
    printf("3ed fill %d %d\n", maxSize, usedSize);  
  
  
    for (unsigned int i = 0; i < usedSize; ++i) {  
        showMatrix(m[i]);  
        printf("\n");  
    }  
}

```

### Calcule des complexités

**populateMatrix** :
```c
int getNumber(const char *src, const char *substring) {
    char destination[100] = {0};//                         1

    if (substring == NULL)//                               1
        return atoi(src);

    const unsigned int length = substring - src;//         2
    strncpy(destination, src, length);//                   1
    destination[length] = '\0';//                          1

    return atoi(destination);
}


LineArray populateLineArray(const char *buffer, unsigned short idx) {
    if (buffer == NULL || buffer[0] == '\0') { //           3
        return NULL;
    }

    char *subBuffer = strchr(buffer, ' '); //               1

    if (subBuffer != NULL)//                                1
        subBuffer = subBuffer + 1;//                        2

    const int value = getNumber(buffer, subBuffer);//       1
    Element *next = populateLineArray(subBuffer, idx + 1);//maxColumn = m

    if (value == 0)//                                       1
        return next;

    Element *current = malloc(sizeof(Element));//           1
    current->column = idx;//                                1
    current->value = value;//                               1
    current->next = next;//                                 1

    return current;
}

void populateMatrix(SparseMatrix *m, const unsigned int line, const unsigned int column) {
    m->maxColumns = column;//                               1
    m->maxLines = line;//                                   1
    m->matrix = malloc(sizeof(LineArray) * m->maxLines);//  1

    for (unsigned int i = 0; i < m->maxLines; ++i) {//      maxLine = n
        char buffer[100] = {0};//                           1
        printf("Enter you %d line:", i + 1);

        fgets(buffer, sizeof(buffer), stdin);//             1

        m->matrix[i] = populateLineArray(buffer, 0);//      1
    }
}
```
```[!info] la complexité de populate matrix est de O(n*m)```