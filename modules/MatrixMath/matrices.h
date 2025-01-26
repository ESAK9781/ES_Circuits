#pragma once

#include <stdbool.h>

typedef struct {
    int w;
    int h;
    float ** values;

    float ** variables;
    int numVariables;
    bool associatedVariables;
} Matrix;


typedef struct {
    float ** variables;
    float * coefficients;
    int numTerms;
    int allocatedTerms;

    float equals;
} LinearEquation;

/**
 * @brief Create a new linear equation that is empty
 * @return Pointer to the new linear equation ADT
 */
LinearEquation * newEquation();

/**
 * @brief Create a new matrix adt
 * @param w the width of the matrix (can be changed later)
 * @param h the height of the matrix (can be changed later)
 * @return pointer to the new matrix adt
 */
Matrix * newMatrix(int w, int h);

/**
 * @brief frees the memory associated with a LinearEquation adt
 * @param equation pointer to the LinearEquation adt
 * @return none
 */
void freeEquation(LinearEquation * equation);

/**
 * @brief frees the memory associated with a Matrix adt
 * @param matrix pointer to the Matrix adt
 * @return none
 */
void freeMatrix(Matrix * matrix);

/**
 * @brief adds a single variable coefficient term to the left side of the linear equation
 * @param equation pointer to the linear equation adt
 * @param variable pointer to where the variable will be stored in memory
 * @param coefficient the coefficient of that variable
 * @return none
 */
void addVariable(LinearEquation * equation, float * variable, float coefficient);

/**
 * @brief incorporate a single equation into a matrix
 * @param matrix pointer to the matrix adt
 * @param equation pointer to the linear equation adt
 * @return none
 */
void includeEquation(Matrix * matrix, LinearEquation * equation);

/**
 * @brief completes jordan gauss elimination on a matrix to convert it into reduced row echelon form
 * @param matrix pointer to the matrix
 * @return none
 */
void jordanGauss(Matrix * matrix);

/**
 * @brief solves a matrix and places the resulting values into variable locations in memory
 * @param matrix pointer to the matrix to solve
 * @return none
 */
void solveMatrix(Matrix * matrix);

/**
 * @brief add a new column to the left side of the matrix
 * @param matrix pointer to the matrix
 * @return none
 */
void addColumn(Matrix * matrix);

/**
 * @brief add a new column to the left side of the matrix that corresponds to a variable
 * @param matrix pointer to the matrix
 * @param var pointer to the variable's location in memory
 * @return none
 */
void addVariableM(Matrix * matrix, float * var);

/**
 * @brief add a single row to the bottom of the matrix
 * @param matrix pointer to the matrix
 * @return none
 */
void addRow(Matrix * matrix);