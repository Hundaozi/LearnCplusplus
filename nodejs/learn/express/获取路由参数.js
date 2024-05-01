//导入express

const express=require('express');


const app=express();
const port = 9000
//获取请求的路由规则

app.get('/:id.html',(req,res)=>{
    //获取url路由参数
    console.log(req.params.id);
    res.setHeader('content-type','text/html;charset=utf-8');
    res.end('商品详情');
});




//启动服务
app.listen(port,()=>{
    console.log('启动成功......')
})