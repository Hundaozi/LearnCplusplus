#include<linearList.h>
#include<iterator>

template<class T>
struct chainNode
{
    T element;
    chainNode<T> *next; //指向下一节点的指针

    //方法
    chainNode(){}
    chainNode(const T& element)
    {
        this->element=element;
    }
    chainNode(const T& element, chainNode<T>* next)
    {
        this->element=element;  //使用this来访问实例的数据成员
        this->next=next;
    }
};

template<class T>
class chain : public linearList<T>
{
    public:

        chain(int initialCapacity=0); //构造函数
        chain(const chain<T>&);  //复制构造函数
        ~chain();

        //抽象数据类型ADT方法
        bool empty() const { return listSize==0;}
        int size() const { return listSize;}
        //const加在后面，表示这个函数不会修改类中的任何数据成员
        //(仅为可读,不可写入)
        T& get(int theIndex) const;
        int indexOf(const T& theElement) const;
        void erase(int theIndex);
        void insert(int theIndex, const T& theElement);
        void output(std::ostream& out)const;

    protected:
        void checkIndex(int theIndex) const; //对索引的检查
        chainNode<T>* firstNode; //指向第一个节点的指针
        int listSize;     //链表的元素个数
};

template<class T>
chain<T>::chain(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        std::ostringstream s;
        s<< "初始容量为 "<<initialCapacity<<" 应该大于0";
        throw illegalParameterValue(s.str());
    }
    firstNode=nullptr; //头结点为空指针
    listSize=0;
};

template<class T>
chain<T>::chain(const chain<T>& theList)
{
    listSize=this->listSize;

    if(listSize==0)  //如果元素大小为0
    {
        firstNode=nullptr;
        return ;
    }

    chainNode<T>* sourceNode=theList.firstNode; //复制第一个节点为源节点

    firstNode = new chainNode<T>(sourceNode->element); //将元素分配给第一个节点

    sourceNode=sourceNode->next;  //往后移

    chainNode<T>* targetNode=firstNode; //将第一个节点分配给新的目标节点

    while(sourceNode !=nullptr)  //源节点不空的时候
    {
        targetNode->next=new chainNode<T>(sourceNode->element); 
        targetNode=targetNode->next; //指针后移
        sourceNode=sourceNode->next; //源节点后移
    }
    targetNode->next=nullptr; //链表结束
};

template<class T>
chain<T>::~chain()
{
    while(firstNode != nullptr) 
    {
        chainNode<T>* nextNode=firstNode->next;
        delete firstNode;   //释放空间
        firstNode= nextNode;
    }
}

template<class T>
T& chain<T>::get(int theIndex) const
{
    checkIndex(theIndex);

    //移动到所需要的节点
    chainNode<T>* currentNode=firstNode;
    for(int i=0; i<theIndex; i++)
        currentNode=currentNode->next;

    return currentNode->element;
}

template<class T>
int chain<T>::indexOf(const T& theElement) const
{
    chainNode<T>* currentNode=firstNode; 
    int index=0; //索引从0开始

    while(currentNode !=nullptr && currentNode->element != theElement)
    {
        currentNode=currentNode->next; //指针后移
        index++;
    }

    if(currentNode==nullptr)
        return -1;
    else    
        return index;  //返回元素对应的索引
}

template<class T>
void chain<T>::erase(int theIndex)
{
    checkIndex(theIndex);

    //索引有效，开始查找
    chainNode<T>* deleteNode;  //删除节点
    if(theIndex==0)
    {
        deleteNode=firstNode;
        firstNode=firstNode->next; //指针后移
    }

    else{
        chainNode<T>* p=firstNode; //p为要删除节点的前一个节点的指针
        for(int i=0; i< theIndex-1; i++)
            p=p->next; //指针后移
        deleteNode = p->next;
        p->next=p->next->next;
    }
    listSize--; //元素个数减一
    delete deleteNode;  //释放掉这一个节点的内存
};

template <class T>
void chain<T>::insert(int theIndex, const T& theElement)
{
    if(theIndex < 0 || theIndex >listSize)
    {
        std::ostringstream s;
        s<<"index = "<<theIndex<<" size = "<<listSize;
        throw illegalParameterValue(s.str());
    }

    if(theIndex==0) //如果从0开始，是初始位置
        firstNode= new chainNode<T>(theElement, firstNode);//new一个新的节点
    else{
        chainNode<T>* p=firstNode;
        for(int i =0; i< theIndex-1; i++)
            p=p->next;
        p->next=new chainNode<T>(theElement, p->next);
    }
    listSize++; //元素个数加一
};

template<class T>
void chain<T>::output(std::ostream& out) const
{
    for(chainNode<T>* currentNode=firstNode; currentNode!= nullptr; currentNode=currentNode->next)
        out<<currentNode->element<<" ";
}

//重载
template<class T>
std::ostream& operator<<(std::ostream& out, const chain<T>& x)
{
    x.output(out);
    return out;
};

