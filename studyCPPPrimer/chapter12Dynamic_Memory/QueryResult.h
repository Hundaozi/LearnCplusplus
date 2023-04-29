#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include <string>
#include <vector>
#include <set>
#include <iostream>


class QueryResult{

    typedef std::vector<std::string>::size_type line_no;
    friend std::ostream& print(std::ostream&, const QueryResult&);
    public:
        QueryResult(std::string s,
                    std::shared_ptr<std::set<line_no>> p,
                    std::shared_ptr<std::vector<std::string>> f):
                    sought(s), lines(p), file(f){}

    private:
        std::string sought;

        std::shared_ptr<std::set<line_no>> lines;

        std::shared_ptr<std::vector<std::string>> file;


};


#endif