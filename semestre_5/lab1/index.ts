function store(){
	let username = document.getElementById("inputUsername")?.value;
	if(username == ""){
		window.alert("Input your username!");
	}else{
		localStorage["tetris.username"] = document.getElementById("inputUsername").value;
		window.location.href = "./main.html";
	}	
}

function read(){
	if(localStorage.hasOwnProperty("tetris.username")){
		let username = localStorage.getItem("tetris.username");
		document.getElementById("inputUsername").value = username;
	}
}