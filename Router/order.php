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

function UpdateDate($type)
{
    require('Database/connection.php');
    $queryOrder = "SELECT Treatment_Date FROM info WHERE Sump_No = '" . $type . "' ORDER BY Treatment_Date DESC";
    $resultOrder = $conn->query($queryOrder);
    if ($resultOrder->num_rows > 0) {
        $rowOrder = $resultOrder->fetch_assoc();
        $format = explode("/", $rowOrder["Treatment_Date"]);
        switch ($format[0]) {
            case "01":
                $format[0] = "ม.ค.";
                break;
            case "02":
                $format[0] = "ก.พ.";
                break;
            case "03":
                $format[0] = "มี.ค.";
                break;
            case "04":
                $format[0] = "เม.ย.";
                break;
            case "05":
                $format[0] = "พ.ค.";
                break;
            case "06":
                $format[0] = "มิ.ย.";
                break;
            case "07":
                $format[0] = "ก.ค.";
                break;
            case "08":
                $format[0] = "ส.ค.";
                break;
            case "09":
                $format[0] = "ก.ย.";
                break;
            case "10":
                $format[0] = "ต.ค.";
                break;
            case "11":
                $format[0] = "พ.ย.";
                break;
            case "12":
                $format[0] = "ธ.ค.";
                break;
        }
        $date = $format[1] . " " . $format[0] . " " . $format[2];
        return $date;
    } else {
        return "ยังไม่มีข้อมูล";
    }
}
