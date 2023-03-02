#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000000

double array[1024][1024];
double arraynew[1024][1024];

double maxv(double a, double b) {
    if (a < b) return b;
    return a;
}


int main(int argc, char** argv) {
    double accuracy;
    int size, iternum;
    accuracy = atof(argv[1]);
    size = atoi(argv[2]);
    iternum = atoi(argv[3]);

    accuracy = 0.0;

    array[0][0] = 10.0;
    array[0][size-1] = 20.0;
    array[size-1][size-1] = 30.0;
    array[size-1][0] = 20.0;

    arraynew[0][0] = 10.0;
    arraynew[0][size - 1] = 20.0;
    arraynew[size-1][size - 1] = 30.0;
    arraynew[size-1][0] = 20.0;


    double error = 1.0;
    double step = 10.0 / size;
    
#pragma acc paralell loop vector vector_length(128) gang num_gangs(1024)
    for (int i = 1; i < size; i++) {
        array[0][i] = array[0][i - 1] + step;
        array[i][0] = array[i - 1][0] + step;
        array[size - 1][i] = array[size - 1][i - 1] + step;
        array[i][size - 1] = array[i - 1][size - 1] + step;

    }

    for (int i = 1; i < size; i++) {
        arraynew[0][i] = arraynew[0][i - 1] + step;
        arraynew[i][0] = arraynew[i - 1][0] + step;
        arraynew[size - 1][i] = arraynew[size - 1][i - 1] + step;
        arraynew[i][size - 1] = arraynew[i - 1][size - 1] + step;

    }


    int i = 0;
     while((i < iternum) && (error > accuracy)){
         error = 0;
        for (int k = 1; k< size-1; k++) {
            for (int j = 1; j < size-1; j++) {
                arraynew[k][j] = 0.25 * (array[k + 1][j] + array[k - 1][j] + array[k][j - 1] + array[k][j + 1]);
                error = maxv(error, arraynew[k][j]-array[k][j]);
            }
        }

        for (int k = 0;  k< size; k++) {
            for (int j = 0; j < size; j++) {
                array[k][j] = arraynew[k][j];
            }
        }
        i++;
    }

     printf("%d %lf", i, error);


    return 0;
}
