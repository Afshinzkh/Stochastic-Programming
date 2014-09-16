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
/// KOSKHOL VASEYE OON 3 ta Adaddi ke masalan migiri bayad probability ro peyda koni

void CalculatePrabability(double *Probability, int *Demand, int Data_num, int d_max)
{
	printf("\nEnter Data Number (Warining! Datas should be less than Maximum Demand i.e. (%d)) : ", d_max);

	int icounter;
	
	for(icounter=0; icounter<Data_num; icounter++)
	{
		printf("\nEnter Data Number '-- %d --' : ",icounter+1);
		scanf("%d",&Demand[icounter]);	
	}
	
	BubbleSort(Demand,Data_num);

	Probability[0] = 1.0/Data_num;
	for (icounter=1; icounter<Data_num; icounter++)
	{
		Probability[icounter] = 1.0/Data_num + Probability[icounter-1];
		///printf("Probability of Demand being %d or less is %.2f\n", Demand[icounter],Probability[icounter] );
	}	

	if(Probability[Data_num-1] == 1)	printf("\nProbability Function Calculated Succesfully\n\n");
	

}

/*double Probability_of(double Data, double *probability, int *Demand, int Data_num)
{
	int icounter;
	double result;
	if (Data <= Demand[0])	return probability[0];
	for (icounter=1; icounter<Data_num)
	{
		if (Data <= Demand[icounter])
			{
				result = ( (probability[icounter]-probability[icounter-1]) / (Demand[icounter]-Demand[icounter-1]) ) * Data;
				break;
			}
	}
	return result;
}*/
