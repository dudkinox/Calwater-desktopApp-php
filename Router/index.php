<?php
session_start();
require('../Database/connection.php');

$Date = isset($_GET["Treatment_Date"]) ? $_GET["Treatment_Date"] : '';
$Batch_No = isset($_GET["Batch_No"]) ? $_GET["Batch_No"] : '';
$Volume = isset($_GET["Volume"]) ? $_GET["Volume"] : '';
$Total_Cr = isset($_GET["Total_Cr"]) ? $_GET["Total_Cr"] : '';
$Cu = isset($_GET["Cu"]) ? $_GET["Cu"] : '';
$Mn = isset($_GET["Mn"]) ? $_GET["Mn"] : '';
$Ni = isset($_GET["Ni"]) ? $_GET["Ni"] : '';
$Pb = isset($_GET["Pb"]) ? $_GET["Pb"] : '';
$Zn = isset($_GET["Zn"]) ? $_GET["Zn"] : '';

$queryID = "SELECT ID FROM info ORDER BY ID DESC";
$resultID = $conn->query($queryID);
$rowID = $resultID->fetch_assoc();

$ID = number_format($rowID["ID"]) + 1;

$query = "INSERT INTO info
        (
        ID, 
        Volume, 
        Batch_No, 
        Meet_MOI_Spec, 
        Sump_No, 
        Treatment_Date, 
        RWWA_ID, 
        TWA_ID, 
        PR_ID) 
        VALUES (
        '',
        '" . $Volume . "',
        '" . $Batch_No . "',
        'YES',
        '" . $Sump_No . "',
        '" . $Date . "',
        '" . $ID . "',
        '" . $ID . "',
        '" . $ID . "')";

if ($conn->query($query) === TRUE) {
    $_SESSION["InsertAlert"] = 1;
    header('location: ../?router=insert');
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}
