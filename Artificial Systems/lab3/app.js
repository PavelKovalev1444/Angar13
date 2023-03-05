const readline = require('readline');
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});
const Agent = require('./agent')
const VERSION = 7

function createAgent(coords, rotationSpeed, teamName, position){
  let agent = new Agent(rotationSpeed, position, teamName)
  require('./socket')(agent, teamName, VERSION)
  if(position === 'l'){
    let leftCoords = coords.split(' ')
    if(leftCoords[0][0] !== '-'){
      leftCoords[0] = '-' + leftCoords[0]
    }
    leftCoords = leftCoords.join(' ')
    setTimeout(() => agent.socketSend("move", leftCoords), 200)
  }else{
    let rightCoords = coords.split(' ')
    if(rightCoords[0][0] !== '-'){
      rightCoords[0] = '-' + rightCoords[0]
    }
    rightCoords = rightCoords.join(' ')
    setTimeout(() => agent.socketSend("move", rightCoords), 200)
  }
}

createAgent('-15 0', 30, 'A', 'l')
//createAgent('-20 10', 30, 'A', 'l')
createAgent('-40 0', 30, 'B', 'r')