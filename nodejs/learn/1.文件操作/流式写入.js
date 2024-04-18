const fs =require('fs');


const ws=fs.createWriteStream('./流式写入.txt');


ws.write('一一一一一一一一体');
ws.write('2222222222222222');




ws.write('333333333333');
//流式写入适合大文件写入或者频繁写入的场景
//wireFile适合写入频次较低的场景

//关闭操作
ws.close();