<?php
session_start();
require('../Database/connection.php');

$Date = isset($_GET["Treatment_Date"]) ? $_GET["Treatment_Date"] : '';
$Batch_No = isset($_GET["Batch_No"]) ? $_GET["Batch_No"] : '';
$sBatch_No = substr($Batch_No, 2);
$Sump_No = ($_GET["Sump_No"]) ? $_GET["Sump_No"] : '';
$Volume = isset($_GET["Volume"]) ? $_GET["Volume"] : '';
$Total_Cr = isset($_GET["Total_Cr"]) ? $_GET["Total_Cr"] : '';
$Cu = isset($_GET["Cu"]) ? $_GET["Cu"] : '';
$Mn = isset($_GET["Mn"]) ? $_GET["Mn"] : '';
$Ni = isset($_GET["Ni"]) ? $_GET["Ni"] : '';
$Pb = isset($_GET["Pb"]) ? $_GET["Pb"] : '';
$Zn = isset($_GET["Zn"]) ? $_GET["Zn"] : '';
$totalmetal = isset($_GET["totalmetal"]) ? $_GET["totalmetal"] : '';
$ca = isset($_GET["ca"]) ? $_GET["ca"] : '';
$modelca = isset($_GET["modelca"]) ? $_GET["modelca"] : '';
$labca = isset($_GET["labca"]) ? $_GET["labca"] : '';
$fe = isset($_GET["fe"]) ? $_GET["fe"] : '';
$modelfe = isset($_GET["modelfe"]) ? $_GET["modelfe"] : '';
$labfe = isset($_GET["labfe"]) ? $_GET["labfe"] : '';
$na = isset($_GET["na"]) ? $_GET["na"] : '';
$modelna = isset($_GET["modelna"]) ? $_GET["modelna"] : '';
$labna = isset($_GET["labna"]) ? $_GET["labna"] : '';
$modeltds = isset($_GET["modeltds"]) ? $_GET["modeltds"] : '';
$labtds = isset($_GET["labtds"]) ? $_GET["labtds"] : '';
$queryID = "SELECT ID FROM info ORDER BY ID DESC";
$resultID = $conn->query($queryID);
$ID = 0;
if ($resultID->num_rows > 0) {
    $rowID = $resultID->fetch_assoc();
    $ID = number_format($rowID["ID"]) + 1;
} else {
    $ID = 1;
}

$query = "INSERT INTO info
        (
        ID, 
        Volume, 
        Batch_No, 
        Meet_MOI_Spec, 
        Sump_No, 
        Treatment_Date,
        Ca, 
        Fe, 
        Na,
        TDS) 
        VALUES (
        '',
        '" . $Volume . "',
        '" . $sBatch_No . "',
        'YES',
        '" . $Sump_No . "',
        '" . $Date . "',
        '" . $ID . "',
        '" . $ID . "',
        '" . $ID . "',
        '" . $ID . "')";
$Ca = "INSERT INTO ca
            (
            ca, 
            model, 
            lab, 
            No) 
            VALUES (
            '" . $ca . "',
            '" . $modelca . "',
            '" . $labca . "',
            '" . $ID . "')";
$Fe = "INSERT INTO fe
            (
            fe, 
            model, 
            lab, 
            No) 
            VALUES (
            '" . $fe . "',
            '" . $modelfe . "',
            '" . $labfe . "',
            '" . $ID . "')";
$Na = "INSERT INTO na
            (
            na, 
            model, 
            lab, 
            No) 
            VALUES (
            '" . $na . "',
            '" . $modelna . "',
            '" . $labna . "',
            '" . $ID . "')";
$TDS = "INSERT INTO tds
            (
            tds, 
            model, 
            lab, 
            No) 
            VALUES (
            '0',
            '" . $modeltds . "',
            '" . $labtds . "',
            '" . $ID . "')";

if (
    $conn->query($query) === TRUE
    && $conn->query($Ca) === TRUE
    && $conn->query($Fe) === TRUE
    && $conn->query($Na) === TRUE
    && $conn->query($TDS) === TRUE
) {
    $_SESSION["InsertAlert"] = 1;
    header('location: ../?router=insert');
} else {
    echo "Error: " . $query . "<br>" . $conn->error;
    echo "Error: " . $Ca . "<br>" . $conn->error;
    echo "Error: " . $Fe . "<br>" . $conn->error;
    echo "Error: " . $Na . "<br>" . $conn->error;
    echo "Error: " . $TDS . "<br>" . $conn->error;
}
