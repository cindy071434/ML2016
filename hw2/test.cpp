#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <cmath>
using namespace std;

double Gaussian(double m,double v,double x)
{
    //cout<<m<<" "<<v<<" "<<x<<" ";
  // cout<<exp(-(x-m)*(x-m)/2/v)/sqrt(v)/2.50662827463<<endl;
   return (-(x-m)*(x-m)/2/v)-log(sqrt(v)/0.398942280401432677939946059934381868475858631164934657665);
}

int main( int argc, char **argv )
{
    ifstream ifss(argv[1]);
    double c0;
    double c1;
    vector<double> m0(57);
    vector<double> m1(57);
    vector<double> v0(57);
    vector<double> v1(57);
    string line;
    string data;

    getline( ifss, line);
    c0=atof(line.c_str());

    getline( ifss, line);
    c1=atof(line.c_str());

    getline( ifss, line);
    istringstream templine(line);
    for(int j=0;j<57;j++)
    {
        getline( templine, data,',');
        m0[j]=atof(data.c_str());
    }

    getline( ifss, line);
    istringstream templine1(line);
    for(int j=0;j<57;j++)
    {
        getline( templine1, data,',');
        m1[j]=atof(data.c_str());
    }

    getline( ifss, line);
    istringstream templine2(line);
    for(int j=0;j<57;j++)
    {
        getline( templine2, data,',');
        v0[j]=atof(data.c_str());
    }

    getline( ifss, line);
    istringstream templine3(line);
    for(int j=0;j<57;j++)
    {
        getline( templine3, data,',');
        v1[j]=atof(data.c_str());
    }

	vector<vector<double> >DData(58,vector<double>(600));

	//string line;
    ifstream fff(argv[2]);

	for(int i=0;i<600;i++)
	{
		getline( fff, line,'\n');
		istringstream templine(line);

        string data;
        getline( templine, data,',');
        for(int j=0;j<57;j++)
        {
            getline( templine, data,',');
            DData[j][i]=atof(data.c_str());
        }
	}

    for(int i=0;i<600;i++)
    {
        DData[57][i]=0;
    }




    int ans;
    int counter=0;
    for(int j=0;j<600;j++)
    {
        double mul0=0,mul1=0;
        for(int i=0;i<57;i++)
        {
            if(abs(v0[i])>0.0000000001 && abs(v1[i])>0.0000000001)
            {
                mul0=mul0+Gaussian(m0[i],v0[i],DData[i][j]);
                mul1=mul1+Gaussian(m1[i],v1[i],DData[i][j]);
            }
           // cout<<mul0<<" "<<mul1<<endl;
        }

        //cout<<mul0<<" "<<mul1<<" ";
        if(mul0+log(c0) > mul1+log(c1)) ans=0;
        else ans=1;
        DData[57][j]=ans;
    }


/*
    for(int i=0;i<num;i++)
    {
        for(int j=0;j<57;j++)
        {
            cout<<D0[i][j]<<" ";
        }
        cout<<endl<<endl;
    }
*/
        ofstream ofss(argv[3]);
        ofss<<"id,label"<<endl;

        for(int i=0;i<600;i++)
        {
            ofss<<i+1<<","<<DData[57][i]<<endl;
        }

        return 0;
}
