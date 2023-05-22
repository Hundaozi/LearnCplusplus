#include<iostream>
#include"../chapter7-Classes/Sales_data.h"

namespace std{
    //自定义hash数据结构
    template<> //
    struct hash<Sales_data>
    {
        typedef size_t result_type;
        typedef Sales_data argument_type;
        size_t operator()(const Sales_data& s) const;
    };

    size_t
    hash<Sales_data>::operator()(const Sales_data& s) const
    {
        return hash<string>() (s.bookNo) ^
               hash<unsigned>() (s.units_sold) ^
               hash<double>() (s.revenue);
    }
}