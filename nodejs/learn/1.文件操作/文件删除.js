const fs=require('fs');

//调用unlink方法
fs.unlink('./test.txt',err=>{
    if(err){
        console.log('删除失败');
        return ;
    }
    console.log('删除成功');
});

//同步
// fs.unlinkSync();

//还有一个删除方法 fs.rm()