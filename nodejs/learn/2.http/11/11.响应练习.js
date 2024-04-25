const http=require('http');
const fs=require('fs');
const path = require('path');

const server=http.createServer((request,response)=>{
    //获取请求url的路径
    let {pathname}=new URL(request.url,'http://127.0.0.1');
    if (pathname==='/') {
        
        let html=fs.readFileSync(__dirname+ '/11_home.html');
        response.end(html);//响应体
    }else if(pathname==='/index.css'){
        let css=fs.readFileSync(__dirname+ '/11index.css');
        response.end(css);
    }else if(pathname==='/index.js'){
        let js=fs.readFileSync(__dirname+ '/11index.js');
        response.end(js);
    }else{
        response.statusCode=404;
        response.end('<h1>404 Not Found</h1>');
    }
    

    
});

//监听端口，启动服务
server.listen(9000,()=>{
    console.log('服务器已经启动....');
})