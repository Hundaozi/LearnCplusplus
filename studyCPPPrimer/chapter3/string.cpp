#include <iostream>
#include <string>
using std::endl;
using std::string ;
using std::cin;
using std::cout;
int main(){
    string line;
    while (getline(cin, line))
        for(auto c:line)
            cout<<c<<endl;
}