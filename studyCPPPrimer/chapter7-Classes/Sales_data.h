
#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
#include <iostream>
class Sales_data
{
    //友元函数
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::ostream &print(std::ostream&, const Sales_data&);
    friend std::istream &read(std::istream, Sales_data&);

    
    public:
        
        Sales_data()=default;

        

        Sales_data(const std::string &s, unsigned n, double p):
            bookNo(s), units_sold(n), revenue(p*n) {}

        //告诉编译器按照实际的类型来构造函数，不允许做隐式转换
        //只能在声明时候使用
        explicit Sales_data(const std::string &s):bookNo(s){}
    
        explicit Sales_data(std::istream &);
        //其他成员函数
    
    std::string isbn() const  { return bookNo;}
    Sales_data& combine(const Sales_data&);

    private:

        double avg_price() const;
        std::string bookNo;
        unsigned units_sold = 0;
        double revenue =0.0;
};

#endif













