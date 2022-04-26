var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
const http = require("http");

var app = express();

// view engine setup
app.use('/public', express.static('public'));
app.engine('pug', require('pug').__express);
app.set("view engine", "pug");
app.set("views",`./public/views`);
app.use(express.json());
app.use(express.urlencoded())
app.use("/jquery", express.static(__dirname + "/node_modules/jquery/dist/"));
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());

app.use('/', indexRouter);

let Rollbar = require('rollbar')
let rollbar = new Rollbar({
  accessToken: '1c4ac6cabe7c448f956d44ab8f109299',
  captureUncaught: true,
  captureUnhandledRejections: true,
})

// record a generic message and send it to Rollbar
rollbar.log('Hello world!')


let connections = [];
let pictureIndex = -1;
let picturesList = require('./public/json/pictures');
let participantList = require('./public/json/participants');
let settingList = require('./public/json/setting');
let seconds = settingList[0].trade_interval;
let curSoldPicture = -1;
let curCustomer = '';
let timerAll;
let timerForTrade;
let endTimerForTrade;

app.set('port',3000);
let server = http.createServer(app);
const io = require('socket.io')(server);
io.on('connection', function (socket) {
  socket.on('new_participant', (data)=>{
    connections.push(socket);
    socket.name = data.name;
    socket.broadcast.emit('new_participant_msg', {msg: data.msg, name: data.name, money: data.money});
    socket.emit('new_participant_msg', {msg: data.msg, name: data.name, money: data.money});
  });

  socket.on('disconnect', ()=>{
    if(connections.indexOf(socket) !== -1) {
      connections.splice(connections.indexOf(socket), 1);
      socket.broadcast.emit('participant_disconnected', {name: socket.name});
      socket.emit('participant_disconnected', {name: socket.name});
    }
  });

  socket.on('send_mess', function(data) {
    socket.broadcast.emit('add_mess', {mess: data.mess, name: data.name});
    socket.emit('add_mess', {mess: data.mess, name: data.name});
  });

  socket.on('start_auction', ()=>{
    startAuctionTimers(socket);
  });

  socket.on('trade_pictures', ()=>{
    pictureIndex = pictureIndex + 1;
    curSoldPicture = pictureIndex;
    if(pictureIndex <= picturesList[picturesList.length-1].id) {
      tradePictures(socket, seconds, pictureIndex);
    }
    if(pictureIndex >= picturesList[picturesList.length-1].id + 1){
      endOfAuction(socket);
    }
  });

  socket.on('offer_price',(data)=>{
    if(picturesList[data.number].cur_price < parseInt(data.new_price) && parseInt(data.customer_money) >= parseInt(data.new_price)) {
      curSoldPicture = data.number;
      curCustomer = data.customer;
      let custId = -1;
      for(let i = 0; i < participantList.length; i++){
        if(participantList[i].name === data.customer){
          participantList[i].money_for_one_trade = (parseInt(participantList[i].money) - parseInt(data.new_price)).toString();
          custId = i;
        }
      }
      picturesList[data.number].cur_price = parseInt(data.new_price);
      socket.broadcast.emit('cur_price_update', {new_price: data.new_price, number: data.number, par_money: participantList[custId].money_for_one_trade, name: curCustomer});
      socket.emit('cur_price_update', {new_price: data.new_price, number: data.number, par_money: participantList[custId].money_for_one_trade, name: curCustomer});
    }
  });
});

function startAuctionTimers(socket){
  let leftSeconds = 0;
  socket.broadcast.emit('update_timers', {time: leftSeconds});
  socket.emit('update_timers', {time: leftSeconds});
  timerAll = setInterval(()=> {
    socket.broadcast.emit('update_timers', {time: leftSeconds + 1});
    socket.emit('update_timers', {time: leftSeconds + 1});
    leftSeconds = leftSeconds + 1;
  }, 1000);
}

function tradePictures(socket, seconds, pictureIndex){
  let leftSeconds = seconds;
  timerForTrade = setInterval(()=> {
    socket.broadcast.emit('timer_for_buy_picture', {
          time: leftSeconds - 1,
          picture: picturesList[pictureIndex]
    });
    socket.emit('timer_for_buy_picture', {
      time: leftSeconds - 1,
      picture: picturesList[pictureIndex]
    });
    leftSeconds = leftSeconds - 1;
  }, 1000);
  setTimeout(()=>{
    console.log("end of trade for one pic");
    leftSeconds = seconds;
    let partMoneyInd = -1;
    if(curCustomer !== ''){
      picturesList[curSoldPicture].sold = curCustomer;
      for(let i = 0; i < participantList.length; i++){
        if(participantList[i].name === curCustomer){
          participantList[i].money = participantList[i].money - picturesList[curSoldPicture].cur_price;
          participantList[i].money_for_one_trade = "0";
          partMoneyInd = i;
        }
      }
      for(let i = 0; i < participantList.length; i++){
        if(participantList[i].name !== curCustomer) {
          participantList[i].money = (parseInt(participantList[i].money) + parseInt(participantList[i].money_for_one_trade)).toString();
        }
      }
    }
    if(curCustomer !== '' && partMoneyInd !== -1) {
      console.log("there is a buyer");
      socket.broadcast.emit('one_picture_sold', {
        time: "Time has gone!",
        buyer: curCustomer,
        soldPicture: picturesList[curSoldPicture],
        buyer_money: participantList[partMoneyInd].money,
        participants: participantList,
        flag: 1
      });
      socket.emit('one_picture_sold', {
        time: "Time has gone!",
        buyer: curCustomer,
        soldPicture: picturesList[curSoldPicture],
        buyer_money: participantList[partMoneyInd].money,
        participants: participantList,
        flag: 1
      });
    }else{
      console.log("there is no a buyer");
      socket.broadcast.emit('one_picture_sold', {
        time: "Time has gone!",
        buyer: curCustomer,
        soldPicture: picturesList[curSoldPicture],
        buyer_money: '-',
        participants: participantList,
        flag: 0
      });
      socket.emit('one_picture_sold', {
        time: "Time has gone!",
        buyer: curCustomer,
        soldPicture: '-',
        buyer_money: '-',
        participants: participantList,
        flag: 0
      });
    }
    curCustomer = '';
    clearTimeout(timerForTrade);
  }, seconds*1000);
  leftSeconds = seconds;
}

function endOfAuction(socket){
  console.log("end of auction");
  clearTimeout(timerAll);
  clearTimeout(timerForTrade);
  socket.broadcast.emit('end_of_auction');
  socket.emit('end_of_auction');
}

server.listen(3000);

module.exports = app;