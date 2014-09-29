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


void CalculatePrabability(double *Probability, int *Demand, int Data_num, int d_max)
{
	printf("\nEnter Data for past demand \n \t (Warining! Datas should be less than Maximum Demand i.e. (%d)) : ", d_max);

	int counter;	
	for(counter=0; counter<Data_num; counter++)
	{
		printf("\nEnter Data Number '-- %d --' : ",counter+1);
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


	int IntervalCount = d_max/100 + 1; 	/// number of intervals that have to be created
	int *IntervalArray;					/// the array containing intervals
	int result;							/// to see each demand is in which interval

	IntervalArray = (int *) malloc((size_t)(IntervalCount) * sizeof(int));

	for (counter = 0; counter<IntervalCount; counter++)
	{
		IntervalArray[counter]=0;
	}
	
	for (counter = 0; counter<Data_num; counter++)
	{
		result = Demand[counter]/100;
		IntervalArray[result]++;
	}
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
