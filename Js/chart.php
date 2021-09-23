<?php 
require('../Database/connection.php');
$queryChartS2 = "SELECT COUNT(Sump_No) AS S2 FROM info WHERE Sump_No = 'S2'";
$queryChartS3 = "SELECT COUNT(Sump_No) AS S3 FROM info WHERE Sump_No = 'S3'";
$queryChartE1 = "SELECT COUNT(Sump_No) AS E1 FROM info WHERE Sump_No = 'E1'";
$resultS2 = $conn->query($queryChartS2);
$resultS3 = $conn->query($queryChartS3);
$resultE1 = $conn->query($queryChartE1);
$rowS2 = $resultS2->fetch_assoc();
$rowS3 = $resultS3->fetch_assoc();
$rowE1 = $resultE1->fetch_assoc();
echo "
var donutChartCanvas = $('#donutChart').get(0).getContext('2d')
    var donutData        = {
      labels: [
          'S2',
          'S3',
          'E1',
      ],
      datasets: [
        {
          data: [".$rowS2["S2"].",".$rowS3["S3"].",".$rowE1["E1"]."],
          backgroundColor : ['#17a2b8', '#28a745', '#ffc107'],
        }
      ]
    }
    var donutOptions = {
      maintainAspectRatio : false,
      responsive : true,
    }
    //Create pie or douhnut chart
    // You can switch between pie and douhnut using the method below.
    new Chart(donutChartCanvas, {
      type: 'doughnut',
      data: donutData,
      options: donutOptions
    })
    ";