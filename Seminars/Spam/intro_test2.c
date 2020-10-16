#include <stdio.h>
#include <stdlib.h>

struct point {int x, y;};
int test(struct point p1, struct point p2);

int main(){

    FILE *data, *result;

    int i, n, dots_on_line=0;
    struct point dots_array[1000];

    if( (data = fopen( "input.txt", "r" )) == NULL){
        printf("Data file error!");
        return 1;
    }
    if( (result = fopen( "output.txt", "w" )) == NULL){
        printf("Result file error!");
        return 1;
    }

    fscanf(data, "%d", &n);
    for (int i = 0; i < n; i++)
        fscanf(data, "%d %d", &dots_array[i].x, &dots_array[i].y);
    
    for (int i = 0; i < n-1; i++)
        dots_on_line += test(dots_array[i], dots_array[i+1]);
    dots_on_line += test(dots_array[n-1], dots_array[0]);

    printf("Dots on line: %d\n", dots_on_line);
    
    fprintf(result,  "Dots on line: %d\n", dots_on_line);
    fclose(data);
    fclose(result);

    getch();
    return 0;
}

int test(struct point p1, struct point p2)
{
    int min_x, min_y, max_x, max_y, x, y;
    int dots_on_line = 0;

    min_x = p1.x > p2.x ? p2.x : p1.x;
    min_y = p1.y > p2.y ? p2.y : p1.y;

    max_x = p1.x > p2.x ? p1.x : p2.x;
    max_y = p1.y > p2.y ? p1.y : p2.y;

    printf("x1=%d, y1=%d, x2=%d, y2=%d\n", p1.x, p1.y, p2.x, p2.y);
    printf("min_x=%d, max_x=%d, min_y=%d, max_y=%d\n", min_x, max_x, min_y, max_y);

    for (x=min_x; x<max_x+1; x++)
        for (y=min_y; y<max_y+1; y++){
            printf("X=%d\tY=%d", x, y);
            if ((x-p1.x)*(p2.y-p1.y)-(y-p1.y)*(p2.x-p1.x) == 0) {
                dots_on_line++;
                printf("\tON LINE\n");
            }
            else
                printf("\n");
        }
    
    dots_on_line--; //удаляем задваивание точек на концах отрезков, образующих угол
    
    printf("Dots on line: %d\n", dots_on_line);

    return dots_on_line;
}