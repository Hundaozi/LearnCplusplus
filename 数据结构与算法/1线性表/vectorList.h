#include<linearList.h>
#include<vector>

template<class T>
class vectorList :public linearList<T>
{
    public:
        vectorList(int initialCapacity=10); //构造函数
        vectorList(const vectorList<T>&);   //拷贝构造函数
        ~vectorList(){ delete element;}

        //ADT方法

        bool empty() const{ return element->empty();} //判断容器是否为空
        int size() const { return (int) element->size();}  //获取容器的元素个数
        T& get(int theIndex) const;  //通过索引取得元素
        int indexOf(const T& theElement) const;  //查找元素的索引
        void erase(int theIndex);          //通过索引删除容器里的元素
        void insert(int theIndex, const T& theEmelent);  //在指定索引位置插入元素
        void output(std::ostream& out) const;   //将容器里的元素打印到输出流

        //增加容器的方法
        int capacity() cosnt { return (int) element->capacity();}

        //线性表的起始和结束为止的迭代器
        typedef typename std::vector<T>::iterator iterator;
        iterator begin() { return element->begin(); }
        iterator end() { return element->end(); }


    protected:
        void checkIndex(int theIndex) const;
        std::vector<T>* element;
};

template<class T>
vectorList<T>::vectorList(int initialCapacity)
{
    //构造函数
    if (initialCapacity < 1  )
    {
        std::ostringstream s;
        s<<"初始的容量为 :" <<initialCapacity<<" 应该大于0";
        throw illegalParameterValue(s.str());
    }

    element= new std::vector<T>; //创建容量为0的空容器

    element->reserve(initialCapacity);//将容器的容量从0增加到设定初始容量

};

//拷贝构造函数
template<class T>
vectorList<T>::vectorList(const vectorList<T>& theList)
{
    element= new std::vector<T>(*theList.element);
};

template<class T>
void vectorList<T>::erase(int theIndex)
{
    checkIndex(theIndex);

    element->erase(begin() + theIndex); 
}

template<class T>
void vectorList<T>::insert(int theIndex, const T& theElement)
{
    if( theIndex <0 || theIndex>size())
    {
        std::ostringstream s;
        s<<"index = "<<theIndex<<" size = "<<size();
        throw illegalParameterValue(s.str());
    
    }

    element->insert(element->begin() + theIndex, theElement); //在索引位置插入元素
};