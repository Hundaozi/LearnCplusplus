var express = require('express');
var router = express.Router();

//记账本的列表
router.get('c', function(req, res, next) {
  res.render('list');
});


//添加记录
router.get('/account/create',function(req,res,next){
  res.render('create');
});

//新登记录
router.post('/account',(req,res)=>{
  //获取请求体的数据
  console.log(req.body);
  res.send('添加记录');
});
module.exports = router;
