#include<bits/stdc++.h>
using namespace std;

void selection_sort(int arr[],int n){
    int min,temp;
    for(int i=0;i<=n-2;i++){
        min=i;
        for(int j=i;j<=n-1;j++){
            if (arr[j]<arr[min]) min=j;
        }
        temp=arr[i];
        arr[i]=arr[min];
        arr[min]=temp;
    }

}

void bubble_sort(int arr[],int n){
    int temp;
    for(int i=n-1;i>=1;i--){
        for(int j=0;j<i;j++){
            if (arr[j]>arr[j+1]){
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

}

int main(){
    int n;
    cout<<"Enter The size of array\n";
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++) cin>>arr[i];
    //selection_sort(arr,n);
    bubble_sort(arr,n);
    cout<<"The sorted array is \n";
    for(int i=0;i<n;i++) cout<<arr[i]<<" ";
}