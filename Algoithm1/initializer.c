#include "helper.h"
#include "initializer.h"




int readParameters(int *T, int *d_max, int *I0, double *h, double *p, double *c, double *k, double *pr, int *dk, int argc, char *argv[])
{
	double pr1,pr2,pr3;
	int dk1,dk2,dk3;

	if (argc != 2)
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
	READ_DOUBLE(argv[1], *k);
	READ_DOUBLE(argv[1], pr1);
	READ_DOUBLE(argv[1], pr2);
	READ_DOUBLE(argv[1], pr3);
	READ_INT(argv[1], dk1);
	READ_INT(argv[1], dk2);
	READ_INT(argv[1], dk3);

	dk[0] = dk1;
	dk[1] = dk2;
	dk[2] = dk3;
	pr[0] = pr1;
	pr[0] = pr2;
	pr[0] = pr3;

	return 0;
}

void init_Emin(double *E_min, int d_max, int T)
{
	printf("init_Emin started\n");
	double (*EMIN)[T+2] = (double(*)[T+2])E_min; 
	int a, b;
	for (a = 0; a <= 2*d_max; a++)
		for (b = 0; b <= T+1; b++)
			EMIN[a][b] = 0;
	printf("init_Emin done.\n");
}

double ProcurementCost( double Q, double c, double k)
{
	return c + k*Q;
}

double CalculateSigmaFirst ( int D_max, int insideSum, double *E_min, int *dk, double *pr, int insideTIME, int T)
{
/*	E_min[i-dk[m]+Q[t+1][i]][t+1] first array is insideSUM and second array is insideTIME */

	double (*EMIN)[T+2] = (double(*)[T+2])E_min; 
	int counter;
	double Sigma = 0;
	for (counter = 0; counter <= D_max; counter++ )
	{
		Sigma += pr[counter]* EMIN[insideSum-dk[counter]][insideTIME];
	}

	return Sigma;
}

double CalculateSigmaSecond ( int D_max, int insideSum, double **E, int *dk, double *pr, int insideTIME)
{
/*	E[I0-dk[m]+Q[1][I0]][1] first array is insideSUM and second array is insideTIME */

	int counter;
	double Sigma = 0;
	for (counter = 0; counter <= D_max; counter++ )
	{
		Sigma += pr[counter]* E[insideSum-dk[counter]][insideTIME];
	}

	return Sigma;
}
