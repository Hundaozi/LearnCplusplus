const http=require('http');


const server=http.createServer((request,response)=>{

    //实例化一个URL对象
    let url=new URL(request.url,'http://127.0.0.1:9000');
    //使用URL对象，所有的属性都可以通过这个URL对象获得。
    console.log(url.pathname);
    response.end("url new");
});


server.listen(9000,()=>{
    console.log('服务器已经启动....');
})