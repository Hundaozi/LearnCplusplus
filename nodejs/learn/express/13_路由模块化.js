
const port=9000;
const express=require('express');
const homeRouter=require('./routes/homeRouter');
const adminRouter=require('./routes/adminRouter');


const app=express();
//设置路由
app.use(homeRouter);
app.use(adminRouter);




app.all('*',(req,res)=>{
    res.send('<h1>404</h1>');
});

app.listen(port,()=>{
    console.log('服务已经启动......');
})