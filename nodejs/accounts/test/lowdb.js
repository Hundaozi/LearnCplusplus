//导入lowdb
const low = require('lowdb')
const FileSync = require('lowdb/adapters/FileSync')
 
const adapter = new FileSync('db.json')
const db = low(adapter)

// //数据初始化
// db.defaults({ posts: [], user: {} })
//   .write()

//写入数据
// db.get('posts').push({
//     id: 2,
//     title:'今天下雨了2'
//     })
//     .write();
//在之前插入
// db.get('posts').unshift({
//     id: 0,
//     title:'今天下雨了0'
//     })
//     .write();

// //获取数据
// console.log(db.get('posts').value());

// //删除数据
// let res=db.get('posts').remove({id:0}).write();
// console.log(res);

// //获取单条数据
// let res=db.get('posts').find({id:1}).value();
// //console.log(res);

//更新数据
let res1=db.get('posts').find({id:1}).assign({title:'哈哈哈哈'}).write();
console.log(res1);