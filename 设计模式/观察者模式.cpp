#include <iostream>
#include <list>

struct Observer;
struct Subject {
  std::list<Observer *> observerList;     // 保存被观察的对象
  virtual void attach(Observer *obj) = 0; // 加入对象
  virtual void detach(Observer *obj) = 0; // 删除对象
  virtual void notify() = 0;              // 通知列表中的所有对象
}; // Subject类是观察者对象的接口

class Stock : public Subject {
private:
  int price = 0; // 股票价格
public:
  int getPrice();                   // 获取股票价格
  void setPrice(int p);                     // 设置股票价格
  void attach(Observer *obj) override; // 重写方法
  void detach(Observer *obj) override; // 重写方法
  void notify() override;              // 重写通知方法
};

struct Observer {
  Subject *sub; // 指向其抽象接口类
  explicit Observer(Subject *sub);
  virtual ~Observer();
  virtual void update() = 0; // 更新观察者列表
};

struct Monitor : Observer {
  explicit Monitor(Subject *sub) : Observer(sub) {}
  void print(double p) const {
    std::cout << "Monitor: " << p << '\n';
  } // 打印价格
  void update() override { print(static_cast<Stock *>(sub)->getPrice()); }
};

struct Billboard : Observer {
  explicit Billboard(Stock *stock) : Observer(stock) {}
  void display(double p) const { std::cout << "Billboard: " << p << '\n'; }
  void update() override { display(static_cast<Stock *>(sub)->getPrice()); }
};

int Stock::getPrice(void) { return price; }

void Stock::setPrice(int p) {
  price = p;
  notify(); // 通知所有对象
}
void Stock::attach(Observer *obj) { observerList.push_back(obj); }
void Stock::detach(Observer *obj) { observerList.remove(obj); }
void Stock::notify() {
  for (auto observer : observerList) {
    observer->update();
  }
}
Observer::Observer(Subject *sub) : sub(sub) { sub->attach(this); }

Observer::~Observer() { sub->detach(this); }
int main() {
  Stock stock;
  Monitor monitor{&stock};
  Billboard board{&stock};
  stock.setPrice(3);
}
