#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <time.h>


int** create_rand_matrix(int rows, int cols, int random);
void free_matrix(int **matrix, int rows);
void set_matrix_to_default(int **matrix, int rows, int cols);
void print_matrix(int **matrix, int rows, int cols);
void default_multiplay(int **matrix1, int **matrix2, int **res_matrix, int common, int row1, int col2);
void VINOGRAD_multiplay(int **matrix1, int **matrix2, int **res_matrix, int common, int row1, int col2);
void VINOGRAD_multiplay_optimized(int **matrix1, int **matrix2, int **res_matrix, int common, int row1, int col2);
LARGE_INTEGER my_timer(void (*matr_mult)(int**, int**, int**, int, int, int), int timelaps, int **matr1, int **matr2, int **matr_res, int common, int row1, int col2);


int main()
{
    srand(5);

    int row1, col1, row2, col2, timelaps;
    row1 = 500;
    col1 = 500;
    row2 = 500;
    col2 = 500;
    timelaps = 100;
    int **matrix1, **matrix2, **res_matrix;

    LARGE_INTEGER mean_dm, mean_vm, mean_vmo;

    matrix1 = create_rand_matrix(row1, col1, 1);
    matrix2 = create_rand_matrix(row2, col2, 1);
    res_matrix = create_rand_matrix(row1, col2, 0);

    printf("Matrix1:-------------------------\n");
    //print_matrix(matrix1, row1, col1);
    printf("Matrix2:-------------------------\n");
    //print_matrix(matrix2, row2, col2);
    printf("---------------------------------\n");
    default_multiplay(matrix1, matrix2, res_matrix, col1, row1, col2);
    printf("Res_matrix DEFAULT\n");
    //print_matrix(res_matrix, row1, col2);
    printf("---------------------------------\n");

    set_matrix_to_default(res_matrix, row1, col2);

    VINOGRAD_multiplay(matrix1, matrix2, res_matrix, col1, row1, col2);
    printf("Res_matrix VINOGRAD\n");
    //print_matrix(res_matrix, row1, col2);
    printf("---------------------------------\n");

    set_matrix_to_default(res_matrix, row1, col2);

    VINOGRAD_multiplay_optimized(matrix1, matrix2, res_matrix, col1, row1, col2);
    printf("Res_matrix VINOGRAD optimized\n");
    //print_matrix(res_matrix, row1, col2);
    //printf("---------------------------------\n");

    set_matrix_to_default(res_matrix, row1, col2);

    mean_dm = my_timer(default_multiplay, timelaps, matrix1, matrix2, res_matrix, col1, row1, col2);
    //printf("Print Res_matrix one more time\n");
    //print_matrix(res_matrix, row1, col2);
    printf("---------------------------------\n");
    printf("Mean time (%d reps) for default_multiplay: %.2f ms\n", timelaps, ((float)mean_dm.QuadPart) / timelaps);

    mean_vm = my_timer(VINOGRAD_multiplay, timelaps, matrix1, matrix2, res_matrix, col1, row1, col2);
    //printf("Print Res_matrix one more time\n");
    //print_matrix(res_matrix, row1, col2);
    printf("---------------------------------\n");
    printf("Mean time (%d reps) for VINOGRAD_multiplay: %.2f ms\n", timelaps, ((float)mean_vm.QuadPart) / timelaps);

    mean_vmo = my_timer(VINOGRAD_multiplay_optimized, timelaps, matrix1, matrix2, res_matrix, col1, row1, col2);
    //printf("Print Res_matrix one more time\n");
    //print_matrix(res_matrix, row1, col2);
    printf("---------------------------------\n");
    printf("Mean time (%d reps) for VINOGRAD_multiplay_optimized: %.2f ms\n", timelaps, ((float)mean_vmo.QuadPart) / timelaps);

    free_matrix(matrix1, row1);
    free_matrix(matrix2, row2);
    free_matrix(res_matrix, row1);
    
    getchar();

    return 0; 
}



int** create_rand_matrix(int rows, int cols, int random)
{
    int row, col;
    int **matrix;

    matrix = (int**) calloc(rows, sizeof(int));
    for (row = 0; row < rows; row++)
        matrix[row] = (int*) calloc(cols, sizeof(int));
    
    if (random){
        for (row = 0; row < rows; row++)
            for (col = 0; col < cols; col++)
                matrix[row][col] = rand() % 100;
    }

    return matrix;
}


void free_matrix(int **matrix, int rows)
{
    int row;

    for (row = 0; row < rows; row++)
        free((void*) matrix[row]);
    free((void*) matrix);
    
    printf("Allocated memory released\n");
}


void set_matrix_to_default(int **matrix, int rows, int cols)
{
    int row, col;

    for (row = 0; row < rows; row++)
        for (col = 0; col < cols; col++)
            matrix[row][col] = 0;
}


void print_matrix(int **matrix, int rows, int cols)
{
    int row, col;

    for (row = 0; row < rows; row++){
        printf("\n");
        for (col = 0; col < cols; col++)
            printf("\t%d", matrix[row][col]);
    }
    printf("\n");
}


void default_multiplay(int **matrix1, int **matrix2, int **res_matrix, int common, int row1, int col2)
{
    int holder, row, col;

    for (holder = 0; holder < common; holder++)
        for (row = 0; row < row1; row++)
            for (col = 0; col < col2; col++)
                res_matrix[row][col] += matrix1[row][holder]*matrix2[holder][col];
}


void VINOGRAD_multiplay(int **matrix1, int **matrix2, int **res_matrix, int common, int row1, int col2)
{
    int i, j, k;
    int *mulH, *mulV;

    mulH = (int*) calloc(row1, sizeof(int));
    mulV = (int*) calloc(col2, sizeof(int));

    // 1 часть
    for (i=0 ; i<row1; i++)
        for (k=0; k<common/2; k++)
            mulH[i] = mulH[i] + matrix1[i][2*k]*matrix1[i][2*k+1];
    // 2 часть
    for (j=0; j<col2; j++)
        for (k=0; k<common/2; k++)
            mulV[j] = mulV[j] + matrix2[2*k][j]*matrix2[2*k+1][j];
    // 3 часть
    for (i=0; i<row1; i++)
        for (j=0; j<col2; j++){
            res_matrix[i][j] = -mulH[i] - mulV[j];
            for (k=0; k<common/2; k++){
                res_matrix[i][j] = res_matrix[i][j] + (
                    (matrix1[i][2*k] + matrix2[2*k+1][j])
                    *(matrix1[i][2*k+1] + matrix2[2*k][j])
                );
            }
        }
    // 4 часть
    if (common % 2 == 1) {
        for (i=0; i<row1; i++)
            for (j=0; j<col2; j++)
                res_matrix[i][j] = res_matrix[i][j] + (
                    matrix1[i][common-1]*matrix2[common-1][j]
                );
    }    
    free((void*) mulH);
    free((void*) mulV); 
}


void VINOGRAD_multiplay_optimized(int **matrix1, int **matrix2, int **res_matrix, int common, int row1, int col2)
{
    int i, j, k;
    int *mulH, *mulV;

    mulH = (int*) calloc(row1, sizeof(int));
    mulV = (int*) calloc(col2, sizeof(int));

    // 1 часть
    for (i=0 ; i<row1; i++)
        for (k=0; k<common/2; k++)
            mulH[i] -= matrix1[i][k<<1]*matrix1[i][(k<<1)+1];
    // 2 часть
    for (j=0; j<col2; j++)
        for (k=0; k<common/2; k++)
            mulV[j] -= matrix2[k<<1][j]*matrix2[(k<<1)+1][j];
    // 3 часть
    for (i=0; i<row1; i++)
        for (j=0; j<col2; j++){
            res_matrix[i][j] = mulH[i] + mulV[j];
            for (k=0; k<common/2; k++){
                res_matrix[i][j] += (
                    (matrix1[i][k<<1] + matrix2[(k<<1)+1][j])
                    *(matrix1[i][(k<<1)+1] + matrix2[k<<1][j])
                );
            }
        }
    // 4 часть
    if (common % 2 == 1) {
        for (i=0; i<row1; i++)
            for (j=0; j<col2; j++)
                res_matrix[i][j] += (
                    matrix1[i][common-1]*matrix2[common-1][j]
                );
    }    
    free((void*) mulH);
    free((void*) mulV); 
}


LARGE_INTEGER my_timer(void (*matr_mult)(int**, int**, int**, int, int, int), int timelaps, int **matr1, int **matr2, int **matr_res, int common, int row1, int col2)            //https://docs.microsoft.com/en-us/windows/win32/sysinfo/acquiring-high-resolution-time-stamps
{
    int i = 0;
    
    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
    LARGE_INTEGER Frequency;

    QueryPerformanceFrequency(&Frequency); 
    QueryPerformanceCounter(&StartingTime);

    for (; i<timelaps; i++) {
        set_matrix_to_default(matr_res, row1, col2);
        matr_mult(matr1, matr2, matr_res, common, row1, col2);
    }

    QueryPerformanceCounter(&EndingTime);
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
    return ElapsedMicroseconds;
}
