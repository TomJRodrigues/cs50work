<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("quote_form.php", ["title" => "Get Quote"]);
    }
    if (!empty($_GET["symbol"]))
    {
        $stock = lookup($_GET["symbol"]);
       // $stock["price"] = number_format($stock["price"], 4);
       // print("Price: " . $stock["price"]);
    }  
?>
