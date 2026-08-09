#include<bits/stdc++.h>
using namespace std;

void explainPair();
void explainVector();
void sorting();
int main(){
    sorting();
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

//comparator
bool comp(pair<int,int> p1,pair<int,int> p2){
    if (p1.second<p2.second) return true;
    if (p1.second>p2.second) return false;
    
    //then it is same
    if (p1.first>p2.first) return true;
    return false;
}

void sorting(){
    int a[]={4,2,9,2,1,10,20};
    sort(a+1,a+5);
    for(int i=0;i<sizeof(a)/sizeof(a[0]);i++){
        cout<<a[i]<<" ";
    }
    pair<int,int> p[]={{1,2},{2,1},{4,1}};
    sort(p,p+4,comp);
    for(int i=0;i<sizeof(p)/sizeof(p[0]);i++){
        cout<<"("<<p[i].first<<","<<p[i].second<<"), ";
    }

    cout<<"\n";
    cout<<__builtin_popcount(7);
    cout<<"\n";
    
    //permutations
    string s="231";
    sort(s.begin(),s.end());
    do{
        cout<<s<<'\n';
    }while(next_permutation(s.begin(),s.end()));
    
}