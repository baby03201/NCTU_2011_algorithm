#include <fstream>
#include <iostream>
#include <ctime>
#include <tchar.h>
#include <windows.h>
using namespace std;

int main(){
    fstream fout;
    int n=70000,MAX=999999,MIN=100000;
    fout.open("testdata7.txt",ios::out);
    srand(time(NULL));
    fout<<n<<endl
        <<"6"<<endl
        <<2<<endl;
    for(int i=0;i<n;i++){
        int random;
        random=rand()%(MAX-MIN+1)+MIN;
        fout<<random<<endl;
    }
    fout.close();
}
