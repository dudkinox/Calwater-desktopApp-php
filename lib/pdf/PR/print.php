<?php
// Connect to database
$conn = mysqli_connect("localhost", "id14233127_data", "Qwertyui-12345678", "id14233127_accom");
if (!$conn) {
  echo "มีปัญหาบางอย่างขัดข้องในการเชื่อมต่อ โปรดติดต่อกีตาร์";
} else {
  // Get data
  // $sql = "SELECT NO,Approve,Date,Name,Type_Buy,About,Number,Count,List,Count_List,Pirce,Bath,Note,Total,FF,G,Fund,General,Project,Law,Date_Use FROM data_pr";
  // $result = $conn->query($sql);

  // variable number is data primary by guitar eiei.
  $number = isset($_GET['id']) ? $_GET['id'] : '';
  $i = 1;
  // if ($result->num_rows > 0) {
  // while ($row = $result->fetch_assoc()) {
  if ($i == $number) {
    require_once __DIR__ . '/../vendor/autoload.php';

    $mpdf = new \Mpdf\Mpdf();
    $text =
      '
<style>
.container{
    font-family: "Garuda";
    font-size: 12pt;
}
h2{
  text-align: center;
  }
/* วันที่ */
.date{
  position: relative;
  left: 60%;
}
/* ตาราง */
table{
  font-family: "Garuda", sans-serif;
  border-collapse: collapse;
  width: 100%;
}

td, th {
  border: 1px solid #dddddd;
  text-align: left;
  padding: 8px;
}

tr:nth-child(even) {
  background-color: #dddddd;
}
</style>

<div class = "container">

</div>
';
    $mpdf->WriteHTML($text);
    $mpdf->Output();
  }
  $i++;
  // }
  // } else {
  //   echo "ไม่พบข้อมูล ข้อมูลอาจจะมีแค่ 0";
  // }
  $conn->close();
}
