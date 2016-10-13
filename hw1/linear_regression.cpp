#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main()
{
	vector<vector<double> >Test(240,vector<double>(162));

	string line;
	fstream ff("test_X.csv");
	int ii=0,jj=0;
	for(int i=0;i<4320;i++)
	{
		getline( ff, line,'\n');
		istringstream templine(line); // string ??? stream
        for(int j=0;j<11;j++)
        {

			string data;
			getline( templine, data,',');

            if (j!=0 && j!=1)
            {
				if(data.compare("NR")==0)
					Test[i/18][jj]=0;
				else 
					Test[i/18][jj]=atof(data.c_str());
                jj++;
            }
		    if(jj==162) jj=0;
         }
	}

	
	
	vector<vector<double> >matrix(4320,vector<double>(24));
	fstream file;
	file.open("train.csv");

	for(int i=0;i<4321;i++)
	{
		getline( file, line,'\n');
		if (i!=0 )
		{
			jj=0;
			istringstream templine(line); // string Âà´«¦¨ stream
			for(int j=0;j<27;j++)
			{
				string data;
				getline( templine, data,',');
				if (j!=0 && j!=1 && j!=2)
				{
					if(data.compare("NR")==0)
						matrix[ii][jj]=0;
					else
						matrix[ii][jj]=atof(data.c_str());
					jj++;
				}
			}
			ii++;
		}
	}



	vector<vector<double> >temp(216,vector<double>(480));
	int a=0,b=0;
	for(int i=0;i<4320;i++)
	if(i%18==0)
    {
        for(int m=0;m<18;m++)
            for(int n=0;n<24;n++)
            {
				temp[a+m][b+n]=matrix[m+i][n];

            }
		b=b+24;
		if(b==480)
        {
			b=0;
			a=a+18;
        }
    }

	
int q=0;

vector<double>R(5652);
for(int i=0;i<12;i++)
    for(int j=0;j<471;j++)
    {
		R[q]=temp[i*18+9][j+9];
		q=q+1;
    }


vector<vector<double> >Data(163,vector<double>(5652));

int t=0;
for(int m=0;m<12;m++)
    for(int i=0;i<471;i++)
	{
        for(int j=0;j<18;j++)
                for(int k=0;k<9;k++)
                        Data[9*j+k+1][t]=temp[m*18+j][i+k];
        t=t+1;
	}





int datanum=5652;
int parnum=163;

vector<double>W(parnum);
vector<double>G(parnum);
vector<double>D(parnum);

W={0.0721946,0.000500402,-0.0339691,-0.00653147,-0.0421718,-0.00747323,0.00474141,0.00413558,-0.0105025,0.07452,0.000524569,0.0336615,0.0587637,0.0119085,0.0476261,0.118186,0.090481,0.125908,0.251571,0.100939,0.022614,0.0626673,-0.30123,0.398844,-0.128822,-0.376131,0.289704,1.06349,-0.220611,0.0212546,-0.227458,-0.0214134,0.3769,-0.242502,-0.0776493,-0.0708147,0.301353,0.0312379,0.0141257,0.106049,-0.0304973,-0.00948204,-0.0902074,0.0581266,0.0877431,-0.151455,0.0162542,-0.0326153,-0.02281,-0.0585496,-0.00751798,-0.00349433,-0.0518957,-0.0805173,0.157209,0.00696407,-0.027048,0.00661776,0.0131869,0.0223619,0.00162146,-0.0252045,0.00670568,0.118448,0.00398019,0.010586,-0.00706911,-0.021968,0.00325393,-0.032698,-0.0228374,-0.0135134,0.101423,0.00635971,0.00791402,-0.0264282,0.0384618,-0.00864551,-0.0356743,0.036731,-0.00347813,0.0368688,-0.0353446,-0.00364341,0.199397,-0.227056,-0.0150478,0.475267,-0.54512,0.0272085,0.947522,0.0316637,-0.0010861,-0.0541317,0.00841685,-0.0475162,0.0483539,0.0159576,-0.0344177,-0.0830303,-0.00320672,0.0156262,-0.000490855,-0.0272102,-0.0214127,0.0119072,-0.0339314,0.0122334,0.0225238,-0.247034,0.281899,-0.0369118,-0.0733898,-0.0128675,0.0598823,-0.10127,0.107754,0.172657,0.010411,0.0163139,0.0251699,-0.0289028,0.0765169,0.108639,0.0748743,0.0815623,0.223611,-0.00047994,0.00293184,-0.000698652,0.00181064,0.00029415,0.00158283,-0.00230844,0.00100899,0.00027592,-0.00197473,-0.000851591,0.00103124,-0.00209987,0.000553898,1.32081e-05,-4.57335e-05,-0.00235026,0.000527203,-0.100693,-0.0538833,0.12032,0.0162981,-0.0560773,-0.0331542,-0.0631357,-0.0889049,-0.0601244,-0.0432953,0.0843837,-0.0696588,-0.115776,-0.0342934,0.237667,-0.019792,-0.156358,0.0845619};

/*
for(int i=0;i<W.size();i++)
{
	W[i]=0.1;
}
*/

for(int i=0;i<5652;i++)
    Data[0][i]=1;

double rate=0.1;
int time=7;

double minimum=10000;
double count=0;


for(int k=0;k<time;k++)
{
        vector<double>Y(datanum);
        for(int n=0;n<datanum;n++)
        {
            for(int m=0;m<parnum;m++)
            {
                Y[n]=Y[n]+W[m]*Data[m][n];
            }
            for(int m=0;m<parnum;m++)
            {
                D[m]=D[m]-2*(R[n]-Y[n])*Data[m][n];
                G[m]=G[m]+D[m]*D[m];
            }
        }

    if(k%1000==0)
    {
	cout<<k<<endl;
	for(int i=0;i<parnum;i++)
		cout<<W[i]<<"  ";
	cout<<endl<<endl;
    }

        for(int m=0;m<parnum;m++)
        {
            W[m]=W[m]-rate*D[m]/sqrt(G[m]);
            D[m]=0;
        }
}






	vector<double>A(240);
	for(int i=0;i<240;i++)
	{
		A[i]=W[0];
		for(int j=1;j<163;j++)
		{
			A[i]=A[i]+W[j]*Test[i][j-1];
		}
	}

	
	

  ofstream ofs("linear_regression.csv");
  ofs<<"id,value\n";

  for (int i=0;i<A.size();i++)
  {
      ofs<<"id_"<<i<<","<<A[i]<<'\n';
  }
  file.close();

  return 0;
}
