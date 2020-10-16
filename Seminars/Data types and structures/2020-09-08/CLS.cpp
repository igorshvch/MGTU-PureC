#include <stdio.h>
#include <time.h>
#include <windows.h>

int edit_distance_matrix(char *word1, char *word2, int len_w1, int len_w2, int **matrix);
int edit_distance_recurrison(char *word1, char *word2, int len_w1, int len_w2, int **matrix);
int edit_distance_damerau_levenshtein(char *word1, char *word2, int len_w1, int len_w2, int **matrix);
int min_val(int a, int b);
int min_3_val(int a, int b, int c);
int max_val(int a, int b);
int** create_matrix(int rows, int cols);
void free_matrix(int **matrix, int rows);
void set_matrix_to_default(int **matrix, int rows, int cols);
void print_matrix(int **matrix, int rows, int cols);
LARGE_INTEGER my_timer(int (*lcs_func)(char*, char*, int, int, int**), int timelaps, char *word1, char *word2, int len_w1, int len_w2, int **matrix);


int main()
{
    int lcs_len, timelaps = 100;
    
    char *word1 = "firstword"; 
    char *word2 = "thirdworld";
    int len_w1 = strlen(word1); 
    int len_w2 = strlen(word2);

    LARGE_INTEGER mean_web, mean_lm, mean_lr, mean_dl;

    int (*distance)(char*, char*, int, int, int**);

    int **matrix; 

    matrix = create_matrix(len_w2+1, len_w1+1);
    printf("Matrix created\n");

    distance = edit_distance_matrix;
    mean_lm = my_timer(distance, timelaps, word1, word2, len_w1, len_w2, matrix);

    print_matrix(matrix, len_w2+1, len_w1+1);
    printf("edit_distance_matrix DONE\n");
    set_matrix_to_default(matrix, len_w2+1, len_w1+1);
    print_matrix(matrix, len_w2+1, len_w1+1);

    distance = edit_distance_recurrison;
    mean_lr = my_timer(distance, timelaps, word1, word2, len_w1, len_w2, matrix);

    print_matrix(matrix, len_w2+1, len_w1+1);
    printf("edit_distance_recurrison DONE\n");
    set_matrix_to_default(matrix, len_w2+1, len_w1+1);
    print_matrix(matrix, len_w2+1, len_w1+1);

    distance = edit_distance_damerau_levenshtein;
    mean_dl = my_timer(distance, timelaps, word1, word2, len_w1, len_w2, matrix);

    print_matrix(matrix, len_w2+1, len_w1+1);
    printf("edit_distance_damerau_levenshtein DONE\n");
    set_matrix_to_default(matrix, len_w2+1, len_w1+1);
    print_matrix(matrix, len_w2+1, len_w1+1);


    printf("=====================================================================================\n");
    printf("Words to compute edit distance:\n\t1)'%s'\n\t2)'%s'\n", word1, word2);
    printf("=====================================================================================\n");

    printf("=====================================================================================\n");

    printf("Length of ED is %d\n", edit_distance_matrix(word1, word2, len_w1, len_w2, matrix)); 
    printf("Mean time (100 reps) for edit_distance_matrix: %.2f ms\n", ((float)mean_lm.QuadPart) / timelaps);

    printf("=====================================================================================\n");

    printf("Length of ED is %d\n", edit_distance_recurrison(word1, word2, len_w1, len_w2, matrix)); 
    printf("Mean time (100 reps) for edit_distance_recurrison: %.2f ms\n", ((float)mean_lr.QuadPart) / timelaps);
    
    printf("=====================================================================================\n");

    printf("Length of ED is %d\n", edit_distance_damerau_levenshtein(word1, word2, len_w1, len_w2, matrix)); 
    printf("Mean time (100 reps) for edit_distance_damerau_levenshtein: %.2f ms\n", ((float)mean_dl.QuadPart) / timelaps);

    printf("=====================================================================================\n");

    free_matrix(matrix, len_w2+1);
    
    getchar();

    return 0; 
}


int edit_distance_matrix(char *word1, char *word2, int len_w1, int len_w2, int **matrix)
{
    int x_coord, y_coord, res;
    
    for (x_coord = 1; x_coord <= len_w2; x_coord++)
        matrix[x_coord][0] = matrix[x_coord-1][0] + 1;

    for (y_coord = 1; y_coord <= len_w1; y_coord++)
        matrix[0][y_coord] = matrix[0][y_coord-1] + 1;

    if (len_w1 == 0)
        return len_w2;
    if (len_w2 == 0)
        return len_w1;

    for (x_coord = 1; x_coord <= len_w2; x_coord++)
        for (y_coord = 1; y_coord <= len_w1; y_coord++)
            matrix[x_coord][y_coord] = min_3_val(
                matrix[x_coord-1][y_coord] + 1,
                matrix[x_coord][y_coord-1] + 1,
                matrix[x_coord-1][y_coord-1] + (word1[y_coord] == word2[x_coord] ? 0 : 1)
            );

    res = matrix[len_w2][len_w1];

    return res;
}


int edit_distance_recurrison(char *word1, char *word2, int len_w1, int len_w2, int **matrix)
{
    int cost;

    if (len_w1 == 0)
        return len_w2;
    if (len_w2 == 0)
        return len_w1;

    return min_3_val(
        edit_distance_recurrison(word1, word2, len_w1-1, len_w2, matrix) + 1,
        edit_distance_recurrison(word1, word2, len_w1, len_w2-1, matrix) + 1,
        edit_distance_recurrison(word1, word2, len_w1-1, len_w2-1, matrix) + (word1[len_w1] == word2[len_w2] ? 0 : 1)
    );
}


int edit_distance_damerau_levenshtein(char *word1, char *word2, int len_w1, int len_w2, int **matrix)
{
    int x_coord, y_coord, res;
    
    for (x_coord = 1; x_coord <= len_w2; x_coord++)
        matrix[x_coord][0] = matrix[x_coord-1][0] + 1;

    for (y_coord = 1; y_coord <= len_w1; y_coord++)
        matrix[0][y_coord] = matrix[0][y_coord-1] + 1;

    if (len_w1 == 0)
        return len_w2;
    if (len_w2 == 0)
        return len_w1;

    for (x_coord = 1; x_coord <= len_w2; x_coord++)
        for (y_coord = 1; y_coord <= len_w1; y_coord++){
            matrix[x_coord][y_coord] = min_3_val(
                matrix[x_coord-1][y_coord] + 1,
                matrix[x_coord][y_coord-1] + 1,
                matrix[x_coord-1][y_coord-1] + (word1[y_coord] == word2[x_coord] ? 0 : 1)
            );
            if ((x_coord > 1) && (y_coord >1) && (word1[x_coord] == word2[y_coord-1]) && (word1[x_coord-1] == word2[y_coord]))
                matrix[x_coord][y_coord] = min_val(
                    matrix[x_coord][y_coord], matrix[x_coord-2][y_coord-2] + (word1[y_coord] == word2[x_coord] ? 0 : 1)
                );
        }

    res = matrix[len_w2][len_w1];

    return res;
}


int min_val(int a, int b) 
{ 
    return (a < b)? a : b; 
}


int min_3_val(int a, int b, int c)
{
    return (a < b)? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)); 
}


int max_val(int a, int b) 
{ 
    return (a > b)? a : b; 
}


int** create_matrix(int rows, int cols)
{
    int row;
    int **matrix;

    matrix = (int**) calloc(rows, sizeof(int));
    for (row = 0; row < rows; row++)
        matrix[row] = (int*) calloc(cols, sizeof(int));
    matrix[0][0] = 0;

    return matrix;
}


void free_matrix(int **matrix, int rows)
{
    int row;

    for (row = 0; row < rows; row++)
        free((void*) matrix[row]);
    free((void*) matrix);
    
    printf("Allocated memory released");
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


LARGE_INTEGER my_timer(int (*lcs_func)(char*, char*, int, int, int**), int timelaps, char *word1, char *word2, int len_w1, int len_w2, int **matrix)            //https://docs.microsoft.com/en-us/windows/win32/sysinfo/acquiring-high-resolution-time-stamps
{
    int i = 0;
    
    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
    LARGE_INTEGER Frequency;

    QueryPerformanceFrequency(&Frequency); 
    QueryPerformanceCounter(&StartingTime);

    for (; i<timelaps; i++)
        lcs_func(word1, word2, len_w1, len_w2, matrix);

    QueryPerformanceCounter(&EndingTime);
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
    return ElapsedMicroseconds;
}
