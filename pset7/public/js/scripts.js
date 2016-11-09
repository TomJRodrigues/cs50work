/**
 * scripts.js
 *
 * Computer Science 50
 * Problem Set 7
 *
 * Global JavaScript, if any.
 */
 
<script src="http://code.jquery.com/jquery-latest.min.js"></script>
<script type="text/javascript">
    /**
     * Gets a quote via JSON.
     */
    function quote()
    {
    var url = 'quote.php?symbol=' + $('#symbol').val();
        $.getJSON(url, function(data) {
            $('#price').html(data.price);
            });
    }
</script>
