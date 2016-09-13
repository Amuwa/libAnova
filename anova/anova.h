/*
 *      ANOVA class
 *
 * Analyse of Variance
 *
 * MengChang WANG, wangmengchang@gmail.com, 2016
 *
 *
 *  (The F-distribution calculation is based on the code posted by iSuwen)
 *      (Please refer to the notes in the file fdistribution.h)
 *
 *  Based on the Design of Experiment
 *      - Total Columns
 *      - the Columns for Error (empty columns)     // 0-based index
 *      - the name of each non-error column         // 0-based index
 *      - Experiment data/records: vector of [combination of levels] + value of [output/response]
 *  After feeding the Data
 *      - doANOVA() : call this member function to get the analysis results
 *
 *
 *
*/
#ifndef ANOVA_H
#define ANOVA_H

#include<vector>
#include <string>

using namespace std;


string PrintNumber(double v, unsigned int tabW=12);
string PrintTitle(string str, unsigned int tabW=12);

struct DataPoint{
    vector<double> x;
    double y;
};


class SignificanceReportItem{
public :
    string source;
    double SumOfSquares;
    int degreeOfFreedom;
    double MeanSquare;
    double Fvalue;
    double pValue;
    bool isTotal;
    bool isError;

    void setFvalue(double f){Fvalue=f;}
    void setPvalue(double p){pValue=p;}

    void show();
    string toString();

};


class SignificanceReport{

    SignificanceReportItem& getErrorItem();

public:
    vector<SignificanceReportItem> items;
    void Add(SignificanceReportItem it);

    void CalculatePvalues();



    string toString();
    void Show();
    vector<SignificanceReportItem> getExtremeSignificantItems();// <= 0.01
    vector<SignificanceReportItem> getUsuallySignificantItems();// <= 0.05

    vector<double> ImportanceVector(double p=0.01);



};


class ANOVA
{
    vector<int> ErrorColumns;
    int TotalColumns;
    vector<string> nameOfColumns; //"Error" for error columns

    vector<DataPoint> ExpData;

public:
    ANOVA(int totalCols, vector<int> errCols);
    //
    //API:
    void SetColumnName(int col, string name); //col 0-based
    void AddData(vector<double> x, double y);
    void AddData(double x[], double y, int cols=-1);
    void AddData(int x[], double y, int cols=-1);
    //
    SignificanceReport doANOVA();
    //
protected:
    //
    bool dEq(double x, double y);
    int FreedomOfCol(int col);
    double averageY();
    double SumOfYatLevel(int col, double v);
    double R(int col);

    double P();
    double W();

    //
    bool isErrorColumn(int col);
    vector<double> LevelsOfCol(int col);
};





#endif // ANOVA_H

