const readline = require('readline');
const Msg = require('./msg')
const singleDTree = require('./singleDTree')
const DTreeManager = require('./DTreeManager')
const goalManTree = require('./goalManTree')

class Agent {
  constructor(rotationSpeed, position, team) {
    this.position = position 
    this.rotationSpeed = rotationSpeed
    this.run = false
    this.act = null
    this.team = team  
  }


  msgGot(msg) {
    let data = msg.toString('utf8')
    this.processMsg(data)
    this.sendCmd()
  }


  setSocket(socket) {
    this.socket = socket
  }


  socketSend(cmd, value) {
    let message = `(${cmd} ${value})`
    this.socket.sendMsg(message)
  }


  processMsg(msg) {
    let data = Msg.parseMsg(msg)
    if (!data) throw new Error("Parse error\n" + msg)
    if (data.cmd == "hear") {
      if (data.msg.includes('play_on')){
        this.run = true
      }
    }
    if (data.cmd == "init"){
      this.initAgent(data.p)
    }
    this.analyzeEnv(data.msg, data.cmd, data.p)
  }


  initAgent(p) {
    if (p[0] == "r"){
      this.position = "r"
    }
    if (p[1]) {
      this.id = p[1]
    }
  }


  analyzeEnv(msg, cmd, p) {
    if(this.run){
      if(cmd === 'see'){
        if (this.position === 'l' && this.id === 1) {
          this.act = DTreeManager.getAction(singleDTree, p)
        }else if(this.position === 'r' && this.id === 1){
          this.act = DTreeManager.getAction(goalManTree, p)
        }
      }
    }
  }

  sendCmd() {
    if (this.run) {
      if (this.act) {
        if (this.act.n == "kick"){
          this.socketSend(this.act.n, this.act.v)
        }else{
          this.socketSend(this.act.n, this.act.v)
        }
      }
      this.act = null
    }
  }
}

module.exports = Agent
