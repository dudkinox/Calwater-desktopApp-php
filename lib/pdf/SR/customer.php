<?php
// Connect to database
$conn = mysqli_connect("localhost", "id14233127_data", "Qwertyui-12345678", "id14233127_accom");
if (!$conn) {
    echo "มีปัญหาบางอย่างขัดข้องในการเชื่อมต่อ โปรดติดต่อกีตาร์";
} else {
    // Get data
    $number = isset($_GET['id']) ? $_GET['id'] : '';
    $sql = "SELECT ID,ID_Card,Name,Old,Sex,Address,Postal_Code,Believe,Phone,Type_Customer,Job,Salary,Education,State,Freetime,Company,Type_Business,Send_Address FROM customer WHERE ID='".$number."'";
    $result = $conn->query($sql);

    // variable number is data primary by guitar eiei.
    if ($result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
          //  PDF import
                require_once __DIR__ . '/../vendor/autoload.php';

                $mpdf = new \Mpdf\Mpdf();
                $text = '
                <style>
                  .container{
                     font-family: "Garuda";
                     font-size: 12pt;
                  }
                  h2 {
                    text-align : center;
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
                
                
                  
                    <h2>
                      ข้อมูลลูกค้า <br> รหัส <br> '.$number.'
                    </h2>
                  
                
                <table>
                  <tr>
                    <th>
                      <h3><b>ข้อมูลพื้นฐาน</b></h3>
                    </th>
                  </tr>
              <tr>
                <td>
                <p><b>เลขประจำตัวผู้เสียภาษี</b> : '.$row["ID_Card"].'</p>
                <br>
                 <p> <b>ชื่อ</b> : '.$row["Name"].'  &nbsp;&nbsp;
                
                  <b>อายุ</b> : '.$row["Old"].' ปี  &nbsp;&nbsp;
                
                  <b>เพศ</b> : '.$row["Sex"].'  
                </p>    
                <br>

              <p>
                <b>
                  สถานะ</b> : '.$row["State"].'
              </p>
              <br>
              <p>
                <b>
                  งานอดิเรก</b> : '.$row["Freetime"].'
              </p>
              <br>
              <p>
                <b>
                  ที่อยู่</b> : '.$row["Address"].'
              </p>
              <br>
              <p>
                <b>
                  รหัสไปรษณีย์&nbsp;
                </b>
                :&nbsp;'.$row["Postal_Code"].'
              </p>
              <br>
              <p>
                <b>
                  ศาสนา</b> : '.$row["Believe"].' &nbsp;&nbsp;
                  <b>โทรศัพท์</b> : 0'.$row["Phone"].'
              </p>
              <br>
                </td>
              </tr>
                <tr>
                  <th>
                    <h3><b>ข้อมูลทางธุรกิจ</b></h3>
                  </th>
                </tr>
              <tr>
              <td>
                <p>
                <b>
                  ประเภทลูกค้า</b> : '.$row["Type_Customer"].'
                </p>
                <br>
                <p>
                <b>
                  อาชีพ</b> : '.$row["Job"].'
                </p>
                <br>
                <p>
                <b>
                  เงินเดือน</b> : '.$row["Salary"].'
                </p>
                <br>
                <p><b>
                  จบการศึกษา</b> : '.$row["Education"].'
                </p>
                <br>
                <p><b>
                  บริษัท</b> : '.$row["Company"].'
                </p>
                <br>
                <p><b>
                  ประเภท</b> : '.$row["Type_Business"].'
                </p>
                <br>
                <p><b>
                  ที่อยู่จัดส่ง</b> : '.$row["Send_Address"].'
                </p>
                <br>
              </td>
              <tr>
                </table>
              </div>
                ';
              
                $mpdf->WriteHTML($text);
                $mpdf->Output();
        }
    } else {
        echo "ไม่พบข้อมูล ข้อมูลอาจจะมีแค่ 0";
    }
    $conn->close();
}

?>