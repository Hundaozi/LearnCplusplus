var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});



//现实网页的表单
router.get('/portarait',(req,res)=>{
  res.render('portarait');
});
//处理文件上传
router.post('/portrait',(req,res)=>{
  res.send('上传成功');
});

module.exports = router;
