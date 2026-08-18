#include<iostream>
using namespace std;
void recursionPrint(int i){
    if (i<1){
        return;
    }
    else{
        cout<<i<<'\n';
        recursionPrint(i-1);
    }
}

int main(){
    recursionPrint(5);
}