//导入fs
const fs=require('fs');

fs.rename('./buffer.ts','./buffer_new.ts', err=>{
    if(err){
        console.log('失败');
        return ;
    }
    console.log('操作成功');
});

//文件的移动
//文件的移动很简单，就是将新路径换一下，不是原来的旧路径即可