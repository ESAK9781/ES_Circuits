#pragma once


/**
 * @brief resize an array of integers, allocates new memory and frees old memory
 * @param array pointer to the old array
 * @param desiredSize target size of the new array
 * @param currentSize the current size of the array
 * @return pointer to the new array
 */
int * expandIntArray(int * array, int desiredSize, int currentSize);


/**
 * @brief resize an array of data structures, allocates new memory and frees old memory
 * @param array pointer to the old array
 * @param elementSize the size of the data type this array is filled with
 * @param desiredSize target size of the new array
 * @param currentSize the current size of the array
 * @return pointer to the new array
 */
void * expandArray(void * array, size_t elementSize, int desiredSize, int currentSize);