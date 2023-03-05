const DT = {
  state: {
    head: 'p',
    command: null
  },
  root: {
    exec(mgr, state) {
      state.command = null
    },
    next: "playerVisible"
  },
  playerVisible: {
    condition: (mgr, state) => mgr.getVisible(state.head),
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
    condition: (mgr, state) => mgr.getDistance(state.head) < 1 && Math.abs(mgr.getAngle(state.head)) < 40,
    trueCond: "playerIsNear",
    falseCond: "playerIsFar"
  },
  playerIsNear: {
    exec(mgr, state) {
      state.command = {
        n: "turn",
        v: "30"
      }
    },
    next: "sendCommand"
  },
  playerIsFar: {
    condition: (mgr, state) => mgr.getDistance(state.head) > 10,
    trueCond: "playerCatchingUp",
    falseCond: "rotateToFindPlayer"
  },
  playerCatchingUp: {
    condition: (mgr, state) => Math.abs(mgr.getAngle(state.head)) > 5,
    trueCond: "turnToPlayer",
    falseCond: "runToPlayer"
  },
  turnToPlayer: {
    exec(mgr, state) {
      state.command = {
        n: "turn",
        v: mgr.getAngle(state.head)
      }
    },
    next: "sendCommand"
  },
  runToPlayer: {
    exec(mgr, state) {
      state.command = {
        n: "dash",
        v: "80"
      }
    },
    next: "sendCommand"
  },
  rotateToFindPlayer: {
    condition: (mgr, state) => {
      let angle = mgr.getAngle(state.head);
      if(angle > 40 || angle < 25){
        return true
      }else{
        return false
      }
    },
    trueCond: "make30turn",
    falseCond: "makeLittleRun"
  },
  make30turn: {
    exec(mgr, state) {
      state.command = {
        n: "turn",
        v: mgr.getAngle(state.head) - 30
      }
    },
    next: "sendCommand"
  },
  makeLittleRun: {
    condition: (mgr, state) => mgr.getDistance(state.head) < 7,
    trueCond: "make20Run",
    falseCond: "make40Run"
  },
  make20Run: {
    exec(mgr, state) {
      state.command = {
        n: "dash",
        v: "20"
      }
    },
    next: "sendCommand"
  },
  make40Run: {
    exec(mgr, state) {
      state.command = {
        n: "dash",
        v: "40"
      }
    },
    next: "sendCommand"
  },
  sendCommand: {
    command: (mgr, state) => state.command
  }
}
module.exports = DT