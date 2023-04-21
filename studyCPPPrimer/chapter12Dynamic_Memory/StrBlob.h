#ifndef STRBLOB_H
#define STRBLOB_H
#include<vector>
#include<memory>
#include<string>

class StrBlob{
    public:
        //自定义类型
        typedef std::vector<std::vector<std::string>>::size_type size_type;
        //构造函数
        StrBlob();

        StrBlob(std::initializer_list<std::string> il);

        //数据的大小
        size_type size() const {return data->size();};
        //判断是否为空
        bool empty() const { return data->empty();};

        //数据向后压入
        void push_back(const std::string &t){ data->push_back(t);};

        //
        void pop_back();

        std::string& front();
        std::string& back();

    private:
    //智能指针 data
        std::shared_ptr<std::vector<std::string>> data;
    //检查函数
        void check(size_type i, const std::string &msg) const;

    
    void StrBlob::check(size_type i, const std::string &msg) const
    {
        if(i>=data->size())
            throw out_of_range(msg);
    }

    std::string& StrBlob::front()
    {
        check(0,"front on empty StrBlob");
        return data->front();
    }

    std::string& StrBlob::back()
    {
        check(0,"back on empty StrBlob");
        return data->back();
    }

    

};



#endif