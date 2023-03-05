const readline = require('readline');
const Msg = require('./msg')
class Agent {
  constructor(rotationSpeed, position, team) {
    this.position = position 
    this.rotationSpeed = rotationSpeed
    this.run = false
    this.act = null
    this.team = team
    this.x = null
    this.y = null
    this.rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout
    })
    this.controller = {
      acts: [
        {act: "flag", fl: "frb"},
        {act: "flag", fl: "gl"},
        {act: "flag", fl: "fc"},
        {act: "kick", fl: "b", goal: "gr"}
      ],
      currentActionIndex: 0
    }
    this.rl.on('line', (input)=>{
      if(this.run){
        if('w' === input) this.act = {n:"dash", v:100}
        if('d' === input) this.act = {n:"turn", v:20}
        if('a' === input) this.act = {n:"turn", v:-20}
        if('s' === input) this.act = {n:"kick", v:100}
      }
    })
    this.flagsCoordinates = {
      ftl50: {x: -50, y: 39}, ftl40: {x: -40, y: 39},
      ftl30: {x: -30, y: 39}, ftl20: {x: -20, y: 39},
      ftl10: {x: -10, y: 39}, ft0: {x: 0, y: 39},
      ftr10: {x: 10, y: 39}, ftr20: {x: 20, y: 39},
      ftr30: {x: 30, y: 39}, ftr40: {x: 40, y: 39},
      ftr50: {x: 50, y: 39}, fbl50: {x: -50, y: -39},
      fbl40: {x: -40, y: -39}, fbl30: {x: -30, y: -39},
      fbl20: {x: -20, y: -39}, fbl10: {x: -10, y: -39},
      fb0: {x: 0, y: -39}, fbr10: {x: 10, y: -39},
      fbr20: {x: 20, y: -39}, fbr30: {x: 30, y: -39},
      fbr40: {x: 40, y: -39}, fbr50: {x: 50, y: -39},
      flt30: {x:-57.5, y: 30}, flt20: {x:-57.5, y: 20},
      flt10: {x:-57.5, y: 10}, fl0: {x:-57.5, y: 0},
      flb10: {x:-57.5, y: -10}, flb20: {x:-57.5, y: -20},
      flb30: {x:-57.5, y: -30}, frt30: {x: 57.5, y: 30},
      frt20: {x: 57.5, y: 20}, frt10: {x: 57.5, y: 10},
      fr0: {x: 57.5, y: 0}, frb10: {x: 57.5, y: -10},
      frb20: {x: 57.5, y: -20}, frb30: {x: 57.5, y: -30},
      fglt: {x:-52.5, y: 7.01}, fglb: {x:-52.5, y:-7.01},
      gl: {x:-52.5, y: 0}, gr: {x: 52.5, y: 0}, fc: {x: 0, y: 0},
      fplt: {x: -36, y: 20.15}, fplc: {x: -36, y: 0},
      fplb: {x: -36, y:-20.15}, fgrt: {x: 52.5, y: 7.01},
      fgrb: {x: 52.5, y:-7.01}, fprt: {x: 36, y: 20.15},
      fprc: {x: 36, y: 0}, fprb: {x: 36, y:-20.15},
      flt: {x:-52.5, y: 34}, fct: {x: 0, y: 34},
      frt: {x: 52.5, y: 34}, flb: {x:-52.5, y: -34},
      fcb: {x: 0, y: -34}, frb: {x: 52.5, y: -34},
      distance(p1, p2) {
        return Math.sqrt((p1.x-p2.x)**2+(p1.y-p2.y)**2)
      },
    }
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
      }else if(data.msg.includes('goal')){
        this.controller.currentActionIndex = 0
      }else if(data.msg.includes('kick_off_r')){
        this.run = false
      }else if(data.msg.includes('kick_off_l')){
        this.run = false
      }else if(data.msg.includes('goal_r')){
        this.run = false
      }else if(data.msg.includes('goal_l')){
        this.run = false
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
        if(this.controller.acts[this.controller.currentActionIndex].act === 'flag'){
          const visibleFlags = p.filter((obj) => obj.cmd && (obj.cmd.p.join('') === this.controller.acts[this.controller.currentActionIndex].fl))
          if(visibleFlags.length){
            if(visibleFlags[0].p[0] < 3){
              this.controller.currentActionIndex += 1
            }else if(visibleFlags[0].p[0] > 3 && visibleFlags[0].p[1] !== 0){
              this.doAction('turn', visibleFlags[0].p[1])
            }else if(visibleFlags[0].p[0] > 3){
              this.doAction('dash', 90)
            }
          }else{
            this.doAction('turn', this.rotationSpeed)
          }
        }else if(this.controller.acts[this.controller.currentActionIndex].act === 'kick'){
          const ball = p.filter((obj) => obj.cmd && (obj.cmd.p[0] === 'b'))
          const visibleFlags = p.filter((obj) => obj.cmd && (obj.cmd.p.join('') === this.controller.acts[this.controller.currentActionIndex].goal))
          if(ball.length){
            if(ball[0].p[0] > 0.5){
              this.doAction('dash', 80)
            }else{
              if(visibleFlags.length){
                let v = '100 ' + visibleFlags[0].p[1]
                this.doAction('kick', v)
              }else{
                this.doAction('kick', '10 45')
              }
            }
          }else{
            this.doAction('turn', this.rotationSpeed)
          }
        }
      }
    }
  }

  doAction(n, v){
    this.act = {
      n: n,
      v: v
    }
  }

  twoFlags(pArray, flags) {
    let detectedFlags = []
    let dist = []
    pArray.forEach(element => {
      if(element.cmd && detectedFlags.length < 2){
        detectedFlags.push(flags[element.cmd.p.join('')])
        dist.push(element.p[0])
      }
    })
    let res = null
    const x1 = detectedFlags[0].x
    const x2 = detectedFlags[1].x

    const y1 = detectedFlags[0].y
    const y2 = detectedFlags[1].y

    if(x1 === x2){
      let yAns = [(y2*y2 - y1*y1 + dist[0]*dist[0] - dist[1]*dist[1])/(2*(y2-y1))]
      let xAns = [
        x1 + Math.sqrt(dist[0]*dist[0] - (yAns[0] - y1)*(yAns[0] - y1)),
        x1 - Math.sqrt(dist[0]*dist[0] - (yAns[0] - y1)*(yAns[0] - y1)),
      ]
      for(let i = 0; i < 2; i++){
        if(xAns[i] <= 54 && xAns[i] >= -54){
          res = {x: xAns[i].toFixed(1), y: -1*yAns[0].toFixed(1)}
        }
      }
    }else if(y1 === y2){
      let xAns = [(x2*x2 - x1*x1 + dist[0]*dist[0] - dist[1]*dist[1])/(2*(x2-x1))]
      let yAns = [
        y1 + Math.sqrt(dist[0]*dist[0] - (xAns[0] - x1)*(xAns[0] - x1)),
        y1 - Math.sqrt(dist[0]*dist[0] - (xAns[0] - x1)*(xAns[0] - x1))
      ]
      for(let i = 0; i < 2; i++){
        if(yAns[i] <= 32 && yAns[i] >= -32){
          res = {x: xAns[0].toFixed(1), y: -1*yAns[i].toFixed(1)}
        }
      }
    }else{
      const al = (y1 - y2)/(x2 - x1)
      const bl = (y2*y2 - y1*y1 + x2*x2 - x1*x1 + dist[0]*dist[0] - dist[1]*dist[1])/(2*(x2 - x1))

      const a = al*al + 1
      const b = -2*(al*(x1 - bl) + y1)
      const c = (x1 - bl)*(x1 - bl) + y1*y1 - dist[0]*dist[0]

      let yAns = [
        (-b + Math.sqrt(b*b - 4*a*c))/(2*a),
        (-b - Math.sqrt(b*b - 4*a*c))/(2*a)
      ]

      let xAns = [
        x1 + Math.sqrt(dist[0]*dist[0] - (yAns[0] - y1)*(yAns[0] - y1)),
        x1 - Math.sqrt(dist[0]*dist[0] - (yAns[0] - y1)*(yAns[0] - y1)),
        x1 + Math.sqrt(dist[0]*dist[0] - (yAns[1] - y1)*(yAns[1] - y1)),
        x1 - Math.sqrt(dist[0]*dist[0] - (yAns[1] - y1)*(yAns[1] - y1)),
      ]
      for(let i = 0; i < 2; i++){
        if(xAns[i] <= 54 && xAns[i] >= -54 && yAns[0] <= 32 && yAns[0] >= -32){
          res = {x: xAns[i].toFixed(1), y: -1*yAns[0].toFixed(1)}
        }
      }
      for(let i = 2; i < 4; i++){
        if(xAns[i] <= 54 && xAns[i] >= -54 && yAns[1] <= 32 && yAns[1] >= -32){
          res = {x: xAns[i].toFixed(1), y: -1*yAns[1].toFixed(1)}
        }
      }
    }
    return res
  }

  threeFlags(pArray, flags) {
    let detectedFlags = []
    let dist = []
    pArray.forEach(element => {
      if(element.cmd && detectedFlags.length < 3){
        if(element.cmd.p && flags[element.cmd.p.join('')] && 
            detectedFlags.filter((el) => el.x === flags[element.cmd.p.join('')].x).length < 2 &&
            detectedFlags.filter((el) => el.y === flags[element.cmd.p.join('')].y).length < 2){
          detectedFlags.push(flags[element.cmd.p.join('')])
          dist.push(element.p[0])
        }
      }
    })
    let res = null
    if(detectedFlags.length > 2){
      
      const x1 = detectedFlags[0].x
      const x2 = detectedFlags[1].x
      const x3 = detectedFlags[2].x

      const y1 = detectedFlags[0].y
      const y2 = detectedFlags[1].y
      const y3 = detectedFlags[2].y
      if(x1 === x2){
        let yAns = [(y2*y2 - y1*y1 + dist[0]*dist[0] - dist[1]*dist[1])/(2*(y2 - y1))]
        if(dist[0]*dist[0] - (yAns[0] - y1)*(yAns[0] - y1) > 0){
          let xAns = [
            x1 + Math.sqrt(dist[0]*dist[0] - (yAns[0] - y1)*(yAns[0] - y1)),
            x1 - Math.sqrt(dist[0]*dist[0] - (yAns[0] - y1)*(yAns[0] - y1))
          ]
          let err1 = Math.abs((xAns[0] - x3)*(xAns[0] - x3) + (yAns[0] - y3)*(yAns[0] - y3) - dist[2]*dist[2])
          let err2 = Math.abs((xAns[1] - x3)*(xAns[1] - x3) + (yAns[0] - y3)*(yAns[0] - y3) - dist[2]*dist[2])
          if(err1 - err2 >= 0){
            res = {
              x: xAns[1].toFixed(1),
              y: -1*yAns[0].toFixed(1)
            }
          }else{
            res = {
              x: xAns[0].toFixed(1),
              y: -1*yAns[0].toFixed(1)
            }
          }
        }
      }else if(x1 === x3){
        let yAns = [(y3*y3 - y1*y1 + dist[0]*dist[0] - dist[2]*dist[2])/(2*(y3 - y1))]
        if(dist[0]*dist[0] - (yAns[0] - y1)*(yAns[0] - y1) > 0){
          let xAns = [
            x1 + Math.sqrt(dist[0]*dist[0] - (yAns[0] - y1)*(yAns[0] - y1)),
            x1 - Math.sqrt(dist[0]*dist[0] - (yAns[0] - y1)*(yAns[0] - y1))
          ]
          let err1 = Math.abs((xAns[0] - x2)*(xAns[0] - x2) + (yAns[0] - y2)*(yAns[0] - y2) - dist[1]*dist[1])
          let err2 = Math.abs((xAns[1] - x2)*(xAns[1] - x2) + (yAns[0] - y2)*(yAns[0] - y2) - dist[1]*dist[1])
          if(err1 - err2 >= 0){
            res = {
              x: xAns[1].toFixed(1),
              y: -1*yAns[0].toFixed(1)
            }
          }else{
            res = {
              x: xAns[0].toFixed(1), 
              y: -1*yAns[0].toFixed(1)
            }
          }
        }
      }else if(x2 === x3){
        let yAns = [(y3*y3 - y2*y2 + dist[1]*dist[1] - dist[2]*dist[2])/(2*(y3 - y2))]
        if(dist[1]*dist[1] - (yAns[0] - y2)*(yAns[0] - y2) > 0){
          let xAns = [
            x2 + Math.sqrt(dist[1]*dist[1] - (yAns[0] - y2)*(yAns[0] - y2)),
            x2 - Math.sqrt(dist[1]*dist[1] - (yAns[0] - y2)*(yAns[0] - y2))
          ]
          if(xAns[0] >= -54 && xAns[0] <= 54){
            res = {
              x: xAns[0].toFixed(1), 
              y: -1*yAns[0].toFixed(1)
            }
          }else{
            res = {
              x: xAns[1].toFixed(1),
              y: -1*yAns[0].toFixed(1)
            }
          }
        }
      }else if(y1 === y2){
        let xAns = [(x2*x2 - x1*x1 + dist[0]*dist[0] - dist[1]*dist[1])/(2*(x2 - x1))]
        if(dist[0]*dist[0] - (xAns[0] - x1)*(xAns[0] - x1) > 0){
          let yAns = [
            y1 + Math.sqrt(dist[0]*dist[0] - (xAns[0] - x1)*(xAns[0] - x1)),
            y1 - Math.sqrt(dist[0]*dist[0] - (xAns[0] - x1)*(xAns[0] - x1))
          ]
          let err1 = Math.abs((xAns[0] - x3)*(xAns[0] - x3) + (yAns[0] - y3)*(yAns[0] - y3) - dist[2]*dist[2])
          let err2 = Math.abs((xAns[0] - x3)*(xAns[0] - x3) + (yAns[1] - y3)*(yAns[1] - y3) - dist[2]*dist[2])
          if(err1 - err2 >= 0){
            res = {
              x: xAns[0].toFixed(1), 
              y: -1*yAns[1].toFixed(1)
            }
          }else{
            res = {
              x: xAns[0].toFixed(1), 
              y: -1*yAns[0].toFixed(1)
            }
          }
        }
      }else if(y1 === y3){
        let xAns = [(x3*x3 - x1*x1 + dist[0]*dist[0] - dist[2]*dist[2])/(2*(x3 - x1))]
        if(dist[0]*dist[0] - (xAns[0] - x1)*(xAns[0] - x1) > 0){
          let yAns = [
            y1 + Math.sqrt(dist[0]*dist[0] - (xAns[0] - x1)*(xAns[0] - x1)),
            y1 - Math.sqrt(dist[0]*dist[0] - (xAns[0] - x1)*(xAns[0] - x1))
          ]
          let err1 = Math.abs((xAns[0] - x2)*(xAns[0] - x2) + (yAns[0] - y2)*(yAns[0] - y2) - dist[1]*dist[1])
          let err2 = Math.abs((xAns[0] - x2)*(xAns[0] - x2) + (yAns[1] - y2)*(yAns[1] - y2) - dist[1]*dist[1])
          if(err1 - err2 > 0){
            res = {
              x: xAns[0].toFixed(1), 
              y: -1*yAns[1].toFixed(1)
            }
          }else{
            res = {
              x: xAns[0].toFixed(1), 
              y: -1*yAns[0].toFixed(1)
            }
          }
        }
      }else if(y2 === y3){
        let xAns = [(x3*x3 - x2*x2 + dist[1]*dist[1] - dist[2]*dist[2])/(2*(x3 - x2))]
        if(dist[1]*dist[1] - (xAns[0] - x2)*(xAns[0] - x2) > 0){
          let yAns = [
            y1 + Math.sqrt(dist[1]*dist[1] - (xAns[0] - x2)*(xAns[0] - x2)),
            y1 - Math.sqrt(dist[1]*dist[1] - (xAns[0] - x2)*(xAns[0] - x2))
          ]
          if(yAns[0] >= -32 && yAns[0] >= 32){
            res = {
              x: xAns[0].toFixed(1),
              y: -1*yAns[0].toFixed(1)
            }
          }else{
            res = {
              x: xAns[0].toFixed(1),
              y: -1*yAns[1].toFixed(1)
            }
          }
        }
      }else{
        const a1 = (y1 - y2)/(x2 - x1)
        const b1 = (y2*y2 - y1*y1 + x2*x2 - x1*x1 + dist[0]*dist[0] - dist[1]*dist[1])/(2*(x2 - x1))

        const a2 = (y1 - y3)/(x3 - x1)
        const b2 = (y3*y3 - y1*y1 + x3*x3 - x1*x1 + dist[0]*dist[0] - dist[2]*dist[2])/(2*(x3 - x1))
        
        const y = (-1*(b1 - b2)/(a2 - a1)).toFixed(1)
        const x = (a1*y + b1).toFixed(1)
        res = {x, y}
      }
    }else{
      res = this.twoFlags(pArray, flags)
    }
    return res
  }

  distanceToPlayer(player, flags){
    let res = []
    res.push(player)
    flags.forEach((flag) => {
      let d1 = flag.p[0]
      let da = player.p[0]
      let da1 = Math.sqrt(Math.abs(
        d1**2 + da**2 -
          2 * da * d1 * Math.cos(Math.abs(flag.p[1] - player.p[1]) * Math.PI / 180)
      ))
      flag.p[0] = da1
      res.push(flag)
    })
    return res
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