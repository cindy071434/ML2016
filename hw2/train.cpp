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
	vector<vector<double> >Data(59,vector<double>(4001));

	string line;
    ifstream ff(argv[1]);

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
        }
	}

    int datanum=4001;
    int parnum=58;

    vector<double>W(parnum);
    vector<double>G(parnum);
    vector<double>D(parnum);
    vector<double>BW(parnum);

//////////

//W={-1.42479,-0.266251,-0.209193,0.0638654,0.974838,0.537968,0.924479,2.13173,0.778662,0.714983,0.147,0.264594,-0.547687,0.107161,0.204409,1.52446,1.10475,0.904233,0.230688,0.100276,1.36883,0.209575,0.342682,2.23581,1.12382,-2.4219,-1.93734,-1.40516,0.0534103,-1.77389,-1.27846,-2.11845,-1.42227,-2.45238,-1.27736,-2.0486,-0.446891,-1.45273,-1.08502,-1.3038,-1.49558,-1.97839,-2.25595,-1.45637,-1.64116,-1.04406,-1.93282,-3.04526,-2.62801,-2.54434,-1.43515,-2.14473,0.519187,2.41606,1.20257,-0.0077542,0.0170245,0.00102275};
W={-1.45609,-0.546607,-0.16868,0.146603,2.27197,0.492538,1.05854,2.49114,0.521774,1.04598,0.113016,-0.0625259,-0.154883,0.0011298,0.0892394,1.0925,0.994403,1.15964,0.12031,0.0814507,0.929782,0.22504,0.221652,3.02203,0.409377,-1.89911,-0.958948,-6.73027,0.661004,-2.06536,-0.396354,-0.192511,-6.55132,-0.724478,0.941363,-1.84127,0.983499,0.221523,-0.601441,-0.964824,-0.449567,-7.02824,-3.05247,-0.967083,-1.48125,-0.776132,-1.53758,-1.83814,-4.01909,-1.33045,-0.800426,-0.844941,0.312054,4.99624,2.69948,-0.0134224,0.00904299,0.000628026};
//W={-1.46362,-0.545042,-0.167114,0.14207,2.2856,0.492385,1.06289,2.50354,0.528563,1.04759,0.116051,-0.0523725,-0.156896,0.000658892,0.0941415,1.10936,1.00296,1.15868,0.11914,0.0813238,0.933233,0.225566,0.221862,3.02894,0.419476,-1.94786,-1.01435,-7.02589,0.669946,-2.08002,-0.401175,-0.214692,-6.8128,-0.817703,0.962075,-1.87422,0.98037,0.190958,-0.609071,-0.96897,-0.449634,-7.28307,-3.08653,-0.97454,-1.5004,-0.781748,-1.58039,-1.85658,-4.11175,-1.359,-0.813129,-0.863994,0.324482,5.00812,2.70867,-0.0132199,0.00929993,0.000733306};
//////////
    for(int i=0;i<4001;i++)
        Data[0][i]=1;

/*
	for(int i=0;i<4001;i++)
    {
        for(int j=0;j<59;j++)
        {
            cout<<Data[j][i]<<" ";
        }
        cout<<endl;
    }

*/


double rate=4.5;
int time=1014;
//0.1 23000
//10 185
//4.5

double minimum=10000;

double bestacc=0;
int bestcount=0;

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
                D[m]=D[m]-2*(Data[58][n]-(1/(1+exp((-1)*Y[n]))))*Data[m][n];
                G[m]=G[m]+D[m]*D[m];
            }
        }

//    if(k%1==0)
    {
        /*
        cout<<k<<endl;
        for(int i=0;i<parnum;i++)
            cout<<W[i]<<"  ";
        cout<<endl<<endl;
*/
        vector<double>Q(datanum);
        double counter=0;
        for(int n=0;n<datanum;n++)
        {
            for(int m=0;m<parnum;m++)
            {
                Q[n]=Q[n]+W[m]*Data[m][n];
            }
            Q[n]=1/(1+exp((-1)*Q[n]));
            if(Q[n]>=0.5) Q[n]=1;
            else Q[n]=0;

            if(Q[n]==Data[58][n]) counter++;
        }

        if(counter/4001>=bestacc)
        {
//            cout<<"count = "<<k<<endl;
//            cout<<"acc = "<<counter/4001<<endl;
            BW=W;
            bestacc=counter/4001;
            bestcount=k;

            for(int i=0;i<BW.size();i++)
            {
 //               cout<<BW[i]<<" ";
            }
 //           cout<<endl;
        }
    }

        for(int m=0;m<parnum;m++)
        {
            W[m]=W[m]-rate*D[m]/sqrt(G[m]);
            D[m]=0;
        }
}

  ofstream ofs(argv[2]);
  ofs<<BW[0];
  for(int i=1;i<BW.size();i++)
  {
    ofs<<","<<BW[i];
  }
    ofs<<endl;

/*

	vector<double>A(240);
	for(int i=0;i<240;i++)
	{
		A[i]=W[0];
		for(int j=1;j<163;j++)
		{
			A[i]=A[i]+W[j]*Test[i][j-1];
		}
	}




  ofstream ofs("kaggle_best.csv");
  ofs<<"id,value\n";

  for (int i=0;i<A.size();i++)
  {
      ofs<<"id_"<<i<<","<<A[i]<<'\n';
  }
  file.close();

*/

  return 0;
}
