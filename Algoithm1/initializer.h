#ifndef __INITIALIZER_H__
#define __INITIALIZER_H__

#include "helper.h"

int readParameters(int *T, int *d_max, int *I0, double *h, double *p, double *c, double *k, double *pr, double *dk, int argc, char *argv[]);
void init_Emin(double *E_min, int d_max, int T);
double ProcurementCost( double Q, double c, double k);
double CalculateSigmaFirst ( int D_max, double insideSum, double *E_min, double *dk, double *pr, int insideTIME);

#endif 