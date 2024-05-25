const mongoose=require('mongoose');

//设置strictQuery 为 true
mongoose.set('strictQuery',true);

//连接mongodb服务
mongoose.connect('mongodb://127.0.0.1/test');




//设置回调

//官方建议用once，不建议使用on
//once ,回调函数只执行一次/ 
mongoose.connection.once('open',()=>{
    console.log('连接成功');
});
mongoose.connection.once('error',()=>{
    console.log('连接失败');
});
mongoose.connection.once('close',()=>{
    console.log('连接关闭');
});