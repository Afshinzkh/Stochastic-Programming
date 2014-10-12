
#include "helper.h"
#include "initializer.h"




///int readParameters(int *T, int *d_max, int *I0, double *h, double *p, double *c, double *k, double *pr, int *dk, int argc, char *argv[])
int readParameters(int *T, int *d_max, int *I0, double *h, double *p, double *c, double *k, double *DP, int argc, char *argv[])
{

  printf("\n******************************* WELCOME! *****************************\n");
  printf("********************** Inventory Model Application  ******************\n");
  printf("********************* Version 1.05  (September 2014) *****************\n");
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


/*	if (argc != 2)
	{
		char szBuff[80];
		sprintf(szBuff, "No file/too many files given!");
		ERROR(szBuff);
	}

	READ_INT(argv[1], *T);
	READ_INT(argv[1], *d_max);
	READ_INT(argv[1], *I0);
	READ_DOUBLE(argv[1], *h);
	READ_DOUBLE(argv[1], *p);
	READ_DOUBLE(argv[1], *c);
	READ_DOUBLE(argv[1], *k);*/
	///READ_DOUBLE(argv[1], pr1);
	///READ_DOUBLE(argv[1], pr2);
	///READ_DOUBLE(argv[1], pr3);
	///READ_INT(argv[1], dk1);
	///READ_INT(argv[1], dk2);
	///READ_INT(argv[1], dk3);

	

	///dk[0] = dk1;
	///dk[1] = dk2;
	///dk[2] = dk3;
	///pr[0] = pr1;
	///pr[1] = pr2;
	///pr[2] = pr3;

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
 
	///double prob = 1.0/Data_num;
///	int random_var;
	int counter;
	double Sigma = 0;
	///srand(time(NULL));
	for (counter = 0; counter < num_DK; counter++ )
	{
	///	printf("%d pr=%f\n",counter, pr[counter] );
	///	printf("dk=%d\n",dk[counter] );
	///printf("Indicessag=%d\n", insideSum - D_K[counter]);
	///	random_var = rand() % D_max;
		Sigma += probability[counter]* Emin[insideSum- D_K[counter]][insideTIME];
	}
	///printf("%d\n", random_var);
	///printf("%.2f\n", Sigma);
	return Sigma;
}

void Generate_Random_Data(int *D_K, int D_max, int *IntervalArray, int *past_data_array,int num_past_data, int IntervalCount, double *prob) /// probability of this random variable should be calculated
{
	srand(time(NULL));
	printf(" 4 Random Data Generated\n");
	int icounter,jcounter;
	int result;
	for(icounter=0; icounter<4; icounter++)
	{
		D_K[icounter] = rand() % D_max;
		
	}


	/// Calculate probability of each random variable

	for (icounter = 0; icounter<4; icounter++)
	{
		result = D_K[icounter]/100;
		for (jcounter=0;jcounter<IntervalCount;jcounter++)
		{
			if (result==jcounter) prob[icounter]= (double) IntervalArray[jcounter]/(double) num_past_data;
		}
		printf("Random data %d is : %d  with the probability of : %.4f \n",icounter+1, D_K[icounter], prob[icounter] );
	}
}


