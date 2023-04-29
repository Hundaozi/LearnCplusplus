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