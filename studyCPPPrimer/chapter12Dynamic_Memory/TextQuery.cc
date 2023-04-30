#include "TextQuery.h"
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <utility>

TextQuery::TextQuery(std::ifstream &is): file(new std::vector<std::string>)
{
    std::string text;

    while(std::getline(is,text)){

        file->push_back(text);        

        int n=file->size()-1; //当前 line的number

        std::istringstream line(text);        //separate the line into words

        std::string word;

        while(line>>word){
            //wm 是一个map ，存储着<string, shared_ptr>
            auto &lines = wm[word];            //lines是一个智能指针 shared_ptr
            if(!lines)
                lines.reset( new std::set<line_no>); //分配一个新的set

            lines->insert(n);
        }
    }
}

//文本请求结果
QueryResult
TextQuery::query(const std::string &sought) const
{
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc=wm.find(sought);

    if(loc==wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

std::ostream &print(std::ostream & os, const QueryResult &qr)
{
    os<<qr.sought<<"  occurs "<< qr.lines->size()<<" "<<make_plural(qr.lines->size(), "time","s") <<std::endl;

    for(auto num: *qr.lines)
        os<< "\t(line) "<<num+1<<") "
          <<*(qr.file->begin() + num) <<std::endl;
    
    return os;
}