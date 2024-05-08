const express=require('express');
const ejs=require('ejs');
const path=require('path');


const app=express();


//设置模版引擎
app.set('view engine','ejs');


//设置模版文件的存放位置
app.set('views',path.resolve(__dirname,'./views'));//绝对路径

app.get('/',(req,res)=>{
    // res.send('/home');

    let title='这是一个标题'
    res.render('home',{title});
});


app.listen(9000,()=>{
    console.log('server......');
});