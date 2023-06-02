#include<iostream>
#include<string>


class Screen{
    public:
        typedef std::string::size_type pos; //类别名定义

        char get_cursor() const{
            return contents[cursor]; //返回内容的光标
        }

        char get()const;

        char get(pos ht, pos wd) const; //获取位置

        static const std::string Screen::*data();//data是一个静态成员，它返回一个指向成员的指针


        //定义一些公有函数
        Screen& home();
        Screen& forward();
        Screen& back();
        Screen& up();
        Screen& down();

        using Action = Screen& (Screen::*)();//action是一个别名
        
        enum Directions {
            HOME,
            FORWARD,
            BACK,
            UP,
            DOWN
        };//枚举

        Screen& move(Directions);

        

    private:

        std::string contents;
        pos cursor;
        pos height, width;  //高度和宽度

        static Action Menu[]; //私有静态成员
};

Screen& Screen::move(Directions cm)
{
    return (this->*Menu[cm])();   //Menu[cm]指向一个成员函数
}

