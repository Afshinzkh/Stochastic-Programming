#ifndef __INITIALIZER_H__
#define __INITIALIZER_H__

#include "helper.h"

int readParameters(int *T, int *d_max, int *I0, double *h, double *p, double *c, double *k, double *pr, int *dk, int argc, char *argv[]);
void init_Emin(double **E_min, int d_max, int T);
double ProcurementCost( double Q, double c, double k);
double CalculateSigmaFirst ( int D_max, int insideSum, double **E_min, int *dk, double *pr, int insideTIME);
double CalculateSigmaSecond ( int D_max, int insideSum, double **xE, int *dk, double *pr, int insideTIME);
#endif 