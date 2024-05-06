const express=require('express');

const app=express();
const port=9000;

app.get('/',(req,res)=>{
    res.send('首页....');
});

//静态资源中间件设置
//这个参数是静态资源文件夹的路径
app.use(express.static(__dirname+ '/public'));//一行代码就搞定了，舒服

//
app.use((req,res,next)=>{
    //防止盗链,如果不是指定的地址，就无法获取资源
    //获取referer
    let referer=req.get('referer');

    if (referer) {
        let url=new URL(referer);
        //获取hostname
        let hostname=url.hostname;
        //console.log(hostname);
        if (hostname!=='127.0.0.1') {
            //响应404
            res.status(404).send('<h1>404 not found</h1>');
            return ;
        }
    }
    // console.log(referer);
    
    next();
});


app.get('/home',(req,res)=>{

    res.send('前台首页');
});

//将中间件放到受约束的路由规则之中
app.get('/admin',(req,res)=>{
    
    res.send('后台首页');
});

app.get('/setting',(req,res)=>{
    res.send('设置页面');
}); 

app.all('*',(req,res)=>{
    res.send('<h1>404</h1>');
});

app.listen(port,()=>{
    console.log('服务已经启动......');
})