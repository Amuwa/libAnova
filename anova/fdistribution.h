#ifndef FDISTRIBUTION_H
#define FDISTRIBUTION_H

/*
 *   F-distribution calculation
 *
 *  Originally composed by  iSuwen :
 *          http://blog.csdn.net/superwen_go/article/details/8926993
 *
 *   Modified by Mengchang Wang @ 2016
 *
*/

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

double FDist(double F,double m,double n);
double betainv(double p,double a,double b);
double betainc(double x,double a, double b);
double beta(double z,double w);
double gamma(double xx);
double beta_cf(double a,double b,double x);


#endif // FDISTRIBUTION_H

