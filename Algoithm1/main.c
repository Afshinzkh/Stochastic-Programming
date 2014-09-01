#ifndef _MAIN_C_
#define _MAIN_C_


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "initialiazer.h"
#include "helper.h"


/*double fun_g (double Q)
{
    return 2 + 3*Q;
}
*/


double cal_sigma (int dmax, double E ,  double prob)
{
    double Sigma = 0 ;
    int i;
    for (i =0; i<=dmax; i++)
    {
        Sigma += prob *  E;
    }
    return Sigma;
}
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

  double *Q = NULL;     /// Optimal desicion
  double *Q_opt = NULL; /// Optimal opptimal desicion
  double *E = NULL;     /// Expected Value
  double *E_min = NULL; /// Minimum Expected Value
  int *I = NULL;        /// Inventory 

  double *pr = (double *) malloc ((size_t)(3 * sizeof(double)));
  double *dk = (double *) malloc ((size_t)(3 * sizeof(double)));
    
  readParameters(&T, &d_max, &I0, &h, &p, &c, &k, pr, dk, argc, argv);

  Q = (double *) malloc((size_t)(T+2) * (2*d_max+1) * sizeof(double));        /// first array is time (t) , second array is inventory
  Q_opt = (double *) malloc((size_t)(T+2) * (2*d_max+1) * sizeof(double));
  E = (double *) malloc((size_t)(2*d_max+1) * (T+2) * sizeof(double));        /// first array is inventory (I) , second array is time
  E_min = (double *) malloc((size_t)(2*d_max+1) * (T+2) * sizeof(double));    
  I = (int *) malloc((size_t)(T+2) * sizeof(int));

    int m,n;      /// useless helper counter


    if (Q == 0 || Q_opt == 0 || E == 0 || E_min == 0 || I == 0) ERROR("Storage cannot be allocated");


    init_E(E, d_max, T);
    I[T+1] = 0;         ///////////////////// bayad barresi shavad
    
    double Sigmas; /// the sum of probabilities


   
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
           for (Q[t+1][i]=abs(I[t]); Q[t+1][i]<= d_max-I[t]; Q[t+1][i]++) /// this loop is stupid and can be merged with the if statement below, but yet we dont touch it
           {
               ///if (Q[t+1][i] <= (d_max-I[t]) && Q[t+1][i] >= abs(I[t]) ) /// because I[t] is negative so the indices should change accordingly
               ///{
               for (m=0;m<=d_max;m++)
               {
                   Sigmas = cal_sigma(d_max,E[i-dk[m]+Q[t+1][i]][t+1],prob);
               }

                E[i][t] = ProcurementCost(Q[t+1][i], c, k) + h*fmax(0,I[t]) + p*fmax(0,I[t]) + Sigmas;
               ///}
               if (E[i][t] < E_min [i][t])
               {
                   E_min [i][t] = E[i][t];
                   Q_opt[t+1][i] = Q[t+1][i];
               }

           }
             printf("E_min (%d, %d) = %f\n", I[t], t, E_min[i][t] );
        }
    }
    E_min[I0][0] = 200;
    Q_opt[1][I0] = 0;
    for (Q[1][I0] = 0; Q[1][I0] <= 2*d_max; Q[1][I0]++)
    {
        if (Q[1][I0]<= fmax(0,d_max-I[0]) && Q[1][I[0]] >= fmin(0,I0))
        {
            E[I[0]][0] = ProcurementCost(Q[1][I0], c, k) + h*fmax(0,I0) + p*fmin(0,I0);/// + sigma_counter(d_max, E[I[0]-])
        }
        if (E[I0][0] < E_min[I0][0])
        {
            E_min[I0][0] = E[I0][0];
             Q_opt[1][I0] = Q[1][I0];
        }

    }

    printf("done!");
    return 0;
}

#endif
