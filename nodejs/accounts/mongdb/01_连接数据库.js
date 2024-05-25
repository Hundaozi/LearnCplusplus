const mongoose=require('mongoose');

//连接mongodb服务
mongoose.connect('mongodb://127.0.0.1/test');

//设置回调

mongoose.connection.on('open',()=>{
    console.log('连接成功');
});
mongoose.connection.on('error',()=>{
    console.log('连接失败');
});
mongoose.connection.on('close',()=>{
    console.log('连接关闭');
});