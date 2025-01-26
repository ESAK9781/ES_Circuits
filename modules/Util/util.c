#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

int * expandIntArray(int * array, int desiredSize, int currentSize) {
    int * out = calloc(desiredSize, sizeof(int));

    if (out == NULL) {
        printf("ERROR: lol, not even enough ram for integers\n");
        exit(-1);
    }

    for (int i = 0; i < currentSize; i++) {
        out[i] = array[i];
    }

    free(array);
    return out;
}

void * expandArray(void * array, size_t elementSize, int desiredSize, int currentSize) {
    void * newArray = calloc(desiredSize, elementSize);

    memcpy(newArray, array, elementSize * currentSize);
    free(array);

    return newArray;
}