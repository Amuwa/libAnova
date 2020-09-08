#include "anova.h"
void TestANOVA() {

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

    a.AddData(x1, y1);   //add a row of data into the ANOVA objects

    vector<double> x2;
    x2.push_back(2);
    x2.push_back(10);
    x2.push_back(10);
    x2.push_back(1);
    double y2 = 28.5;
    a.AddData(x2, y2);

    vector<double> x3;
    x3.push_back(3);
    x3.push_back(10);
    x3.push_back(20);
    x3.push_back(3);
    double y3 = 14.6;
    a.AddData(x3, y3);

    vector<double> x4;
    x4.push_back(1);
    x4.push_back(40);
    x4.push_back(20);
    x4.push_back(1);
    double y4 = 19.5;
    a.AddData(x4, y4);

    vector<double> x5;
    x5.push_back(2);
    x5.push_back(40);
    x5.push_back(30);
    x5.push_back(3);
    double y5 = 18.4;
    a.AddData(x5, y5);

    vector<double> x6;
    x6.push_back(3);
    x6.push_back(40);
    x6.push_back(10);
    x6.push_back(2);
    double y6 = 15.6;
    a.AddData(x6, y6);

    vector<double> x7;
    x7.push_back(1);
    x7.push_back(70);
    x7.push_back(10);
    x7.push_back(3);
    double y7 = 20.5;
    a.AddData(x7, y7);

    vector<double> x8;
    x8.push_back(2);
    x8.push_back(70);
    x8.push_back(20);
    x8.push_back(2);
    double y8 = 20.6;

    a.AddData(x8, y8);

    vector<double> x9;
    x9.push_back(3);
    x9.push_back(70);
    x9.push_back(30);
    x9.push_back(1);
    double y9 = 13;

    a.AddData(x9, y9);

    //set the name of each column (the source)
    a.SetColumnName(0, "Mat");
    a.SetColumnName(1, "Qty");
    a.SetColumnName(2, "Time");

    //perform the Analysis (the result will be shown on screen)
    //  this function returns a SignificanceReport object, you can further utilize the data in your program
    a.doANOVA();

    //Export as MatLab scripts
    a.ExportToMatlabScript("test.m");

}


void TestANOVA2() {
    vector<int> eCols;
    eCols.push_back(2);
    eCols.push_back(5);
    eCols.push_back(8);
    ANOVA a(9, eCols);

    vector<double> x1;
    x1.push_back(1);
    x1.push_back(1);
    x1.push_back(4);
    x1.push_back(4);
    x1.push_back(4);
    x1.push_back(4);
    x1.push_back(2);
    x1.push_back(3);
    x1.push_back(1);
    double y1 = 0;
    a.AddData(x1, y1);

    vector<double> x2;
    x2.push_back(1);
    x2.push_back(2);
    x2.push_back(3);
    x2.push_back(1);
    x2.push_back(3);
    x2.push_back(2);
    x2.push_back(4);
    x2.push_back(2);
    x2.push_back(4);
    double y2 = 0;
    a.AddData(x2, y2);

    vector<double> x3;
    x3.push_back(1);
    x3.push_back(3);
    x3.push_back(2);
    x3.push_back(3);
    x3.push_back(1);
    x3.push_back(1);
    x3.push_back(3);
    x3.push_back(4);
    x3.push_back(3);
    double y3 = 20;
    a.AddData(x3, y3);

    vector<double> x4;
    x4.push_back(1);
    x4.push_back(4);
    x4.push_back(1);
    x4.push_back(2);
    x4.push_back(2);
    x4.push_back(3);
    x4.push_back(1);
    x4.push_back(1);
    x4.push_back(2);
    double y4 = 0;
    a.AddData(x4, y4);

    vector<double> x5;
    x5.push_back(2);
    x5.push_back(1);
    x5.push_back(3);
    x5.push_back(3);
    x5.push_back(2);
    x5.push_back(4);
    x5.push_back(4);
    x5.push_back(4);
    x5.push_back(2);
    double y5 = 20;
    a.AddData(x5, y5);

    vector<double> x6;
    x6.push_back(2);
    x6.push_back(2);
    x6.push_back(4);
    x6.push_back(2);
    x6.push_back(1);
    x6.push_back(2);
    x6.push_back(2);
    x6.push_back(1);
    x6.push_back(3);
    double y6 = 40;
    a.AddData(x6, y6);

    vector<double> x7;
    x7.push_back(2);
    x7.push_back(3);
    x7.push_back(1);
    x7.push_back(4);
    x7.push_back(3);
    x7.push_back(1);
    x7.push_back(1);
    x7.push_back(3);
    x7.push_back(4);
    double y7 = 0;
    a.AddData(x7, y7);

    vector<double> x8;
    x8.push_back(2);
    x8.push_back(4);
    x8.push_back(2);
    x8.push_back(1);
    x8.push_back(4);
    x8.push_back(3);
    x8.push_back(3);
    x8.push_back(2);
    x8.push_back(1);
    double y8 = 0;
    a.AddData(x8, y8);

    vector<double> x9;
    x9.push_back(3);
    x9.push_back(1);
    x9.push_back(2);
    x9.push_back(4);
    x9.push_back(1);
    x9.push_back(3);
    x9.push_back(4);
    x9.push_back(1);
    x9.push_back(4);
    double y9 = 0;
    a.AddData(x9, y9);

    vector<double> x10;
    x10.push_back(3);
    x10.push_back(2);
    x10.push_back(1);
    x10.push_back(1);
    x10.push_back(2);
    x10.push_back(1);
    x10.push_back(2);
    x10.push_back(4);
    x10.push_back(1);
    double y10 = 0;
    a.AddData(x10, y10);

    vector<double> x11;
    x11.push_back(3);
    x11.push_back(3);
    x11.push_back(4);
    x11.push_back(3);
    x11.push_back(4);
    x11.push_back(2);
    x11.push_back(1);
    x11.push_back(2);
    x11.push_back(2);
    double y11 = 20;
    a.AddData(x11, y11);

    vector<double> x12;
    x12.push_back(3);
    x12.push_back(4);
    x12.push_back(3);
    x12.push_back(2);
    x12.push_back(3);
    x12.push_back(4);
    x12.push_back(3);
    x12.push_back(3);
    x12.push_back(3);
    double y12 = 0;
    a.AddData(x12, y12);

    vector<double> x13;
    x13.push_back(4);
    x13.push_back(1);
    x13.push_back(1);
    x13.push_back(3);
    x13.push_back(3);
    x13.push_back(3);
    x13.push_back(2);
    x13.push_back(2);
    x13.push_back(3);
    double y13 = 0;
    a.AddData(x13, y13);

    vector<double> x14;
    x14.push_back(4);
    x14.push_back(2);
    x14.push_back(2);
    x14.push_back(2);
    x14.push_back(4);
    x14.push_back(1);
    x14.push_back(4);
    x14.push_back(3);
    x14.push_back(2);
    double y14 = 0;
    a.AddData(x14, y14);

    vector<double> x15;
    x15.push_back(4);
    x15.push_back(3);
    x15.push_back(3);
    x15.push_back(4);
    x15.push_back(2);
    x15.push_back(2);
    x15.push_back(3);
    x15.push_back(1);
    x15.push_back(1);
    double y15 = 20;
    a.AddData(x15, y15);

    vector<double> x16;
    x16.push_back(4);
    x16.push_back(4);
    x16.push_back(4);
    x16.push_back(1);
    x16.push_back(1);
    x16.push_back(4);
    x16.push_back(1);
    x16.push_back(4);
    x16.push_back(4);
    double y16 = 20;
    a.AddData(x16, y16);

    vector<double> x17;
    x17.push_back(1);
    x17.push_back(1);
    x17.push_back(4);
    x17.push_back(2);
    x17.push_back(2);
    x17.push_back(1);
    x17.push_back(3);
    x17.push_back(2);
    x17.push_back(4);
    double y17 = 20;
    a.AddData(x17, y17);

    vector<double> x18;
    x18.push_back(1);
    x18.push_back(2);
    x18.push_back(3);
    x18.push_back(3);
    x18.push_back(1);
    x18.push_back(3);
    x18.push_back(1);
    x18.push_back(3);
    x18.push_back(1);
    double y18 = 60;
    a.AddData(x18, y18);

    vector<double> x19;
    x19.push_back(1);
    x19.push_back(3);
    x19.push_back(2);
    x19.push_back(1);
    x19.push_back(3);
    x19.push_back(4);
    x19.push_back(2);
    x19.push_back(1);
    x19.push_back(2);
    double y19 = 40;
    a.AddData(x19, y19);

    vector<double> x20;
    x20.push_back(1);
    x20.push_back(4);
    x20.push_back(1);
    x20.push_back(4);
    x20.push_back(4);
    x20.push_back(2);
    x20.push_back(4);
    x20.push_back(4);
    x20.push_back(3);
    double y20 = 0;
    a.AddData(x20, y20);

    vector<double> x21;
    x21.push_back(2);
    x21.push_back(1);
    x21.push_back(3);
    x21.push_back(1);
    x21.push_back(4);
    x21.push_back(1);
    x21.push_back(1);
    x21.push_back(1);
    x21.push_back(3);
    double y21 = 20;
    a.AddData(x21, y21);

    vector<double> x22;
    x22.push_back(2);
    x22.push_back(2);
    x22.push_back(4);
    x22.push_back(4);
    x22.push_back(3);
    x22.push_back(3);
    x22.push_back(3);
    x22.push_back(4);
    x22.push_back(2);
    double y22 = 0;
    a.AddData(x22, y22);

    vector<double> x23;
    x23.push_back(2);
    x23.push_back(3);
    x23.push_back(1);
    x23.push_back(2);
    x23.push_back(1);
    x23.push_back(4);
    x23.push_back(4);
    x23.push_back(2);
    x23.push_back(1);
    double y23 = 60;
    a.AddData(x23, y23);

    vector<double> x24;
    x24.push_back(2);
    x24.push_back(4);
    x24.push_back(2);
    x24.push_back(3);
    x24.push_back(2);
    x24.push_back(2);
    x24.push_back(2);
    x24.push_back(3);
    x24.push_back(4);
    double y24 = 0;
    a.AddData(x24, y24);

    vector<double> x25;
    x25.push_back(3);
    x25.push_back(1);
    x25.push_back(2);
    x25.push_back(2);
    x25.push_back(3);
    x25.push_back(2);
    x25.push_back(1);
    x25.push_back(4);
    x25.push_back(1);
    double y25 = 0;
    a.AddData(x25, y25);

    vector<double> x26;
    x26.push_back(3);
    x26.push_back(2);
    x26.push_back(1);
    x26.push_back(3);
    x26.push_back(4);
    x26.push_back(4);
    x26.push_back(3);
    x26.push_back(1);
    x26.push_back(4);
    double y26 = 20;
    a.AddData(x26, y26);

    vector<double> x27;
    x27.push_back(3);
    x27.push_back(3);
    x27.push_back(4);
    x27.push_back(1);
    x27.push_back(2);
    x27.push_back(3);
    x27.push_back(4);
    x27.push_back(3);
    x27.push_back(3);
    double y27 = 40;
    a.AddData(x27, y27);

    vector<double> x28;
    x28.push_back(3);
    x28.push_back(4);
    x28.push_back(3);
    x28.push_back(4);
    x28.push_back(1);
    x28.push_back(1);
    x28.push_back(2);
    x28.push_back(2);
    x28.push_back(2);
    double y28 = 0;
    a.AddData(x28, y28);

    vector<double> x29;
    x29.push_back(4);
    x29.push_back(1);
    x29.push_back(1);
    x29.push_back(1);
    x29.push_back(1);
    x29.push_back(2);
    x29.push_back(3);
    x29.push_back(3);
    x29.push_back(2);
    double y29 = 0;
    a.AddData(x29, y29);

    vector<double> x30;
    x30.push_back(4);
    x30.push_back(2);
    x30.push_back(2);
    x30.push_back(4);
    x30.push_back(2);
    x30.push_back(4);
    x30.push_back(1);
    x30.push_back(2);
    x30.push_back(3);
    double y30 = 0;
    a.AddData(x30, y30);

    vector<double> x31;
    x31.push_back(4);
    x31.push_back(3);
    x31.push_back(3);
    x31.push_back(2);
    x31.push_back(4);
    x31.push_back(3);
    x31.push_back(2);
    x31.push_back(4);
    x31.push_back(4);
    double y31 = 40;
    a.AddData(x31, y31);

    vector<double> x32;
    x32.push_back(4);
    x32.push_back(4);
    x32.push_back(4);
    x32.push_back(3);
    x32.push_back(3);
    x32.push_back(1);
    x32.push_back(4);
    x32.push_back(1);
    x32.push_back(1);
    double y32 = 20;
    a.AddData(x32, y32);


    vector<string> cnames;
    cnames.push_back(string("CoefA"));
    cnames.push_back(string("MeanB"));
    cnames.push_back(string("Error"));
    cnames.push_back(string("CoefC"));
    cnames.push_back(string("CoefD"));
    cnames.push_back(string("Error"));
    cnames.push_back(string("MeanE"));
    cnames.push_back(string("CoefE"));
    cnames.push_back(string("Error"));
    a.SetColumnNames(cnames);
    a.doANOVA();
    a.ExportToMatlabScript("test2.m");
}

