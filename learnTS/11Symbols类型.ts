//自ECMAScript 2015起，symbol成为了一种新的原生类型，就像number和string一样。
//  let sym1=Symbol();
//  let sym2 = Symbol("key"); // 可选的字符串key
//  //Symbols是不可改变且唯一的。

// let sym3 = Symbol("key");

// console.log(sym2 === sym3); // false, symbols是唯一的

//像字符串一样，symbols也可以被用做对象属性的键。

// let sym=Symbol();

// let obj={
//     [sym]:"value"
// };
// console.log(obj[sym]);

// //哦，键就是名字的意思。键值对那个键..

//Symbols也可以与计算出的属性名声明相结合来声明对象的属性和类成员。

const getClassNameSymbol=Symbol();

class C{
    [getClassNameSymbol](){
        return "C";
    }
}

let c=new C();//创建一个实例
let className=c[getClassNameSymbol]();
//有点多此一举的感觉，可能我还没有领悟其妙用


//哦哦，懂了符号类型用作符号，就是个符号而已。又是一个节省代码量的语法糖