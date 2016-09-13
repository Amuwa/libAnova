#include "fdistribution.h"

int mainx()
{

double y;

y=FDist(1,2,12);
printf("F=%10.7f\n",y);

return 0;
}



/*
*  P{ F > F(m, n) } = p
*返回p值
*/
double FDist(double F,double m,double n)
{
    double xx=0.0,p=0.0;

    if(m<=0 || n<=0) p=-1;
    else if(F>0)
    {
        xx=F/(F+n/m);
        p=betainc(xx,m/2,n/2);
    }
    return(1-p);
}

double betainv(double p,double a,double b)
{

    int count_max_limit=100;
    int count_max=0;
    double x,xnew,y,h,pbeta,logkerna,logkernb;
    double crit=1.818989403545857e-012; // 双精度时的设置
    //	float crit=6.4155306e-006;          // 单精度时的设置

    if(p==0) x=0;
    if(p==1) x=1;

    x=a/(a+b);
    if(x<crit) x=crit;
    if(x>1-crit) x=1-crit;
    h=1;

    while((h>(crit*fabs(x))) && (h>crit) && (count_max<count_max_limit))
    {
        count_max=count_max+1;

        if(x>1) p=1;
        pbeta=betainc(x,a,b);
        if(pbeta>1) pbeta=1;

        logkerna=(a-1)*log(x);
        if((a==1) && (x==0)) logkerna=0;
        logkernb=(b-1)*log(1-x);
        if((b==1) && (x==1)) logkernb=0;
        y=exp(logkerna+logkernb-log(beta(a,b)));

        h=(pbeta-p)/y;
        xnew=x-h;

        if(xnew<=0) xnew=x/10;
        if(xnew>=1) xnew=1-(1-x)/10;

        x=xnew;
    }
    return x;
}

// 后面的函数都经过测试，是准确的，与Matlab的计算结果一致
double beta(double z,double w)
{
    int m,n,k,l,j;
    double h[10],bb[10],hh,t1,s1,ep,s,x,t2,g;
    double eps=1e-10;

    m=1;
    n=1;
    hh=1;
    h[0]=hh;
    t1=0;
    s1=t1;
    bb[0]=s1;
    ep=1.0+eps;

    while((ep>=eps)&&(m<=9))
    {
        s=0.0;
        for(k=0;k<=n-1;k++)
        {
            x=(k+0.5)*hh;
            //          s=s+f(x,z,w);
            s=s+pow(x,z-1)*pow(1-x,w-1);//对f(x)=pow(x,z-1)*pow(1-x,w-1)的积分（一维积分的有理分式法）
        } //对f(x,z,w)=pow(x,z-1)*pow(1-x,w-1)积分后就是贝他函数，积分区间是[a,b]=[0,1]
        t2=(t1+hh*s)/2.0;
        m=m+1;
        h[m-1]=h[m-2]/2.0;
        g=t2;
        l=0;
        for(j=2;j<=m;j++)
        {
            s=g-bb[j-2];
            if(l==0){
                if(fabs(s)+1.0==1.0){ l=1;}
                else{ g=(h[m-1]-h[j-2])/s;}
            }
        }
        bb[m-1]=g;
        if(l!=0) bb[m-1]=1.0e+35;
        g=bb[m-1];
        for(j=m;j>=2;j--)
            g=bb[j-2]-h[j-2]/g;
        ep=fabs(g-s1);
        s1=g;
        t1=t2;
        hh=hh/2.0;
        n=n+n;
    }
    return(g);
}

double betainc(double x,double a, double b)/* 不完全Beta函数 */
{
    double y,BT,AAA;

    if(x==0 || x ==1)
        BT=0;
    else
    {
        AAA=gamma(a+b)-gamma(a)-gamma(b);
        BT=exp(AAA+a*log(x)+b*log(1-x));
    }
    if(x<(a+1)/(a+b+2))
        y=BT*beta_cf(a,b,x)/a;
    else
        y=1-BT*beta_cf(b,a,1-x)/b;

    return y;
}

double beta_cf(double a,double b,double x)
{
    int count,count_max=100;
    double eps=0.0000001;
    double AM=1;
    double BM=1;
    double AZ=1;
    double QAB;
    double QAP;
    double QAM;
    double BZ,EM,TEM,D,AP,BP,AAP,BPP,AOLD;

    QAB=a+b;
    QAP=a+1;
    QAM=a-1;
    BZ=1-QAB*x/QAP;

    for(count=1;count<=count_max;count++)
    {
        EM=count;
        TEM=EM+EM;
        D=EM*(b-count)*x/((QAM+TEM)*(a+TEM));
        AP=AZ+D*AM;
        BP=BZ+D*BM;
        D=-(a+EM)*(QAB+EM)*x/((a+TEM)*(QAP+TEM));
        AAP=AP+D*AZ;
        BPP=BP+D*BZ;
        AOLD=AZ;
        AM=AP/BPP;
        BM=BP/BPP;
        AZ=AAP/BPP;
        BZ=1;
        if(fabs(AZ-AOLD)<eps*fabs(AZ)) return(AZ);
    }
    return AZ;
}

double gamma(double xx)
{
    double coef_const[7];
    double step=2.50662827465;
    double HALF=0.5;
    double ONE=1;
    double FPF=5.5;
    double SER,temp,x,y;
    int j;

    coef_const[1]=76.18009173;
    coef_const[2]=-86.50532033;
    coef_const[3]=24.01409822;
    coef_const[4]=-1.231739516;
    coef_const[5]=0.00120858003;
    coef_const[6]=-0.00000536382;

    x=xx-ONE;
    temp=x+FPF;
    temp=(x+HALF)*log(temp)-temp;
    SER=ONE;
    for(j=1;j<=6;j++)
    {
        x=x+ONE;
        SER=SER+coef_const[j]/x;
    }
    y=temp+log(step*SER);

    return y;
}



