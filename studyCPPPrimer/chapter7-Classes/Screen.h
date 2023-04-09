#include<iostream>
#include<string>
#include "Window_mgr.h"

// extern std::ostream& storeOn(std::ostream & ,Screen &);
// extern BitMap& storeOn(Bitmap &, Screen &);
class Screen{

    friend std::ostream& storeOn(std::ostream & , Screen &);
    friend class Window_mgr;

    public:
        //类型别名
        typedef std::string::size_type pos;

        // using pos = std::string::size_type; //同等效果

        //构造函数
        Screen()=default;

        //函数重载

        Screen &set(char);
        Screen &set(pos, pos , char);



        Screen(pos ht, pos wd, char c):height(ht), width(wd),contents(ht * wd, c ){}

        inline
        Screen &move(pos r, pos c)
         {
            pos row= r* width;      //计算行的位置
            cursor=row +c;         // 将光标移动到该行中的列
            return *this;          //返回这个对象作为左值
        }

        char get(pos r,pos c) const
        {
            pos row =r * width;     //计算行的位置
            return contents[row + c]; //return character at the given 列
        }

        // inline char get(pos ht, pos wd) const;  //显式内联函数

        void some_member() const;

        Screen &display(std::ostream &os)
        {
            do_display(os);
            return *this;
        }
        const Screen &display(std::ostream &os) const
        {
            do_display(os);
            return *this;
        }
        
   

    private:
        pos cursor=0;
        pos height=0, width=0;
        std::string contents;

        //mutable，可变的，易变的。
        //是const的反义词，被它定义后可以永久处于可以改变的状态，是为了突破const的限制
        mutable size_t access_ctr;  

        //size_t用来存储长度
        

        //显示函数，将内容输出到显示上
        void do_display(std::ostream &os) const{
            os<<contents;
        }

    
};

//get的定义
inline Screen &Screen::set(char c)
{
    contents[cursor]=c;  //在当前光标位置设置新值
    return *this;        //返回这个对象作为一个左值
}
inline Screen &Screen::set(pos r, pos col, char ch)
{
    contents[r*width + col] =ch;  //设置一个指定位置给 给定值
    return *this;
}

void Screen::some_member() const
{
    ++access_ctr;
}

