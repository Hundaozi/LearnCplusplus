const http=require('http');


const server=http.createServer((request,response)=>{

    
    response.end();
});


server.listen(9000,()=>{
    console.log('服务器已经启动....');
})