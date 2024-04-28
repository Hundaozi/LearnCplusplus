const exp = require("constants");

function hello(){
    console.log('模块化你好');
}

function hahaha() {
    console.log('hahaha');
}
// //暴露数据
// module.exports={
//     hello,
//     hahaha
// }
//也可以使用变量导出
exports.hello=hello;
exports.hahaha=hahaha;
//export=smodule.exports={}