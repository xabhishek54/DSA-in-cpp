#include<iostream>
using namespace std;
void swap(int *a,int *b){
    int temp=*a;
    *b=*a;
    *a=*temp;
}
void reverseArray(int i,int arr[],int n){
    if (i>n/2){
        return;
    }
    swap(i+1,arr[i],arr[n-i-1]);
}

int main(){
    
}