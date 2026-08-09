#include<bits/stdc++.h>
using namespace std;

void explainPair();
void explainVector();

int main(){
    explainVector();
}

//pairs
void explainPair(){
    pair<int,int> p={6,7};
    cout<<p.first<<" "<<p.second;
    pair<int,pair<int,int>> q={7,{6,9}};
    cout<<q.first<<" "<<q.second.first<<" "<<q.second.second;
    //pair  can be used as a data type
}

void explainVector(){
    vector<int> v;
    v.push_back(2);
    v.emplace_back(3);
    v.push_back(25);

    vector<pair<int,int>> vec;
    vec.push_back({1,2});
    vec.emplace_back(1,2);

    vector<int> a(5,99);
    vector<int> b(a);
     //vectors are dynamic in nature
    
     cout<<v[0]<<'\n';

     //we were learning containier till now, now iterator
     
    //  vector<int>::iterator it=v.begin();
    //  cout<<*(it)<< "\n";
    //  it+=2;
    //  cout<<*(it)<< " ";
     for(vector<int>::iterator it=v.begin(); it !=v.end();it++){
        cout<<*(it)<< " ";
     }

     for(auto it=v.begin();it!=v.end();it++){
        cout << *(it) << " ";

     }

     v.insert(v.end(),{4,5,1,23,34});
     v.erase(v.begin()+3,v.begin()+5);
    for(auto it=v.begin();it!=v.end();it++){
        cout << *(it) << " ";

     }


}