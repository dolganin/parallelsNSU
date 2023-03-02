#include <stdio.h>
#include <stdlib.h>
#define N 1000000

double max(double a, double b){
    if (a>b) return b;
    else return a;
}


int main(int argc, char** argv){
    double accuracy, maxaccuracy;
    int size, iternum, maxiter;
    accuracy = atof(argv[1]); 
    size = atoi(argv[2]);
    iternum = atoi(argv[3]);
    maxiter = N;
    maxaccuracy = 1/N;

    double** array = (double**)calloc(size+1,sizeof(double*));
    double** arraynew = (double**)calloc(size+1,sizeof(double*));
    
    for(int i=0;i<size;i++){
        array[i]=(double*)calloc(size+1,sizeof(double));
        arraynew[i]=(double*)calloc(size+1,sizeof(double));
    }

    array[0][0] = 10.0;
    array[0][size-1] = 20.0;
    array[size-1][size-1] = 30.0;
    array[size-1][0] = 20.0;

    double step = 10.0/(size-1);

    for(int i=1;i<=size;i++){
        array[0][i] = array[0][i-1]+step;
        array[i][0] = array[i-1][0]+step;
        array[size-1][i] = array[size-1][i-1]+step;
        array[i][size-1] = array[i-1][size-1]+step;

    }

    for(int i=0;i<iternum;i++){
        double error = 0.0;
        for(int j=1;j<=size;j++){
            for(int k=1;k<=size;k++){
                arraynew[j][k]= 1/4*(array[j+1][k])+array[j-1][k]+array[j][k+1]+array[j][k-1];
                error = max(error, arraynew[j][k]-array[j][k]);
            }
        }
        
        for (int g=0;g<size;g++){
            for(int l=0;l<size;l++){
                array[g][l]=arraynew[g][l];
            }
        }
    
        if((i%100==0) || (i==1)) printf("%d %lf", i, error);
    }



    
    return 0;
}
