#include <iostream>
double sum_price(int,double);
double in_a_month(int[],double[],int[]);
double ave(int ,double);
int main()
{
	int ori=10;
	double price[30];
	int man_sum[30];
	int gu_sum=5000*10000;
	double avg[30];
	double price_sum[30];

	for(int i=0;i<30;i++)
	{
		man_sum[i]=i+30;
	}
	for(int i=0;i<30;i++)
	{
		price[i]=ori++;
	}
	for(int i=0;i<30;i++)
	{
		price_sum[i]=gu_sum*price[i];
	}
	for(int i=0;i<30;i++)
	{
		avg[i]=price_sum[i]/man_sum[i];
	}

	
	printf("%s\t%s\t%s\n","Man","Total sum","Avg sum" );
	for(int i=0;i<30;i++)
	{
		printf("%d\t%f\t%f\n",man_sum[i],price_sum[i],avg[i] );
	}

	system("pause");
}
