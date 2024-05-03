const express=require('express');

const app=express();
const port=9000;

app.get('/',(req,res)=>{
    req.end('重定向成功');
});


app.get('/home',(req,res)=>{
    // //原生响应
    // res.statusCode=404;
    // res.statusMessage='404 message';
    // res.setHeader('xxx','yyy');
    // res.write('res.write\n');

    //express响应
    res.status(500);
    res.set('aaa','bbb');
    res.send('hello gagagagag\n');

    


    res.end('hello express');
});
app.get('/other',(req,res)=>{
    //跳转响应
    res.redirect('http://127.0.0.1');
})


app.listen(port,()=>{
    console.log('服务已经启动......');
})