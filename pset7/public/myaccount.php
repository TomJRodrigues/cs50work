<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("account_form.php", ["title" => "My Account"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // ensure username, password, and confirmation aren't blank
        if (empty($_POST["oldpassword"]) || empty($_POST["newpassword"]) || empty($_POST["newconfirmation"])) {
            apologize("You must fill out all fields.");
        }
        
        // ensure they are equal as well.
        if ($_POST["newpassword"] != $_POST["newconfirmation"])
        {
            apologize("Your new passwords do not match.");
        }
        
        // query database for user's hash
        $hash = query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);
        $hash = $hash[0];
        
        // compare hash of user's input against hash that's in database
        if (crypt($_POST["oldpassword"], $hash["hash"]) != $hash["hash"]) {
            apologize("Incorrect password.");
        }
        else {
            // insert their entry into the database
            $result = query("UPDATE `users` SET `hash` = ? WHERE `id` = ?", crypt($_POST["newpassword"]), $_SESSION["id"]);
                
            if ($result === false)
            {
                apologize("Sorry, a database error occurred, please try again.");
            }
            else {
                redirect("/myaccount.php");
            }
        }
        
        
    }
?>
