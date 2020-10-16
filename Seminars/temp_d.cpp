#include <stdio.h>
#include <math.h>

void array_print(double *arr, int len);
double triangle_area(double a, double b, double c);
double distance(double x1, double x2, double y1, double y2);

int main() {
    int n, i;
    double ac[] = {7, 9, 11, 8};
    double bc[] = {1, 2, 3, 4};
    double fc[] = {4, 3, 2, 1};
    double *af, *bf, *cf, *s, *m; // добавил массив m
    n = 5;

    af = new double[n];
    array_print(ac, n);
    bf = new double[n];
    array_print(bc, n); // у тебя был bf. На печать выводился неинициализированный массив с мусором внутри
    cf = new double[n];
    array_print(fc, n); // у тебя был fc

    for (i = 0; i < n; i++) {
        af[i] = ac[i];
        bf[i] = bc[i];
        cf[i] = fc[i];
    }

    printf("\n\n"); // визуально отделим принты

    s = new double[n];
    m = new double[n]; // выделил память подм m
    for (i = 0; i < n; i++){
        s[i] = triangle_area(af[i], bf[i], cf[i]);
        m[i] = distance(af[0], bf[0], af[i], bf[i]); // добавил вычисление расстояние по координатам из массивов
    }

    array_print(s, n);
    array_print(m, n); // добавил печать m

    return 0;
}

void array_print(double *arr, int len)
{
    int i;

    for (i=0; i<len; i++)
        printf("\t%.2f", arr[i]);
    printf("\n");
}

double triangle_area(double a, double b, double c)
{
    double p, s;

    p = (a+b+c)/2;

    if ((a+b)>c && (a+c)>b && (b+c)>a)
        s = sqrt(p*(p-a)*(p-c)*(p-b));
    else {
        printf("FUNC triangle_area: this is not a triangle\n");
        s = 0;
    }

    return s;
}


double distance(double x1, double x2, double y1, double y2)
{
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}