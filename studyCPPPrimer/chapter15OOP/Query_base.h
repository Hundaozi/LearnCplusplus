#include<string>
#include "TextQuery.h"

class Query_base{
    friend class Query;

    protected:

        using line_no = TextQuery::line_no;
        virtual ~Query_base() = default; //默认析构函数

    private:

        virtual QueryResult eval(const TextQuery &) const =0;
        virtual std::string rep()cosnt = 0;
};