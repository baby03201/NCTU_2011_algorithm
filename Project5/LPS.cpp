#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int c[100][100],b[100][100];

void LCS_LENGTH(char x[],char y[]){
    int m,n;
    m=strlen(x);
    n=strlen(y);
    for(int i=1;i<=m;i++)
        c[i][0]=0;
    for(int j=0;j<=n;j++)
        c[0][j]=0;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            if(x[i-1]==y[j-1]){
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]=1;
            }else if( c[i-1][j] >= c[i][j-1] ){
                c[i][j]=c[i-1][j];
                b[i][j]=2;
            }else{
                c[i][j]=c[i][j-1];
                b[i][j]=3;
            }
}

void PRINT_LCS(char x[],int i,int j){
    if(b[i][j]==1){
        PRINT_LCS(x,i-1,j-1);
        cout<<x[i-1]<<" ";
    }else if(b[i][j]==2) PRINT_LCS(x,i-1,j);
    else PRINT_LCS(x,i,j-1);
}

int main(){
    string input;
    char x[100],y[100];
    int index=0;
    cin>>input;
    cout<<input;
}
