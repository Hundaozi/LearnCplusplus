#ifndef SIZECOMP_H
#define SIZECOMP_H
#include<string>

class SizeComp{

    public:
        SizeComp(size_t n): sz(n){}

        bool operator()(const std::string &s) const{
            return s.size() >= sz;
        }
    private:
        size_t sz;
};


#endif