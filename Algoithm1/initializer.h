#ifndef __INITIALIZER_H__
#define __INITIALIZER_H__

#include "helper.h"

int readParameters(int *T, int *d_max, int *I0, double *h, double *p, double *c, double *k, double *DP, int argc, char *argv[]);
void init_Emin(double **Emin, int d_max, int T);
double ProcurementCost( double Q, double c, double k);
double CalculateSigma ( int D_max, int insideSum, double **Emin, int *D_K, double *pr, int insideTIME, int num_future);


#endif 