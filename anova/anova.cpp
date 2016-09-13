#include "anova.h"
#include "fdistribution.h"
#include <iostream>
#include <string>
#include <sstream>


//utility function to sort numbers and strings
string PrintNumber(double v, unsigned int tabW){
    ostringstream sstream;
    sstream << v;
    string x = sstream.str();

    if(x.length()<tabW){
        int z=tabW-x.length();
        for(int i=0;i<z;i++){
            x += " ";
        }
    }
    return x;
}

string PrintTitle(string str, unsigned int tabW){
    if(str.length()>=tabW-2){
        str.erase( str.begin()+tabW-2, str.end() );
        str += "..";
        return str;
    }
    else{
        int z=tabW-str.length();
        for(int i=0;i<z;i++){
            str += " ";
        }
        return str;
    }
}



void SignificanceReportItem::show(){
    if(isTotal){        
        cout<<"\t"<<PrintTitle(source,10)<<PrintNumber(SumOfSquares,16)<<PrintNumber(degreeOfFreedom,8)<<endl;
    }
    else if(isError){
        cout<<"\t"<<PrintTitle(source,10)<<PrintNumber(SumOfSquares,16)<<PrintNumber(degreeOfFreedom,8)<<PrintNumber(MeanSquare)<<endl;
    }else{        
        cout<<"\t"<<PrintTitle(source,10)<<PrintNumber(SumOfSquares,16)<<PrintNumber(degreeOfFreedom,8)<<PrintNumber(MeanSquare)<<PrintNumber(Fvalue)<<PrintNumber(pValue)<<endl;
    }
}

string SignificanceReportItem::toString(){
    ostringstream sstream;
    if(isTotal){
        sstream<<"\t"<<PrintTitle(source,10)<<PrintNumber(SumOfSquares,16)<<PrintNumber(degreeOfFreedom,8);
    }
    else if(isError){
        sstream<<"\t"<<PrintTitle(source,10)<<PrintNumber(SumOfSquares,16)<<PrintNumber(degreeOfFreedom,8)<<PrintNumber(MeanSquare);
    }else{
        sstream<<"\t"<<PrintTitle(source,10)<<PrintNumber(SumOfSquares,16)<<PrintNumber(degreeOfFreedom,8)<<PrintNumber(MeanSquare)<<PrintNumber(Fvalue)<<PrintNumber(pValue);
    }
    string x = sstream.str();
    return x;
}


SignificanceReportItem NULLitem;
SignificanceReportItem& SignificanceReport::getErrorItem(){
    for(unsigned i=0;i<items.size();i++){
        if(items.at(i).isError){
            return items.at(i);
        }
    }

    {
        NULLitem.source="NULL";
        NULLitem.MeanSquare=9.9e25;
        NULLitem.isError=true;
        NULLitem.SumOfSquares=9.9e28;
        NULLitem.degreeOfFreedom=10;
        //error!!
    }
    return NULLitem;
}

void SignificanceReport::Add(SignificanceReportItem it){
    items.push_back(it);
}

void SignificanceReport::CalculatePvalues(){
    SignificanceReportItem errorItem=getErrorItem();

    if(errorItem.MeanSquare <=1.0e-6){
        //no obvious error column is set, should choose the least Msqr item as the error column
        double minMSrq = 9.9e119;
        for(unsigned int i=0;i<items.size();i++){
            if(items.at(i).isError || items.at(i).isTotal){continue;}//skip error/total items
            if(items.at(i).MeanSquare<minMSrq){
                minMSrq = items.at(i).MeanSquare;
                errorItem = items.at(i);
            }
        }
    }

    for(unsigned int i=0;i<items.size();i++){
        if(items.at(i).isError || items.at(i).isTotal){continue;}//skip error/total items
        //Fvalue
        double fv = items.at(i).MeanSquare / errorItem.MeanSquare;
        items.at(i).setFvalue(fv);
        //pValue
        //F-test: if fv >  F(item freedom, err freedom)_p
        double p = FDist(fv, items.at(i).degreeOfFreedom, errorItem.degreeOfFreedom);
        items.at(i).setPvalue(p);
    }
}


vector<SignificanceReportItem> SignificanceReport::getExtremeSignificantItems(){
    vector<SignificanceReportItem> rs;
    int sz = items.size();
    for(int i=0;i<sz;i++){
        if(!items.at(i).isTotal && !items.at(i).isError){
            if(items.at(i).pValue <= 0.01){
                rs.push_back(items.at(i));
            }
        }
    }
    return rs;
}

vector<SignificanceReportItem> SignificanceReport::getUsuallySignificantItems(){
    vector<SignificanceReportItem> rs;
    int sz = items.size();
    for(int i=0;i<sz;i++){
        if(!items.at(i).isTotal && !items.at(i).isError){
            if(items.at(i).pValue <= 0.05 && items.at(i).pValue > 0.01){
                rs.push_back(items.at(i));
            }
        }
    }
    return rs;
}

vector<double> SignificanceReport::ImportanceVector(double p){
    int sz = items.size();
    vector<double> rs;
    for(int i=0;i<sz;i++){
        if(!items.at(i).isTotal && !items.at(i).isError){
            if(items.at(i).pValue<=p){
                rs.push_back(1.0);
            }else{
                rs.push_back(0.0);
            }
        }
    }
    return rs;
}


string SignificanceReport::toString(){
    ostringstream sstream;
    sstream<<"ANOVA Results:"<<"\r\n";
    sstream<<"---------------------------------------------------------------------------------"<<"\r\n";
    sstream<<"\t"<<PrintTitle(string("Source"),10)<<PrintTitle(string("Sum Sqr"),16)<<PrintTitle(string("DoF"),8)
          <<PrintTitle(string("M. Sqr"))<<PrintTitle(string("F-val"))
         <<PrintTitle(string("Prob"))<<"\r\n";
    sstream<<"---------------------------------------------------------------------------------"<<"\r\n";
    for(unsigned int i=0;i<items.size();i++){
        sstream<<items.at(i).toString()<<"\r\n";
    }

    sstream<<"---------------------------------------------------------------------------------"<<endl;
    string x = sstream.str();
    return x;
}

void SignificanceReport::Show(){
    cout<<toString()<<endl;
}


ANOVA::ANOVA(int totalCols, vector<int> errCols)
{
    TotalColumns=totalCols;
    ErrorColumns.clear();
    for(unsigned int i=0;i<errCols.size();i++){
        ErrorColumns.push_back(errCols.at(i));
    }
}


void ANOVA::SetColumnName(int col, string name){ //col 0-based
    if(nameOfColumns.size()<1){
        for(int i=0;i<TotalColumns;i++){
            nameOfColumns.push_back(string(""));
        }
    }
    nameOfColumns.at(col)=name;
}


void ANOVA::AddData(vector<double> x, double y){
    DataPoint d;
    d.x.clear();
    for(unsigned int i=0;i<x.size();i++){
        d.x.push_back(x.at(i));
    }
    d.y=y;
    ExpData.push_back(d);
}


void ANOVA::AddData(double x[], double y, int cols){
    if(cols<0){
        cols = TotalColumns;
    }
    DataPoint d;
    d.x.clear();
    for(int i=0;i<cols;i++){
        d.x.push_back(x[i]);
    }
    d.y=y;

    ExpData.push_back(d);
}

void ANOVA::AddData(int x[], double y, int cols){
    if(cols<0){
        cols = TotalColumns;
    }
    DataPoint d;
    d.x.clear();
    for(int i=0;i<cols;i++){
        d.x.push_back(x[i]);
    }
    d.y=y;

    ExpData.push_back(d);
}



bool ANOVA::dEq(double x, double y){
    double e=1.0e-5;
    return (x <= y+e && x >= y-e);
}


vector<double> ANOVA::LevelsOfCol(int col){
    int C = ExpData.size();
    vector<double> vs;
    for(int c=0;c<C;c++){
        double v = ExpData.at(c).x.at(col);
        {
            bool has = false;
            for(unsigned int i=0;i<vs.size();i++){
                if(dEq(vs.at(i),v)){
                    has = true;
                    break;
                }
            }
            if(!has){
                vs.push_back(v);
            }
        }
    }
    return vs;
}

int ANOVA::FreedomOfCol(int col){
    int C = ExpData.size();

    vector<double> vs;
    for(int c=0;c<C;c++){
        double v = ExpData.at(c).x.at(col);
        {
            bool has = false;
            for(unsigned int i=0;i<vs.size();i++){
                if(dEq(vs.at(i),v)){
                    has = true;
                    break;
                }
            }
            if(!has){
                vs.push_back(v);
            }
        }
    }

    int dof = vs.size() -1;//level number minus 1
    return dof;
}

double ANOVA::averageY(){
    int C = ExpData.size();

    double sum=0.0;
    for(int c=0;c<C;c++){
        sum += ExpData.at(c).y;
    }

    return sum/C;
}


//Page 96 of He Shaohua book.
//T_ij
double ANOVA::SumOfYatLevel(int col, double v){
    int C = ExpData.size();
    double rs = 0.0;
    for(int c=0;c<C;c++){
        double xv = ExpData.at(c).x.at(col);
        {
            if(dEq(xv,v)){
                rs += ExpData.at(c).y;
            }
        }
    }
    return rs;
}

//Page 96 of He Shaohua book.
double ANOVA::R(int col){
    vector<double> vs = LevelsOfCol(col);

    int L= vs.size();
    double sumsq=0.0;
    for(int j=0;j<L;j++){
        double sy = SumOfYatLevel(col,vs.at(j));
        sumsq += (sy*sy);
    }

    return sumsq/L;
}

//Page 96 of He Shaohua book.
double ANOVA::P(){
    int C = ExpData.size();
    double rs = 0.0;
    for(int c=0;c<C;c++){
        double yv = ExpData.at(c).y;
        rs += yv;
    }

    return (rs*rs)/C;
}

//Page 96 of He Shaohua book.
double ANOVA::W(){
    int C = ExpData.size();
    double rs = 0.0;
    for(int c=0;c<C;c++){
        double yv = ExpData.at(c).y;
        rs += (yv*yv);
    }
    return rs;
}

bool ANOVA::isErrorColumn(int col){
    for(unsigned int i =0;i<ErrorColumns.size();i++){
        if(ErrorColumns.at(i) == col){
            return true;
        }
    }
    return false;
}

SignificanceReport ANOVA::doANOVA(){

    double theW = W();
    double theP = P();

    SignificanceReport report;

    //1-total variance
    SignificanceReportItem totalItem;
    {
        totalItem.source=string("Total");
        //freedom
        totalItem.degreeOfFreedom=0;
        for(int i=0;i<TotalColumns;i++){
            totalItem.degreeOfFreedom += FreedomOfCol(i);
        }
        //sum of square
        totalItem.SumOfSquares = theW - theP;
        //
        totalItem.MeanSquare = totalItem.SumOfSquares/totalItem.degreeOfFreedom;
        //
        totalItem.Fvalue =0.0;
        totalItem.pValue = 0.0;

        totalItem.isTotal = true;
        totalItem.isError = false;
    }

    //2-each NON-Error Col
    double errsqr=totalItem.SumOfSquares;
    int errDof=totalItem.degreeOfFreedom;
    for(int c=0; c<TotalColumns; c++){
        if(isErrorColumn(c)){continue;}
        SignificanceReportItem aItem;
        aItem.source = nameOfColumns.at(c);
        aItem.degreeOfFreedom = FreedomOfCol(c);
        aItem.SumOfSquares = R(c)-theP;
        aItem.MeanSquare = aItem.SumOfSquares/aItem.degreeOfFreedom;
        aItem.Fvalue =0.0;
        aItem.pValue = 0.0;

        aItem.isTotal=false;
        aItem.isError = false;


        errsqr -= aItem.SumOfSquares;
        errDof -= aItem.degreeOfFreedom;        

        report.Add(aItem);//colect normal items

    }

    //3-error cols
    SignificanceReportItem errorItem;
    {
        errorItem.source=string("Error");
        errorItem.degreeOfFreedom = errDof;
        errorItem.SumOfSquares=errsqr;
        errorItem.MeanSquare=errsqr/errDof;
        errorItem.Fvalue=0.0;
        errorItem.pValue=0.0;
        errorItem.isTotal=false;
        errorItem.isError=true;
    }

    //4-colect error item and total item
    report.Add(errorItem);
    report.Add((totalItem));

    //5-Get Fvalue and pValues
    report.CalculatePvalues();


    //optional - to show on screen
    report.Show();


    return report;
}

/*
void TestANOVA(){
    vector<int> eCols;
    eCols.push_back(3);//the 4th col

    ANOVA a(4, eCols);

    vector<double> x1;
    x1.push_back(1);
    x1.push_back(10);
    x1.push_back(30);
    x1.push_back(2);
    double y1 = 30.4;

    a.AddData(x1,y1);

    vector<double> x2;
    x2.push_back(2);
    x2.push_back(10);
    x2.push_back(10);
    x2.push_back(1);
    double y2 = 28.5;
    a.AddData(x2,y2);

    vector<double> x3;
    x3.push_back(3);
    x3.push_back(10);
    x3.push_back(20);
    x3.push_back(3);
    double y3 = 14.6;
    a.AddData(x3,y3);

    vector<double> x4;
    x4.push_back(1);
    x4.push_back(40);
    x4.push_back(20);
    x4.push_back(1);
    double y4=19.5;
    a.AddData(x4, y4);

    vector<double> x5;
    x5.push_back(2);
    x5.push_back(40);
    x5.push_back(30);
    x5.push_back(3);
    double y5=18.4;
    a.AddData(x5, y5);

    vector<double> x6;
    x6.push_back(3);
    x6.push_back(40);
    x6.push_back(10);
    x6.push_back(2);
    double y6=15.6;
    a.AddData(x6, y6);

    vector<double> x7;
    x7.push_back(1);
    x7.push_back(70);
    x7.push_back(10);
    x7.push_back(3);
    double y7=20.5;
    a.AddData(x7, y7);

    vector<double> x8;
    x8.push_back(2);
    x8.push_back(70);
    x8.push_back(20);
    x8.push_back(2);
    double y8=20.6;
    a.AddData(x8, y8);

    vector<double> x9;
    x9.push_back(3);
    x9.push_back(70);
    x9.push_back(30);
    x9.push_back(1);
    double y9=13;a.AddData(x9, y9);

    a.SetColumnName(0,"mType");
    a.SetColumnName(1,"Qty");
    a.SetColumnName(2,"Time");

    a.doANOVA();


}
*/



