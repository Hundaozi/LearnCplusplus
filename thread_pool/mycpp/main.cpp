#include<iostream>
#include<random>

#include "../myinclude/thread_pool.h"

//用于生成随机数
std::random_device rd;

//std::mt19937是C++标准库中的一个伪随机数生成器类，它实现了梅森旋转算法（Mersenne Twister）。
//mt19937类是一个随机数引擎，可以生成高质量的伪随机数序列。
//返回值是unsigned int。
std::mt19937 mt(rd());

//随机生成一个整数，均匀分布。
std::uniform_int_distribution<int> dist(-1000, 1000);
//使用rnd时候，rnd会调用dist，并传递给mt中的参数，即rd
auto rnd = std::bind(dist, mt);

//模拟一个复杂计算
void simulateHardCompute(){
    //沉睡一个时间，时间=2000毫秒+rnd随机生成的数
    std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

//相乘，并打印
void multiply(const int a, const int b) {
  simulateHardCompute();
  const int res = a * b;
  std::cout << a << " * " << b << " = " << res << std::endl;
}

//输出乘积的结果
void multiply_output(int & out, const int a, const int b) {
  simulateHardCompute();
  out = a * b;
  std::cout << a << " * " << b << " = " << out << std::endl;
}
//返回乘积结果
int multiply_return(const int a, const int b) {
  simulateHardCompute();
  const int res = a * b;
  std::cout << a << " * " << b << " = " << res << std::endl;
  return res;
}

int main(int argc, char *argv[]){
    //实例化一个线程池对象
    thread_pool pool(3);

    pool.init();//初始化线程池

    //在线程池中提交任务函数
    for (int i = 1; i < 3; ++i) {
        for (int j = 1; j < 10; ++j) {
        pool.submit(multiply, i, j);
        }
    }

    //提交具有ref传递的输出参数的函数
    int output_ref;
    auto future1 = pool.submit(multiply_output, std::ref(output_ref), 5, 6);

    //等待乘法输出完成
    future1.get();
    std::cout << "最后一个 运算结果为： " << output_ref << std::endl;

    //提交带返回参数的任务函数
    auto future2 = pool.submit(multiply_return, 5, 3);

    // 等待计算结果
    int res = future2.get();
    std::cout << "上一次 的运算结果为： " << res << std::endl;

    pool.shutdown();

    return 0;
}

