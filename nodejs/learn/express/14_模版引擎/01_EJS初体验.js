const ejs=require('ejs');

//字符串
let helo1='你好';
let str=`哈哈哈哈  ${helo1} `; 

console.log(str);

//使用ejs渲染
let lubenwei='卢本伟  <%= niubi%>';
let niubi='牛逼';
let result=ejs.render(lubenwei,{niubi:niubi});

console.log(result);