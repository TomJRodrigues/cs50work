<form action="myaccount.php" method="post">
    <fieldset>
        <h4>Change Your Password</h4>
        <div class="form-group">
            <input autofocus class="form-control" name="oldpassword" placeholder="Old Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="newpassword" placeholder="New Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="newconfirmation" placeholder="Retype New Password" type="password"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Submit Changes</button>
        </div>
    </fieldset>
</form>
<div>
    or <a href="login.php">log in</a>
</div>
