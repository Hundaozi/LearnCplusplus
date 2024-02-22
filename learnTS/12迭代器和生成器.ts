//学过C++都会熟悉的概念，用于自动遍历

/*
当一个对象实现了Symbol.iterator属性时，我们认为它是可迭代的。
 一些内置的类型如 Array，Map，Set，String，Int32Array，Uint32Array等都已经实现了各自的Symbol.iterator。 
 对象上的 Symbol.iterator函数负责返回供迭代的值。
*/

//for..of会遍历可迭代的对象，调用对象上的Symbol.iterator方法。

// let someArray=[1,"hello",true];
// for(let e of someArray){
//     console.log(e);
// }
// //就是范围遍历

/*
for..of和for..in均可迭代一个列表；但是用于迭代的值却不同，
for..in迭代的是对象的 键 的列表，而for..of则迭代对象的键对应的值。
*/
//哦哦，一个输出键，一个输出值

// let list =[10,23,31,44,15];
// for(let i in list){
//     console.log(i);//输出0,1,2,3,4
// }
// for(let i of list){
//     console.log(i);//输出数组里的值
// }

//另一个区别是for..in可以操作任何对象；它提供了查看对象属性的一种方法。
// 但是 for..of关注于迭代对象的值。
//嗯。。。用索引当然可以操作对象了。。
// let pets = new Set(["Cat", "Dog", "Hamster"]);
// pets["species"] = "mammals";

// for (let pet in pets) {
//     console.log(pet); // "species"
//     //报错，因为没有species这个索引
// }

// for (let pet of pets) {
//     console.log(pet); // "Cat", "Dog", "Hamster"
// }