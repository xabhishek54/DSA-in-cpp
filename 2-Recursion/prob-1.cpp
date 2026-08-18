#include<iostream>
using namespace std;
void recursionPrint(int i){
    if (i<1){
        return;
    }
    else{
        recursionPrint(i-1);
        cout<<i<<'\n';
    }
}

int main(){
    recursionPrint(5);
}