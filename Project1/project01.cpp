#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;

void print(const char *v, const int size)
{
  if (v != 0) {
    for (int i = 0; i < size; i++) {
      cout<<v[i]<<" ";
    }
    cout<<endl;
  }
} // print


void swap(char *v, const int i, const int j)
{
  int t;
  t = v[i];
  v[i] = v[j];
  v[j] = t;
}


void rotateLeft(char *v, const int start, const int n)
{
  int tmp = v[start];
  for (int i = start; i < n-1; i++) {
    v[i] = v[i+1];
  }
  v[n-1] = tmp;
} // rotateLeft


void permute(char *v, const int start, const int n)
{
  print(v, n);
  if (start < n) {
    int i, j;
    for (i = n-2; i >= start; i--) {
      for (j = i + 1; j < n; j++) {
	swap(v, i, j);
	permute(v, i+1, n);
      } // for j
      rotateLeft(v, i, n);
    } // for i
  }
} // permute

int main(){
    char input[10000];
    cin>>input;
    permute(input,0,strlen(input));
}
