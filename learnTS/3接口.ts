// function printLable(
//     labeObject:{ 
//         label: string
//     }){
//     console.log(labeObject.label);
// }
// let myObj = { size: 10, label: "Size 10 Object" };
// printLable(myObj);

// /**
//  * 需要注意的是，
//  * 我们传入的对象参数实际上会包含很多属性，
//  * 但是编译器只会检查那些必需的属性是否存在，
//  * 并且其类型是否匹配。
//  */

// interface labelledValue{
//     label:string;
// }//定义一个接口
// function printLable(
//     labeObject: labelledValue
// ){
//     console.log(labeObject.label)
// }

// let obj1={
//     size:10,
//     label: "Size 10 of Object"
// }
// printLable(obj1);

//可选属性，加？号即可

// interface SquareConfig{
//     color?: string;
//     width?: number;
// }
// function create(config:SquareConfig):{color: string; area: number}{
//     let newSquare={
//         color: "white",
//         area:100
//     };
//     if(config.color){
//         newSquare.color=config.color;
//     }
//     if(config.width){
//         newSquare.area=config.width * config.width;
//     }

//     return newSquare;//将对象返回
// }

// let myObj=create({
//     color:"black"
// });

// //只读属性，前面加readonly

// interface Point{
//     readonly x:number;
//     readonly y:number;
// }
// let p1:Point={ x:10,y:20}
// console.log(p1);
// // p1.x=5;// error

//TypeScript具有ReadonlyArray<T>类型，
//它与Array<T>相似，只是把所有可变方法去掉了，
//因此可以确保数组创建后再也不能被修改：

// let a1:number[]=[1,2,3,4,5]
// let ro:ReadonlyArray<number>=a1;
// // ro[0]=12;//error
// // ro.length=100;//error
// //重新变成number
// a1=ro as number[];
// console.log(a1);
// a1[2]=10;
// console.log(a1);
// //做为变量使用的话用 const，若做为属性则使用readonly。

//为了使用接口表示函数类型，我们需要给接口定义一个调用签名。 
//它就像是一个只有参数列表和返回值类型的函数定义。
//参数列表里的每个参数都需要名字和类型。

// interface SearchFunc{
//     (source:string, subString:string):boolean
// }
// //这样定义后，我们可以像使用其它接口一样使用这个函数类型的接口。 
// let mySearch: SearchFunc;
// mySearch = function(src, sub) {
//     let result = src.search(sub);
//     return result > -1;
// }
// console.log(mySearch);

//类类型
//实现接口

// interface ClockInterface {
//     currentTime: Date;
//     setTime(d: Date);
// }

// class Clock implements ClockInterface {
//     currentTime: Date;
//     setTime(d: Date) {
//         this.currentTime = d;
//     }
//     constructor(h: number, m: number) { }
// }

//继承接口

// interface Shape{
//     color: string;
// }
// interface Square extends Shape{
//     sideLength: number;
// }
// let square=<Square>{};
// console.log(square);
// square.color="blue";
// square.sideLength=10;
// console.log(square);

interface Shape {
    color: string;
}

interface PenStroke {
    penWidth: number;
}

interface Square extends Shape, PenStroke {
    sideLength: number;
}

let square = <Square>{};
console.log(square);
square.color = "blue";
square.sideLength = 10;
square.penWidth = 5.0;
console.log(square);