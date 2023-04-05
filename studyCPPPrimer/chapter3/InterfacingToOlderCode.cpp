//C+++和C语言代码的链接

#include<iostream>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

int main()
{
    int int_arr[]={0,1,2,3,4,5};

    // vector<int> ivec(begin(int_arr),end(int_arr));
    // for(auto i:ivec)
    //     cout<<i<<endl;

    vector<int> subVec(int_arr+1, int_arr+4);
    for(auto j:subVec)
        cout<<j<<endl;

}
