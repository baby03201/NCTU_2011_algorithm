#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

struct data{
    int id;
    int prior;
    int arrival;
    int execute;
    int left;
}queue[10000],storage[10000],done[10000];

void swap(data A[],int a,int b){
    int tmp_id,tmp_prior,tmp_arrival,tmp_execute,tmp_left;
    tmp_id=A[b].id;
    tmp_prior=A[b].prior;
    tmp_arrival=A[b].arrival;
    tmp_execute=A[b].execute;
    tmp_left=A[b].left;
    A[b].id=A[a].id;
    A[b].prior=A[a].prior;
    A[b].arrival=A[a].arrival;
    A[b].execute=A[a].execute;
    A[b].left=A[a].left;
    A[a].id=tmp_id;
    A[a].prior=tmp_prior;
    A[a].arrival=tmp_arrival;
    A[a].execute=tmp_execute;
    A[a].left=tmp_left;
}

void min_heapify(data array[],int index,int size){
    for(int i=index;array[i].id && 2*i<=size;){
        int l,r,lowest;
        l=2*i;
        r=2*i+1;
        if(array[l].prior<array[i].prior && l<=size)
            lowest=l;
        else
            lowest=i;

        if(array[r].prior<array[lowest].prior && r<=size)
            lowest=r;

        if(lowest!=i){
            swap(array,i,lowest);
            i=lowest;
        }else{
            break;
        }
    }
}

data extract_min(data A[],int size){
    if(size<1)
        cout<<"heap underflow\n";
    data min;
    min=A[1];
    swap(A,1,size);
    size-=1;
    min_heapify(A,1,size);
    return min;
}

void decrease_key(data A[],int i,int key){
    A[i].prior=key;
    while(i>1 && A[i/2].prior>A[i].prior){
        swap(A,i,i/2);
        i/=2;
    }

}

int insert(data A[],int id,int arrive,int key,int execute,int left,int size){
    size+=1;
    A[size].prior=2147483647; //make it uppest bound
    A[size].id=id;
    A[size].arrival=arrive;
    A[size].execute=execute;
    A[size].left=left;
    decrease_key(A,size,key);
    return size;
}


int main(){
    int index=-1;
    fstream fin;
    fin.open("test2.txt",ios::in);
    while(fin.good()){
        fin>>storage[++index].id
           >>storage[index].arrival
           >>storage[index].prior
           >>storage[index].execute;
    }
    //sorting storage in arrive time

    for(int i=0;i<=index;i++){
        for(int j=i+1;j<=index;j++){
            if(storage[i].arrival > storage[j].arrival){
                swap(storage,i,j);
            }
        }
    }
    data process;
    int running=0,ptr=0,size=0,dsize=0,finish;
    //follow time to insert data
    for(int time=0;ptr<=index || size>0;time++){

        if(storage[ptr].arrival==time){

            if(running==0){
                process.id=storage[ptr].id;
                process.arrival=storage[ptr].arrival;
                process.prior=storage[ptr].prior;
                process.execute=storage[ptr].execute;
                process.left=storage[ptr].execute;
                running=1;

            }else{
                //new arrival data ,compare priority between process and current data
                process.left--;
                if(process.prior>storage[ptr].prior){

                    if(process.left==0){
                        dsize=insert(done,process.id,process.arrival,process.prior,process.execute,time,dsize);
                        process.id=storage[ptr].id;
                        process.arrival=storage[ptr].arrival;
                        process.prior=storage[ptr].prior;
                        process.execute=storage[ptr].execute;
                        process.left=storage[ptr].execute;
                    }else{

                        size=insert(queue,process.id,process.arrival,process.prior,process.execute,process.left,size);
                        process.id=storage[ptr].id;
                        process.arrival=storage[ptr].arrival;
                        process.prior=storage[ptr].prior;
                        process.execute=storage[ptr].execute;
                        process.left=storage[ptr].execute;
                    }
                }else{

                    if(process.left==0){

                        dsize=insert(done,process.id,process.arrival,process.prior,process.execute,time,dsize);
                        process.id=storage[ptr].id;
                        process.arrival=storage[ptr].arrival;
                        process.prior=storage[ptr].prior;
                        process.execute=storage[ptr].execute;
                        process.left=storage[ptr].execute;
                        running=1;
                    }else{
                        size=insert(queue,storage[ptr].id,storage[ptr].arrival,storage[ptr].prior,storage[ptr].execute,storage[ptr].execute,size);
                    }
                }
            }
            ptr++;
        }else if(running == 1){
            process.left--;
            if(process.left==0){
                if(size>0){
                    dsize=insert(done,process.id,process.arrival,process.prior,process.execute,time,dsize);
                    data buffer;
                    buffer=extract_min(queue,size);
                    size--;
                    process.id=buffer.id;
                    process.arrival=buffer.arrival;
                    process.prior=buffer.prior;
                    process.execute=buffer.execute;
                    process.left=buffer.left;
                }else if(size==0){

                    dsize=insert(done,process.id,process.arrival,process.prior,process.execute,time,dsize);
                    running=0;
                }
            }else{

            }

        }else if(running == 0){
            if(size>0){

                data buffer;
                buffer=extract_min(queue,size);
                size--;
                process.id=buffer.id;
                process.arrival=buffer.arrival;
                process.prior=buffer.prior;
                process.execute=buffer.execute;
                process.left=buffer.left;
                running=1;
            }
        }
        finish=time;
        }
        finish+=process.left;
        dsize=insert(done,process.id,process.arrival,process.prior,process.execute,finish,dsize);
        int total=0;
        for(int i=1;i<=dsize;i++){
            int sum;
            sum=done[i].left-done[i].arrival-done[i].execute;
            total+=sum;
        }

        cout<<(float)total/(index+1)<<endl
            <<finish<<endl;
    }


