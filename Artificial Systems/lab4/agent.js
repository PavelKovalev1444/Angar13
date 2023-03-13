const readline = require('readline');
const Msg = require('./msg')
const doPassTree = require('./doPassTree')
const doGoalTree = require('./doGoalTree')
const DTreeManager = require('./DTreeManager')

class Agent {
  constructor(rotationSpeed, position, team, isGoalie) {
    this.position = position 
    this.rotationSpeed = rotationSpeed
    this.run = false
    this.act = null
    this.team = team
    this.isGoalie = isGoalie
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
      if (data.msg.includes('kick_off') || data.msg.includes('goal')){
        this.run = false
        //this.act = {n: "move", v: "-15 10"}
        if(this.position === 'l' && this.id === 1) {
          this.socketSend(
            "move", "-15 -10"
          )
          doPassTree.state.next = 0
          doPassTree.state.kicked = false
          doPassTree.state.N = 18
        }else if(this.position === 'l' && this.id === 2){
          this.socketSend(
            "move", "-15 10"
          )
          doGoalTree.state.N = 5
          doGoalTree.state.next = 0
          doGoalTree.state.prev = -1
          doGoalTree.state.prevState = null
        }
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
        if(this.position === 'l' && this.id === 1) {
          this.act = DTreeManager.getAction(doPassTree, p)
        }else if(this.position === 'l' && this.id === 2){
          this.act = DTreeManager.getAction(doGoalTree, p)
        }
      }else if(cmd === 'hear'){
        if(this.position === 'l' && this.id === 2){
          //console.log('hear')
          //console.log(p)
          //console.log(p[2])
          if(p[2] === `"go"`){
            doGoalTree.state.prev = doGoalTree.state.next
            doGoalTree.state.prevState = doGoalTree.state.sequence[doGoalTree.state.prev]
            doGoalTree.state.next = doGoalTree.state.sequence.length - 1
            doGoalTree.state.action = doGoalTree.state.sequence[doGoalTree.state.next]
          }
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
