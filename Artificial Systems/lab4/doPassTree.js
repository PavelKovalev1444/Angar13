const FL = "flag"
const PA = "pass"
const ST = "stay"

const DT = {
  name: 'pass',
  state: {
    N: 18,
    next: 0,
    kicked: false,
    sequence: [
      {
        act: FL, 
        fl: "fplc"
      },
      {
        act: PA, 
        fl: "b", 
        goal: "gr"
      },
      {
        act: ST
      }
    ],
    command: null
  },
  root: {
    exec(mgr, state) {
      state.action = state.sequence[state.next]
      state.command = null
    },
    next: "checkIsKicked"
  },
  checkIsKicked:{
    condition: (mgr, state) => state.kicked,
    trueCond: "sayCommand",
    falseCond: "chooseAction"
  },
  chooseAction:{
    condition: (mgr, state) => state.action.act != ST,
    trueCond: "goalVisible",
    falseCond: "stay"
  },
  goalVisible: {
    condition: (mgr, state) => mgr.getVisible(state.action.fl),
    trueCond: "rootNext",
    falseCond: "rotate"
  },
  rotate: {
    exec(mgr, state) {
      state.command = {
        n: "turn",
        v: "90"
      }
    },
    next: "sendCommand"
  },
  rootNext: {
    condition: (mgr, state) => state.action.act == FL,
    trueCond: "flagSeek",
    falseCond: "findBall"
  },
  stay:{
    exec(mgr, state) {
      state.command = {
        n: "turn",
        v: 0
      }
    },
    next: "sendCommand"
  },
  flagSeek: {
    condition: (mgr, state) => 3 > mgr.getDistance(state.action.fl),
    trueCond: "closeFlag",
    falseCond: "farGoal"
  },
  closeFlag: {
    exec(mgr, state) {
      state.next++
      state.action = state.sequence[state.next]
    },
    next: "rootNext"
  },
  farGoal: {
    condition: (mgr, state) => Math.abs(mgr.getAngle(state.action.fl)) > 4,
    trueCond: "rotateToGoal",
    falseCond: "runToGoal"
  },
  rotateToGoal: {
    exec(mgr, state) {
      state.command = {
        n: "turn",
        v: mgr.getAngle(state.action.fl)
      }
    },
    next: "sendCommand"
  },
  runToGoal: {
    exec(mgr, state){
      state.command = {
        n: "dash",
        v: 70
      }
    },
    next: "sendCommand"
  },
  findBall: {
    condition: (mgr, state) => mgr.getVisible(state.action.fl),
    trueCond: "checkBallAngle",
    falseCond: "rotateToSeekBall"
  },
  checkBallAngle: {
    condition: (mgr, state) => Math.abs(mgr.getAngle(state.action.fl)) < 4,
    trueCond: "checkBallDistance",
    falseCond: "rotateToBall"
  },
  checkBallDistance: {
    condition: (mgr, state) => mgr.getDistance(state.action.fl) < 5,
    trueCond: "runSlowOrStop",
    falseCond: "runFast"
  },
  runSlowOrStop: {
    condition: (mgr, state) => mgr.getDistance(state.action.fl) < 0.5,
    trueCond: "isComradeNear",
    falseCond: "runSlow"
  },
  runSlow:{
    exec(mgr, state){
      state.command = {
        n: "dash",
        v: 30
      }
    },
    next: "sendCommand"
  },
  runFast:{
    exec(mgr, state){
      state.command = {
        n: "dash",
        v: 70
      }
    },
    next: "sendCommand"
  },
  isComradeNear: {
    condition: (mgr, state) => mgr.isComradeHere(),
    trueCond: "getAngleOfComrade",
    falseCond: "waitOrRotate"
  },
  getAngleOfComrade:{
    exec(mgr, state){
      state.comradeAngle = mgr.getComradeAngle()
    },
    next: "checkComradeAngle"
  },
  checkComradeAngle: {
    condition: (mgr, state) => state.comradeAngle !== -444,
    trueCond: "kickToComrade",
    falseCond: "waitOrRotate"
  },
  kickToComrade: {
    exec(mgr, state){
      console.log('state.comradeAngle = ', state.comradeAngle)
      state.kicked = true
      state.command = {
        n: "kick",
        v: `65 ${state.comradeAngle - 15}`
      }
    },
    next: "sendCommand"
  },
  sayCommand:{
    exec(mgr, state){
      state.next++
      state.action = state.sequence[state.next]
      state.kicked = false
      state.command = {
        n: "say",
        v: "catch*my*goal*tovarisch"
      }
    },
    next: "sendCommand"
  },
  waitOrRotate: {
    condition: (mgr, state) => state.N > 0,
    trueCond: "wait",
    falseCond: "rotateToFindComrade"
  },
  wait: {
    exec(mgr, state){
      state.N -= 1
      state.command = {
        n: "turn",
        v: 0
      }
    },
    next: "sendCommand"
  },
  rotateToFindComrade: {
    exec(mgr, state){
      state.command = {
        n: "kick",
        v: `10 -30`
      }
    },
    next: "sendCommand"
  },
  runToBall: {
    exec(mgr, state){
      state.command = {
        n: "dash",
        v: 80
      }
    },
    next: "sendCommand"
  },
  rotateToBall: {
    exec(mgr, state) {
      state.command = {
        n: "turn",
        v: mgr.getAngle(state.action.fl)
      }
    },
    next: "sendCommand"
  },
  rotateToSeekBall: {
    exec(mgr, state) {
      state.command = {
        n: "turn",
        v: 45
      }
    },
    next: "sendCommand"
  },
  sendCommand: {
    command: (mgr, state) => state.command
  }
}
module.exports = DT
