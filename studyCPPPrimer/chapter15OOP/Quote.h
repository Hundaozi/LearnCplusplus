#include<string>
//基类
class Quote{
    public:

        Quote() =default;
        Quote(const std::string &book, double sales_price):bookNo(book),price(){ }

        std::string isbn() const {return bookNo;};

        virtual double net_price(std::size_t n) const{ return n * price;}

        virtual ~Quote()=default;
    
    private:
        std::string bookNo;
    protected:
        double price=0.0;
};

//派生类
class Bulk_quote : public Quote{
    public:
        Bulk_quote()=default;
        Bulk_quote(const std::string &book, double p,std::size_t qty, double disc):
                                        Quote(book, p), min_qty(qty), discount(disc) { }


        double net_price(std::size_t) const override;

    private:
        std::size_t min_qty=0;
        double discount=0.0;
    //这个函数生成折扣价格
    double Bulk_quote::net_price(std::size_t cnt)const
    {
        if(cnt >= min_qty)
            return cnt * (1 - discount) * price;
        else
            return cnt * price;
    }
};

class Disc_quote: public Quote{
    public:

        Disc_quote()=default; //默认构造函数

        Disc_quote(const std::string& book, double price, std::size_t qty, double disc):
                                    Quote(book, price), quantity(qty), discount(disc){}


    private:

        std::size_t quantity=0;

        double discount=0.0;
};
