const express=require('express');


//创建路由对象
const router=express.Router();
//创建路由规则

app.get('/admin',(req,res)=>{
    
    res.send('后台首页');
});

app.get('/setting',(req,res)=>{
    res.send('设置页面');
}); 

//最后一步，暴露router
module.exports=router;