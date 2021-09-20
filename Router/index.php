<?php
session_start();
require('../Database/connection.php');

$Date = isset($_GET["Treatment_Date"]) ? $_GET["Treatment_Date"] : '';
$Batch_No = isset($_GET["Batch_No"]) ? $_GET["Batch_No"] : '';
$Sump_No = ($_GET["Sump_No"]) ? $_GET["Sump_No"] : '';
$Volume = isset($_GET["Volume"]) ? $_GET["Volume"] : '';
$Total_Cr = isset($_GET["Total_Cr"]) ? $_GET["Total_Cr"] : '';
$Cu = isset($_GET["Cu"]) ? $_GET["Cu"] : '';
$Mn = isset($_GET["Mn"]) ? $_GET["Mn"] : '';
$Ni = isset($_GET["Ni"]) ? $_GET["Ni"] : '';
$Pb = isset($_GET["Pb"]) ? $_GET["Pb"] : '';
$Zn = isset($_GET["Zn"]) ? $_GET["Zn"] : '';

$queryID = "SELECT ID FROM info ORDER BY ID DESC";
$resultID = $conn->query($queryID);
$ID = 0;
if($resultID->num_rows>0){
    $rowID = $resultID->fetch_assoc();
    $ID = number_format($rowID["ID"]) + 1;
}
else{
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
        RWWA_ID, 
        TWA_ID) 
        VALUES (
        '',
        '" . $Volume . "',
        '" . $Batch_No . "',
        'YES',
        '" . $Sump_No . "',
        '" . $Date . "',
        '" . $ID . "',
        '" . $ID . "')";

$queryRWW = "INSERT INTO raw_waste_water_analysis
            (
            ID,  
            Total_Cr, 
            Cu, 
            Mn, 
            Ni, 
            Pb, 
            Zn, 
            TDS) 
            VALUES (
            " . $ID . ",
            " . $Total_Cr . ",
            " . $Cu . ",
            " . $Mn . ",
            " . $Ni . ",
            " . $Pb . ",
            " . $Zn . ",
            0)";
            
 $queryTWA = "INSERT INTO treat_water_analysis
            (
            ID,  
            `Total_Cr:0.25`, 
            `Cu:2.0`, 
            `Mn:5.0`, 
            `Ni:1.0`, 
            `Pb:0.2`, 
            `Zn:5.0`, 
            `TDS:None`) 
            VALUES (
            " . $ID . ",
            " . $Total_Cr . ",
            " . $Cu . ",
            " . $Mn . ",
            " . $Ni . ",
            " . $Pb . ",
            " . $Zn . ",
            0)";   

if ($conn->query($query) === TRUE) {
    if ($conn->query($queryRWW) === TRUE) {
        if ($conn->query($queryTWA) === TRUE) {
            $_SESSION["InsertAlert"] = 1;
            header('location: ../?router=insert');
        }else{
            echo "Error: " . $queryTWA . "<br>" . $conn->error; 
        }
    }else {
        echo "Error: " . $queryRWW . "<br>" . $conn->error;
    }
} else {
    echo "Error: " . $query . "<br>" . $conn->error;
}
