#include<iostream>
#include<string>
//线性表的抽象类
template<class T>
class linerList
{
    public:

        virtual ~linerList() {}; //析构函数

        virtual bool empty() const=0; //返回true， 当且仅当线性表为空

        virtual int size() const=0;   //返回线性表的元素个数

        virtual T& get(int theIndex) const=0; //返回索引为theIndex的元素

        virtual int indexOf(const T& theElement) const=0; //返回这个元素第一次出现时候的索引

        virtual void erase(int theIndex) const=0; //删除元素

        virtual void insert(int theIndex, const T& theElement) =0; //将元素插在指定的索引位置上

        virtual void output(std::ostream& out ) const=0; //把线性表插入输出流out
};

//变长一维数组
template<class T>
void changeLength1D(T*& a,int oldLength, int newLength)
{
    if(newLength<0)
        throw illegalParameterValue("新的长度必须大于等于0");
    
    T* temp=new T[newLength]; //new一个新的长度数组

    int number=min(oldLength,newLength);//需要复制的元素的个数

    copy(a, a+ number, temp);
    delete []a;         //释放老数组的内存空间
    a=temp;
};

class illegalParameterValue
{
    public:
        illegalParameterValue():message("Illegal parameter value"){}

        illegalParameterValue(char* theMessage)
        {
            message=theMessage;
        }
        void outputMessage()
        {
            std::cout<<message<<std::endl;
        }
    private:
        std::string message;
};