let isLogin=false;

// //js
// if(isLogin){
//     console.log('<span>欢迎回来</span>');
// }else{
//     console.log('<button>登录</button> <button>注册</button>');
// }

//ESJ
const ejs=require('ejs');
const fs=require('fs');
let html=fs.readFileSync('./03_home.html').toString();
let result=ejs.render(html,{isLogin:isLogin});

console.log(result);