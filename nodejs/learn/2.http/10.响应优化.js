const http=require('http');
const fs=require('fs');

const server=http.createServer((request,response)=>{

    //这里使用绝对路径，同步读取
    let html1=fs.readFileSync(__dirname+'/10_home.html');

    response.end(html1);//响应体
});

//监听端口，启动服务
server.listen(9000,()=>{
    console.log('服务器已经启动....');
})