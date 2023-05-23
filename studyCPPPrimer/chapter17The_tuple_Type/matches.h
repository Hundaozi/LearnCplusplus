#include<iostream>
#include"../chapter7-Classes/Sales_data.h"
#include<tuple>
#include<vector>
#include<string>
#include<algorithm>
//使用元组
typedef std::tuple<std::vector<Sales_data>::size_type,
                   std::vector<Sales_data>::const_iterator,
                   std::vector<Sales_data>::const_iterator> matches;

std::vector<matches>
findBook(const std::vector<std::vector<Sales_data>> &files,
         const std::string &book)
{
    std::vector<matches> ret; //初始化为空

    for(auto it = files.cbegin(); it != files.cend(); ++it){

        auto found=std::equal_range(it->cbegin(),it->cend(), book , compareIsbn);

        if(found.first != found.second)

            ret.push_back(std::make_tuple(it - files.cbegin(), found.first, found.second));
    }
    return ret;
}

void reportResults(std::istream &in, std::ostream &os, const std::vector<std::vector<Sales_data>> &files)
{
    std::string s;
    while(in >> s){
        auto trans = findBook(files, s);
        if(trans.empty()){

            std::cout<< s << "not found in any stores" <<std::endl;
            continue;    //get the next book to look for

        }

        for(const auto &store : trans)
            os << "store"<< std::get<0>(store) <<" sales: " << accumulate(std::get<1>(),std::get<2>(store),
                                                               Sales_data(s)) <<std::endl;
    }
}