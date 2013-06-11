#include <iostream>
#include <cstring>
using namespace std;

void output(char*array,int length){
    for(int i=0;i<length;i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
}

void rotate(char *array,int head,int length){
    char buffer = array[head];
    for(int i=head;i<length-1;i++){
        array[i]=array[i+1];
    }
    array[length-1]=buffer;
}

void swap(char* array,int a,int b){
    char buffer = array[a];
    array[a]=array[b];
    array[b]=buffer;
}

void permutation(char *array,int start,int length){
    output(array,length);
    if(start<length){
        for(int i=length-2;i>=start;i--){
            for(int j=i+1;j<=length-1;j++){
                swap(array,i,j);
                permutation(array,i+1,length);
            }
            rotate(array,i,length);
        }
    }
}

int main(){
    char input[10000];
    int length;
    cin >> input;
    length=strlen(input);
    permutation(input,0,length);
}
