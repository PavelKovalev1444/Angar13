let indexOfEditing = -1;
$(document).ready(function () {
  prerequisits();
  ajax_change_information();
});

function prerequisits() {
  $('#id01').removeAttr("style").hide();
  $('#id02').removeAttr("style").hide();
}

function edit_participant_new() {
  $('#id01').show();
}

function ajax_change_information() {
  $(".save_btn").click(function () {
    $('#id01').removeAttr("style").hide();
    $.get("/ajx_change_settings", {
      start_auction_date: $("#start_auc_date").val(),
      trade_auction_timeout: $("#trade_timeout").val(),
      trade_auction_interval: $("#trade_interval").val(),
      pause_auction_time: $("#pause_time").val()
    }).done(data => {
      let date_variable = JSON.parse(data);
      $("#st_auc_dt").text(date_variable.start_auc_date);
      $("#trd_tm").text(date_variable.trade_timeout);
      $("#trd_int").text(date_variable.trade_interval);
      $("#ps_tm").text(date_variable.pause_time);
    });
  });
}

function deletingRows(value) {
  let index = value;
  let elem = "#tr" + index;
  $(elem).remove();
  $.get("/ajx_delete_participant/" + index.toString());
}

function edit_participant_info(value) {
  indexOfEditing = value;
  $('#id02').show();
}

function ajax_edit_participant_info() {
  let newName = $("#editNameInput").val();
  let newMoney = $("#editMoneyInput").val();
  $.get("/ajx_edit_participant", {
    id: indexOfEditing,
    name: newName,
    money: newMoney
  });
  let col1 = "#0td" + indexOfEditing;
  let col2 = "#1td" + indexOfEditing;

  if (newName !== "") {
    console.log(newName);
    $(col1).text(newName);
  }

  if (newMoney !== "") {
    console.log(newMoney);
    $(col2).text(newMoney);
  }
}