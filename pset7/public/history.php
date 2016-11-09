<?php

    // configuration
    require("../includes/config.php");
    
    // query to find out user and their shares
    $history = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    
    // render history, pass in share lookup prices
    render("history_form.php", ["title" => "History", "history" => $history]);
?>
