<?php

    // configuration
    require("../includes/config.php");
    
    // query to find out user and their shares
    $rows = query("SELECT * FROM portfolio WHERE id = ?", $_SESSION["id"]);
    
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }   
    }
    
    $cashs = query("SELECT `cash` FROM `users` WHERE `id` = ?", $_SESSION["id"]);
    $cash = $cashs[0]["cash"];

    // render portfolio, pass in share lookup prices
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash]);
?>
