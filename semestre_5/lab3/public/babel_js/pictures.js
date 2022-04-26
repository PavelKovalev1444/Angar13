let indexOfEditing = -1;

$(document).ready(()=>{
    prerequisits();
});

function prerequisits() {
    $('#id01').removeAttr("style").hide();
    $('#id02').removeAttr("style").hide();
}

function edit_picture_trade(value){
    let elem = "#tradeSpanChanging" + value.toString();
    let text = $(elem).text();
    let textToSpan = "";
    if(text === "На торгах"){
        textToSpan = "Вне торгов";
        $(elem).text("Вне торгов");
    }else{
        textToSpan = "На торгах";
        $(elem).text("На торгах");
    }
    $.get("/ajx_trade_or_not_trade", {
        id: value,
        text: textToSpan
    });
}

function add_pic(){
    $('#id01').show();
}

function edit_picture_info(value){
    indexOfEditing = value;
    $('#id02').show();
}

function ajax_edit_picture_info(){
    let newName = $("#editNameInput").val();
    let newAuthor = $("#editAuthorInput").val();
    let newDesc = $("#editDescInput").val();
    let newStart_price = $("#editMoneyInput").val();
    let newMin_step = $("#editMinStepInput").val();
    let newMax_step = $("#editMaxStepInput").val();
    let newPath = $("#editPathInput").val();
    $.get("/ajx_edit_picture", {
        id: indexOfEditing,
        name: newName,
        author: newAuthor,
        desc: newDesc,
        start_price: newStart_price,
        min_step: newMin_step,
        max_step: newMax_step,
        path: newPath
    });
    let col1 = "#1td" + indexOfEditing;
    let col2 = "#2td" + indexOfEditing;
    let col3 = "#3td" + indexOfEditing;
    let col4 = "#4td" + indexOfEditing;
    let col5 = "#5td" + indexOfEditing;
    let col6 = "#6td" + indexOfEditing;
    if(newName !== "") {
        $(col1).text(newName);
    }
    if(newAuthor !== "") {
        $(col2).text(newAuthor);
    }
    if(newDesc !== "") {
        $(col3).text(newDesc);
    }
    if(newStart_price !== "") {
        $(col4).text(newStart_price);
    }
    if(newMin_step !== "") {
        $(col5).text(newMin_step);
    }
    if(newMax_step !== "") {
        $(col6).text(newMax_step);
    }
}