#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "initialCondition.h"
#include "write_pgm.h"
#include "matrix.h"

#ifdef _OPENMP
#include <omp.h>
#endif

void setInitialCondition(Matrix m){
   for(int i = 0; i < m.rows; i++){
      for(int j = 0; j < m.columns; j++){
         double x = 1.0 / (m.rows - 1) * i;
         double y = 1.0 / (m.columns - 1) * j;
         m.data[i][j] = initialCondition(x, y);
      }
   }
}

void step(double k, double h, Matrix tip1, Matrix ti, Matrix tim1) {
   #pragma omp parallel num_threads(2)
   {
      int currentThread = omp_get_thread_num();
      int start, end;

      if(currentThread == 0){
         start = 1;
         end = (tip1.rows - 1) / 2;
      }else{
         start = (tip1.rows - 1) / 2;
         end = tip1.rows - 1;
      }

      for (int row = start; row < end; row++) {
         for (int col = 1; col < tip1.columns - 1; col++){
            tip1.data[row][col]
               = k * k / (h * h) * (ti.data[row - 1][col]
               - 4 * ti.data[row][col] + ti.data[row + 1][col]
               + ti.data[row][col - 1] + ti.data[row][col + 1])
               + 2 * ti.data[row][col] - tim1.data[row][col];

         }
      }

    }
}


void main(int argc, char *argv[]){
   char fileName[16];
   double h = atof(argv[1]);
   double k = atof(argv[2]);
   double endTime = atof(argv[3]);
   int printEveryNSteps = atoi(argv[4]);
   int printEveryNPoints = atoi(argv[5]);
   int steps = 1;
   double t = 0.0;

   if (k >= h) {
      fprintf(stderr, "ERROR: k >= h ");
   }

   int N = (int)(1.0 / h) + 1;
   sprintf(fileName, "%06d.pgm", 0);

   Matrix *states = malloc(3 * sizeof(Matrix));
   states[0] = create_matrix(N, N);
   setInitialCondition(states[0]);
   states[1] = create_matrix(N, N);
   setInitialCondition(states[1]);
   states[2] = create_matrix(N, N);

   write_pgm(states[0], printEveryNPoints, fileName);

   while (t <= endTime) {
      Matrix uk = states[(steps + 1) % 3];
      Matrix ukm1 = states[steps % 3];
      Matrix ukm2 = states[(steps - 1) % 3];

      step(k, h, uk, ukm1, ukm2);

      if (steps % printEveryNSteps == 0) {
         sprintf(fileName, "%06d.pgm", steps / printEveryNSteps);
         printf("%s, t = %f \n", fileName, t);
         write_pgm(uk, printEveryNPoints, fileName);
      }

      ++steps;
      t = k * steps;
   }
}

