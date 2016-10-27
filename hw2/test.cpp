#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main( int argc, char **argv )
{
	vector<double>W(58);
    ifstream ff(argv[1]);
    string line;
    getline( ff, line,'\n');
    istringstream templine(line);

    for(int j=0;j<58;j++)
    {
        string data;
        getline( templine, data,',');
        W[j]=atof(data.c_str());

        //cout<<W[j]<<" ";
    }
    //cout<<endl;




	vector<vector<double> >Data(59,vector<double>(600));

	//string line;
    ifstream fff(argv[2]);

	for(int i=0;i<600;i++)
	{
		getline( fff, line,'\n');
		istringstream templine(line);

        string data;
        getline( templine, data,',');
        for(int j=1;j<58;j++)
        {
            getline( templine, data,',');
            Data[j][i]=atof(data.c_str());
        }
	}

    for(int i=0;i<600;i++)
    {
        Data[0][i]=1;
        Data[58][i]=0;
    }
/*
    for(int i=0;i<600;i++)
    {
        for(int j=0;j<59;j++)
            cout<<Data[j][i]<<" ";
        cout<<endl;
    }
*/

        for(int n=0;n<600;n++)
        {
            for(int m=0;m<58;m++)
            {
                Data[58][n]=Data[58][n]+W[m]*Data[m][n];
            }
            Data[58][n]=1/(1+exp((-1)*Data[58][n]));
            if(Data[58][n]>=0.5) Data[58][n]=1;
            else Data[58][n]=0;
        }

        ofstream ofs(argv[3]);
        ofs<<"id,label"<<endl;

        for(int i=0;i<600;i++)
        {
            ofs<<i+1<<","<<Data[58][i]<<endl;
        }

}

