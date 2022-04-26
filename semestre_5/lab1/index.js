function store(){
	var input = document.getElementById("inputUsername");
	var username = input.value;
	if(username == ""){
		window.alert("Input your username!");
	}else{
		localStorage["tetris.username"] = input.value;
		window.location.href = "./main.html";
	}	
}

function read(){
	if(localStorage.hasOwnProperty("tetris.username")){
		let username = localStorage.getItem("tetris.username");
        let input = document.getElementById("inputUsername");
        input.value = username;
	}
}