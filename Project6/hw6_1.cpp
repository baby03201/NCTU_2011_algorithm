#include <iostream>
#include <math.h>
#include <fstream>
#define INFINITE (int) (pow(2,31)-1)
#define MAX 10000
using namespace std;

int graph[MAX][MAX]; // maintance adjacency list & weight list
int dist[MAX],predecessor[MAX],S[MAX],min_priority_queue[MAX];

int w(int a, int b){
    return graph[a][b];
}

void min_heapify(int array[],int index,int size){
    for(int i=index;array[i] && 2*i<=size;){
        int l,r,lowest;
        l=2*i;
        r=2*i+1;
        if(dist[array[l]] < dist[array[i]] && l<=size)
            lowest=l;
        else
            lowest=i;

        if(dist[array[r]] < dist[array[lowest]] && r<=size)
            lowest=r;

        if(lowest!=i){
            //swap(array,i,lowest);
            int tmp = array[i];
            array[i] = array[lowest];
            array[lowest] = tmp;
            i=lowest;
        }else{
            break;
        }
    }
}

int extract_min(int A[],int size){

    if(size<1)
        cout<<"heap underflow\n";
    int min,tmp;
    min=A[1];
    tmp = A[1];
    A[1] = A[size];
    A[size] = tmp;
    size-=1;
    min_heapify(A,1,size);

    return min;
}

void decrease_key(int A[],int i,int who){
    A[i] = who;
    while(i>1 && dist[A[i/2]] > dist[A[i]]){
        int tmp;
        tmp = A[i];
        A[i] = A[i/2];
        A[i/2] = tmp;
        i/=2;
    }
}

void decrease_key(int A[],int i){

    while(i>1 && dist[A[i/2]] > dist[A[i]]){
        int tmp;
        tmp = A[i];
        A[i] = A[i/2];
        A[i/2] = tmp;
        i/=2;
    }
}

void initialize_single_source(int num,int s){
    //foreach vertex v = G.v
    //      v.d = oo;
    //      v.n = NIL;
    //s.d = 0;
    for(int i = 1; i <= num; i++)
    {
        dist[i] = INFINITE;
        predecessor[i] = -1;
    }
    dist[s] = 0;
}

void relax(int u, int v,int index_q){
    //if v.d > u.d + w(u,v)
    //     v.d = u.d + w(u,v)
    //     v.p = u
    //cout<<"relax\n";
    int v_d, u_d, w_uv,buffer,tmp;
    v_d = dist[v];
    u_d = dist[u];
    w_uv = graph[u][v];
    if(u_d == INFINITE) buffer = INFINITE;
    else buffer = u_d + w_uv;
    if ( v_d > buffer )
    {
        dist[v] = buffer;
        for( int i = 1 ; i <= index_q ; i++)
            if(min_priority_queue[i] == v) tmp = i;
        decrease_key(min_priority_queue,tmp);
        predecessor[v] = u;
    }
}

void dijkstra(int num,int s){
    //cout<<"dijkstra\n";
    int i_s = 0,index_q = 1;
    initialize_single_source(num,s);
    //Q = G.v
    for( int i = 1; i <= num; i++){
        min_priority_queue[index_q] = i;
        decrease_key(min_priority_queue,index_q,i);
        index_q++;
    }
    index_q--;

    while(index_q>=1){
        int u;

        u = extract_min(min_priority_queue,index_q);
        index_q--;
        S[i_s++] = u;

        for( int i = 1; i <= num ; i++)
            if(graph[u][i] != 0)
                relax(u,i,index_q);

    }
    /*for( int i = 1; i <= num; i++)
            cout<< dist[i] << " "<<predecessor[i]<<endl;
        cout<<endl;*/
}

void print_path(int s, int v)
{
    if ( v == s )
        cout << s <<" ";
    else if ( predecessor[v] == -1 )
        cout << "no path from "<< s <<" to "<<v<<" exists";
    else
    {
        print_path ( s , predecessor[v] );
        cout << v <<" ";
    }
}
int main()
{
    int nodes_num,a,b,c;
    char first_in;
    fstream fin;
    fin.open("testdata1_1.txt",ios::in);
    memset(graph,0,sizeof(graph));
    fin >> nodes_num;
    while (fin >> first_in)
    {
        if (first_in != '*'){
        fin >>  b >> c;
        a = first_in - '0';
        graph[a][b] = c;
        }else{break;}
    }

    while(fin>>a>>b){
        dijkstra(nodes_num,a);
        if(dist[b] != INFINITE){
            cout<<"Weight: "<<dist[b]<<endl;
            cout<<"path: ";
        }
        print_path(a,b);
        cout<<endl<<endl;
    }
    fin.close();
}
