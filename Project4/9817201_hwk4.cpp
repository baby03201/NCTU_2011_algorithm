#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

int partition(int A[],int p,int r){
    int i,x,tmp;
    x=A[r];
    i=p-1;
    for(int j=p;j<r;j++){
        if(A[j]<=x){
            i=i+1;
            tmp=A[i];
            A[i]=A[j];
            A[j]=tmp;
        }
    }
    tmp=A[r];
    A[r]=A[i+1];
    A[i+1]=tmp;
    return i+1;
}

int randomized_partition(int A[],int p,int r){
    int i,tmp;
    srand(time(0));
    i=rand()%(r-p+1)+p;
    //cout<<i<<endl;
    tmp=A[i];
    A[i]=A[r];
    A[r]=tmp;
    return partition(A,p,r);
}

void randomized_qsort(int A[],int p, int r){
    //fin.open("".ios::in);
    if(p<r){
        int q;
        q=randomized_partition(A,p,r);
        randomized_qsort(A,p,q-1);
        randomized_qsort(A,q+1,r);
    }
}

void radix_sort(string A[],int n,int k,int size){
    // n: number of digits
    // k: number of digits sort each pass
    int s=n-1,d;
    while(s>=0){
        for(int j=0;j<size;j++){
            int count=1,x=1,esi=0,f;
            d=s;
            f=s;
            while(count<=k && f>=0){

                int buf=A[j][f]-'0';
                esi+=buf*x;
                x*=10;
                f--;
                count++;
            }
            if(j==size-1){s=s-k;}
            for(int z=j+1;z<size;z++){
                int t,ct=1,x1=1,edi=0;
                t=d;
                while(ct<=k && t>=0){
                    int buf=A[z][t]-'0';
                    edi+=buf*x1;
                    x1*=10;
                    t--;
                    ct++;
                }
                if(esi>edi){
                    string tmp;
                    tmp = A[z];
                    A[z]=A[j];
                    A[j]=tmp;
                    esi=edi;
                }

            }
        }
    }

}

int randomized_selection(int A[],int p,int r,int i){
    int q,k;
    if(p==r)
        return A[p];
    q=randomized_partition(A,p,r);
    k=q-p+1;
    if(i==k)    // pivot value is the answer
        return A[q];
    else if (i<k)
        return randomized_selection(A,p,q-1,i);
    else
        return randomized_selection(A,q+1,r,i-k);
}

int main(){
    fstream fin;
    fin.open("testdata7.txt",ios::in);
    //-----------------------------------------------------------
    //randomized quicksort
    /*
    int array_size,x=1;
    int array[100000];
    fin>>array_size;
    while(fin>>array[x]){
        ++x;
    }
    //fin.close();
    randomized_qsort(array,1,array_size);
    fstream fout;
    fout.open("rqsort.txt",ios::out);
    int q=1;
    while(q<=array_size){
        fout<<array[q++]<<endl;
    }
    fout.close();
    */
    //-----------------------------------------------------------
    //radix sort
    //*
    int size,num_digits,num_pass,y=0;
    fin>>size>>num_digits>>num_pass;
    string radix[100000];
    while(fin>>radix[y]){
        y++;
    }
    fin.close();
    radix_sort(radix,num_digits,num_pass,size);
    fstream fout;
    fout.open("radixsort.txt",ios::out);
    int n=0;
    while(n<size){
        fout<<radix[n]<<endl;
        n++;
    }
    fout.close();
    //*/
    //------------------------------------------------------------
    //randomed selection
    /*
    int ar_size,largest,r=1;
    int selection[100000];
    fin>>ar_size>>largest;
    while(fin>>selection[r]){
        r++;
    }
    fin.close();
    cout<<randomized_selection(selection,1,ar_size,ar_size-largest+1)<<endl;
    */
    //------------------------------------------------------------

}
