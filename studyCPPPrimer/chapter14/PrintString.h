#ifndef PRINTSTRING_H
#define PRINTSTRING_H

#include<string>
#include<iostream>


class PrintString{
    public:
    PrintString(std::ostream &o=std::cout, char c=' '):
        os(o), sep(c) {}

    void operator() (const std::string &s) const {os<<s<<sep;}

    private:
        std::ostream &os;
        char sep;
};







#endif PRINTSTRING_H