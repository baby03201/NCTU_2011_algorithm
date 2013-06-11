#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;
int c[100][100],b[100][100];
string answer;
int number;

void PRINT_LCS(char x[],int i,int j){

    if(i==0 || j==0) return;
    if(b[i][j]==1){
        PRINT_LCS(x,i-1,j-1);
        number++;
        answer+=x[i];
        answer+=" ";
    }else if(b[i][j]==2) PRINT_LCS(x,i-1,j);
    else PRINT_LCS(x,i,j-1);
}

void LCS_LENGTH(char x[],char y[]){

    int m,n;
    m=strlen(x)-1;
    n=strlen(y)-1;
    for(int i=1;i<=m;i++)
        c[i][0]=0;
    for(int j=0;j<=n;j++)
        c[0][j]=0;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            if(x[i]==y[j]){
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]=1;
            }else if( c[i-1][j] >= c[i][j-1] ){
                c[i][j]=c[i-1][j];
                b[i][j]=2;
            }else{
                c[i][j]=c[i][j-1];
                b[i][j]=3;
            }
    number=0;
    answer="";
    PRINT_LCS(x,m,n);
    cout<<number<<endl
        <<answer<<endl;
}

int main(){
    string input;
    char x[100],y[100];
    int index=0;
    //fstream fin;
    //fin.open("input.txt",ios::in);
    cin>>input;
    //fin.close();
    const char * tmp;
    tmp=input.c_str();
    strcpy(x,tmp);

    for(int i=strlen(x);i>0;i--){
        y[++index]=x[i-1];
        x[i]=x[i-1];
    }
    y[0]='0';
    x[0]='0';
    LCS_LENGTH(x,y);
}
