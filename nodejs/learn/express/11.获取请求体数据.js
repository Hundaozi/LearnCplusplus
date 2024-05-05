/**
 * 
 * 按照要求搭建HTTP服务
 * GET /login 现实表单网页
 * POST /login 获取表单中的用户名 和密码
 */


//导入express
const express =require('express');
//导入消息中间件
const bodyParser=require('body-parser');
//创建应用对象

const app=express();



//获取json解释器
const jsonParser=bodyParser.json();
//url解释
const urlencodedParser=bodyParser.urlencoded({extended:false});

//创建路由规则
app.get('/login',(req,res)=>{
    // res.send('表单页面');
    //响应html内容
    res.sendFile(__dirname + '/11_form.html');
})

//POST
app.post('/login',urlencodedParser,(req,res)=>{
    console.log(req.body);//获取请求体
    res.send('获取用户数据');
})

//启动服务
app.listen(9000,()=>{
    console.log('服务器启动......');
});
