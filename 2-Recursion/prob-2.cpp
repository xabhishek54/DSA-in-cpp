#include<iostream>
using namespace std;
//FUnctional Way
int sum_Recursion(int a){
    if (a<1){
        return 0;
    }
    return a+sum_Recursion(a-1);
}

//Paramaterized way
void sum_para(int a,int sum){
    if (a<1){
        cout<<sum;
        return;
    }
    sum_para(a-1,sum+a);
}


int main(){
    cout<<sum_Recursion(5)<<'\n';
    sum_para(5,0);
}