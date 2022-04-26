const canvas1 = document.getElementById("board");
const ctx = canvas1.getContext("2d");
const canvas2 = document.getElementById("cur_figur");
const ctxCurFigur = canvas2.getContext("2d");

function chooseFigure(){
	let fig = Math.floor(Math.random() * (6)) + 0;
	let curFigM;
    switch(fig){
		case 0:
			curFigM = [[0,0,0,0],
			  		   [1,1,1,1],
			           [0,0,0,0],
			           [0,0,0,0]];
			                    
			currentTetraminoRow = -1;
			currentTetraminoCol = fieldArray[0].length / 2 - Math.ceil(curFigM[0].length / 2);

			figType = "I"; 
			break;
		case 1:
			curFigM = [[1,1],
			  		   [1,1]];   		   
			currentTetraminoRow = -2;
			currentTetraminoCol = fieldArray[0].length / 2 - Math.ceil(curFigM[0].length / 2);

			figType = "O"; 
			break;
		case 2:
			curFigM = [[0,1,0],
			  		   [0,1,0],
			           [0,1,1]];			        			
			currentTetraminoRow = -2;
			currentTetraminoCol = fieldArray[0].length / 2 - Math.ceil(curFigM[0].length / 2);

			figType = "L";          
			break;
		case 3:
			curFigM = [[0,1,0],
			  		   [0,1,1],
			           [0,0,1]];
			currentTetraminoRow = -2;
			currentTetraminoCol = fieldArray[0].length / 2 - Math.ceil(curFigM[0].length / 2);

			figType = "Z";         
			break;
		case 4:
			curFigM = [[0,0,1],
			  		   [0,1,1],
			           [0,1,0]];
			           
			currentTetraminoRow = -2;
			currentTetraminoCol = fieldArray[0].length / 2 - Math.ceil(curFigM[0].length / 2);

			figType = "S";           
			break;
		case 5:
			curFigM = [[0,0,1],
			  		   [0,0,1],
			           [0,1,1]];
			currentTetraminoRow = -2;
			currentTetraminoCol = fieldArray[0].length / 2 - Math.ceil(curFigM[0].length / 2);         
			figType = "J"; 
			break;
		case 6:	
			curFigM = [[0,1,0],
				       [1,1,1],
				       [0,0,0]];
			currentTetraminoRow = -2;
			currentTetraminoCol = fieldArray[0].length / 2 - Math.ceil(curFigM[0].length / 2);
			figType = "T";         
			break;	
	}
	return {
        figType: figType,      
        curFig: curFigM,  
        row: currentTetraminoRow,        
        col: currentTetraminoCol     
      };
}

document.body.onkeydown = function (e) {
    var keys = {
        37: "left",
        38: "rotate",
        39: "right",
        40: "down"
    };
    if (typeof(keys[e.keyCode]) != "undefined"){
        keyPressEvent(keys[e.keyCode]);
        drawField(currentTetramino.row, currentTetramino.col);
    }
}

function keyPressEvent(key){
	switch(key){
		case "left":
			if(canMove(canMove(currentTetramino.curFig, currentTetramino.row, currentTetramino.col - 1))){
				currentTetramino.col--;
			}
			break;
		case "rotate":
			let rotatedFig = rotateRight90(currentTetramino.curFig);
			if(canMove(rotatedFig, currentTetramino.row, currentTetramino.col)){
				currentTetramino.curFig = rotatedFig;
			}
			break;
		case "right":
			if(canMove(currentTetramino.curFig, currentTetramino.row, currentTetramino.col + 1)){
				currentTetramino.col++;
			}
			break;
		case "down":
			if(canMove(currentTetramino.curFig, currentTetramino.row + 1, currentTetramino.col)){
				currentTetramino.row++;
			}
			break;	
	}
}

function rotateRight90(matrix) {
	let result = [];
  	for (let i = matrix.length - 1; i >= 0; i--) {
    	for (let j = 0; j < matrix[i].length; j++) {
      		if (!result[j]) {
        		result[j] = [];
      		}
      		result[j].push(matrix[i][j]);
    	}
  	}
  	return result;
}

function canMove(figMatrix, figRow, figCol){
    for (let row = 0; row < figMatrix.length; row++) {
    	for (let col = 0; col < figMatrix[row].length; col++) {
        	//if(figMatrix[row][col] && fieldArray[figRow + row][figCol + col]){
        		if (figMatrix[row][col] && (
              		figCol + col < 0 ||
              		figCol + col >= fieldArray[0].length ||
              		figRow + row >= fieldArray.length ||
              		fieldArray[figRow + row][figCol + col])
            	){
            	return false;
          	//	}
          	}
        }
    }
  return true;
}

function drawField(row, col){
	ctx.clearRect(0, 0, canvas1.width, canvas1.height);
	ctx.fillStyle = "purple";
    ctx.strokeStyle = "black";
	for(let i = 0; i < fieldArray.length; i++){
		for(let j = 0; j < fieldArray[i].length; j++){
			if(fieldArray[i][j]){
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}
		}
	}

	for(let i = row; i < row + currentTetramino.curFig.length; i++){
		for(let j = col; j < col + currentTetramino.curFig[i - row].length; j++){
			if(i < 0 || j < 0){
				continue;
			}
			if(fieldArray[i][j] == 0 && currentTetramino.curFig[i-row][j-col] == 1){
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}
		}
	}
}

			
function drawTetraminoOnSmallBoard(figure){
	let width = 100;
	let height = 100;
    let block_width = 25;
    let block_height = 25;
    ctxCurFigur.fillStyle = "purple";
    ctxCurFigur.strokeStyle = "black";
    ctxCurFigur.clearRect(0, 0, canvas2.width, canvas2.height);
    for (let y = 0; y < figure.curFig.length; y++){
        for (let x = 0; x < figure.curFig[y].length; x++){
            if (figure.curFig[y][x]){
            	ctxCurFigur.fillRect(25*x,25*y,25,25);
            	ctxCurFigur.strokeRect(25*x,25*y,25,25);
            }
        }
    }
}

function blockFigure(){
	for (let row = 0; row < currentTetramino.curFig.length; row++) {
    	for (let col = 0; col < currentTetramino.curFig[row].length; col++) {
      		if (currentTetramino.curFig[row][col]) {
        		if (currentTetramino.row + row < 0) {
          			alert("Game over");
        		}
        		fieldArray[currentTetramino.row + row][currentTetramino.col + col] = 1;
      		}
    	} 
  	}

	for(let row = fieldArray.length - 1; row >= 0; ){
    	if(fieldArray[row].every(elem => elem == 1)){
    		for (let i = row; i >= 0; i--) {
        		for (let j = 0; j < fieldArray[i].length; j++) {
          			fieldArray[i][j] = fieldArray[i-1][j];
        		}
   	   		}
    	}else {
      		row--;
    	}
  }
}

function play(){
	if(!canMove(currentTetramino.curFig, currentTetramino.row + 1, currentTetramino.col)){
		blockFigure();
		start();
	}else{
		currentTetramino.row += 1;
		drawField(currentTetramino.row, currentTetramino.col);
	}
}

function start(){
	clearInterval(inter)
	currentTetramino = chooseFigure();
	console.log("start currentTetramino.row = ", currentTetramino.row, "start currentTetramino.col = ", currentTetramino.col);
	drawTetraminoOnSmallBoard(currentTetramino);
	drawField(currentTetramino.row, currentTetramino.col);


	inter = setInterval(() => play(), 1000);
}

let playerName = localStorage["tetris.username"];
let curLevel = 1;
let gameOver = false;
let points = 0;
let inter;

document.getElementById("player_name").innerHTML = playerName;
document.getElementById("current_level").innerHTML = curLevel;

var rows = 24;
var cols = 16;
var fieldArray = Array(rows).fill(Array(cols).fill(0));

var currentTetramino, currentTetraminoCol, currentTetraminoRow;

start();