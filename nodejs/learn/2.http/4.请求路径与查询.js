const http=require('http');

const url=require('url');

const server=http.createServer((request, response)=>{

    //2.解析url
    //console.log(url);

    let res=url.parse(request.url,true);
    //解析完后是一个对象
    
    //获取路径
    let pathname=res.pathname;
    //console.log(pathname);

    //查询字符串
    let keyword=res.query.keyword;
    console.log(keyword);
     
    response.end('url');
});



server.listen(9000,()=>{
    console.log('http....');
})