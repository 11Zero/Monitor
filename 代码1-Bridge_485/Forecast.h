#include <stdio.h>
#include "stdafx.h"

/*#if _MSC_VER > 1000
#pragma once
#endif 

class Forecast
{
public:
	Forecast();*/
	// ����[min,max]�ϵľ��ȷֲ�,min��maxҪ����Ĳ�������һ��
	//template <class T>
	double rand(double min, double max);
	// ���ֵΪmiu������Ϊsigma����̫�ֲ�������x���ĺ���ֵ
	double normal(double x, double miu,double sigma);
	//���վ��������ں���ֵ��������λ�÷ֲ�����õ���̫����xֵ
	double randn(double miu, double sigma, double min , double max);
	double gaussrand(double miu,double sigma);
	double gaussrand();
	double mymorlet(double t);
	double d_mymorlet(double t);
	double randn(int type);
	double AverageRandom(double min,double max) ;
	double NormalRandom(double miu,double sigma,double min,double max);
	//void mapminmax1(double *matrix ,double ymin ,double ymax);
	//void mapminmax2(double **matrix ,double ymin ,double ymax,int 0_col_1_row);
	//~Forecast();
//};
 