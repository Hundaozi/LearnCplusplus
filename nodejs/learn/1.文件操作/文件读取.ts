//引入fs文件模块
const fs=require('fs');


// //默认是异步读取，很好
// fs.readFile('data.txt',(err,data)=>{
//     if(err){
//         console.log('读取失败');
//         return ;
//     }
//     console.log(data.toString());
// });

let data=fs.readFileSync('./data.txt');
console.log(data.toString());

/*
读取文件可以干嘛？
做一件事情首先要只要他的目的

电脑开机
程序运行
编辑打开文件
查看文件，资料
播放视频
播放音乐
查看日志
上传文件
查看聊天记录，如色图

*/