#include <iostream>
#include <fstream>
#include <math.h>
#define INFINITE (int) (pow(2,31)-1)
#define MAX 10000
using namespace std;

int W[MAX][MAX];


int main(){
    int num,a,b,c;

    fstream fin;
    fin.open("testdata2_2.txt",ios::in);
    fin>>num;
    for(int i = 1; i <= num; i++){
        for(int j = 1; j <= num; j++)
            if( i == j ) W[i][j] = 0;
            else W[i][j] = INFINITE;
    }

    while(fin>>a>>b>>c){
        W[a][b] = c;
    }

    fin.close();

    for(int k = 1; k <= num ; k++){
        for(int i = 1; i <= num; i++){
            for(int j = 1; j <= num ; j++){
                int buffer;
                if ( W[i][k] == INFINITE || W[k][j] == INFINITE )
                    buffer = INFINITE;
                else
                    buffer = W[i][k] + W[k][j];
                if ( W[i][j] < buffer )
                    W[i][j] = W[i][j];
                else
                    W[i][j] = buffer;
            }
        }
    }
    for(int i = 1; i <= num ; i++){
        for( int j = 1; j <= num; j++){
            if(W[i][j] == INFINITE)
                cout<<"n ";
            else
                cout<< W[i][j]<< " ";
        }
    cout<<endl;
    }
}
