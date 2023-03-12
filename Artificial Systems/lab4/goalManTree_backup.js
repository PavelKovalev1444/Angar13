const FL = "flag"
const KI = "kick"
const goalManDT = {
  state: {
    next: 0,
    sequence: [
      {
          act: FL,
          fl: 'gr'
      },
      {
          act: KI,
          fl: 'b',
          goal: 'fc'
      }
    ],
    command: null
  },
  root: {
    exec(mgr, state) {
      state.action = state.sequence[state.next]
      state.command = null
    },
    next: "goalVisible"
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
        v: "30"
      }
    },
    next: "sendCommand"
  },
  rootNext: {
    condition: (mgr, state) => state.action.act == FL,
    trueCond: "flagSeek",
    falseCond: "isInsideArea"
  },
  isInsideArea: {
    condition: (mgr, state) => {
      let pos = mgr.getPos()
      if(pos){
        return (pos.x >= 30 && Math.abs(pos.y) <= 20)
      }else{
        return true
      }       
    },
    trueCond: "ballVisible",
    falseCond: "returnToGoal"
  },
  flagSeek: {
    condition: (mgr, state) => mgr.getDistance(state.action.fl) < 5,
    trueCond: 'closeFlag',
    falseCond: 'farFlag'
  },
  closeFlag: {
    exec(mgr, state) {
      state.next++
      state.action = state.sequence[state.next]
    },
    next: "rootNext"
  },
  farFlag: {
    condition: (mgr, state) => mgr.getAngle(state.action.fl) < 5,
    trueCond: 'runToFlag',
    falseCond: 'rotateToFlag'
  },
  runToFlag: {
    exec(mgr, state) {
      state.command = {
        n: "dash",
        v: "100"
      }
    },
    next: "sendCommand"
  },
  rotateToFlag: {
    exec(mgr, state) {
      state.command = {
        n: "turn",
        v: mgr.getAngle(state.action.fl)
      }
    },
    next: "sendCommand"
  },
  ballVisible: {
    condition: (mgr, state) => mgr.getVisible(state.action.fl),
    trueCond: 'checkBallDistance',
    falseCond: 'rotate'
  },
  checkBallDistance: {
    condition: (mgr, state) => mgr.getDistance(state.action.fl) < 32,
    trueCond: 'isBallNear',
    falseCond: 'returnToGoal'
  },
  isBallNear: {
    condition: (mgr, state) => mgr.getDistance(state.action.fl) < 3,
    trueCond: 'canCatchBall',
    falseCond: 'angleToRunToBall'
  },
  canCatchBall: {
    condition: (mgr, state) => mgr.getDistance(state.action.fl) < 2,
    trueCond: 'catchBall',
    falseCond: 'kickBall'
  },
  catchBall: {
    exec(mgr, state) {
      state.command = {
        n: "catch",
        v: mgr.getAngle(state.action.fl)
      }
    },
    next: "sendCommand"
  },
  kickBall: {
    condition: (mgr, state) => mgr.getVisible(state.action.goal),
    trueCond: 'canSeeGoal',
    falseCond: 'cannotSeeGoal'
  },
  canSeeGoal: {
    exec(mgr, state) {
      state.command = {
        n: "kick",
        v: `55 45` // пофиксить удары по направлению к воротам соперников
      }
    },
    next: "sendCommand"
  },
  cannotSeeGoal: {
    exec(mgr, state) {
      state.command = {
        n: "kick",
        v: '55 45'
      }
    },
    next: "sendCommand"
  },
  angleToRunToBall: {
    condition: (mgr, state) => mgr.getAngle(state.action.fl) < 5,
    trueCond: 'runToBall',
    falseCond: 'rotateToRunToBall'
  },
  runToBall: {
    exec(mgr, state) {
      state.command = {
        n: "dash",
        v: '90'
      }
    },
    next: "sendCommand"
  },
  rotateToRunToBall: {
    exec(mgr, state) {
      state.command = {
        n: "turn",
        v: mgr.getAngle(state.action.fl)
      }
    },
    next: "sendCommand"
  },
  returnToGoal: {
    exec(mgr, state) {
      state.command = null
      state.next = 0
    },
    next: "root"
  },
  sendCommand: {
      command: (mgr, state) => state.command
  }
}
module.exports = goalManDT
