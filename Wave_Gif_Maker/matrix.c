#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix create_matrix(unsigned rows, unsigned columns){
   Matrix mat;
   mat.rows = rows;
   mat.columns = columns;
   mat.data = (double **) malloc(rows *  sizeof(double*));
   for(int i = 0; i < rows; i++){
    mat.data[i] = (double *) malloc(columns * sizeof(double));
    for(int j = 0; j < columns; j++){
      mat.data[i][j] = 0.0;
    }
   }
   return mat;
}

void print_matrix(Matrix mat){
   for(int i = 0; i < mat.rows; i++){
    printf("%lf", mat.data[i][0]);
    for(int j = 1; j < mat.columns; j++){
     printf(" %lf", mat.data[i][j]);
    }
   printf("\n");
   }
}

void free_matrix(Matrix mat){
   for(int i = 0; i <  mat.rows; i++){
     free(mat.data[i]);
   }
    free(mat.data);
}

