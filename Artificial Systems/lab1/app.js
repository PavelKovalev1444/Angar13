const readline = require('readline');
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});
const Agent = require('./agent')
const VERSION = 7

function createAgent(coords, rotationSpeed, teamName, position){
  let agent = new Agent(rotationSpeed, position)
  require('./socket')(agent, teamName, VERSION)
//agent.socketSend("move", coords) Вводим x с минусом
  agent.socketSend("move", `-${coords}`) //Вводим x без минуса
}

rl.question('Начальные координаты игрока: ', (coordsPlayer) => {
  rl.question('Скорость вращения игрока: ', (rotationSpeedPlayer) => {
    rl.question('Имя команды игрока: ', (teamNamePlayer) => {
      rl.question('Начальные координаты противника: ', (coordsEnemy) => {
        rl.question('Скорость вращения противника: ', (rotationSpeedEnemy) => {
          rl.question('Имя команды противника: ', (teamNameEnemy) => {
            createAgent(coordsPlayer, rotationSpeedPlayer, teamNamePlayer, 'l')
            createAgent(coordsEnemy, rotationSpeedEnemy, teamNameEnemy, 'r')
            rl.close()
          })
        })
      });
    })
  })
});