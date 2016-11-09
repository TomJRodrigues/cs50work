<div>
    <strong><?php !empty($_POST) ? print("Sold " . $_POST["amount"] . " share(s) of " . $_POST["symbol"] . "  for $" . ($_POST["amount"] * $soldstockprice)) : false ?></strong>
    <br></br>
</div>
<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            Share: <select autofocus class="form-control" name="symbol">
                <?php foreach ($positions as $position): ?>
                    <option><?= $position["symbol"] ?></option>
                <?php endforeach ?>
            </select>
        </div>
        <div class="form-group">
            Amount: <input class="form-control" name="amount" placeholder="0" type="number" min="0" max="<?= $position['shares'] ?>"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
<div>
    <a href="logout.php"><strong>Log Out</strong></a>
</div>
