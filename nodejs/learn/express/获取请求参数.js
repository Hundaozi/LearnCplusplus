//导入express

const express=require('express');


const app=express();
const port = 9000
//获取请求的路由规则

app.get('/request',(req,res)=>{
    //1.获取报文的方式与原始http的方式是兼容的

    console.log('req.method:'+req.method);
    console.log('req.url:'+req.url);
    console.log('req.httpVersion:'+req.httpVersion);
    console.log('req.headers:'+req.headers);

    //2.express独有的获取报文的方式
    //获取路径
    console.log('req.path:'+req.path);
    //获取查询字符串
    console.log('req.query:'+req.query);

    //查询ip
    console.log('req.ip:'+req.ip);

    //获取指定的请求头
    console.log(req.get('host'));

    res.send('请求报文的获取');
});

//启动服务
app.listen(port,()=>{
    console.log('启动成功......')
})