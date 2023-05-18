#include<vector>
#include<memory>
#include<string>
#include<list>

template <typename T> class Blob{
    public:

        typedef T value_type;
        typedef typename std::vector<T>::size_type size_type;

        Blob();
        Blob(std::initializer_list<T> il);

        size_type size() const { return data->size(); }
        bool empty() const { return data->empty(); }

        void push_back(const T &t) { data->push_back(t);}

        void push_back(T &&t) { data->push_back(std::move(t));}

        void pop_back();

        T& back();
        T& operator[] (size_type i);

    private:

        std::shared_ptr<std::vector<T>> data; //智能指针

        void check(size_type i, const std::string &msg) const;
};

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if(i>=data->size())//如果超过最大容量，则丢出一个错误
        throw std::out_of_range(msg);
}