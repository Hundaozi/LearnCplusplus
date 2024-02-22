// function identity<T>(arg:T):T{
//     return arg;
// }
// //泛型
// //方法一
// let output1=identity<string>("string");
// //方法二
// let output2=identity("string_2");//自动类型推导

// //直接输出类型的长度可能会错误
// function loggingIdentity<T>(arg:T):T{
//     console.log(arg.length);//T类型没有长度
//     return arg;
// }

// function loggingIdentity<T>(arg: T[]): T[] {
//     console.log(arg.length);  // Array has a .length, so no more error
//     return arg;
// }
// //数组当然有长度

//泛型函数的类型与非泛型函数的类型没什么不同，
//只是有一个类型参数在最前面，像函数声明一样
// function identity<T>(arg:T):T{
//     return arg;
// }

// // let myIdentity:<T>(arg:T) =>T =identity;\
// interface GenericIdentityFn{
//     <T>(arg: T):T;
// }
// let myIdentity:GenericIdentityFn=identity;

// //

// //泛型类
// class GenericNumber<T>{
//     zeroValue:T;
//     add:(x:T,y:T)=>T;//add函数，参数都是T类型，函数的返回值也是T类型
// }
// let myGenericNumber = new GenericNumber<number>();

// let stringNumeric = new GenericNumber<string>();
// stringNumeric.zeroValue = "";
// stringNumeric.add = function(x, y) { return x + y; };

// console.log(stringNumeric.add(stringNumeric.zeroValue, "test"));

//在TypeScript使用泛型创建工厂函数时，需要引用构造函数的类类型。
function create<T>(c:{
    new():T;}):T{
        return new c();//奇怪的写法
}
//原来如此，参数的构造函数也要指定类型