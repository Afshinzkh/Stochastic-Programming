#ifndef _MAIN_C_
#define _MAIN_C_


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
  double DP;      /// Delivery Performance
  

  double **Q;     /// desicion to decide number of product to buy
  double **Q_opt; /// Optimal desicion
  double **E;     /// Expected Value
  double **E_min; /// Minimum Expected Value
  int *I;         /// Inventory 


  
 ///   srand(time(NULL));

    /*int a;
    for (int i=0; i<6; i++)
    {
    a = rand()%350;
    printf("a is: %d\n", a );
    }*/


  readParameters(&T, &d_max, &I0, &h, &p, &c, &k, &DP, argc, argv);
  ///printf(" DP IS : %f\n", DP);
  DP = 1.0 - (DP/100.0) ; /// Delivery Performance Alignment
  ///printf(" DP IS : %f\n", DP);

  /************ ALLOCATION OF PAST DATA MATRICES  *******************************/  
  printf("\n\t\t\t *** STEP 2 : PAST DEMAND DATA ***\n");
  int num_past_data;   /// The Number of Past Demand Data that user should type in
  printf("\nEnter Number of Past Data you have, in order to calculate the Probability: ");
  scanf("%d", &num_past_data);
  double *ProbabilityArray = (double *) malloc ((size_t)(num_past_data * sizeof(double)));
  int *past_data_array = (int *) malloc ((size_t)(num_past_data * sizeof(int)));
  /****************************************************************************/  
  /// This part is to devide the demand in to intervals and calculate probability of each interval
  int IntervalCount = d_max/100 + 1;
  int *IntervalArray; 
  IntervalArray = (int *) malloc((size_t)(IntervalCount) * sizeof(int));



  CalculatePrabability(IntervalArray, past_data_array, num_past_data, d_max, IntervalCount);
  
  /***********************************Calculation of Future DATA****************************************/
  printf("\n\t\t\t *** STEP 3 : FUTURE DEMAND DATA ***\n");
  double *prob;
  int *D_K;
  int num_DK;   /// Number of D_K
  int choose_num; /// the method number should be 1 or 2
  printf("\nchoose Method: 1) with random variables 2) with forecast data: ");
  scanf("%d", &choose_num);
  if (choose_num==1)
  {
    num_DK = 10;
    prob = (double *) malloc ((size_t)(num_DK * sizeof(double)));
    D_K = (int *) malloc((size_t) num_DK * sizeof(int));
    Generate_Random_Data(D_K, d_max, IntervalArray, past_data_array,num_past_data, IntervalCount, prob);
    
  }
  
  else if (choose_num == 2) /// I have to think about this shit as well
  {  
   /// int num_forecast; /// Number of forecast data
   /// printf("Enter Number of Data you might have for next month:");
   /// scanf("%d",&num_forecast);
    num_DK = 3;
    prob = (double *) malloc ((size_t)(num_DK * sizeof(double)));
    D_K = (int *) malloc((size_t)(num_DK) * sizeof(int));

    GetFutureDemand(IntervalArray, past_data_array, num_past_data, d_max, IntervalCount, D_K, prob);
  }
  else  ERROR("Wrong Number!!!");



  ///readParameters(&T, &d_max, &I0, &h, &p, &c, &k, ProbabilityArray, past_data_array, argc, argv);
  
  /************ Allocate the size of Matrices *******************************/
  
  Q = matrix(0,T+2,0,2*d_max+1);
  Q_opt = matrix(0,T+2,0,2*d_max+1);
  E = matrix(0,2*d_max+1,0,T+2);
  E_min = matrix(0,2*d_max+1,0,T+2);
  I = (int *) malloc((size_t)(T+2) * sizeof(int));

  if (Q == 0 || Q_opt == 0 || E == 0 || E_min == 0 || I == 0) ERROR("Storage cannot be allocated");


  


    init_Emin(E_min, d_max, T);     ///Initializes the E_min Matrix to zero for all values, "This is because the future Values should be 
                                    /// Zero for first Loop"
    I[T+1] = 0;        
    int t;                         ///time counter
    int I_indice = 0;              /// helper counter. this is actually the indices for I[t] but since I[t]
                                  /// is sometimes negative, we use I_indice to prevent that

    p = p + (DP*p);
  ///  int pitch = d_max/100;
    int Qt_DP; /// Qt with added Delivery Performance;
    printf("Heewwww\n");
    for (t=T;t >=1 ;t--)
    {
        for (I[t] = -d_max; I[t] <= d_max; I[t]++)
        {
           I_indice = I[t] + d_max;     /// here I_indice is defined
           E_min[I_indice][t] = 900000;
           Q_opt[t+1][I_indice] = 0.0;
           for (Q[t+1][I_indice]=fmin(I[t],0); Q[t+1][I_indice]<= fmax(d_max-I[t],0); Q[t+1][I_indice]++) 
           {
                Qt_DP = Q[t+1][I_indice]; /// + ///floor(DP * Q[t+1][I_indice]);

                //// add delivery performance --> Q[t+1][I_indice] = Q[t+1][I_indice] + floor(DP * Q[t+1][I_indice])
                  ///printf("\nHERE!!!\n");
               /// if (I_indice % pitch == 0) printf("=");
                E[I_indice][t] = ProcurementCost(Q[t+1][I_indice], c, k) + h*fmax(0,I[t]) + p*fmin(0,I[t]) + CalculateSigma(d_max, I_indice+Qt_DP, E_min, D_K, prob, t+1, num_DK);
                ///printf("Here is E: %.2f for Q = %2.f \n", E[I_indice][t], Q[t+1][I_indice] );
                if (E[I_indice][t] < E_min [I_indice][t])
                {
                   E_min [I_indice][t] = E[I_indice][t];
                   Q_opt[t+1][I_indice] = Qt_DP;
                }

           }
                

/*              printf("E_min (%d, %d) = %4.0f\t *\n", I[t], t, E_min[I_indice][t] );
                printf("Q_opt (%d, %d) = %4.0f \t *\n", t+1, I[t], Q_opt[t+1][I_indice] );
                printf("**************************\n");*/
        }
    }
    
    int I0_indice = I0+d_max;      ///here I0_indice is defined has the same feauter of I_indice butfor I0
    int Q1_DP;           /// same as QT_DP
    E_min[I0_indice][0] = 900000;
    Q_opt[1][I0_indice] = 0.0;
    for (Q[1][I0_indice] = fmin(I0,0); Q[1][I0_indice] <= fmax(0,d_max-I0); Q[1][I0_indice]++)
    {
       
      Q1_DP = Q[1][I0_indice] ;////+ floor(DP * Q[1][I0_indice]);
       E[I0_indice][0] = ProcurementCost(Q[1][I0_indice], c, k) + h*fmax(0,I0) + p*fmin(0,I0) + CalculateSigma(d_max, I0_indice+Q1_DP, E_min, D_K, prob, 1, num_DK);
      /// printf("E is %f for Q %f\n", E[I0_indice][0], Q[1][I0_indice]);
       if (E[I0_indice][0] < E_min[I0_indice][0])
        {
            E_min[I0_indice][0] = E[I0_indice][0];
            Q_opt[1][I0_indice] = Q1_DP;
        }

    }
    printf("\n*****************************\n");
    printf("* E_min(%d, 0) = %.2f    *\n", I0, E_min[I0_indice][0] );  
    printf("* Q_opt(1, %d) = %.2f     *\n", I0, Q_opt[1][I0_indice]);
    printf("*****************************\n");
///+ floor(DP * Q_opt[1][I0_indice])
  /************** Freeing the Matrices ********************/
    free(Q);
    free(Q_opt);
    free(I);
    free(E);
    free(E_min);
    free(past_data_array); 
    free(ProbabilityArray);
    free(prob);
    free(IntervalArray);
    free(D_K);



    
    printf("***********DONE!*************\n\n");
    return 0;
}

#endif
