//所谓的流式就是，一块一块的读取呗
//readFile是一次性全读完
const fs=require('fs');

const rs=fs.createReadStream('./data.txt');


rs.on('data',chunk=>{
    //console.log(chunk.length);
})

rs.on('end',()=>{
    console.log('读取完成');
})