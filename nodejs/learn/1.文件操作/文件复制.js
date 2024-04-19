//复制的逻辑很简单，就是将文件的数据读取出来，然后写入新的空文件中

const fs=require('fs');
const process=require('process');

const rs=fs.createReadStream('./test.txt');
//每次只取64kb的数据为一块
const ws=fs.createWriteStream('./test1111.txt',rs);

console.log(process.memoryUsage());