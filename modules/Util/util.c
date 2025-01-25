#include <stdlib.h>
#include <stdio.h>

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