#include<iostream>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

int main()
{
    // int ia[3][4]={
    //     {0,1,2,3},
    //     {4,5,6,7},
    //     {8,9,10,11}
    // };
    // for (const auto &row :ia)
    //     for(auto col:row)
    //         cout<<col<<endl;

    int ia[3][4];
    // int  (*p)[4]=ia;
    // p= &ia[2];
    // cout<<p<<endl;

    // for (auto p =ia;p!= ia+3;++p){
    //     for (auto q =*p; q != *p +4; ++q)
    //         cout<<*q<< ' ';
    //     cout<<endl;
    // }

    for(auto p=begin(ia);p!=end(ia); ++p){
        for(auto q =begin(*p); q!= end(*p);++q)
            cout<<*q<< ' ';
    cout<<endl;
    }

    return 0;
}