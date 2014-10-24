#ifndef __PROBCALCULATOR_H__
#define __PROBCALCULATOR_H__

#include "helper.h"

void BubbleSort(int *Demand, int Data_num);
void Calculate_Deviation(int *forecast_data, int number_of_data, double *mean, double *deviation);
void CalculatePrabability(int *IntervalArray, int *Demand, int Data_num, int d_max, int IntervalCount);
void GetFutureDemand(int *IntervalArray, int *Past_Data_Array, int num_past_data, int d_max, int IntervalCount, int *futureDemand, double *prob);
void Generate_Random_Data(int *D_K, int D_max, int *IntervalArray, int *past_data_array,int num_past_data, int IntervalCount, double *prob);

#endif