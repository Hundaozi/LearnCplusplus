const http=require('http')

const server=http.createServer((request,response)=>{
    response.setHeader('content-type','text/html;charset=utf-8');//设置响应头
    response.end('Http Server......启动中'); //设置响应体
});

//监听,比纯 C++简单太多，真是纯牛马
server.listen(9000,()=>{
    console.log('你好！')
});

