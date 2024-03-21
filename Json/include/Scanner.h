#pragma once
#include <iostream>
#include <string>

namespace hundaozi
{
    namespace json
    {
        // 扫描器
        class Scanner
        {
        public:
            Scanner(const std::string &source) : source_(source), current_(0) {}
            // 要移动就不能const了
            Scanner(std::string &&source) : source_(std::move(source)), current_(0) {}

            // Token类型
            enum class JsonTokenType
            {
                // [
                BEGIN_ARRAY = 0;
                // ]
                END_ARRAY,
                // {
                BEGIN_OBJECT,
                // }
                END_OBJECT,

                // : 名字分隔符
                NAME_SEPARATOR,
                // , 值分隔符
                VALUE_SEPARATOR,

                // number
                VALUE_NUMBER,
                // string
                VALUE_STRING,

                // true
                LITERAL_TRUE,
                // false
                LITERAL_FALSE,

                // null
                LITERAL_NULL,

                // end of source
                END_OF_SOURCE,

                // 错误
                ERROR
            }

        private:
        }
    }
}