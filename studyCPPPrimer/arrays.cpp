#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    // int ia[]={0,1,2,3,4,5,6,7,8,9};
    // int *beg=begin(ia);
    // int *last=end(ia);

    // cout<<beg<<endl;   //输出地址
    // cout<<last<<endl;  //输出地址

    // cout<<*beg<<endl;   //输出值
    // cout<<*last<<endl;  //输出值

    // int arr[]={0,1,2,3,4,5,6,7,8,9};

    // int *pbeg = begin(arr), *pend=end(arr);

    // while(pbeg != pend && *pbeg>=0)
    //     ++pbeg;
    // cout<<pbeg<<endl;
    // cout<<pend<<endl;

    // cout<<*pbeg<<endl;
    // cout<<*pend<<endl;

    constexpr size_t sz=5;
    int arr[sz]={1,2,3,4,5};
    int *ip=arr;   //等于int *ip=&arr[0]
    int *ip2=ip+4;

    // cout<<*ip<<endl;
    // cout<<*ip2<<endl;
    // cout<<ip<<endl;
    // cout<<ip2<<endl;

    auto n=end(arr)-begin(arr);
    cout<<n<<endl;    //n的结果是5，是arr中项的个数
    return 0;
}