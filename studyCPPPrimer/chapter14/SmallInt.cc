#include<iostream>

//定义一个有转换操作符的类
class SmallInt{
    public:

        SmallInt(int i = 0):val(i)
        {
            if(i < 0|| i>255)
                throw std::out_of_range("Bad SmallInt value");
        }
        // explicit operator int() const {return val;}
        operator int() const {return val;}

    private:
        std::size_t val;
};

int main()
{

    SmallInt si;
    // si=4;
    // si+3;
    return 0;
}