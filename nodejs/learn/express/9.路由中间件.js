const express=require('express');

const app=express();
const port=9000;


//声明路由中间件
//通过这些中间件来校验用户信息，简单，高效，易于使用
let checkCodeMiddleware=(req,res,next)=>{
    //判断url中的code
    if(req.query.code==='521'){
        next();//如果满足，就执行相应的路由回调即可
    }else{
        res.send('暗号错误，不给你进');
    }
}


app.get('/home',(req,res)=>{

    res.send('前台首页');
});

//将中间件放到受约束的路由规则之中
app.get('/admin',checkCodeMiddleware,(req,res)=>{
    
    res.send('后台首页');
});

app.get('/setting',checkCodeMiddleware,(req,res)=>{
    res.send('设置页面');
});

app.all('*',(req,res)=>{
    res.send('<h1>404</h1>');
});

app.listen(port,()=>{
    console.log('服务已经启动......');
})