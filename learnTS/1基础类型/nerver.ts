//never 表示任何类型的子类型
//never类型表示的是那些永不存在的值的类型

function error(message:string):never{
    throw new Error(message);
}

function fail(){
    return error("一些错误");

}
infiniteLoop();
// fail();

function infiniteLoop(): never{
    while(true){
        console.log("一条无用的信息");
    }
}
