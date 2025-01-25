#pragma once


/**
 * @brief resize an array of integers, allocates new memory and frees old memory
 * @param array pointer to the old array
 * @param desiredSize target size of the new array
 * @param currentSize the current size of the array
 * @return pointer to the new array
 */
int * expandIntArray(int * array, int desiredSize, int currentSize);