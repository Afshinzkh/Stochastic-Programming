
#include "helper.h"
#include "initializer.h"




///int readParameters(int *T, int *d_max, int *I0, double *h, double *p, double *c, double *k, double *pr, int *dk, int argc, char *argv[])
int readParameters(int *T, int *d_max, int *I0, double *h, double *p, double *c, double *k, double *DP, int argc, char *argv[])
{

  printf("\n******************************* WELCOME! *****************************\n");
  printf("********************** Inventory Model Application  ******************\n");
  printf("********************* Version 1.06  (October 2014) *******************\n");
  printf("************************ Written By : Afshin Loni  *******************\n");
  printf("**** Under Supervision of : Dipl.-Wirtsch.-Ing. Steffi Hoppenheit ****\n");
  printf("******** Lehrstuhl für Fördertechnik Materialfluss Logistik  *********\n");
  printf("******************* Technische Universität München *******************\n");
  printf("******************* ****************************** *******************\n");
  printf("******************* ****************************** *******************\n");
  printf("\n  In this Application you should Enter the requested data in 3 Steps\n");
  printf("\n\t\t\t *** STEP 1 : PRIMARY DATA ***\n");
  
  printf("\tTime Period (T) :                   ");
  scanf("%d", T);
  printf("\tMaximum Demand  :                   ");
  scanf("%d", d_max);
  printf("\tCurrent Inevntory Level :           ");
  scanf("%d", I0);
  printf("\tHolding Cost :                      ");
  scanf("%lf", h);
  printf("\tPenalty Cost :                      ");
  scanf("%lf", p);
  printf("\tAdminstartional Cost :              ");
  scanf("%lf", c);
  printf("\tPrecurement Cost per Piece :        ");
  scanf("%lf", k);
  printf("\tDelivery Performance (Percentage) : ");
  scanf("%lf", DP);

	return 0;
}

void init_Emin(double **Emin, int d_max, int T)
{
	int a, b;
	for (a = 0; a <= 2*d_max; a++)
		for (b = 0; b <= T+1; b++)
			Emin[a][b] = 0;
	
}

double ProcurementCost( double Q, double c, double k)
{
	///if (Q==0) return 0;
	return c + k*Q;
}

double CalculateSigma( int D_max, int insideSum, double **Emin, int *D_K, double *probability, int insideTIME, int num_DK)
{
/*	E_min[i-dk[m]+Q[t+1][i]][t+1] first array is insideSUM and second array is insideTIME */
 

	int counter;
	double Sigma = 0;
	
	for (counter = 0; counter < num_DK; counter++ )
	{
		Sigma += probability[counter]* Emin[insideSum- D_K[counter]][insideTIME];
	}
	
	return Sigma;
}




