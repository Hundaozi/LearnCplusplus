#ifndef QUOTE_H
#define QUOTE_H

#include <memory>
#include <iostream>
#include <string>
#include <cstddef>
#include <set>
//基类
class Quote{
    public:

        Quote() =default;
        Quote(const std::string &book, double sales_price):bookNo(book),price(){ }

        std::string isbn() const {return bookNo;};

        virtual double net_price(std::size_t n) const{ return n * price;}

        virtual ~Quote()=default;

        virtual Quote* clone() const &{ return new Quote(*this);}

        virtual Quote* clone() && { return new Quote(std::move(*this));}
    
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

        Bulk_quote* clone() const & { return new Bulk_quote(*this); } //左值
        Bulk_quote* clone() &&
                    {
                        return new Bulk_quote(std::move(*this));//右值引用
                    }

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

class Basket{
    public:
        //使用智能指针添加项
        void add_item(const std::shared_ptr<Quote> &sale){
            items.insert(sale);
        }

        double total_receipt(std::ostream&) const;

        void add_item(const Quote& sale){
            items.insert(std::shared_ptr<Quote>(sale.clone()));
        }

        void add_item(Quote&& sale){
            items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
        }

    private:

        static bool compare(const std::shared_ptr<Quote> &lhs,
                            const std::shared_ptr<Quote> &rhs){
                                return lhs->isbn() < rhs->isbn();
                            }

        std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};

    double Basket::total_receipt(std::ostream &os)const
    {
        double sum=0.0;

        for(auto iter = items.cbegin();
                 iter != items.cend();
                 iter = items.upper_bound(*iter))
                 {
                    sum += print_total(os, **iter, items.count(*iter));
                 }
        os << "Total Sale: "<< sum <<std::endl;
        return sum;
    }
};

#endif