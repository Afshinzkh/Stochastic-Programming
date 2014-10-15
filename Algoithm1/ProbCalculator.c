#include "helper.h"
#include "ProbCalculator.h"


void BubbleSort(int *Demand, int Data_num)
{
	int icounter,jcounter,Swap;
	for (icounter=0; icounter<Data_num - 1; icounter++)
	{
		for (jcounter=0; jcounter<Data_num - icounter - 1; jcounter++)
		{
			if (Demand[jcounter] > Demand[jcounter+1])
			{
				Swap = Demand[jcounter];
				Demand[jcounter] = Demand[jcounter+1];
				Demand[jcounter+1] = Swap;
			}
		}
	}

}

void Calculate_Deviation(int *forecast_data, int number_of_data, double *mean, double *deviation)
{
	int icounter;
	int sum=0;
	for ( icounter = 0; icounter < number_of_data; icounter++)
	{
		sum+=forecast_data[icounter];
	}
	*mean= (double) sum / (double) number_of_data;
	sum =0;
	for ( icounter = 0; icounter < number_of_data; icounter++)
	{
		sum += (*mean - forecast_data[icounter]) * (*mean - forecast_data[icounter]);
	}
	*deviation = sqrt(sum/number_of_data);

	printf("Mean = %.4f\t Standard Deviation = %.4f\n", *mean, *deviation );
}


void CalculatePrabability(int *IntervalArray, int *Demand, int Data_num, int d_max, int IntervalCount)
{
	
	printf("\nEnter Data for past demand \n  (Warining! Datas should be less than Maximum Demand i.e. (%d)) :\n", d_max);

	int counter;	
	for(counter=0; counter<Data_num; counter++)
	{
		printf("Enter Data Number '-- %d --' : ",counter+1);
		scanf("%d",&Demand[counter]);	
		if (Demand[counter] > d_max)
		{
			printf("Wrong Number. Data Should be less than %d . Try again!\n", d_max);
			counter--;
		}
	}

	/// How to calculate probability is like this:
	///		we have d_max e.g. 3000 . we make some intervals from 0 to 3000.
	///		each interval has length of 100 numbers. eg. 0 to 99 and 100 to 199 etc
	///		number of intervals we have , would be d_max/100+1 i.e. "int IntervalCount"
	/// 	then we make an array contatining Interval Numbers with the size of IntervalCount i.e. "int *Interval array"
	///		after that in a for loop we check each "past data" that has been entered by user and see in which interval are they
	///		so each interval will have a weight and the probability of a number being in that interval is weight / (total number of past data)


/*	int IntervalCount = d_max/100 + 1; 	/// number of intervals that have to be created
	int *IntervalArray;	*/				/// the array containing intervals /// ino bayad befresti tooye main . c
	int result;							/// to see each demand is in which interval
/*
	IntervalArray = (int *) malloc((size_t)(IntervalCount) * sizeof(int));*/

	for (counter = 0; counter<IntervalCount; counter++)
	{
		IntervalArray[counter]=0;
	}
	
	for (counter = 0; counter<Data_num; counter++)
	{
		result = Demand[counter]/100;
		IntervalArray[result]++;
	}
	printf("\n********************** Probability Function Calculated Succesfully ***********\n\n");
	/// now it is time to check the future demand 
/*	for (counter = 0; counter<Data_num; counter++)
	{
		probability[counter]
	}*/
/*	for (counter = 0; counter<IntervalCount; counter++)
	{
		printf("interval number %d is equal to : %d \n", counter, IntervalArray[counter]);
	}*/
}

void GetFutureDemand(int *IntervalArray, int *Demand_Data_Array, int Demand_Data_num, int d_max, int IntervalCount, int *D_K, double *prob, int number_of_data)
{
	int icounter;
	int jcounter;
	int result;
	///int number_of_data;
	int *forecast_data = (int *) malloc((size_t) number_of_data * sizeof(int));

	printf("Enter The Requiered Demand for next month\n (Warining! Datas should be less than Maximum Demand i.e. (%d))\n", d_max);
	for (icounter = 0; icounter<number_of_data; icounter++)
	{
		printf("Demand forecast  %d :  ", icounter+1);
		scanf("%d", &forecast_data[icounter]);
		if (forecast_data[icounter] > d_max)
		{
			printf("Wrong Number. Data Should be less than %d . Try again!\n", d_max);
			icounter--;
		}
	}

    printf("******************* ****************************** *******************\n");
    double deviation; /// standard deviation
    double mean; 		/// average
    Calculate_Deviation(forecast_data, number_of_data, &mean, &deviation);
    D_K[0] = floor (mean - deviation);
    D_K[1] = floor (mean);
    D_K[2] = floor (mean + deviation);

	for (icounter = 0; icounter<3; icounter++)
	{
		result = D_K[icounter]/100;
	///	printf("result = %d\n", result);
		for (jcounter=0;jcounter<IntervalCount;jcounter++)
		{
			if (result==jcounter) prob[icounter]= (double) IntervalArray[jcounter]/(double) Demand_Data_num;
		}
		printf("\t\tprobability for forecast %d  is : %.4lf\n", D_K[icounter], prob[icounter]);
	}
	

}
