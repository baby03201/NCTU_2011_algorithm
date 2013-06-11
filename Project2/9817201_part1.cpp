#include <iostream>
#include <cstring>
using namespace std;

int array[10000];


int left(int i){
    return 2*i;
}

int right(int i){
    return 2*i+1;
}


int main(){
    int size,index,x=1,i,length;
    cin>>size>>index;

    while(x<=size){
        cin>>array[x++];
    }

    for(i=index;array[i] && 2*i<=size;){
        int l,r,largest;
        l=left(i);
        r=right(i);
        if(array[l]>array[i] && l<size)
            largest=l;
        else
            largest=i;
        if(array[r]>array[largest] && r<size)
            largest=r;

        if(largest!=i){
            int tmp;
            tmp=array[largest];
            array[largest]=array[i];
            array[i]=tmp;
            i=largest;
        }
    }
    for(int i=1;i<=size;i++)
        cout<<array[i]<<endl;

}


