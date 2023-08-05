function  callAjaxGet(id, callback) {
    let xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if(this.readyState == 4 && this.status == 200)
            callback(this.responseText);
    };
    xhttp.open("GET",`/filter/${id}`,true);
    xhttp.send();
}

function in_library(button){
    let id = button.id;
    callAjaxGet('without_filter', (response) => {
        let array_id = JSON.parse(response);
        for(let el of array_id) {
            let cur_th = document.getElementById(el.id);
            cur_th.style.visibility = "visible";
        }
    });
    callAjaxGet(id, (response) => {
        let array_id = JSON.parse(response);
        for(let el of array_id) {
            let cur_th = document.getElementById(el.id);
            cur_th.style.visibility = "hidden";
        }
    });
}

function without_filter(button){
    let id = button.id;
    callAjaxGet(id, (response) => {
        let array_id = JSON.parse(response);
        for(let el of array_id) {
            let cur_th = document.getElementById(el.id);
            cur_th.style.visibility = "visible";
        }
    });
}

function date_return(button){
    let id = button.id;
    callAjaxGet(id, (response) => {
        let array_id = JSON.parse(response);
        for(let el of array_id) {
            let cur_th = document.getElementById(el.id);
            cur_th.style.visibility = "hidden";
        }
    });
}