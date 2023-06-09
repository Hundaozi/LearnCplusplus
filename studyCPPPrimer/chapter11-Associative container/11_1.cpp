#include<iostream>
#include<string>
#include<map>
#include<set>

using namespace std;

int main(){

    map<string ,size_t> word_count;
    set<string> exclude ={"The","But","And","Or","An","A",
                          "the","but","and","or","an","a"
    };

    map<string,string> authors={
        {"Joyce","James"},
        {"Austen","Jane"},
        {"Dickens","Charles"}
    };

    string word;

    while(cin>>word)
        if (exclude.find(word)==exclude.end())
            ++word_count[word];

    for(const auto &w:word_count)
        cout<<w.first<<" occurs "<<w.second
            <<((w.second>1)? " time " : " time ") <<endl;

    return 0;
}