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

int main(){
    int n;
    cout<<"Enter The size of array\n";
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++) cin>>arr[i];
    selection_sort(arr,n);
    for(int i=0;i<=n;i++) cout<<arr[i]<<" ";
}