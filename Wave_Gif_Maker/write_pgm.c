#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

int scale(double value, double max){
   int output = 127 / max * value + 127;
   return output;
}

void write_pgm(Matrix mat, int printEveryNPoints, char *filename){
   FILE *fp = fopen(filename, "w");
   if(!fp){
     printf("File unable to be opened. Now exiting program.\n");
     exit(1);
   }

   fprintf(fp, "P2\n");
   fprintf(fp, "%d %d\n", mat.columns, mat.rows);
   fprintf(fp, "255\n");

   // Get max value in matrix
   double max = fabs(mat.data[0][0]);
   for(int i = 0; i < mat.rows; i++){
      for(int  j = 0; j < mat.columns; j++){
         if(fabs(mat.data[i][j]) > max){
            max = fabs(mat.data[i][j]);
         }
      }
   }

   // Output scaled matrix values to file
   for(int i = 0; i < mat.rows; i++){
      for(int j = 0; j < mat.columns; j++){
         fprintf(fp, "%0d ", scale(mat.data[i][j], max));
      }
      fprintf(fp, "\n");

   }
   fclose(fp);
}
