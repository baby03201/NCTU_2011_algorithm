#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;
int c[100][100],b[100][100];

string x0,y0,z0;

void PRINT_LCS(char x[],char y[],int i,int j){
    int Score,ScoreDiag,ScoreUp,ScoreLeft;

    while(i>0 && j>0){
        Score = c[i][j];
        ScoreDiag = c[i-1][j-1];
        ScoreUp = c[i-1][j];
        ScoreLeft = c[i][j-1];
        if(b[i][j]==1){
            if(Score == ScoreDiag+1){
                x0=x[i]+x0;
                y0=y[j]+y0;
                --i;
                --j;
            }
        }else if(b[i][j]==-1){
            if(Score == ScoreLeft-2 && b[i][j-1]!=-1){
                y0=y[j]+y0;
                x0=" "+x0;
                --j;
            }else if( Score == ScoreDiag-1){
                y0=y[j]+y0;
                x0=x[i]+x0;
                --i;
                --j;
            }else if( Score == ScoreUp-2){
                y0=" "+y0;
                x0=x[i]+x0;
                --i;
            }
        }else{
            if(Score == ScoreLeft-2){
                x0=" "+x0;
                y0=y[j]+y0;
                --j;
            }else if(Score == ScoreDiag-1){
                y0=y[j]+y0;
                x0=x[i]+x0;
                --i;
                --j;
            }else if(Score == ScoreUp-2){
                y0=" "+y0;
                x0=x[i]+x0;
                --i;
            }
        }

    }
    while(i > 0){
        x0=x[i]+x0;
        y0=" "+y0;
        --i;
    }
    while(j > 0){
        x0=" "+x0;
        y0=y[j]+y0;
        --j;
    }

}

void LCS_LENGTH(char x[],char y[]){

    int m,n;
    m=strlen(x)-1;
    n=strlen(y)-1;
    c[0][0]=0;
    for(int i=1;i<=m;i++)
        c[i][0]=c[i-1][0]-2;
    for(int j=1;j<=n;j++)
        c[0][j]=c[0][j-1]-2;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            if(x[i]==y[j]){
                int p,q,r;
                p=c[i-1][j-1]+1;
                q=c[i-1][j]-2;
                r=c[i][j-1]-2;
                if(p>=q && p>=r){
                    c[i][j]=p;
                    b[i][j]=1;
                }else if(q>=p && q>=r){
                    c[i][j]=q;
                    b[i][j]=-2;
                }else{
                    c[i][j]=r;
                    b[i][j]=-3;
                }
            }else{
                int p,q,r;
                p=c[i-1][j-1]-1;
                q=c[i-1][j]-2;
                r=c[i][j-1]-2;
                if(p>=q && p>=r){
                    c[i][j]=p;
                    b[i][j]=-1;
                }else if(q>=p && q>=r){
                    c[i][j]=q;
                    b[i][j]=-2;
                }else{
                    c[i][j]=r;
                    b[i][j]=-3;
                }
            }


   /* for(int i=0;i<=m;i++){
        for(int j=0;j<=n;j++)
            cout<<c[i][j]<<" ";
        cout<<endl;
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)
            cout<<b[i][j]<<" ";
        cout<<endl;
    }*/
    x0="";
    y0="";

    PRINT_LCS(x,y,m,n);

    cout<<x0<<endl
        <<y0<<endl;
}

int main(){
    string input1,input2;
    char x[100],y[100];
    int index=0,number=0;
    fstream fin;
    fin.open("input2_5.txt",ios::in);
    fin>>input1>>input2;
    fin.close();
    const char *tmp1,*tmp2;
    tmp1=input1.c_str();
    tmp2=input2.c_str();
    strcpy(x,tmp1);
    strcpy(y,tmp2);
    int m,n;
    m=strlen(x);
    n=strlen(y);

    for(int i=m;i>0;i--)
        x[i]=x[i-1];

    for(int j=n;j>0;j--)
        y[j]=y[j-1];
    y[0]='0';
    x[0]='0';
    y[n+1]='\0';
    x[m+1]='\0';

    LCS_LENGTH(x,y);
    tmp1=x0.c_str();
    tmp2=y0.c_str();
    x[0]='\0';
    y[0]='\0';
    strcpy(x,tmp1);
    strcpy(y,tmp2);
    z0="";
    for(int i=0;i<strlen(x);i++)
        if(x[i]==y[i]){
            z0+="+";
            number+=1;
        }else if(x[i]==' ' || y[i]==' '){
            z0+="*";
            number+=-2;
        }else{
            z0+="-";
            number+=-1;
        }

    fstream fout;
    fout.open("ouput2_5.txt",ios::out);
    fout<<number<<endl
        <<x0<<endl
        <<y0<<endl
        <<z0<<endl;
    fout.close();
}
