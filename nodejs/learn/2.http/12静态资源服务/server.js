const http=require('http');
const fs=require('fs');

const server=http.createServer((request,response)=>{
    //获取请求url的路径
    let {pathname}=new URL(request.url,'http://127.0.0.1');

    //声明一个根目录
    let root=__dirname + '/page';
    //拼接文件路径
    let filePath =  root + pathname;

    //读取文件，fs 异步api
    fs.readFile(filePath,(err,data)=>{
        if(err){
            response.setHeader('content-type','text/html;charset=utf-8');
            response.statusCode = 500;
            response.end('文件读取失败...');
            console.log('读取错误');
            return ;
        }
        //响应文件内容
        response.end(data);
    });

    
});

//监听端口，启动服务
server.listen(9000,()=>{
    console.log('服务器已经启动....');
})