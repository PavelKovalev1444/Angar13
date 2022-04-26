var express = require('express');
var router = express.Router();

var fs = require('fs');
var sharesList = require('../json/sharesList.json');
const tmpShareList = require("../json/sharesList.json");

router.get('/sharesGet', (req, res, next)=>{
    res.end(JSON.stringify(JSON.parse(fs.readFileSync('./json/sharesList.json'))));
});

router.post('/sharesAdd',(req, res, next)=>{
    fs.writeFile("./json/sharesList.json", JSON.stringify(req.body),(err)=>{
        if(err)
            throw err;
    });
});

router.post('/sharesChanging', (req, res, next)=>{
    for(let i = 0; i < sharesList.length; i++){
        if(sharesList[i].share_id === req.body.share_id){
            sharesList[i].emitent_name = req.body.emitent_name;
            sharesList[i].share_price = parseInt(req.body.share_price);
            sharesList[i].distribution = req.body.distribution;
            sharesList[i].max_change = parseInt(req.body.max_change);
            sharesList[i].amount = parseInt(req.body.amount);
        }
    }
    fs.writeFile("./json/sharesList.json", JSON.stringify(sharesList),(err)=>{
        if(err)
            throw err;
    });
});

router.delete('/sharesDeleting/:num',(req, res, next)=>{
    let tmpShareList = require('../json/sharesList.json');
    for(let i = 0; i < tmpShareList.length; i++){
        if(tmpShareList[i].share_id === parseInt(String(req.params.num))){
            tmpShareList.splice(i, 1);
        }
    }
    fs.writeFile("./json/sharesList.json", JSON.stringify(tmpShareList),(err)=>{
        if(err)
            throw err;
    });
});

module.exports = router;
