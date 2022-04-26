$(document).ready(function () {
    prerequisits();
    ajax_change_settings();
});

function prerequisits() {
    $('#id01').removeAttr("style").hide();
}

function edit_setting() {
    $('#id01').show();
}

function ajax_change_settings(){
    $(".save_btn").click(function(){
        $('#id01').removeAttr("style").hide();
        $.get("/ajx_change_settings", {
            start_auction_date: $("#start_auc_date").val(),
            trade_auction_timeout: $("#trade_timeout").val(),
            trade_auction_interval: $("#trade_interval").val(),
            pause_auction_time: $("#pause_time").val()
        }).done(data=>{
            let date_variable = JSON.parse(data);
            $("#st_auc_dt").text(date_variable.start_auc_date);
            $("#trd_tm").text(date_variable.trade_timeout);
            $("#trd_int").text(date_variable.trade_interval);
            $("#ps_tm").text(date_variable.pause_time);
        });
    });
}