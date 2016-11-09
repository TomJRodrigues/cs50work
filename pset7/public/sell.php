<?php

    // configuration
    require("../includes/config.php");

    // get the values
    $rows = query("SELECT * FROM portfolio WHERE id = ?", $_SESSION["id"]);
    
    // to make values accessible to us
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
    $soldstockprice = 0;
    
    // if user reached page via POST (as by submitting a form via POST)
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // delete the shares
        query("UPDATE `portfolio` SET `shares` = (`shares` - ?) WHERE `symbol` = ? AND `id` = ?", $_POST["amount"], $_POST["symbol"], $_SESSION["id"]);
        
        $soldstock = lookup($_POST["symbol"]);
        $soldstockprice = $soldstock["price"];
        
        // add the cash
        query("UPDATE `users` SET `cash` = `cash` + ? WHERE `id` = ?", $_POST["amount"] * $soldstockprice, $_SESSION['id']);
        
        // enter sale into history table
        query("INSERT INTO `history`(`id`, `transaction`, `time`, `shares`, `symbol`, `price`) VALUES (?, ?, NOW(), ?, ?, ?)", $_SESSION["id"], "SELL", $_POST["amount"], $_POST["symbol"], $_POST["amount"] * $soldstockprice);
    }
    
    // pass in values
    render("sell_form.php", ["positions" => $positions, "soldstockprice" => $soldstockprice]);
?>
