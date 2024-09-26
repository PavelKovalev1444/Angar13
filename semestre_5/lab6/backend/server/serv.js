const express = require('express');
const path = require('path');
const session = require('express-session');
const cookieParser = require('cookie-parser');
const cors = require('cors');
const http = require('http');

let app = express();
const port = 8080;

const corsOptions = {
    'credentials': true,
    'origin': true,
    'methods': 'GET,HEAD,PUT,PATCH,POST,DELETE',
    'allowedHeaders': 'Authorization,X-Requested-With,X-HTTP-Method-Override, Content-Type, Cache-Control, Accept',
};

app.set('data', path.join(__dirname, 'data'));
app.use(express.static('data'));

app.use(cors(corsOptions));
app.use(express.json());
app.use(express.urlencoded());

app.use(cookieParser());

app.use(session({
    secret: "keyboard cat",
    resave: false,
    saveUninitialized: false
}));

const server = http.createServer(app);

const { Server } = require("socket.io");
const { connect} = require("socket.io-client");
const fs = require("fs");
const io = new Server(server, {
    cors: {
        origin: "http://localhost:3000",
        methods: ["GET", "POST"]
    }
});



let sharesLaw;

app.get('/sendBrokers', (req, res, next)=>{
    let tmpjson = JSON.parse(fs.readFileSync('./brokerslist.json'));
    res.end(JSON.stringify(tmpjson));
});

app.get('/sendShares', (req, res, next)=>{
    let tmpjson = JSON.parse(fs.readFileSync('./sharesList.json'));
    res.end(JSON.stringify(tmpjson));
});

app.post('/selectLawShares', (req,res,next)=>{
    console.log(req.body);
});


app.get('/getUser/:name', (req,res,next)=>{
    fs.readFile("./brokerslist.json", (err, data) =>{
        let brokers = JSON.parse(data);
        let broker;
        for(let i = 0; i < brokers.length; i++){
            if(brokers[i].broker_name === req.params.name){
                broker = brokers[i];
            }
        }
        res.send(broker);
    });
});

app.get('/getUsers', (req,res,next)=>{
    fs.readFile("./brokerslist.json", (err, data) =>{
        let brokers = JSON.parse(data);
        res.send(brokers);
    });
});

app.get('/getShares', (req,res,next)=>{
    fs.readFile("./sharesList.json", (err, data) =>{
        let sales = JSON.parse(data);
        res.send(sales);
    });
});

let timer;

io.on('connection' , function(socket) {
    socket.on('requestDataForAdmin', ()=>{
        socket.emit('getData',{brokers: brokers})
    });

    socket.on('requestDataForUser', (data)=>{
        let broker;
        for(let i = 0; i < brokers.length; i++){
            if(brokers[i].broker_name === data.name){
                broker = brokers[i];
            }
        }
        socket.emit('sendDataForUser', {broker: broker});
    });

    socket.on('buyShareEvent', (data)=>{
        fs.writeFileSync('./sharesList.json', JSON.stringify(data.sharesList),(err)=>{
            if(err)
                throw err;
        });
        fs.writeFileSync('./brokerslist.json', JSON.stringify(data.brokersList),(err)=>{
            if(err)
                throw err;
        });
        let shares = JSON.parse(fs.readFileSync('./sharesList.json'));
        let brokers = JSON.parse(fs.readFileSync('./brokerslist.json'));
        socket.broadcast.emit('buyShareEvent', {users: brokers, shares:shares});
        socket.emit('buyShareEvent', {users: brokers, shares:shares});
    });

    socket.on('startTrade', (data)=>{
        //console.log('startTrade on server');
        recalculation(socket);
        socket.broadcast.emit('startTrade');
    });

    socket.on('endTrade', (data)=>{
        clearInterval(timer);
        socket.broadcast.emit('endTrade');
    })
});

function recalculation(socket){
    timer = setInterval(()=>{
        let shares = JSON.parse(fs.readFileSync('./sharesList.json'));
        for(let i = 0; i < shares.length; i++){
            shares[i].share_price = Math.round(Math.random() * (200 - 10) + 10);
        }
        socket.broadcast.emit('updatePrices', shares);
        socket.emit('updatePrices', shares);
    }, 8000);
}

app.listen(port);
server.listen(3030);

module.exports = app;