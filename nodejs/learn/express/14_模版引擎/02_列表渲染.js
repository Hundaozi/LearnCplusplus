const ejs=require('ejs');
const fs=require('fs');

let html=fs.readFileSync('./02_xiyou.html').toString();

const xiyouji=['唐僧','孙悟空','猪八戒','沙悟净','白空马'];



let result=ejs.render(html,{xiyouji:xiyouji});
console.log(result);