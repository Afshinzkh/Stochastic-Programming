#ifndef _MAIN_C_
#define _MAIN_C_


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "initializer.h"
#include "helper.h"


/*double fun_g (double Q)
{
    return 2 + 3*Q;
}
*/

/*
double cal_sigma (int dmax, double E ,  double prob)
{
    double Sigma = 0 ;
    int i;
    for (i =0; i<=dmax; i++)
    {
        Sigma += prob *  E;
    }
    return Sigma;
}*/
//double cal_E (int i, int t, double Q, double E[])
//{
//
//}
int main(int argc, char *argv[])
{
  int T;          /// Time Period
  int I0;         /// Current Inventory Level
  int d_max;      /// Maximum demand
  double h;       /// Inventory holding cost
  double p;       /// Pentalty cost
  double c;       /// Admin cost
  double k;       /// Procurement cost per piece

  double **Q;     /// desicion to decide number of product to buy
  double **Q_opt; /// Optimal desicion
  double **E;     /// Expected Value
  double **E_min;  /// Minimum Expected Value
  ///double (*Emin)[T+2] = (double(*)[T+2])E_min; 
  int *I;        /// Inventory 

  double *pr = (double *) malloc ((size_t)(3 * sizeof(double)));
  int *dk = (int *) malloc ((size_t)(3 * sizeof(int)));
    
  readParameters(&T, &d_max, &I0, &h, &p, &c, &k, pr, dk, argc, argv);

  
  Q = matrix(0,T+2,0,2*d_max+1);
  Q_opt = matrix(0,T+2,0,2*d_max+1);
  E = matrix(0,2*d_max+1,0,T+2);
  E_min = matrix(0,2*d_max+1,0,T+2);
  ///Q = (double **) malloc((size_t)(T+2) * (2*d_max+1) * sizeof(double));        /// first array is time (t) , second array is inventory
  ///Q_opt = (double **) malloc((size_t)(T+2) * (2*d_max+1) * sizeof(double));
  ///E = (double **) malloc((size_t)(2*d_max+1) * (T+2) * sizeof(double));        /// first array is inventory (I) , second array is time
  ///E_min = (double *) malloc((size_t)(2*d_max+1) * (T+2) * sizeof(double));    
  I = (int *) malloc((size_t)(T+2) * sizeof(int));

  /*  int m,n;      /// useless helper counter*/

  printf("\n*********WELCOME!*********\n");
  ///  if (Q == 0 || Q_opt == 0 || E == 0 || E_min == 0 || I == 0) ERROR("Storage cannot be allocated");


    init_Emin(E_min, d_max, T);
    I[T+1] = 0;         ///////////////////// bayad barresi shavad
    
    /*double Sigmas; /// the sum of probabilities*/

  ///  printf("%f %f %f\n", pr[0],pr[1],pr[2]);
   
    int t; ///counter
    int i = 0; /// helper counter. this is actually the indices for I[t] but since I[t]
                    /// is sometimes negative, we use i to prevent that
    for (t=T;t >=1 ;t--)
    {
        for (I[t] = -d_max; I[t] <= d_max; I[t]++)
        {
           i = I[t] + d_max; /// here i is defined
           E_min[i][t] = 200;
           Q_opt[t+1][i] = 0;
           for (Q[t+1][i]=fmin(I[t],0); Q[t+1][i]<= fmax(d_max-I[t],0); Q[t+1][i]++) /// this loop is stupid and can be merged with the if statement below, but yet we dont touch it
           {
               ///if (Q[t+1][i] <= (d_max-I[t]) && Q[t+1][i] >= abs(I[t]) ) /// because I[t] is negative so the indices should change accordingly
               ///{
          /*     for (m=0;m<=d_max;m++)
               {
                   Sigmas = cal_sigma(d_max,E[i-dk[m]+Q[t+1][i]][t+1],prob);
               }*/
               ///    printf("Entered For Loop %f and %d\n", Q[t+1][i], i);

                E[i][t] = ProcurementCost(Q[t+1][i], c, k) + h*fmax(0,I[t]) + p*fmax(0,I[t]) + CalculateSigma(d_max, i+Q[t+1][i], E_min, dk, pr, t+1);
               ///}
                  ///printf("done with E\n");
               if (E[i][t] < E_min [i][t])
               {
                   E_min [i][t] = E[i][t];
                   Q_opt[t+1][i] = Q[t+1][i];
               }

           }
             printf("E_min (%d, %d) = %.2f \t *\n", I[t], t, E_min[i][t] );
             printf("Q_opt (%d, %d) = %.2f \t *\n", t+1, I[t], Q_opt[t+1][i] );
             printf("**************************\n");
        }
    }
    
    int indice = I0+d_max;
    E_min[indice][0] = 200;
    Q_opt[1][indice] = 0;
    for (Q[1][indice] = fmin(I0,0); Q[1][indice] <= fmax(0,d_max-I0); Q[1][indice]++)
    {
       /* if (Q[1][I0]<= fmax(0,d_max-I0) && Q[1][I0] >= fmin(0,I0))
        {*/
      ///    printf("Entered Second For %f and %d\n", Q[1][indice], indice);
            E[indice][0] = ProcurementCost(Q[1][indice], c, k) + h*fmax(0,I0) + p*fmin(0,I0) + CalculateSigma(d_max, indice+Q[1][indice], E_min, dk, pr, 1);
       /* }*/
        if (E[indice][0] < E_min[indice][0])
        {
            E_min[indice][0] = E[indice][0];
             Q_opt[1][indice] = Q[1][indice];
        }

    }
    printf("E_min(%d, 0) = %.2f \t *\n", I0, E_min[indice][0] );  
    printf("Q_opt(1, %d) = %.2f \t *\n", I0, Q_opt[1][indice] );
    printf("**************************\n");
    free(Q);
    free(Q_opt);
    free(I);
    free(E);
    free(E_min);
    free(dk); 
    free(pr);
    printf("**********DONE!***********\n\n");
    return 0;
}

#endif
