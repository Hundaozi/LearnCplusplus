const http=require('http');
const fs=require('fs');
const path = require('node:path/posix');
const { MIMEParams } = require('util');
let mimes={
    html:'text/html',
    css:'text/css',
    js:'text/javascript',
    png:'image/png',
    jpg:'image/jpg',
    gif:'image/gif',
    mp4:'video/mp4',
    mp3:'audio/mpeg',
    json:'application/json'
}
const server=http.createServer((request,response)=>{

    if(request.method !=='GET'){
        response.statusCode=405;
        response.end('<h1>405 not Fuound!</h1>');
        return ;
    }
    //获取请求url的路径
    let {pathname}=new URL(request.url,'http://127.0.0.1');

    //声明一个根目录
    let root=__dirname + '/page';
    //拼接文件路径
    let filePath =  root + pathname;

    //读取文件，fs 异步api
    fs.readFile(filePath,(err,data)=>{
        if(err){
            //设置字符标准
            response.setHeader('content-type','text/html;charset=utf-8');
            //判断错误代号
            switch (err.code) {
                case 'ENOENT':
                    response.statusCode=404;
                    response.end('<h1>404 Not Found!</h1>');
                return ;
                case 'EPERM':
                    response.statusCode=403;
                    response.end('<h1>403 Forbidden</h1>');
                default:
                    response.statusCode=500;
                    response.end('<h1>服务器内部错误</h1>');
            }
            
            // response.statusCode = 500;
            // response.end('文件读取失败...');
            console.log('读取错误');
            return ;
        }
        //获取文件的后缀名
        let ext=path.extname(filePath).slice(1);
        //console.log(ext);
        //获取对应的类型
        let type=mimes[ext];
        if (type) {
            //匹配到了类型
            response.setHeader('content-type',type);
            
        }else{
            //配有匹配到我们预设的类型
            response.setHeader('content-type','application/octet-stream');
            //即下载文件类型
        }

        //response.setHeader('conten-type','xxx');
        //响应文件内容
        response.end(data);
    });

    
});

//监听端口，启动服务
server.listen(9000,()=>{
    console.log('服务器已经启动....');
})