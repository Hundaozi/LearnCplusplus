#include<iostream>
#include<string>
using namespace std;

//数组的操作和指针的交互

int main(){
    // int ia[]={0,2,3,6,8};
    // int last=*(ia +4 ); //等于ia[4]
    // cout<<last<<endl;
    // cout<<&last<<endl;

    // int new_last=*ia+4; //第一个值加4
    // cout<<new_last<<endl;
    // cout<<&new_last<<endl;

    // int ia[]={0,2,4,6,8};

    // int i=ia[2];    //i的值为4
    // cout<<i<<endl;

    // int *p=ia;      //获取ia的地址
    // cout<<*p<<endl;
    // cout<<p<<endl;

    int ia[]={0,2,4,6,8};

    int *p=&ia[2];     //指针指向第三个值
    cout<<p<<endl;    //获取第三个值的地址
    cout<<*p<<endl;

    int j=p[1];     //等于*(p + 1)
                    //p[1]等于 ia[3]
    cout<<j<<endl;
   

    return 0;
}