//类arrayList的一个迭代器

#include<iterator>
template<class T>
class iterator
{
    public:
        //用C++的typedef语句实现双向迭代器
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T* pointer;   //代表指针
        typedef T& reference; //代表引用

        //构造函数
        iterator(T* thePosition-0 ){ position=thePosition; }

        //解引用操作符
        T& operator*()const { return *position ;}
        T* operator->() const { return &*position ;}

        //迭代器的值增加

        //前加
        iterator& operator++()
        {
            ++position;
            return *this;
        }
        //后加
        iterator operator++(int)
        {
            iterator old = *this;
            ++position;
            return old;
        }

        //迭代器的值减少
        iterator& operator--()
        {
            --position;
            return *this;
        }
        //后加
        iterator operator--(int)
        {
            iterator old = *this;
            --position;
            return old;
        }
        
        bool operator!=(const iterator right) const
        {
            return position != right.position;
        }

        bool operator==(const iterator right) const
        {
            return position == right.position;
        }
    

    protected:
        T* position;

};