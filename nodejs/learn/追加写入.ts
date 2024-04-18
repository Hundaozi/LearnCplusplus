const fs=require('fs')

fs.appendFile('./test.txt','这是一个朴实无华的追加',err=>{
    if(err){
        console.log('追加错误，写入失败');
        return  ;
    }
    console.log('追加写入成功');
});