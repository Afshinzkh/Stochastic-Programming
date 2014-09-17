#ifndef _MAIN_C_
#define _MAIN_C_


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "initializer.h"
#include "helper.h"
#include "ProbCalculator.h"



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
  double **E_min; /// Minimum Expected Value
  int *I;         /// Inventory 

  
  readParameters(&T, &d_max, &I0, &h, &p, &c, &k, argc, argv);

  /************ Allocate the size of Matrices *******************************/  

  int Demand_Data_num;   /// The Number of Demand Data that user should type in
  printf("\nEnter Number of Data you have: ");
  scanf("%d", &Demand_Data_num);
  double *ProbabilityArray = (double *) malloc ((size_t)(Demand_Data_num * sizeof(double)));
  int *Demand_Data_Array = (int *) malloc ((size_t)(Demand_Data_num * sizeof(int)));
  CalculatePrabability(ProbabilityArray, Demand_Data_Array, Demand_Data_num, d_max);

  ///readParameters(&T, &d_max, &I0, &h, &p, &c, &k, ProbabilityArray, Demand_Data_Array, argc, argv);
  
  /************ Allocate the size of Matrices *******************************/
  
  Q = matrix(0,T+2,0,2*d_max+1);
  Q_opt = matrix(0,T+2,0,2*d_max+1);
  E = matrix(0,2*d_max+1,0,T+2);
  E_min = matrix(0,2*d_max+1,0,T+2);
  I = (int *) malloc((size_t)(T+2) * sizeof(int));

  if (Q == 0 || Q_opt == 0 || E == 0 || E_min == 0 || I == 0) ERROR("Storage cannot be allocated");

  printf("\n*********WELCOME!*********\n");
  


    init_Emin(E_min, d_max, T);     ///Initializes the E_min Matrix to zero for all values, "This is because the future Values should be 
                                    /// Zero for first Loop"
    I[T+1] = 0;        
    int t;                         ///time counter
    int I_indice = 0;              /// helper counter. this is actually the indices for I[t] but since I[t]
                                  /// is sometimes negative, we use I_indice to prevent that

    for (t=T;t >=1 ;t--)
    {
        for (I[t] = -d_max; I[t] <= d_max; I[t]++)
        {
           I_indice = I[t] + d_max;     /// here I_indice is defined
           E_min[I_indice][t] = 900000;
           Q_opt[t+1][I_indice] = 0.0;
           for (Q[t+1][I_indice]=fmin(I[t],0); Q[t+1][I_indice]<= fmax(d_max-I[t],0); Q[t+1][I_indice]++) 
           {


                E[I_indice][t] = ProcurementCost(Q[t+1][I_indice], c, k) + h*fmax(0,I[t]) + p*fmin(0,I[t]) + CalculateSigma(d_max, I_indice+Q[t+1][I_indice], E_min, Demand_Data_Array, ProbabilityArray, t+1, Demand_Data_num);
                ///printf("Here is E: %.2f for Q = %2.f \n", E[I_indice][t], Q[t+1][I_indice] );
                if (E[I_indice][t] < E_min [I_indice][t])
                {
                   E_min [I_indice][t] = E[I_indice][t];
                   Q_opt[t+1][I_indice] = Q[t+1][I_indice];
                }

           }
                printf("E_min (%d, %d) = %4.0f\t *\n", I[t], t, E_min[I_indice][t] );
                printf("Q_opt (%d, %d) = %4.0f \t *\n", t+1, I[t], Q_opt[t+1][I_indice] );
                printf("**************************\n");
        }
    }
    
    int I0_indice = I0+d_max;     ///here I0_indice is defined has the same feauter of I_indice butfor I0
    E_min[I0_indice][0] = 900000;
    Q_opt[1][I0_indice] = 0.0;
    for (Q[1][I0_indice] = fmin(I0,0); Q[1][I0_indice] <= fmax(0,d_max-I0); Q[1][I0_indice]++)
    {
       
       E[I0_indice][0] = ProcurementCost(Q[1][I0_indice], c, k) + h*fmax(0,I0) + p*fmin(0,I0) + CalculateSigma(d_max, I0_indice+Q[1][I0_indice], E_min, Demand_Data_Array, ProbabilityArray, 1, Demand_Data_num);
      /// printf("E is %f for Q %f\n", E[I0_indice][0], Q[1][I0_indice]);
       if (E[I0_indice][0] < E_min[I0_indice][0])
        {
            E_min[I0_indice][0] = E[I0_indice][0];
            Q_opt[1][I0_indice] = Q[1][I0_indice];
        }

    }
    printf("E_min(%d, 0) = %.2f \t *\n", I0, E_min[I0_indice][0] );  
    printf("Q_opt(1, %d) = %.2f \t *\n", I0, Q_opt[1][I0_indice] );
    printf("**************************\n");

  /************** Freeing the Matrices ********************/
    free(Q);
    free(Q_opt);
    free(I);
    free(E);
    free(E_min);
    free(Demand_Data_Array); 
    free(ProbabilityArray);

    
    printf("**********DONE!***********\n\n");
    return 0;
}

#endif
