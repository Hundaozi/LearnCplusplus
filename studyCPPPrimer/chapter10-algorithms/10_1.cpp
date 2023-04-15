#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(){
    vector<int> vec={1,2,34,654,43,42,55};
    int val =42;
    auto result= find(vec.cbegin(),vec.cend(), val);
    cout<<"the value "<<val 
        <<(result ==vec.cend()? "is not present": " is present")<<endl;
}