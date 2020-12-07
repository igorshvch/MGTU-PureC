#include "editdist.h"

int edit_distance_matrix(EMPT_CHAR_MATRIX* wt1, EMPT_CHAR_MATRIX* wt2)
{
    int x_coord, y_coord, res, **matrix, i;
    
    matrix = create_zero_matrix(wt1->rows+1, wt2->rows+1);
    
    for (x_coord = 1; x_coord <= wt1->rows; x_coord++)
        matrix[x_coord][0] = matrix[x_coord-1][0] + 1;
    for (y_coord = 1; y_coord <= wt2->rows; y_coord++)
        matrix[0][y_coord] = matrix[0][y_coord-1] + 1;

    if (wt1->rows == 0)
        return wt2->rows;
    if (wt2->rows == 0)
        return wt1->rows;

    for (x_coord = 1; x_coord <= wt1->rows; x_coord++)
        for (y_coord = 1; y_coord <= wt2->rows; y_coord++)
            matrix[x_coord][y_coord] = MIN_3_VAL(
                matrix[x_coord-1][y_coord] + 1,
                matrix[x_coord][y_coord-1] + 1,
                matrix[x_coord-1][y_coord-1] + ((strcmp(wt1->table[x_coord], wt2->table[y_coord]) == 0) ? 0 : 1)
            );

    res = matrix[wt1->rows][wt2->rows];

    for (i=0; i<wt1->rows+1; i++)
        free((void *) matrix[i]);
    free ((void *) matrix);

    return res;
}

int** create_zero_matrix(int rows, int cols)
{
    int row;
    int **matrix;

    matrix = (int**) calloc(rows, sizeof(int));
    for (row = 0; row < rows; row++)
        matrix[row] = (int*) calloc(cols, sizeof(int));
    matrix[0][0] = 0;

    return matrix;
}
