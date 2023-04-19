#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<utility>
using namespace std;

pair<string,int>
process(vector<string> &v)
{
    if(!v.empty())
        return make_pair(v.back(), v.back().size());        //生成新的pair
    else    
        return pair<string, int>();
}

int main(){
    

    return 0;
}