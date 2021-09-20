const canvas1 = document.getElementById("board");
const ctx = canvas1.getContext("2d");
const canvas2 = document.getElementById("cur_figur");
const ctxCurFigur = canvas2.getContext("2d");

function chooseFigure(){
	let fig = Math.floor(Math.random() * (6)) + 0;
	var curFigM;
	switch(fig){
		case 0:
			curFigM = [[0,0,0,0],
			  		   [1,1,1,1],
			           [0,0,0,0],
			           [0,0,0,0]];          
			currentTetraminoRow = 0;
			currentTetraminoCol = fieldArray[0].length/2;
			figType = "I"; 
			break;
		case 1:
			curFigM = [[0,0,0,0],
			  		   [0,1,1,0],
			           [0,1,1,0],
			           [0,0,0,0]];
			currentTetraminoRow = 1;
			currentTetraminoCol = fieldArray[0].length/2;
			figType = "O"; 
			break;
		case 2:
			curFigM = [[0,1,0,0],
			  		   [0,1,0,0],
			           [0,1,1,0],
			           [0,0,0,0]];
			currentTetraminoRow = 2;
			currentTetraminoCol = fieldArray[0].length/2; 
			figType = "L";          
			break;
		case 3:
			curFigM = [[0,1,0,0],
			  		   [0,1,1,0],
			           [0,0,1,0],
			           [0,0,0,0]];
			currentTetraminoRow = 2;
			currentTetraminoCol = fieldArray[0].length/2;  
			figType = "Z";         
			break;
		case 4:
			curFigM = [[0,0,1,0],
			  		   [0,1,1,0],
			           [0,1,0,0],
			           [0,0,0,0]];
			currentTetraminoRow = 2;
			currentTetraminoCol = fieldArray[0].length/2;
			figType = "S";           
			break;
		case 5:
			curFigM = [[0,0,1,0],
			  		   [0,0,1,0],
			           [0,1,1,0],
			           [0,0,0,0]];
			currentTetraminoRow = 2;
			currentTetraminoCol = fieldArray[0].length/2;          
			figType = "J"; 
			break;
		case 6:	
			curFigM = [[0,0,0,0],
				       [0,0,1,0],
			           [0,1,1,1],
			           [0,0,0,0]];
			currentTetraminoRow = 1;
			currentTetraminoCol = fieldArray[0].length/2; 
			figType = "T";         
			break;	
	}
	return {
        figType: figType,      // название фигуры (L, O, и т.д.)
        curFig: curFigM,  // матрица с фигурой
        row: currentTetraminoRow,        // текущая строка (фигуры стартую за видимой областью холста)
        col: currentTetraminoCol         // текущий столбец
      };;
}

document.body.onkeydown = function (e) {
    var keys = {
        37: "left",
        38: "rotate",
        39: "right",
        40: "down"
    };
    if (typeof(keys[e.keyCode]) != "undefined"){
    	//console.log("Key activated: ", keys[e.keyCode]);
        keyPressEvent(keys[e.keyCode]);
        drawField(currentTetramino.row, currentTetramino.col);
    }
}

function keyPressEvent(key){
	switch(key){
		case "left":
			if(canMove(currentTetramino)){
				currentTetramino.col--;
			}
			break;
		/*case "rotate":
			if(canMove(currentTetramino, currentTetraminoRow, currentTetraminoCol)){
				currentTetraminoCol--;
			}
			break;*/
		case "right":
			if(canMove(currentTetramino)){
				currentTetramino.col++;
			}
			break;
		case "down":
			if(canMove(currentTetramino)){
				currentTetramino.row++;
			}
			break;
	}
}

function canMove(tetramino) {
	for (let row = 0; row < fieldArray.length; row++) {
    	for (let col = 0; col < fieldArray[row].length; col++) {
      		if (matrix[row][col] && (
          		cellCol + col < 0 ||
          		cellCol + col >= fieldArray[0].length ||
          		cellRow + row >= fieldArray.length ||
          		fieldArray[cellRow + row][cellCol + col])
        		) {
        			return false;
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

	for(let i = 0; i < fieldArray.length; i++){
		for(let j = 0; j < fieldArray[i].length; j++){
			if(fieldArray[i][j]){
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}
		}
	}
	switch(currentTetramino.figType){
		case "I":  
            ctx.fillRect(25*col,25*row,25,25);
            ctx.strokeRect(25*col,25*row,25,25);

            ctx.fillRect(25*(col+1), 25*row,25,25);
            ctx.strokeRect(25*(col+1), 25*row,25,25);

            ctx.fillRect(25*(col-1),25*row,25,25);
            ctx.strokeRect(25*(col-1),25*row,25,25);

            ctx.fillRect(25*(col-2),25*row,25,25);
            ctx.strokeRect(25*(col-2),25*row,25,25);
			break;
		case "J":
            ctx.fillRect(25*col,25*row,25,25);
            ctx.strokeRect(25*col,25*row,25,25);

            ctx.fillRect(25*(col - 1), 25*row,25,25);
            ctx.strokeRect(25*(col - 1), 25*row,25,25);

            ctx.fillRect(25*col,25*(row - 1),25,25);
            ctx.strokeRect(25*col,25*(row - 1),25,25);

            ctx.fillRect(25*col,25*(row-2),25,25);
            ctx.strokeRect(25*col,25*(row-2),25,25);
			break;
		case "O":  
            ctx.fillRect(25*col,25*row,25,25);
            ctx.strokeRect(25*col,25*row,25,25);

            ctx.fillRect(25*(col-1),25*row,25,25);
            ctx.strokeRect(25*(col-1),25*row,25,25);

            ctx.fillRect(25*col,25*(row-1),25,25);
            ctx.strokeRect(25*col,25*(row-1),25,25);

            ctx.fillRect(25*(col-1),25*(row-1),25,25);
            ctx.strokeRect(25*(col-1),25*(row-1),25,25);
			break;
		case "L":
            ctx.fillRect(25*col,25*row,25,25);
            ctx.strokeRect(25*col,25*row,25,25);

            ctx.fillRect(25*(1+col), 25*row,25,25);
            ctx.strokeRect(25*(1+col), 25*row,25,25);

            ctx.fillRect(25*col,25*(row - 1),25,25);
            ctx.strokeRect(25*col,25*(row - 1),25,25);

            ctx.fillRect(25*col,25*(row - 2),25,25);
            ctx.strokeRect(25*col,25*(row - 2),25,25);
			break;
		case "S":
            ctx.fillRect(25*(col-1),25*row,25,25);
            ctx.strokeRect(25*(col-1),25*row,25,25);

            ctx.fillRect(25*col, 25*(row - 1),25,25);
            ctx.strokeRect(25*col, 25*(row - 1),25,25);

            ctx.fillRect(25*(col-1),25*(row - 1),25,25);
            ctx.strokeRect(25*(col-1),25*(row - 1),25,25);

            ctx.fillRect(25*col,25*(row - 2),25,25);
            ctx.strokeRect(25*col,25*(row - 2),25,25);
			break;
		case "Z":
            ctx.fillRect(25*col,25*row,25,25);
            ctx.strokeRect(25*col,25*row,25,25);

            ctx.fillRect(25*col, 25*(row - 1),25,25);
            ctx.strokeRect(25*col, 25*(row - 1),25,25);

            ctx.fillRect(25*(col-1),25*(row -1),25,25);
            ctx.strokeRect(25*(col-1),25*(row -1),25,25);

            ctx.fillRect(25*(col-1),25*(row-2),25,25);
            ctx.strokeRect(25*(col-1),25*(row-2),25,25);
			break;
		case "T":
            ctx.fillRect(25*col,25*row,25,25);
            ctx.strokeRect(25*col,25*row,25,25);

            ctx.fillRect(25*(1+col), 25*row,25,25);
            ctx.strokeRect(25*(1+col), 25*row,25,25);

            ctx.fillRect(25*(col-1),25*row,25,25);
            ctx.strokeRect(25*(col-1),25*row,25,25);

            ctx.fillRect(25*col,25*(row-1),25,25);
            ctx.strokeRect(25*col,25*(row-1),25,25);
			break;
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
    for (let y = 0; y < 4; y++){
        for (let x = 0; x < 4; x++){
            if (figure.curFig[y][x]){
            	ctxCurFigur.fillRect(25*x,25*y,25,25);
            	ctxCurFigur.strokeRect(25*x,25*y,25,25);
            }
        }
    }
}

function blockFigure(){
	switch(currentTetramino.figType){
		case "I":  
			fieldArray[row][col] = 1;
			fieldArray[row][col+1] = 1;
			fieldArray[row][col-1] = 1;
			fieldArray[row][col-2] = 1;
			break;
		case "J":
			fieldArray[row][col] = 1;
			fieldArray[row][col-1] = 1;
			fieldArray[row-1][col] = 1;
			fieldArray[row-2][col] = 1;
			break;
		case "O":
			fieldArray[row][col] = 1;
			fieldArray[row][col-1] = 1;
			fieldArray[row-1][col] = 1;
			fieldArray[row-1][col-1] = 1;  
			break;
		case "L":
			fieldArray[row][col] = 1;
			fieldArray[row][col+1] = 1;
			fieldArray[row-1][col] = 1;
			fieldArray[row-2][col] = 1;
			break;
		case "S":
			fieldArray[row][col-1] = 1;
			fieldArray[row-1][col] = 1;
			fieldArray[row-1][col-1] = 1;
			fieldArray[row-2][col] = 1;
			break;
		case "Z":
			fieldArray[row][col] = 1;
			fieldArray[row-1][col] = 1;
			fieldArray[row-1][col-1] = 1;
			fieldArray[row-2][col-1] = 1;
			break;
		case "T":
			fieldArray[row][col] = 1;
			fieldArray[row][col+1] = 1;
			fieldArray[row][col-1] = 1;
			fieldArray[row-1][col] = 1;
			break;
	}
}

function play(){
	if(!canMove(currentTetramino, currentTetramino.row, currentTetramino.col)){
		blockFigure();

	}
}

function start(){
	clearInterval(inter)
	currentTetramino = chooseFigure();
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