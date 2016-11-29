#include<iostream>
#include<fstream>
#include<string>
using namespace std;
 
int main(int argc, char* argv[]){
    ofstream ofs("title.txt");

    
    string filename=string(argv[1])+"title_StackOverflow.txt";

///    cout<<filename<<endl;
    fstream fp;
    string line;
    fp.open(filename.c_str(), ios::in);//開啟檔案
    if(!fp){//如果開啟檔案失敗，fp為0；成功，fp為非0
        cout<<"Fail to open file: "<<filename<<endl;
    }
//    cout<<"File Descriptor: "<<fp<<endl;
    while(getline(fp,line)){
	string oline=line;
	bool diff=false;
	char who;
	for (int i=0;i<line.size();i++)
	{
		int a=(int)line[i];
		if(!((65<=a && a<=90)||(97<=a && a<=122)||a==32))
		{
			line[i]=' ';
			who=line[i];
			diff=true;
		}
	}
	if(diff==true)
	{
//		cout<<oline<<endl;
//		cout<<line<<endl;
//		cout<<endl;
	}
	ofs<<line<<endl;
    }
 
    fp.close();//關閉檔案
}
