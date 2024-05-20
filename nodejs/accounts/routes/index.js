var express = require('express');
var router = express.Router();


//导入lowdb
const low = require('lowdb')
const FileSync = require('lowdb/adapters/FileSync');
const shortid = require('shortid');
 
const adapter = new FileSync(__dirname+ '/../data/db.json')
const db = low(adapter)

//导入shortid
const id=require('shortid');


//记账本的列表
router.get('/account', function(req, res, next) {

  //获取所有的账单信息
  let accounts=db.get('accounts').value();
  //console.log(accounts);
  res.render('list',{accounts:accounts});
});


//添加记录
router.get('/account/create',function(req,res,next){
  res.render('create');
});

//新增加记录
router.post('/account',(req,res)=>{
  //获取请求体的数据
  console.log(req.body);

  //生产id
  let id=shortid.generate();
  //写入数据
  db.get('accounts').unshift(//数据往前加，后加入的在前面
    {
      id:id,
      ...req.body
    }).write();

    //成功提醒
  res.render('success',{msg: '添加成功哦', url: '/account'});
});
module.exports = router;
