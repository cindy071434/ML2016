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
	vector<vector<double> >Data(59,vector<double>(4001));
//58
//1~57

	string line;
    ifstream ff(argv[1]);

    int num=0;
	for(int i=0;i<4001;i++)
	{
		getline( ff, line,'\n');
		istringstream templine(line);

        string data;
        getline( templine, data,',');
        for(int j=1;j<59;j++)
        {
            getline( templine, data,',');
            Data[j][i]=atof(data.c_str());
            if(j==58 && int(Data[j][i])==0) num++;
        }
	}


	vector<vector<double> >D0(num,vector<double>(57));
	vector<vector<double> >D1(4001-num,vector<double>(57));

    int a=0,b=0;
    for(int i=0;i<4001;i++)
    {
        if(int(Data[58][i])==0)
        {
            for(int j=1;j<58;j++)
            {
                D0[a][j-1]=Data[j][i];
            }
            a++;
        }
        else
        {
            for(int j=1;j<58;j++)
            {
                D1[b][j-1]=Data[j][i];
                //cout<<D1[b][j-1]<<" ";
            }
            b++;
        }
    }

/*
    ofstream ofs("D1.csv");
    for(int i=0;i<D1.size();i++)
    {
        ofs<<D1[i][0];
        for(int j=1;j<57;j++)
            ofs<<","<<D1[i][j];
        ofs<<endl;
    }
	*/
    vector<double> m0(57);
    vector<double> m1(57);
    vector<double> v0(57);
    vector<double> v1(57);

    for(int i=0;i<57;i++)
    {
        for(int j=0;j<num;j++)
            m0[i]=m0[i]+D0[j][i];
        m0[i]=m0[i]/double(num);

        for(int j=0;j<(4001-num);j++)
            m1[i]=m1[i]+D1[j][i];
        m1[i]=m1[i]/double(4001-num);

    }

    //cout<<4001-num<<endl;


    for(int i=0;i<57;i++)
    {
        for(int j=0;j<num;j++)
            v0[i]=v0[i]+(D0[j][i]-m0[i])*(D0[j][i]-m0[i]);
        v0[i]=v0[i]/double(num);

        for(int j=0;j<(4001-num);j++)
            v1[i]=v1[i]+(D1[j][i]-m1[i])*(D1[j][i]-m1[i]);
        v1[i]=v1[i]/double(4001-num);
    }

    ofstream ofss(argv[2]);
    ofss<<double(num)/4001<<endl;
    ofss<<double(4001-num)/4001<<endl;


    ofss<<m0[0];
    for(int i=1;i<m0.size();i++)
    {
        ofss<<","<<m0[i];
    }
    ofss<<endl;

    ofss<<m1[0];
    for(int i=1;i<m0.size();i++)
    {
        ofss<<","<<m1[i];
    }
    ofss<<endl;

    ofss<<v0[0];
    for(int i=1;i<m0.size();i++)
    {
        ofss<<","<<v0[i];
    }
    ofss<<endl;

    ofss<<v1[0];
    for(int i=1;i<m0.size();i++)
    {
        ofss<<","<<v1[i];
    }
    ofss<<endl;

//cout<<double(num)/4001<<endl;
/*
    for(int i=0;i<57;i++)
        cout<<v1[i]<<" ";
*/
//Data[1~57][4001]




/*
    int ans;
    int counter=0;
    for(int j=0;j<4001;j++)
    {
        double mul0=0,mul1=0;
        for(int i=1;i<58;i++)
        {
            if(abs(v0[i-1])>0.0000000001 && abs(v1[i-1])>0.0000000001)
            {
                mul0=mul0+Gaussian(m0[i-1],v0[i-1],Data[i][j]);
                mul1=mul1+Gaussian(m1[i-1],v1[i-1],Data[i][j]);
            }
           // cout<<mul0<<" "<<mul1<<endl;
        }

        cout<<mul0<<" "<<mul1<<" ";
        if(mul0+log(num) > mul1+log(4001-num)) ans=0;
        else ans=1;
        //cout<<ans<<endl;
        if(ans==int(Data[58][j])) counter++;
    }
    cout<<double(counter)/4001<<endl;
*/
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

  return 0;
}
