const canvas1 = document.getElementById("board");
const ctx = canvas1.getContext("2d");
const canvas2 = document.getElementById("cur_figur");
const ctxCurFigur = canvas2.getContext("2d");


let playerName = localStorage["tetris.username"];
let curLevel = 1;
let gameOver = false;
let points = 0;
let inter;
let timer = 1300;

if (document.getElementById("player_name")) {
	document.getElementById("player_name").innerHTML = playerName
} 
document.getElementById("current_level")?.innerHTML = curLevel + '';
document.getElementById("points")?.innerHTML = points + '';

var rows = 24;
var cols = 16;
var currentTetramino, nextTetramino;
var fieldArray = new Array(rows);

function chooseFigure(){
	let fig = Math.floor(Math.random() * (6)) + 0;
	let colIndex = Math.floor(Math.random() * (7)) + 1;
	let figColor = "";
	let figType;
	switch(colIndex){
		case 1:
			figColor = "rgba(255,0,0,1)";//red
			break;
		case 2:
			figColor = "rgba(0,255,0,1)";//green
			break;
		case 3:
			figColor = "rgba(0,0,255,1)";//blue
			break;
		case 4:
			figColor = "rgba(255,255,0,1)";//yellow
			break;
		case 5:
			figColor = "rgba(0,255,255,1)";//seawave
			break;
		case 6:
			figColor = "rgba(255,0,255,1)";//purple
			break;
		case 7:
			figColor = "rgba(255,165,0,1)";//orange
			break;
	}
	let curFigM;
	let leftX,leftY,rightX,rightY;
    switch(fig){
		case 0:
			curFigM = [[0,0,0,0],
			  		   [1,1,1,1],
			           [0,0,0,0],
			           [0,0,0,0]];
			curFigM[1][0] = colIndex;
			curFigM[1][1] = colIndex;
			curFigM[1][2] = colIndex;
			curFigM[1][3] = colIndex;           
			leftX = fieldArray[0].length / 2 - 2;
			leftY = 0;
			rightX = fieldArray[0].length / 2 + 1;
			rightY = 3;

			figType = "I"; 
			break;
		case 1:
			curFigM = [[1,1],
			  		   [1,1]];
			curFigM[0][0] = colIndex;
			curFigM[0][1] = colIndex;
			curFigM[1][0] = colIndex;
			curFigM[1][1] = colIndex; 
			leftX = fieldArray[0].length / 2 - 1;
			leftY = 0;
			rightX = fieldArray[0].length / 2 ;
			rightY = 1;

			figType = "O"; 
			break;
		case 2:
			curFigM = [[0,1,0],
			  		   [0,1,0],
			           [0,1,1]];
			curFigM[0][1] = colIndex;
			curFigM[1][1] = colIndex;
			curFigM[2][1] = colIndex;
			curFigM[2][2] = colIndex;            	
			leftX = fieldArray[0].length / 2 - 1;
			leftY = 0;
			rightX = fieldArray[0].length / 2 + 1;
			rightY = 2;

			figType = "L";          
			break;
		case 3:
			curFigM = [[0,1,0],
			  		   [0,1,1],
			           [0,0,1]];
			curFigM[0][1] = colIndex;
			curFigM[1][1] = colIndex;
			curFigM[1][2] = colIndex;
			curFigM[2][2] = colIndex;            
			leftX = fieldArray[0].length / 2 - 1;
			leftY = 0;
			rightX = fieldArray[0].length / 2 + 1;
			rightY = 2;

			figType = "Z";         
			break;
		case 4:
			curFigM = [[0,0,1],
			  		   [0,1,1],
			           [0,1,0]];
			curFigM[0][2] = colIndex;
			curFigM[1][1] = colIndex;
			curFigM[1][2] = colIndex;
			curFigM[2][1] = colIndex;           
			leftX = fieldArray[0].length / 2 - 1;
			leftY = 0;
			rightX = fieldArray[0].length / 2 + 1;
			rightY = 2;

			figType = "S";           
			break;
		case 5:
			curFigM = [[0,0,1],
			  		   [0,0,1],
			           [0,1,1]];
			curFigM[0][2] = colIndex;
			curFigM[1][2] = colIndex;
			curFigM[2][2] = colIndex;
			curFigM[2][1] = colIndex;           
			leftX = fieldArray[0].length / 2 - 1;
			leftY = 0;
			rightX = fieldArray[0].length / 2 + 1;
			rightY = 2;

			figType = "J"; 
			break;
		case 6:	
			curFigM = [[0,1,0],
				       [1,1,1],
				       [0,0,0]];
			curFigM[0][1] = colIndex;
			curFigM[1][0] = colIndex;
			curFigM[1][1] = colIndex;
			curFigM[1][2] = colIndex;	       
			leftX = fieldArray[0].length / 2 - 1;
			leftY = 0;
			rightX = fieldArray[0].length / 2 + 1;
			rightY = 2;

			figType = "T";         
			break;	
	}
	return {
        figType: figType,      
        curFig: curFigM,
        figColor: figColor,
        colIndex: colIndex,   
        leftX: leftX,
        leftY: leftY,
        rightX: rightX,
        rightY:rightY
      };
}

document.body.onkeydown = function (e) {
    var keys = {
    	32: "probel",
        37: "left",
        38: "rotate",
        39: "right",
        40: "down"
    };
    if (typeof(keys[e.keyCode]) != "undefined"){
        keyPressEvent(keys[e.keyCode]);
        drawField();
    }
}

function keyPressEvent(key){
	switch(key){
		case "left":
			if(canMove(-1,0,currentTetramino.curFig)){
				currentTetramino.leftX--;
				currentTetramino.rightX--;
			}
			break;
		case "rotate":
			let rotatedFig = rotateRight90(currentTetramino.curFig);
			if(canMove(0,0,rotatedFig)){
				currentTetramino.curFig = rotatedFig;
			}
			break;
		case "right":
			if(canMove(1,0,currentTetramino.curFig)){
				currentTetramino.leftX++;
				currentTetramino.rightX++;
			}
			break;
		case "down":
			if(canMove(0,1,currentTetramino.curFig)){
				currentTetramino.leftY++;
				currentTetramino.rightY++;
			}
			break;
		case "probel":
			while(canMove(0,1,currentTetramino.curFig)){
				currentTetramino.leftY++;
				currentTetramino.rightY++;
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

function canMove(deltaX, deltaY, figMatrix){
	let leftXNew = currentTetramino.leftX + deltaX;
    let rightXNew = currentTetramino.rightX + deltaX;
    let leftYNew = currentTetramino.leftY + deltaY;
    let rightYNew = currentTetramino.rightY + deltaY;
    if(deltaX > 0){
    	if(rightXNew >= fieldArray[0].length){
    		let sum  = 0;
    		for(let i = 0; i < figMatrix.length; i++){
    			sum += figMatrix[i][figMatrix[i].length - (rightXNew - fieldArray[0].length) - 1];
    		}
    		if(sum > 0){
    			return false;
    		}
    	}else{
    		for(let i = leftYNew; i < rightYNew + 1; i++){
    			for(let j = leftXNew; j < rightXNew + 1; j++){
    				if(figMatrix[i - leftYNew][j - leftXNew] > 0){
    					if(fieldArray[i][j] != 0){
    						return false;
    					}
    				}
    			}
    		}
    	}
    }else if(deltaX < 0){
    	if(leftXNew < 0){
    		let sum  = 0;
    		for(let i = 0; i < figMatrix.length; i++){
    			sum += figMatrix[i][-1 - leftXNew];
    		}
    		if(sum > 0){
    			return false;
    		}
    	}else{
    		for(let i = leftYNew; i < rightYNew + 1; i++){
    			for(let j = leftXNew; j < rightXNew + 1; j++){
    				if(figMatrix[i - leftYNew][j - leftXNew] > 0){
    					if(fieldArray[i][j] != 0){
    						return false;
    					}
    				}
    			}
    		}
    	}
    }else if(deltaY > 0){
    	if(rightYNew >= fieldArray.length){
    		let sum  = 0;
    		for(let j = 0; j < figMatrix[0].length; j++){
    			sum += figMatrix[figMatrix.length - (rightYNew - fieldArray.length) - 1][j];
    		}
    		if(sum > 0){
    			return false;
    		}
    	}else{
    		for(let i = leftYNew; i < rightYNew + 1; i++){
    			for(let j = leftXNew; j < rightXNew + 1; j++){
    				if(figMatrix[i - leftYNew][j - leftXNew] > 0){
    					if(fieldArray[i][j] != 0){
    						return false;
    					}
    				}
    			}
    		}
    	}
    }
    if(deltaX == 0 && deltaY == 0){
    	if(rightYNew >= fieldArray.length){
    		let sum  = 0;
    		for(let j = 0; j < figMatrix[0].length; j++){
    			sum += figMatrix[figMatrix.length - (rightYNew - fieldArray.length) - 1][j];
    		}
    		if(sum > 0){
    			return false;
    		}
    	}else{
    		for(let i = leftYNew; i < rightYNew + 1; i++){
    			for(let j = leftXNew; j < rightXNew + 1; j++){
    				if(figMatrix[i - leftYNew][j - leftXNew] > 0){
    					if(fieldArray[i][j] != 0){
    						return false;
    					}
    				}
    			}
    		}	
    	}
    	if(rightXNew >= fieldArray[0].length){
    		let sum  = 0;
    		for(let i = 0; i < figMatrix.length; i++){
    			sum += figMatrix[i][figMatrix[i].length - (rightXNew - fieldArray[0].length) - 1];
    		}
    		if(sum > 0){
    			return false;
    		}
    	}else{
    		for(let i = leftYNew; i < rightYNew + 1; i++){
    			for(let j = leftXNew; j < rightXNew + 1; j++){
    				if(figMatrix[i - leftYNew][j - leftXNew] > 0){
    					if(fieldArray[i][j] != 0){
    						return false;
    					}
    				}
    			}
    		}
    	}
    	if(leftXNew < 0){
    		let sum  = 0;
    		for(let i = 0; i < figMatrix.length; i++){
    			sum += figMatrix[i][-1 - leftXNew];
    		}
    		if(sum > 0){
    			return false;
    		}
    	}else{
    		for(let i = leftYNew; i < rightYNew + 1; i++){
    			for(let j = leftXNew; j < rightXNew + 1; j++){
    				if(figMatrix[i - leftYNew][j - leftXNew] > 0){
    					if(fieldArray[i][j] != 0){
    						return false;
    					}
    				}
    			}
    		}
    	}	
    }
  	return true;
}

function drawField(){
	ctx.clearRect(0, 0, canvas1.width, canvas1.height);
    ctx.strokeStyle = "black";
	for(let i = 0; i < fieldArray.length; i++){
		for(let j = 0; j < fieldArray[i].length; j++){
			if(fieldArray[i][j] == 1){
				ctx.fillStyle = "rgba(255,0,0,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}else if(fieldArray[i][j] == 2){
				ctx.fillStyle = "rgba(0,255,0,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}else if(fieldArray[i][j] == 3){
				ctx.fillStyle = "rgba(0,0,255,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}else if(fieldArray[i][j] == 4){
				ctx.fillStyle = "rgba(255,255,0,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}else if(fieldArray[i][j] == 5){
				ctx.fillStyle = "rgba(0,255,255,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}else if(fieldArray[i][j] == 6){
				ctx.fillStyle = "rgba(255,0,255,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}else if(fieldArray[i][j] == 7){
				ctx.fillStyle = "rgba(255,165,0,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}
		}
	}
	for(let i = currentTetramino.leftY; i < currentTetramino.leftY + currentTetramino.curFig.length; i++){	
		for(let j = currentTetramino.leftX; j < currentTetramino.leftX + currentTetramino.curFig.length; j++){
			if(i < 0 || j < 0 || i >= fieldArray.length || j >= fieldArray[0].length){
				continue;
			}
			if(fieldArray[i][j] == 0 && currentTetramino.curFig[i-currentTetramino.leftY][j-currentTetramino.leftX] > 0){
            	ctx.fillStyle = currentTetramino.figColor;
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}
		}
	}
}

			
function drawTetraminoOnSmallBoard(){
    ctxCurFigur.clearRect(0, 0, canvas2.width, canvas2.height);
    ctxCurFigur.strokeStyle = "black";
    ctxCurFigur.fillStyle = nextTetramino.figColor;
    for (let y = 0; y < nextTetramino.curFig.length; y++){
        for (let x = 0; x < nextTetramino.curFig[y].length; x++){
            if (nextTetramino.curFig[y][x] > 0){
            	ctxCurFigur.fillRect(25*x,25*y,25,25);
            	ctxCurFigur.strokeRect(25*x,25*y,25,25);
            }
        }
    }
}

function blockFigure(){
  	for(let i = currentTetramino.leftY; i < currentTetramino.rightY + 1; i++){
  		for(let j = currentTetramino.leftX; j < currentTetramino.rightX + 1; j++){
  			if(currentTetramino.curFig[i-currentTetramino.leftY][j-currentTetramino.leftX] > 0){
  				if(i < fieldArray.length && i >= 0 && j >= 0 && j < fieldArray[0].length){
  					fieldArray[i][j] = currentTetramino.colIndex;
  				}
  			}
  		}
  	}
  	ctx.clearRect(0, 0, canvas1.width, canvas1.height);
    ctx.strokeStyle = "black";
	for(let i = 0; i < fieldArray.length; i++){
		for(let j = 0; j < fieldArray[i].length; j++){
			if(fieldArray[i][j] == 0){
				ctx.fillStyle = "rgba(255,255,255,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}else if(fieldArray[i][j] == 1){
				ctx.fillStyle = "rgba(255,0,0,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}else if(fieldArray[i][j] == 2){
				ctx.fillStyle = "rgba(0,255,0,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}else if(fieldArray[i][j] == 3){
				ctx.fillStyle = "rgba(0,0,255,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}else if(fieldArray[i][j] == 4){
				ctx.fillStyle = "rgba(255,255,0,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}else if(fieldArray[i][j] == 5){
				ctx.fillStyle = "rgba(0,255,255,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}else if(fieldArray[i][j] == 6){
				ctx.fillStyle = "rgba(255,0,255,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}else if(fieldArray[i][j] == 7){
				ctx.fillStyle = "rgba(255,165,0,1)";
            	ctx.fillRect(25*j,25*i,25,25);
            	ctx.strokeRect(25*j,25*i,25,25);
			}
		}
	}
}

function countPoints(){
	for(let i = fieldArray.length - 1; i >=0; i--){
		let zeroCounter = 0;
		for(let j = 0; j < fieldArray[i].length; j++){
			if(fieldArray[i][j] != 0){
				zeroCounter++;				
			}
		}
		if(zeroCounter == fieldArray[i].length){
			points += 25;
			for(let y = i - 1; y >= 0; y--){
				for(let x = 0; x < fieldArray[i].length; x++){
					fieldArray[y + 1][x] = fieldArray[y][x];
				}
			}
		}
	}
}

function changeLevel(){
	if(points == 25){
		curLevel = 2;
		timer -= 300;
		//timer = 100;
	}else if(points == 250){
		curLevel = 3;
		timer -= 200;
	}else if(points == 500){
		curLevel = 4;
		timer -= 100;
	}else if(points == 750){
		curLevel = 5;
		timer -= 100;
	}else if(points == 1000){
		curLevel = 6;
		timer -= 50;
	}else if(points == 1250){
		curLevel = 7;
		timer -= 25;
	}

}

function writeInfo(){
	document.getElementById("player_name").innerHTML = playerName;
	document.getElementById("current_level").innerHTML = curLevel;
	document.getElementById("points").innerHTML = points;
}

function writeRecords(){
	let tmpResults;
	if(localStorage.length > 1){
		tmpResults = [];
		for(let key in localStorage){
			if(localStorage.getItem(key) != "undefined" && key != "tetris.username" && localStorage.getItem(key) != null){
				console.log(key)
				tmpResults.push([key, String(localStorage.getItem(key))]);
			}
		}
		tmpResults.push([playerName, points]);
		tmpResults.sort(function (a,b){return b[1] - a[1];});
		while(tmpResults.length > 25){
			tmpResults.pop();
		}
        for(let i = 0; i < tmpResults.length; i++){
        	console.log("tmpResults[",i,"][0], tmpResults[",i,"][1] = ", tmpResults[i][0], tmpResults[i][1]);
        	if(localStorage.hasOwnProperty(tmpResults[i][0])){
        		if(tmpResults[i][1] > localStorage.getItem(tmpResults[i][0])){
        			localStorage.setItem(tmpResults[i][0], tmpResults[i][1]);
        		}
        	}
        }
	}else{
		tmpResults = [playerName, points];
		localStorage.setItem(playerName, String(points));
	}
	let table = '<table class="simple-little-table">';
	if(tmpResults != []){
    	for(let i = 0; i < tmpResults.length; i++){
    	    table += '<tr>';
    	        table += '<td>' + (i + 1) +'</td>';
    	        table += '<td>' + tmpResults[i][0] +'</td>';
    	        table += '<td>' + tmpResults[i][1] +'</td>';
    	    table += '</tr>';
    	}
    	table += '</table>';
    	document.getElementById("recordsTable").innerHTML = table;
	}
}

function play(){
	if(!canMove(0,1,currentTetramino.curFig)){
		blockFigure();
		countPoints();
		changeLevel();
		writeRecords();
		writeInfo();
		delete currentTetramino;
		currentTetramino = nextTetramino;
		nextTetramino = chooseFigure();
		if(!canMove(0,0,currentTetramino.curFig)){
			alert("Game over");
			start();
		}
		drawTetraminoOnSmallBoard();
		drawField();
	}else{
		currentTetramino.leftY += 1;
		currentTetramino.rightY += 1;
		drawField();
		drawTetraminoOnSmallBoard();

	}
}

function start(){
	for (let i=0; i < rows; i++){
    fieldArray[i] = new Array(cols);
    for (let j=0; j < cols; j++)
        fieldArray[i][j]=0;
	}
	clearInterval(inter);
	currentTetramino = chooseFigure();
	nextTetramino = chooseFigure();
	drawTetraminoOnSmallBoard();
	drawField();
	writeRecords();
	inter = setInterval(() => play(), timer);
}

start();