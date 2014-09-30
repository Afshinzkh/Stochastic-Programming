#ifndef __PROBCALCULATOR_H__
#define __PROBCALCULATOR_H__

#include "helper.h"

void BubbleSort(int *Demand, int Data_num);
void CalculatePrabability(int *IntervalArray, int *Demand, int Data_num, int d_max, int IntervalCount);
void GetFutureDemand(int *IntervalArray, int *Demand_Data_Array, int Demand_Data_num, int d_max, int IntervalCount, int *futureDemand, double *prob);

#endif