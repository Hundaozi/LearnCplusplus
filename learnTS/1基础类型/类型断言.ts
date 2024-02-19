let someValue:any= "这是一条字符串";

let strLength:number =(<string>someValue).length;


//as语法

let strLength2:number=(someValue as string).length;

//let 用来代替var