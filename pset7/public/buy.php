<?php

    // configuration
    require("../includes/config.php");

    // pass in values
    render("buy_form.php");
    
    // if user reached page via POST (as by submitting a form via POST)
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // get users cash amount
        $cashs = query("SELECT `cash` FROM users WHERE id = ?", $_SESSION["id"]);
        $cash = $cashs[0]["cash"];
        
        // make symbol uppercase
        $_POST["symbol"] = strtoupper ( $_POST["symbol"] );
        
        // check stock price and total purchase amount
        $stock = lookup($_POST["symbol"]);
        $stock["price"] = number_format($stock["price"], 4);
        $stockprice = $stock["price"] * $_POST["amount"];
        
        // check if user has the cash
        if ($cash > $stockprice) {
            // debit cash accordingly
            query("UPDATE `users` SET `cash` = `cash` - ? WHERE `id` = ?", $_POST["amount"] * $stock["price"], $_SESSION['id']);
        
            // update SQL to reflect stock purchase
            query("INSERT INTO portfolio (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $_POST["symbol"], $_POST["amount"]);
            
            // enter purchase into history table
            query("INSERT INTO `history`(`id`, `transaction`, `time`, `shares`, `symbol`, `price`) VALUES (?, ?, NOW(), ?, ?, ?)", $_SESSION["id"], "BUY", $_POST["amount"], $_POST["symbol"], $_POST["amount"] * $stock["price"]);
        }
        else { // TODO make this render better
            apologize("Sorry, insufficient funds.");
        }
    }
?>
