<?php
session_start();
require('../Database/connection.php');
$key = isset($_GET["delete"]) ? $_GET["delete"] : '';
$no = isset($_GET["no"]) ? $_GET["no"] : '';
echo $key." ".$no;
$query = "DELETE FROM `info` WHERE `Batch_No` = '".$key."'";
$ca = "DELETE FROM `ca` WHERE `No` = '".$no."'";
$fe = "DELETE FROM `fe` WHERE `No` = '".$no."'";
$na = "DELETE FROM `na` WHERE `No` = '".$no."'";
$tds = "DELETE FROM `tds` WHERE `No` = '".$no."'";
if(
    $conn->query($query) === TRUE
&& $conn->query($ca) === TRUE
&& $conn->query($fe) === TRUE
&& $conn->query($na) === TRUE
&& $conn->query($tds) === TRUE
){
    $_SESSION["delete"] = 1;
    header('location: ../?router=insert');
}else{
    echo "Error: " . $query . "<br>" . $conn->error;
}
