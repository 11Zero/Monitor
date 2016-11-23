#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "Forecast.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define pi 3.1415926535897
#define rd (rand()/(RAND_MAX+1.0))
//Forecast::Forecast()
//{}
// 区间[min,max]上的均匀分布,min和max要求传入的参数类型一致
//template <class T>
double rand(double min, double max)
{
    return min + (max - min) * ::rand() / (RAND_MAX + 1.0);
}

// 求均值为miu，方差为sigma的正太分布函数在x处的函数值
double normal(double x, double miu,double sigma)
{
    return 1.0 / sqrt(2.0 * pi) / sigma * exp(-1.0 * (x - miu) * (x - miu) / (2.0 * sigma * sigma));
}
 
//按照矩形区域在函数值曲线上下位置分布情况得到正太函数x值
double randn(double miu, double sigma, double min , double max)
{
    double x, y, dScope;
    do
    {
        x = rand(min,max);
        y = normal(x,miu,sigma);
        dScope = rand(0.0, normal(miu,miu,sigma));
    }
    while(dScope > y);
    return x;
}


double AverageRandom(double min,double max)  
{  
	int minInteger = (int)(min*10000);  
	int maxInteger = (int)(max*10000);  
	int randInteger = rand()*rand();  
	int diffInteger = maxInteger - minInteger;  
	int resultInteger = randInteger % diffInteger + minInteger;  
	return resultInteger/10000.0;  
}  
double NormalRandom(double miu,double sigma,double min,double max)//产生正态分布随机数
{
	double x;
	double dScope;
	double y;
	do
	{
		x = AverageRandom(min,max);
		y = normal(x, miu, sigma);
		dScope = AverageRandom(0, normal(miu,miu,sigma));
	}while( dScope > y);
	return x;
}

double gaussrand(double miu,double sigma)
{
    static double V1, V2, S;
    static int phase = 0;
    double X;
     
    if ( phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;
             
            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);
         
        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);
         
    phase = 1 - phase;
 
    return X*sqrt(sigma)+miu;
}
 

double gaussrand()
{
    static double U, V;
    static int phase = 0;
    double Z;

    if(phase == 0)
    {
         U = (rand() + 1.1) / (RAND_MAX +2.);
         V = rand() / (RAND_MAX + 1.);
         Z = sqrt(-1 * log(U))* sin(2 * pi * V);
    }
    else
    {
         Z = sqrt(-2 * long(U)) * cos(2 * pi * V);
    }

    phase = 1 - phase;
    return Z;
}



double randn(int type)
{
    //按照12个均匀分布之和减去6得到正态分布函数的x值
    if (type==1)
        return rd+rd+rd+rd+rd+rd+rd+rd+rd+rd+rd+rd-6.0;
    //按照计算公式y=sqrt(-2*ln(U))*cos(2*PI*V)计算得到x
    else if(type==2)
        return sqrt(-2*log(rand()/(RAND_MAX+1.0)))*cos(2*pi*rand()/(RAND_MAX+1.0));
    else
        return randn(0.0,1.0,-10.0,10.0);
}


double mymorlet(double t)
{
	return exp(-pow(t,2)/2)*cos(1.75*t);
}

double d_mymorlet(double t)
{
	return -1.75*sin(1.75*t)*exp(-pow(t,2)/2)-t*cos(1.75*t)*exp(-pow(t,2)/2);
}


/*void mapminmax1(double* matrix ,double ymin ,double ymax)
{
	int i=0,j=0;
	int max = 0;
	int min = 0;
	for(i = 0; i < sizeof(matrix)/sizeof(*matrix);i++)
	{
		max = *(matrix+i)>max?(*(matrix+i)):max;
		min = *(matrix+i)<min?(*(matrix+i)):min;
	}
	for(i = 0; i < sizeof(matrix)/sizeof(*matrix);i++)
	{
		*(matrix+i) = (ymax - ymin)*(*(matrix+i) - min)/(max - min) + ymin;
	}
}
void mapminmax2(double **matrix ,double ymin ,double ymax,int 0_col_1_row)
{
	int i=0,j=0;
	int max = 0;
	int min = 0;
	if(0_col_1_row == 0)
	{
		for(j = 0; j < sizeof(*matrix)/sizeof(**matrix);j++)
		{
			for(i = 0; i < sizeof(matrix)/sizeof(*matrix);i++)
			{
				max = *(*(matrix+i)+j)>max?(*(*(matrix+i)+j)):max;
				min = *(*(matrix+i)+j)<min?(*(*(matrix+i)+j)):min;
			}
			for(i = 0; i < sizeof(matrix)/sizeof(matrix[0]);i++)
			{
				*(*(matrix+i)+j) = (ymax - ymin)*(*(*(matrix+i)+j) - min)/(max - min) + ymin;
			}
			max = 0;
			min = 0;
		}
	}
	 if(0_col_1_row == 1)
	 {
		 for(j = 0; j < sizeof(matrix)/sizeof(*matrix);j++)
		 {
			 for(i = 0; i < sizeof(*matrix)/sizeof(**matrix);i++)
			 {
				 max = *(*(matrix+j)+i)>max?(*(*(matrix+j)+i)):max;
				 min = *(*(matrix+j)+i)<min?(*(*(matrix+j)+i)):min;
			 }
			 for(i = 0; i < sizeof(*matrix)/sizeof(**matrix);i++)
			 {
				 *(*(matrix+j)+i) = (ymax - ymin)*(*(*(matrix+j)+i) - min)/(max - min) + ymin;
			 }
			 max = 0;
			 min = 0;
		 }	 
	 }
}*/
// 简单算法，实际结果和公式法差不多
/*#define rd (rand()/(RAND_MAX+1.0))
double randn(double miu, double sigma)
{
    return (rd + rd + rd + rd + rd + rd + rd + rd + rd + rd + rd + rd - 6.0) * 0.5 * sigma + miu;
}*/
 
  
  
/*void main()
{
    int i;
    srand((unsigned)time( NULL ));
    for (i = 0; i < 128; i++)
    {
        printf("%f%c", randn(2.0, 0.4), (i % 8 == 7) ? '\n' : ' ');
    }
    printf("\n");
    for (i = 0; i < 128; i++)
    {
        printf("%f%c", randn(2.0, 0.4, 0.0, 4.0), (i % 8 == 7) ? '\n' : ' ');
    }
    printf("\n");
}*/