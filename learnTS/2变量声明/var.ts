//通过var关键字定义JavaScript变量。
// var a = 10;


// function f() {
//     var message = "Hello, world!";

//     return message;
// }

//当用let声明一个变量，
//它使用的是词法作用域或块作用域。
// 不同于使用 var声明的变量那样可以在包含它们的函数外访问，
//块作用域变量在包含它们的块或for循环之外是不能访问的。

// let hello = "Hello!";
// console.log(hello);
// function f1(input:boolean){
//     let a=100;
//     if(input){
//         let b=a+1;
//         return b;
//     }

//     //return b;超出了b的作用域
// }

// function f2(condition:boolean,x:number){
//     if(condition){
//         let x=100;
//         return x;
//     }
//     return x;
// }
// f2(true,0);

// function theCityThatAlwaysSleeps() {
//     let getCity;

//     if (true) {
//         let city = "Seattle";
//         getCity = function() {
//             return city;
//         }
//     }

//     return getCity();
// }
// theCityThatAlwaysSleeps();

// for(let i=0;i<10;++i){
//     setTimeout(function() {
//         console.log(i); },
//          100 * i);
    
// }

// const numLivesForCat=9;
// const kitty={
//     name:"狸花猫",
//     numLives:numLivesForCat,
// }

// kitty.name="四川简州猫";

//类型匹配
// function f([first,second]:[number,number]){
//     console.log(first);
//     console.log(second);
// }

// f([111,222])

let o={
    a:"hahah",
    b:12,
    c:"cccc"
};
console.log(o);
let {a,b}=o;
console.log({a,b});

