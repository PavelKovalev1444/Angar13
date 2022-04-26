var express = require('express');
var router = express.Router();

var fs = require('fs');

router.get('/settingsGet', (req, res, next)=>{
    //res.end(JSON.stringify(JSON.parse(fs.readFileSync('./json/stockSettings.json'))));
    let tmpjson = JSON.parse(fs.readFileSync('./json/stockSettings.json'));
    res.end(JSON.stringify(tmpjson));
});

router.post('/settingsAdd',(req, res, next)=>{
    console.log(req.body);
    fs.writeFile("./json/stockSettings.json", JSON.stringify(req.body),(err)=>{
        if(err)
            throw err;
    });
});

module.exports = router;
