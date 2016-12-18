#include <stdio.h>
#include "stdafx.h"

/*#if _MSC_VER > 1000
#pragma once
#endif 

class Forecast
{
public:
	Forecast();*/
	// 区间[min,max]上的均匀分布,min和max要求传入的参数类型一致
	//template <class T>
	double rand(double min, double max);
	// 求均值为miu，方差为sigma的正太分布函数在x处的函数值
	double normal(double x, double miu,double sigma);
	//按照矩形区域在函数值曲线上下位置分布情况得到正太函数x值
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
 