const fs=require('fs');

// //创建文件夹
// fs.mkdir('./html',err=>{
//     if(err){
//         console.log('文件夹创建失败');
//         return ;
//     }
//     console.log('文件夹创建成功！');
// });
// // fs.mkdirSync();//同步创建

//递归创建，需要添加第二个属性

// fs.mkdir('./a/b/c',{recursive:true},err=>{
//         if(err){
//         console.log('文件夹递归创建失败');
//         return ;
//     }
//     console.log('文件夹递归创建成功！');
// })

//读取文件夹
fs.readdir('../1.文件操作',(err,data)=>{
    if(err){
        console.log('文件夹读取失败');
        return ;
    }
    console.log('读取成功:');
    console.log(data);

});
//删除文件夹fs.rmdir(),并且也可以加上递归删除的标志