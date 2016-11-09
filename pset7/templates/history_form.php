<ul class="nav nav-pills">
    <li><a href="quote.php">Quote</a</li>
    <li><a href="buy.php">Buy</a</li>
    <li><a href="sell.php">Sell</a</li>
    <li><a href="history.php">History</a</li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>

<table class="table table-striped">

    <thead>
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>
    
    <tbody>
        <?php foreach ($history as $historys): ?>
        
            <tr>
                <td><?= $historys["transaction"] ?></td>
                <td><?= $historys["time"] ?></td>
                <td><?= $historys["symbol"] ?></td>
                <td><?= $historys["shares"] ?></td>
                <td><?= $historys["price"] ?></td>
            </tr>
        <?php endforeach ?>
    </tbody>
</table>
<div>
    <a href="logout.php"><strong>Log Out</strong></a>
</div>
