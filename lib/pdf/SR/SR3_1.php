<?php
// Connect to database
$conn = mysqli_connect("localhost", "id14233127_data", "Qwertyui-12345678", "id14233127_accom");
if (!$conn) {
    echo "มีปัญหาบางอย่างขัดข้องในการเชื่อมต่อ โปรดติดต่อโปรแกรมเมอร์จูเนียร์";
} else {
    // Get data
    
    $number = isset($_GET['id']) ? $_GET['id'] : '';
    $num_com = isset($_GET['com']) ? $_GET['com'] : '';
    
    $sql = "SELECT ID,Date,select_customer,Address,Postal_Code,ID_Card,Type_Business,Name,Allcase,promotion,Discount,tota_vat,VAT,VAT_num,Money,VAT_AT,VAT_AT_num,bye,note FROM sale WHERE ID='".$number."'";
    $sql2 = "SELECT Name_company,Type_company,Type_vat,Type_size,Address_company,ID_vat,Phone_company,Web_company FROM Company WHERE Name_Company='".$num_com."'";
    $sql_ID_slip = "SELECT ID_slip FROM id_receipt WHERE ID_sale='".$number."'";
    
    $result = $conn->query($sql);
    $result2 = $conn->query($sql2);
    $result_slip = $conn->query($sql_ID_slip);
    $row2 = $result2->fetch_assoc();
    $row_slip = $result_slip->fetch_assoc();
    $ID_slip = $row_slip['ID_slip'];

    function Convert($amount_number)
    {
        $amount_number = number_format($amount_number, 2, ".","");
        $pt = strpos($amount_number , ".");
        $number = $fraction = "";
        if ($pt === false) 
            $number = $amount_number;
        else
        {
            $number = substr($amount_number, 0, $pt);
            $fraction = substr($amount_number, $pt + 1);
        }
        
        $ret = "";
        $baht = ReadNumber ($number);
        if ($baht != "")
            $ret .= $baht . "บาท";
        
        $satang = ReadNumber($fraction);
        if ($satang != "")
            $ret .=  $satang . "สตางค์";
        else 
            $ret .= "ถ้วน";
        return $ret;
    }
     
    function ReadNumber($number)
    {
        $position_call = array("แสน", "หมื่น", "พัน", "ร้อย", "สิบ", "");
        $number_call = array("", "หนึ่ง", "สอง", "สาม", "สี่", "ห้า", "หก", "เจ็ด", "แปด", "เก้า");
        $number = $number + 0;
        $ret = "";
        if ($number == 0) return $ret;
        if ($number > 1000000)
        {
            $ret .= ReadNumber(intval($number / 1000000)) . "ล้าน";
            $number = intval(fmod($number, 1000000));
        }
        
        $divider = 100000;
        $pos = 0;
        while($number > 0)
        {
            $d = intval($number / $divider);
            $ret .= (($divider == 10) && ($d == 2)) ? "ยี่" : 
                ((($divider == 10) && ($d == 1)) ? "" :
                ((($divider == 1) && ($d == 1) && ($ret != "")) ? "เอ็ด" : $number_call[$d]));
            $ret .= ($d ? $position_call[$pos] : "");
            $number = $number % $divider;
            $divider = $divider / 10;
            $pos++;
        }
        return $ret;
    }

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
                  /* ตาราง */
                  table{
                    font-family: "Garuda", sans-serif;
                    border-collapse: collapse;
                    width: 100%;
                  }
                  td {
                    border: 0px solid #dddddd;
                    text-align: left;
                    padding: 3px;
                  }

                  th {
                    border: 1px solid #000000;
                    text-align: left;
                    padding: 4px;
                  }
                  tr:nth-child(even) {
                  
                  }
               
                  h4.mix{
                    margin: 25px 50px 75px 100px;
                    border-radius: 20px;
                    border : solid green;
                    background-color:rgb(207, 233, 156);
                 }
                    
                
                  
</style>
<!-- หัวเรื่อง -->                
              <div class = "container">
                <div class = "topic">
                  
                <table>
                <tr><td><h3><b>บริษัท '.$row2["Name_company"].' จำกัด</b></h3></td>      <td style = "width: 140px;"></td>       <td><table><tr><th style = "text-align:center;border: 3px solid #87CEFA;" ><h4>สำหรับลูกค้า</h4></th></tr></table></td></tr>
                <tr><td style = "width: 400px;">ที่อยู่ : '.$row2["Address_company"].' </td>       <td></td></tr>
                <tr><td>โทร. '.$row2["Phone_company"].' เลขประจำตัวผู้เสียภาษี '.$row2["ID_vat"].' </td>       <td></td></tr>
                </table>
                <br>
                <table>
                 <tr>
                  <td style = "width: 150px;"></td>
                  <td>
                  <table>
                  <tr>
                  <th style = "text-align:center;border: 3px solid #87CEFA;">ใบเสร็จรับเงิน<br>RECEIPT</th>
                  </tr>
                  </table>
                  </td>
                  <td style = "width: 150px;"></td>
                 </tr> 
                </table>
                <br>
                <table>
                <tr><td style = "width: 350px;">นามลูกค้า '.$row["Name"].'</td>   <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>       <td>เลขที่</td><td style = "text-align:right">'.$ID_slip.'</td></tr>
                <tr><td style = "width: 350px;">ที่อยู่ '.$row["Address"].'</td>     <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>       <td>วันที่</td><td style = "text-align:right">'.$row["Date"].'</td></tr>
                <tr><td style = "width: 350px;">เลขประจำตัวผู้เสียภาษี '.$row["ID_Card"].'</td>  <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>    <td></td><td></td></tr>
                </table>



                </div>
<!-- ====== -->

               
<!-- ตาราง --> 

                    <table>
                    
                      <tr bgcolor = "LightSkyBlue">
                      <th style = "text-align:center">
                      ลำดับ
                       </th>
                       
                        <th style = "text-align:center">
                          รายการ
                        </th>
                        <th style = "text-align:center">
                          จำนวน
                        </th>
                        <th style = "text-align:center">
                          ราคาต่อหน่วย
                        </th>
                        <th style = "text-align:center">
                          รวมเงิน
                        </th>
                      </tr>
                    
			';

      $mpdf->WriteHTML($text);

      $conn1 = mysqli_connect("localhost", "id14233127_data", "Qwertyui-12345678", "id14233127_accom");
			if (!$conn1) {
				echo "มีปัญหาบางอย่างขัดข้องในการเชื่อมต่อ โปรดติดต่อกีตาร์";
			} else {
				$sql1 = "SELECT ID_sale,ID_stock,Name_stock,Num_select,Sell_unit,Sum_unit FROM sale_stock WHERE ID_sale = '".$number."'";
        $result1 = $conn1->query($sql1);
        $i = 0;
				if ($result1->num_rows > 0) {
					while ($row1 = $result1->fetch_assoc()) {
            $i++;
						$text_1 = '<tr valign="middle">
         
            <th style = "text-align:center"> '.$i.' </th>
            
            <th style = "text-align:center"> '. $row1["Name_stock"] .' </th>
            
            <th style = "text-align:center"> '. $row1["Num_select"] .' </th>
            
            <th style = "text-align:center"> '. number_format($row1["Sell_unit"],2) .'</th>
            
            <th style = "text-align:center"> '. number_format($row1["Sum_unit"],2) .' </th>
            
            
            </tr>
           
            
            ';
            
            $mpdf->WriteHTML($text_1);
         
					}
				}
				$conn1->close();
			}
    

      $text_2 = '
     

 </table>



<!-- ===== -->      

<div style = "position: absolute;bottom: 5%;right: 7.5%; left: 7.5%">
<table>
 <tr><td style = "width: 410px;"> <table><tr><th style = "text-align:left"><h5>ตัวอักษร. ('.Convert($row['bye']).')</h5></th></tr></table></td>          <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">รวมเงิน </td> <td style = "text-align:right">'.number_format($row['Allcase'], 2).'  บาท</td></td></tr></table></tr>
 <tr><td><b>หมายเหตุ</b> <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">ส่วนลด </td> <td style = "text-align:right">'.number_format($row['Discount'], 2).'  บาท</td></td></tr></table></tr>
 <tr><td>'.$row['note'].' </td>                  <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">จำนวนเงินหลังหักส่วนลด </td> <td style = "text-align:right">'.number_format($row['Money'], 2).'  บาท</td></td></tr></table></tr>
 <tr><td></td>                   <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">ภาษีมูลค่าเพิ่ม 7% </td> <td style = "text-align:right">'.number_format($row['VAT_num'], 2).'  บาท</td></td></tr></table></tr>
 <tr><td></td>                  <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">จำนวนเงินรวม </td> <td style = "text-align:right">'.number_format($row['tota_vat'], 2).'  บาท</td></td></tr></table></tr>
 <tr><td></td>       <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">ภาษีหัก ณ ที่จ่าย 3% </td> <td style = "text-align:right">'.number_format($row['VAT_AT_num'], 2).'  บาท</td></td></tr></table></tr>
 <tr><td></td>       <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">จำนวนเงินทั้งสิ้น </td> <td style = "text-align:right">'.number_format($row['bye'], 2).'  บาท</td></td></tr></table></tr>
</table>
<br>


<table>
<tr><th style = "text-align:left"><h5>ได้รับสินค้าไว้เรียบร้อยแล้ว<br><br><br>ผู้รับสินค้า<br><br>วันที่</h5></th>  <th><h5>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  <br><br><br>ผู้ส่งสินค้า<br><br>วันที่</h5></th>   <th style = "text-align:center"><h5>ในนาม บริษัท '.$row2["Name_company"].' จำกัด <br><br><br><br><br><br>ผู้มีอำนาจลงนาม</h5></th>  </tr>

</table>
</div>
            ';
                $mpdf->WriteHTML($text_2);
                $mpdf->AddPage();
                

                $text2 = '
                <style>
                .container{
                   font-family: "Garuda";
                   font-size: 12pt;
                }
                /* ตาราง */
                table{
                  font-family: "Garuda", sans-serif;
                  border-collapse: collapse;
                  width: 100%;
                }
                td {
                  border: 0px solid #dddddd;
                  text-align: left;
                  padding: 3px;
                }

                th {
                  border: 1px solid #000000;
                  text-align: left;
                  padding: 4px;
                }
                tr:nth-child(even) {
                  background-color: #fff;
                }
             
                h4.mix{
                  margin: 25px 50px 75px 100px;
                  border-radius: 20px;
                  border : solid green;
                  background-color:rgb(207, 233, 156);
               }
                  
              
                
</style>
<!-- หัวเรื่อง -->                
            <div class = "container">
              <div class = "topic">

              <table>
              <tr><td><h3><b>บริษัท '.$row2["Name_company"].' จำกัด</b></h3></td>      <td style = "width: 140px;"></td>       <td><table><tr><th style = "text-align:center;border: 3px solid #FF8C00;"><h4>สำหรับบัญชี</h4></th></tr></table></td></tr>
              <tr><td style = "width: 400px;">ที่อยู่ : '.$row2["Address_company"].' </td>       <td></td></tr>
              <tr><td>โทร. '.$row2["Phone_company"].' เลขประจำตัวผู้เสียภาษี '.$row2["ID_vat"].' </td>       <td></td></tr>
              </table>

              <br>
              <table>
                 <tr>
                  <td style = "width: 150px;"></td>
                  <td>
                  <table>
                  <tr>
                  <th style = "text-align:center;border: 3px solid #FF8C00;">สำเนาใบเสร็จรับเงิน<br>COPY RECEIPT</th>
                  </tr>
                  </table>
                  </td>
                  <td style = "width: 150px;"></td>
                 </tr> 
                </table>
               <br>
              
           
         
              <table>
              <tr><td style = "width: 350px;">นามลูกค้า '.$row["Name"].'</td>   <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>       <td>เลขที่</td><td style = "text-align:right">'.$ID_slip.'</td></tr>
              <tr><td style = "width: 350px;">ที่อยู่ '.$row["Address"].'</td>     <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>       <td>วันที่</td><td style = "text-align:right">'.$row["Date"].'</td></tr>
              <tr><td style = "width: 350px;">เลขประจำตัวผู้เสียภาษี '.$row["ID_Card"].'</td>  <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>    <td></td><td></td></tr>
              </table>



              </div>
<!-- ====== -->

            
<!-- ตาราง --> 
                  <table>
                  
                    <tr bgcolor ="DarkOrange">
                      <th style = "text-align:center">
                        ลำดับ
                      </th>
                      <th style = "text-align:center">
                        รายการ
                      </th>
                      <th style = "text-align:center">
                        จำนวน
                      </th>
                      <th style = "text-align:center">
                        ราคาต่อหน่วย
                      </th>
                      <th style = "text-align:center">
                        รวมเงิน
                      </th>
                    </tr>';

                    $mpdf->WriteHTML($text2);

                    $conn1 = mysqli_connect("localhost", "id14233127_data", "Qwertyui-12345678", "id14233127_accom");
			if (!$conn1) {
				echo "มีปัญหาบางอย่างขัดข้องในการเชื่อมต่อ โปรดติดต่อกีตาร์";
			} else {
				$sql1 = "SELECT ID_sale,ID_stock,Name_stock,Num_select,Sell_unit,Sum_unit FROM sale_stock WHERE ID_sale = '".$number."'";
        $result1 = $conn1->query($sql1);
        $i = 0;
				if ($result1->num_rows > 0) {
					while ($row1 = $result1->fetch_assoc()) {
            $i++;
						$text2_1 = '<tr valign="middle">
         
            <th style = "text-align:center"> '.$i.' </th>
            
            <th style = "text-align:center"> '. $row1["Name_stock"] .' </th>
            
            <th style = "text-align:center"> '. $row1["Num_select"] .' </th>
            
            <th style = "text-align:center"> '. number_format($row1["Sell_unit"],2) .'</th>
            
            <th style = "text-align:center"> '. number_format($row1["Sum_unit"],2) .' </th>
            
            </tr>
           
            
            ';
            
            $mpdf->WriteHTML($text2_1);
         
					}
				}
				$conn1->close();
			}
                
                $text2_2 = '
              </table>       
<!-- ===== -->      
<div style = "position: absolute;bottom: 5%;right: 7.5%; left: 7.5%">
<table>
 <tr><td style = "width: 410px;"> <table><tr><th style = "text-align:left"><h5>ตัวอักษร. ('.Convert($row['bye']).')</h5></th></tr></table></td>          <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">รวมเงิน </td> <td style = "text-align:right">'.number_format($row['Allcase'], 2).'  บาท</td></td></tr></table></tr>
 <tr><td><b>หมายเหตุ</b> <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">ส่วนลด </td> <td style = "text-align:right">'.number_format($row['Discount'], 2).'  บาท</td></td></tr></table></tr>
 <tr><td>'.$row['note'].' </td>                  <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">จำนวนเงินหลังหักส่วนลด </td> <td style = "text-align:right">'.number_format($row['Money'], 2).'  บาท</td></td></tr></table></tr>
 <tr><td></td>                   <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">ภาษีมูลค่าเพิ่ม 7% </td> <td style = "text-align:right">'.number_format($row['VAT_num'], 2).'  บาท</td></td></tr></table></tr>
 <tr><td></td>                  <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">จำนวนเงินรวม </td> <td style = "text-align:right">'.number_format($row['tota_vat'], 2).'  บาท</td></td></tr></table></tr>
 <tr><td></td>       <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">ภาษีหัก ณ ที่จ่าย 3% </td> <td style = "text-align:right">'.number_format($row['VAT_AT_num'], 2).'  บาท</td></td></tr></table></tr>
 <tr><td></td>       <td style = "border: 0px solid #000000; width: 250px;"><table><tr><td style = "text-align:left">จำนวนเงินทั้งสิ้น </td> <td style = "text-align:right">'.number_format($row['bye'], 2).'  บาท</td></td></tr></table></tr>
</table>
<br>


<table>
<tr><th style = "text-align:left"><h5>ได้รับสินค้าไว้เรียบร้อยแล้ว<br><br><br>ผู้รับสินค้า<br><br>วันที่</h5></th>  <th><h5>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;  <br><br><br>ผู้ส่งสินค้า<br><br>วันที่</h5></th>   <th style = "text-align:center"><h5>ในนาม บริษัท '.$row2["Name_company"].' จำกัด <br><br><br><br><br><br>ผู้มีอำนาจลงนาม</h5></th>  </tr>

</table>
</div>
            ';
   

             $mpdf->WriteHTML($text2_2);
             
                $mpdf->Output();
        }
    } else {
        echo "ไม่พบข้อมูล ข้อมูลอาจจะมีแค่ 0";
    }
    $conn->close();
}

?>