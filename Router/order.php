<?php
function Order($type)
{
    require('Database/connection.php');
    $queryOrder = "SELECT COUNT(Sump_No) AS orders FROM info WHERE Sump_No = '" . $type . "'";
    $resultOrder = $conn->query($queryOrder);
    if ($resultOrder->num_rows > 0) {
        $rowOrder = $resultOrder->fetch_assoc();
        return $rowOrder["orders"];
    } else {
        return 0;
    }
}
