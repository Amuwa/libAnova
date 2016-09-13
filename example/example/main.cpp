#include <iostream>
#include "../../anova/libAnova.h"


using namespace std;

void TestANOVA(){

    //define columns
    vector<int> eCols;
    eCols.push_back(3);//the 3rd (0-based) column is the empty column

    ANOVA a(4, eCols);//total 4 columns with the last column as the error column


    //prepare data and add data into ANOVA object
    vector<double> x1;
    x1.push_back(1);    //0-th column
    x1.push_back(10);   //1st column
    x1.push_back(30);   //2nd column
    x1.push_back(2);    //3rd column
    double y1 = 30.4;   //the y value/response

    a.AddData(x1,y1);   //add a row of data into the ANOVA objects

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
    double y9=13;

    a.AddData(x9, y9);

    //set the name of each column (the source)
    a.SetColumnName(0,"Mat");
    a.SetColumnName(1,"Qty");
    a.SetColumnName(2,"Time");

    //perform the Analysis (the result will be shown on screen)
    //  this function returns a SignificanceReport object, you can further utilize the data in your program
    a.doANOVA();


}


int main()
{
    cout << "Example of libANOVA\r\nwangmengchang@gmail.com\r\n\r\n" << endl;
    TestANOVA();
    return 0;
}

