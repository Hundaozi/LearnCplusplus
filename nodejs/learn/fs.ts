//所谓的文件模块，就是为了实现与硬盘和内存的数据交互
//实际上就是一组数据结构与函数，用来作为我们操作程序的工具

//require用来导入模块
const fs=require('fs');

// //第二步，写入文件
// fs.writeFile('./test.txt','这个世界是物质组成的', err=>{
//      if(err){
//         console.log('写入失败');
//         return ;
//      }
//      console.log('写入成功');
// });//为什么没有智能提示？
// //文件如果不存在，那就帮我们自动创建

//同步写入
fs.writeFileSync('./data.txt','这个世界是物质组成的,而且我们都会死',err=>{
    if(err){
        console.log('同步写入失败')
        return ;
    }
    console.log('同步写入成功');
});