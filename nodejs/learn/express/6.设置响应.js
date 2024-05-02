const express=require('express');

const app=express();
const port=9000;




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


app.listen(port,()=>{
    console.log('服务已经启动......');
})