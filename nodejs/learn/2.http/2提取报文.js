const http=require('http')

const server=http.createServer((request,response)=>{
    response.setHeader('content-type','text/html;charset=utf-8');//设置响应头
    //获取请求的方法
    //console.log('请求方法为：'+ request.method);
    //获取请求的url
    //console.log(request.url);
    //console.log('请求状态码为：'+request.statusCode);
    //console.log('http版本为：'+request.httpVersion+'\n')

    console.log('http请求头内容为：'+request.headers.host);
    response.end('Http......'); //设置响应体
});


server.listen(9000,()=>{
    console.log('服务器已经启动咯')
});
