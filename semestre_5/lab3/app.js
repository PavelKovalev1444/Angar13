let https = require("https");
let fs = require("fs");
let file = require("fs");

const options = {
    key: fs.readFileSync(__dirname + "/public/example.key", "utf8"),
    cert: fs.readFileSync(__dirname + "/public/example.csr", "utf8")
};


let express = require("express");
let server = express();
server.use('/public', express.static('public'));
server.engine('pug', require('pug').__express);
server.set("view engine", "pug");
server.set("views",`./public/pug`);
server.use(express.json());
server.use(express.urlencoded())

const path = require("path");
server.use(express.static(path.join(__dirname, "public")));
server.use("/jquery", express.static(__dirname + "/node_modules/jquery/dist/"));

let httpsServer = https.createServer(options, server).listen(3000, ()=>{
});

let picturesList = require('./public/json/pictures');
let participantsList = require('./public/json/participants');
let settingsList = require('./public/json/setting');

server.get("/", (req, res) => {
    res.render("index");
});

server.get("/pictures", (req, res) => {
    res.render("pictures", {pictures: picturesList});
});

server.get("/participants", (req, res) => {
    res.render("participants", {participants: participantsList});
});

server.get("/settings", (req, res) => {
    res.render("settings", {settings: settingsList[0]});
});

server.get("/ajx_change_settings", (req, res)=>{
    if(req.query.start_auction_date !== ""){
        settingsList[0].start_auc_date = req.query.start_auction_date;
    }
    if(req.query.trade_auction_timeout !== ""){
        settingsList[0].trade_timeout = req.query.trade_auction_timeout;
    }
    if(req.query.trade_auction_interval !== ""){
        settingsList[0].trade_interval = req.query.trade_auction_interval;
    }
    if(req.query.pause_auction_time !== ""){
        settingsList[0].pause_time = req.query.pause_auction_time;
    }

    file.writeFile("./public/json/setting.json", JSON.stringify(settingsList),function(err){
        if(err)
            throw err;
    })
    res.end(JSON.stringify(settingsList[0]));
});

server.post("/addParticipant", (req, res)=>{
    let addParticipant = req.body;
    if(isNaN(addParticipant.money)){
        addParticipant.money = '';
    }
    addParticipant["id"] = participantsList[participantsList.length-1].id + 1
    participantsList.push(addParticipant);
    res.redirect("/participants");
});

server.get("/ajx_delete_participant/:num", (req,res)=>{
    let id = req.params.num;
    for(let i = 0; i < participantsList.length; i++){
        if(participantsList[i].id.toString() === id){
            participantsList.splice(i,1);
            break;
        }
    }
});

server.get("/ajx_edit_participant", (req,res)=>{
    let idx = req.query.id.toString();
    for(let i = 0; i < participantsList.length; i++){
        if(participantsList[i].id.toString() === idx){
            if(req.query.name !== ""){
                participantsList[i].name = req.query.name;
            }
            if(req.query.money !== ""){
                participantsList[i].money = req.query.money;
            }
        }
    }
});

server.get("/ajx_trade_or_not_trade",(req, res)=>{
    console.log(picturesList);
    let idx = req.query.id.toString();
    for(let i = 0; i < picturesList.length; i++) {
        if (picturesList[i].id.toString() === idx) {
            picturesList[i].trade = req.query.text;
        }
    }
    console.log(picturesList);
});

server.post("/addPicture", (req, res)=>{
    let addPicture = req.body;
    if(isNaN(addPicture.money)){
        addPicture.money = '';
    }
    addPicture["id"] = picturesList[picturesList.length-1].id + 1;
    addPicture["trade"] = "Вне торгов";
    picturesList.push(addPicture);
    res.redirect("/pictures");
});

server.get("/ajx_edit_picture", (req,res)=>{
    let idx = req.query.id.toString();
    console.log(req.query);
    for(let i = 0; i < picturesList.length; i++){
        if(picturesList[i].id.toString() === idx){
            if(req.query.name !== ""){
                picturesList[i].name = req.query.name;
            }
            if(req.query.author !== ""){
                console.log("changed author");
                picturesList[i].author = req.query.author;
            }
            if(req.query.desc !== ""){
                picturesList[i].desc = req.query.desc;
            }
            if(req.query.start_price !== ""){
                picturesList[i].start_price = req.query.start_price;
            }
            if(req.query.min_step !== ""){
                picturesList[i].min_step = req.query.min_step;
            }
            if(req.query.max_step !== ""){
                picturesList[i].max_step = req.query.max_step;
            }
            if(req.query.path !== ""){
                picturesList[i].path = req.query.path;
            }
        }
    }
});

//server.listen(3000);