#ifndef MESSAGE_H
#define MESSAGE_H


#include<string>
#include<set>

class Message{

    friend class Folder;        //将文件夹类定义为友元函数

    public:

        explicit Message(const std::string &str = ""):contents(str) {}

        Message(const Message&);       //copy 构造函数
        Message& operator=(const Message&);      //copy 分配函数
        ~Message();

        void save(Folder&);
        void remove(Folder&);

    private:

        std::string contents; //存储内容

        std::set<Folder*> folders; //存储Message里出现的指针

        void add_to_Folders(const Message&) ;  //添加到文件夹

        void remove_from_Folders();           //从文件夹删除

    void Message::save(Folder &f)
    {   
        folders.insert(&f);     //保存指针
        f.addMsg(this);        //addMsg是Folfer类里的方法
    }
    void Message::remove(Folder &f)
    {
        folders.erase(&f);       //移除指针
        f.remMsg(this);
    }

    void Message::add_to_Folders(const Message &m)
    {
        for(auto f : m.folders)
            f->addMsg(this); //add a pointer to this Message to that Folder
    }

    void Message::remove_from_Folders()
    {
        for(auto f : folders)
            f->remMsg(this);      //从文件夹中江这个Message 移除
    }

    //交换函数

    void swap(Message& lhs, Message& rhs)
    {
        using std::swap;

        for(auto f : lhs.folders)
            f->remMsg(&lhs);
        
        for(auto f : rhs.folders)
            f->remMsg(&rhs);

        swap(lhs.folders, rhs.folders);
        swap(lhs.contents, rhs.contents);

        for(auto f : lhs.folders)
            f->addMsg(&lhs);
        
        for(auto f : rhs.folders)
            f->addMsg(&rhs);
    }

};

//实现
Message::Message(const Message&m):
    contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);
}

Message::~Message()
{
    remove_from_Folders();
}

Message& Message::operator=(const Message &rhs)
{
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);
    return *this;
}


class Folder{

    friend class Message;
    friend void swap(Message&, Message&);

    public:
        Folder(const Folder&);
        ~Folder();

        Folder & operator=(const Folder &);

        Folder() { }

        void save(Message&);
        void remove(Message&);

        void debug_print();


    private:

        std::set<Message*> msgs; //存储指针

        void add_to_Message(const Folder&);
        void remove_from_Msgs();
        void addMsg(Message *m) { msgs.insert(m);}
        void remMsg(Message *m) { msgs.erase(m);}


};




#endif