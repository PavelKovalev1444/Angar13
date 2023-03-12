const positionLocator = require('./positionLocator')

module.exports = {
  getAction(dt, p) {
    this.p = p
    function execute(dt, title, Manager) {
      if(dt.name === 'doGoal'){
        console.log('title = ', title)
      }
      const action = dt[title]
      if(typeof action.exec == "function"){
        action.exec(Manager, dt.state)
        return execute(dt, action.next, Manager)
      }
      if(typeof action.condition == "function"){
        const cond = action.condition(Manager, dt.state)
        if(cond){
          return execute(dt, action.trueCond, Manager)
        }
        return execute(dt, action.falseCond, Manager)
      }
      if(typeof action.command == "function"){
        return action.command(Manager, dt.state)
      }
      throw new Error(`Unexpected node in DT: ${title}`)
    }
    return execute(dt, "root", this)
  },
  getVisible(obj){
    //console.log('getVisible')
    //console.log('obj = ', obj)
    let objects = null
    if(obj === 'p'){
      objects = this.p.find(el => el.cmd && el.cmd.p[0] === obj)
      //console.log('objects = ', objects)
      //console.log('================')
      return Boolean(objects)
    }else{
      objects = this.p.find(el => el.cmd && el.cmd.p.join('') === obj)
      //console.log('objects = ', objects)
      //console.log('================')
      return Boolean(objects)
    }
  },
  getDistance(obj){
    //console.log('getDistance')
    //console.log('obj = ', obj)
    let objects = null
    if(obj === 'p'){
      objects = this.p.find(el => el.cmd && el.cmd.p[0] === obj)
    }else{
      objects = this.p.find(el => el.cmd && el.cmd.p.join('') === obj)
    }
    //console.log('objects = ', objects)
    if(objects){
      if(objects.p.length > 1){
        //console.log(objects.p[0])
        //console.log('objects.p[0] = ', objects.p[0])
        //console.log('================')
        return objects.p[0]
      }else{
        //console.log('objects.p[0] = ', null)
        //console.log('================')
        return null
      }
    }else{
      //console.log('objects.p[0] = ', null)
      //console.log('================')
      return null
    }
  },
  getAngle(obj) {
    //console.log('================')
    //console.log('getAngle')
    //console.log('obj = ', obj)
    let objects = null
    if(obj === 'p'){
      objects = this.p.find(el => el.cmd && el.cmd.p[0] === obj)
    }else{
      objects = this.p.find(el => el.cmd && el.cmd.p.join('') === obj)
    }
    //console.log('objects = ', objects)
    if(objects){
      if(objects.p.length === 1){
        //console.log('objects.p[0] = ', objects.p[0])
        //console.log('================')
        return objects.p[0]
      }else{
        //console.log('objects.p[1] = ', objects.p[1])
        //console.log('================')
        return objects.p[1]
      }
    }else{
      return null
    }
  },
  getPos() {
    const visibleFlags = this.p.filter((obj) => obj.cmd && (obj.cmd.p[0] === 'f'))
    let curPos = null
    if(visibleFlags.length > 1){
      curPos = positionLocator.threeFlags(visibleFlags)
      if(curPos){
        curPos.x = curPos.x - 0
        curPos.y = curPos.y - 0
      }
    }
    //console.log(curPos)
    //console.log('=================')
    return curPos
  },
  isInsideArea(){
    let pos = this.getPos()
    let res = null
    if(pos){
      console.log(pos)
      res = pos.x > 30 && Math.abs(pos.y) < 16
    }
    //console.log('isInsideArea = ', res)
    return res
  },
  isComradeHere(){
    let players = this.p.filter(el => el.cmd && el.cmd.p[0] === 'p')
    let res = false
    //console.log('isComradeHere')
    if(players){
      //console.log(players)
      players.forEach(player => {
        //console.log('player = ', player)
        if(player.cmd.p.length > 1){
          //console.log('player.cmd = ', player.cmd)
          if(player.cmd.p[1] === `"A"`){
            //console.log('player.cmd.p = ', player.cmd.p)
            res = true
          }
        }
      });
    }
    //console.log('res = ', res)
    return res
  },
  getComradeAngle() {
    let players = this.p.filter(el => el.cmd && el.cmd.p[0] === 'p')
    let res = -444
    //console.log('getComradeAngle')
    if(players){
      //console.log(players)
      players.forEach(player => {
        //console.log('player = ', player)
        if(player.cmd.p.length > 1){
          //console.log('player.cmd = ', player.cmd)
          if(player.cmd.p[1] === `"A"`){
            //console.log('player.cmd.p = ', player.cmd.p)
            res = player.p[1]
            //console.log('res = ', res)
            return res
          }
        }
      });
    }
    return res
  }
}
