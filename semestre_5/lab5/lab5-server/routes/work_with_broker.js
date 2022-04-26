var express = require('express');
var router = express.Router();

var fs = require('fs');
var brokerList = require('../json/brokerslist.json');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.post('/brokersAdd', (req, res, next)=>{
  fs.writeFile("./json/brokerslist.json", JSON.stringify(req.body),function(err){
    if(err)
      throw err;
  });
});

router.get('/brokersAdd', (req, res, next)=>{
  let tmpjson = JSON.parse(fs.readFileSync('./json/brokerslist.json'));
  res.end(JSON.stringify(tmpjson));
});

router.post('/brokersChanging', (req, res, next)=>{
  for(let i = 0; i < brokerList.length; i++){
    if(brokerList[i].broker_id === req.body.broker_id){
      brokerList[i].broker_money = req.body.broker_money;
    }
  }
  fs.writeFile("./json/brokerslist.json", JSON.stringify(brokerList),function(err){
    if(err)
      throw err;
  });
});

router.post('/brokersDeleting', (req, res, next)=>{
  fs.writeFile("./json/brokerslist.json", JSON.stringify(req.body),function(err){
    if(err)
      throw err;
  });
});

module.exports = router;
