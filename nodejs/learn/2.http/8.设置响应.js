const http=require('http')

const server=http.createServer((request,response)=>{
    response.setHeader('content-type','text/html;charset=utf-8');//设置响应头
    //设置响应状态码
    // response.statusCode =200;
    // response.statusCode =404;
    response.statusMessage='nodejs';
    response.end('88888888888888'); //设置响应体
});

//监听
server.listen(9000,()=>{
    console.log('服务器已经启动......')
});
