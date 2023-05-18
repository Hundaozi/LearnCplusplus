#include<vector>
#include<memory>
#include"Blob.h"
template<typename T> 
class BlobPtr
{
    public:
        BlobPtr(): curr(0) { }

        BlobPtr(Blob<T> &a, size_t sz=0 ): wptr(a.data), curr(sz) { }

        T& operator*() const
        {
            auto p = check(curr, "dereference past end");
            return (*p)[curr];
        }
        //自增和自减重载
        BlobPtr& operator++();
        BlobPtr& operator--();

    private:

        std::shared_ptr<std::vector<T>> check(std::size_t const std::string &) const;

        std::weak_ptr<std::vector<T>> wptr;
        std::size_t curr;
};