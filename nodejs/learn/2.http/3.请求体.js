const http=require('http')

const server=http.createServer((request,response)=>{
    response.setHeader('content-type','text/html;charset=utf-8');//设置响应头
    //1.声明变量
    let body='';
    //2.data绑定事件
    request.on('data',chunk=>{
        body+=chunk;
    })
    //3.绑定end事件
    request.on('end',()=>{
        console.log(body);
    })
    //浏览器响应
    response.end('http...');

});


server.listen(9000,()=>{
    console.log('你好！')
});
