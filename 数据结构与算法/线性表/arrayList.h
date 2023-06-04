#include<linearList.h>
#include<iterator.h>

template<class T>
class arrayList : public linearList<T>
{
    public:
        
        arrayList(int initialCapacity=0); //构造函数
        arrayList(const arrayList<T>&);   //复制构造函数
        ~arrayList(){
            delete [] element; //删除数组，释放空间
        }
        //ADT方法
        bool empty() const{
            return listSize==0;
        }
        int size() {
            return listSize; //返回元素数量
        }
        T& get(int theIndex) const;   //通过索引获取元素
        int indexOf(const T& theElement) const;   //返回元素的索引
        void erase(int theIndex);    //通过索引删除元素
        void insert(int theIndex, const T& theElement);

    protected:
         void checkIndex(int theIndex) const; //如果索引无效，则抛出异常

         T* element; //存储线性表元素的一维数组
         int arrayLength;    //一维数组的容量
         int listSize;        //线性表的元素个数
};

//通过迭代器 复制
template<class iterator>
void copy(iterator start, iterator end, iterator to)
{
    while(start!=end)
    {
        *to=*start;  //将开始元素分配给目的地
        start++;
        to++;
    }
}

//构造函数的实现
template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        std::ostringstream s;     //字符串输出流
        s << "初始化装填容量 " <<initialCapacity<< " 必须大于0";
        throw illegalParameterValue(s.str());
    }

    arrayList=initialCapacity;
    element=new T[arrayLength];    //new一个容量为arrayLength的数组
    listSize=0;        //初始元素个数为0

}

//复制构造函数
template<class T>
arrayList<T>::arrayList(const arrayList<T> & theList)
{
    arrayLength=theList.arrayLength;
    listSize=theList.listSize;
    element=new T[arrayLength];     //拷贝构造一个新的数组

    copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{
    //确定索引在0和listSize -1 之间
    if(theIndex < 0 || theIndex >=listSize)
    {
        std::ostringstream s;
        s << "index = "<<theIndex << " size "<<listSize;
        throw illegalParameterValue(s.str());
    }
}

template<class T>
T& arrayList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return element[theIndex]; //返回索引所对应的元素
};

template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{
    //查找元素
    int theIndex=(int)(find(element, element + listSize, theElement) - element );

    if(theIndex==listSize) 
        return -1;   //没有找到
    else
        return theIndex;
};

template <class T>
void arrayList<T>::erase(int theIndex)
{
    checkIndex(theIndex); //检查是否存在这个索引

    copy(element + theIndex +1 , element + listSize, element+ theIndex);

    element[--listSize].~T();  //调用析构函数
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
    if(theIndex <0 || theIndex >listSize)
    {
        std::ostringstream s;
        s<<" index = "<<theIndex <<" size = "<<listSize;
        throw illegalParameterValue(s.str());
    }

    //确定数组是否已满
    if(listSize== arrayList)
    {   
        // void changeLength1D(T*& a,int oldLength, int newLength)
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *=2; //容量扩大为两倍
    }

    //将元素往右边移动一个位置
    copy_backward(element + theIndex, element+ listSize, element + listSize +1);

    element[theIndex]= theElement;
    listSize++; //元素个数增加一个
}

