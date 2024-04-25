

const http=require('http')

const server=http.createServer((request,response)=>{
    
    //解构赋值，获取请求方法
    let {method}=request;

    //获取url路径
    let {pathname}=new URL(request.url,'http://127.0.0.1');
    response.setHeader('content-type','text/html;charset=utf-8');//设置响应头
    

    console.log(method);
    console.log(pathname);

    //判断
    if(method==='GET' && pathname==='/login'){
        //登录情形
        response.end('登录页面');
    }else if(method==='GET' && pathname==='/reg' ){
        response.end('注册页面');
    }else{
        response.end('404 Not Found!');
    }
    
    
});

//监听
server.listen(9000,()=>{
    console.log('服务器已经启动.....listen....')
});

