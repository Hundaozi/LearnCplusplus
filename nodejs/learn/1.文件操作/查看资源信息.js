const fs=require('fs')

fs.stat('./data.txt',(err,data)=>{
     if(err){
        console.log('操作失败');
        return ;
     }
     console.log(data.isFile());//判断文件是否为文件，还可以有很多方法
     console.log(data.isDirectory());
});