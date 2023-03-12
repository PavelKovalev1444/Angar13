const FL = "flag"
const KI = "kick"
const DT = {
  name: 'doGoal',
  state: {
    next: 0,
    sequence: [
      {
        act: FL, 
        fl: "fplb"
      },
      {
        act: FL, 
        fl: "fgrb"
      },
      {
        act: KI, 
        fl: "b", 
        goal: "gr"
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
        v: "90"
      }
    },
    next: "sendCommand"
  },
  rootNext: {
    condition: (mgr, state) => state.action.act === FL,
    trueCond: "isFlagVisible",
    falseCond: "ballSeek"
  },
  isFlagVisible: {
    condition: (mgr, state) => mgr.getVisible(state.action.fl),
    trueCond: "flagSeek",
    falseCond: "rotate"
  },
  flagSeek: {
    condition: (mgr, state) => 4 > Math.abs(mgr.getAngle(state.action.fl)),
    trueCond: "checkFlagDistance",
    falseCond: "rotateToGoal"
  },
  checkFlagDistance: {
    condition: (mgr, state) => 5 > mgr.getDistance(state.action.fl),
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
        v: 90
      }
    },
    next: "sendCommand"
  },
  ballSeek: {
    condition: (mgr, state) => mgr.getVisible(state.action.fl),
    trueCond: "checkAngleToBall",
    falseCond: "rotateToFindBall"
  },
  checkAngleToBall: {
    condition: (mgr, state) => Math.abs(mgr.getAngle(state.action.fl)) < 4,
    trueCond: "checkDistanceToBall",
    falseCond: "rotateToBall"
  },
  checkDistanceToBall: {
    condition: (mgr, state) => mgr.getDistance(state.action.fl) < 0.5,
    trueCond: "isGoalVisible",
    falseCond: "runToBall"
  },
  isGoalVisible: {
    condition: (mgr, state) => mgr.getVisible(state.action.goal),
    trueCond: "checkAngleToGoal",
    falseCond: "rotateToFindGoal"
  },
  checkAngleToGoal: {
    condition: (mgr, state) => Math.abs(mgr.getAngle(state.action.goal)) < 10,
    trueCond: "checkDistanceToGoal",
    falseCond: "kickToGoal"
  },
  checkDistanceToGoal: {
    condition: (mgr, state) => Math.abs(mgr.getAngle(state.action.goal)) < 20,
    trueCond: "kickStrongToGoal",
    falseCond: "kickWeakToGoal"
  },
  kickStrongToGoal:{
    exec(mgr, state) {
      state.command = {
        n: "kick",
        v: `90 ${mgr.getAngle(state.action.goal)}`
      }
    },
    next: "sendCommand"
  },
  kickWeakToGoal:{
    exec(mgr, state) {
      state.command = {
        n: "kick",
        v: `30 ${mgr.getAngle(state.action.goal)}`
      }
    },
    next: "sendCommand"
  },
  kickToGoal:{
    exec(mgr, state) {
      state.command = {
        n: "kick",
        v: `10 ${mgr.getAngle(state.action.goal)}`
      }
    },
    next: "sendCommand"
  },
  rotateToFindGoal: {
    exec(mgr, state) {
      state.command = {
        n: "kick",
        v: '10 45'
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
  rotateToFindBall: {
    exec(mgr, state) {
      state.command = {
        n: "turn",
        v: 45
      }
    },
    next: "sendCommand"
  },
  runToBall: {
    exec(mgr, state) {
      state.command = {
        n: "dash",
        v: 80
      }
    },
    next: "sendCommand"
  },
  sendCommand: {
    command: (mgr, state) => state.command
  }
}
module.exports = DT
