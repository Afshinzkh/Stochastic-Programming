#ifndef __INITIALIZER_H__
#define __INITIALIZER_H__

#include "helper.h"

int readParameters(int *T, int *d_max, int *I0, double *h, double *p, double *c, double *k, double *pr, double *dk, int argc, char *argv[]);
void init_E(double *E, int d_max, int T);


#endif 