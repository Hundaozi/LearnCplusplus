//中间件的本质就是回调函数

const express=require('express');
const fs=require('fs');
const path = require('path');
const app=express();
const port=9000;


//声明全局中间件函数
function recordMiddleware(req,res,next) {
    //获取ulr和ip
    let {url,ip}=req;//解构赋值
    console.log(url,ip);
    //将信息保存在文件中
    fs.appendFileSync(path.resolve(__dirname,'./access.log'),`${url} ${ip}\r\n`);

    next();
}

//使用中间件
app.use(recordMiddleware);

app.get('/home',(req,res)=>{

    res.send('前台首页');
});
app.get('/other',(req,res)=>{
    //跳转响应
    res.redirect('http://127.0.0.1');
})


app.get('/admin',(req,res)=>{
    res.send('后台首页');
});

app.all('*',(req,res)=>{
    res.send('<h1>404</h1>');
});

app.listen(port,()=>{
    console.log('服务已经启动......');
})