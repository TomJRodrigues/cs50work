<ul class="nav nav-pills">
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="myaccount.php">My Account</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>

<table class="table table-striped">

    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>
    
    <tbody>
        <?php foreach ($positions as $position): ?>
        
            <tr>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["name"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td><?= $position["price"] ?></td>
                <td><?= ($position["price"] * $position["shares"]) ?></td>
            </tr>
        <?php endforeach ?>
        <tr>
            <td colspan="4">CASH</td>
            <td><?=$cash?></td>
        </tr>
    </tbody>
</table>
<div>
    <a href="logout.php"><strong>Log Out</strong></a>
</div>
