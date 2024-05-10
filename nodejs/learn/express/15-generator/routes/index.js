var express = require('express');
var router = express.Router();
const formidable = require('formidable');
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
  //创建form对象
  const form = formidable({ 
    multiples: true,
    //设置上传文件的保存目录
    uploadDir: __dirname+'/../public/images',
    //保持文件后缀
    keepExtensions:true
   });
  //解析请求报文
  form.parse(req, (err, fields, files) => {
    if (err) {
      next(err);
      return;
    }
    //console.log(fields);
    //console.log(files);
    let url='/images/' + files.portrait.newFilename;//应该保存在数据库
    
    res.send(url);
    //res.json({ fields, files });
  });
});

module.exports = router;
