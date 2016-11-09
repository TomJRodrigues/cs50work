<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // ensure username, password, and confirmation aren't blank
        if (empty($_POST["username"]))
        {
            apologize("You must provide a username.");
        }   
        else if (empty($_POST["password"]))
        {
            apologize("You must provide a password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must re-type your password.");
        }
        
        // ensure they are equal as well.
        if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Your passwords do not match.");
        }
        
        // insert their entry into the database
        $result = query("INSERT INTO users (email, username, hash, cash) VALUES(?, ?, ?, 10000.00)",
            $_POST["email"], $_POST["username"], crypt($_POST["password"]));
            
        if ($result === false)
        {
            apologize("Sorry, a database error occurred, please try again.");
        }
        
        // log user in
        $rows = query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
        $_SESSION["id"] = $id;

        // redirect to index
        redirect("/");
    }
    
?>
