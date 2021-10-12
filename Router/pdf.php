<?php
// Get data
$page = isset($_GET["page"]) ? $_GET["page"] : '';
// data Topic

require_once __DIR__ . '/../lib/pdf/vendor/autoload.php';
require('../Database/connection.php');

$mpdf = new \Mpdf\Mpdf(['format' => 'A4-L']);

$style = '
<style>
    .container{
        font-family: "Garuda";
    }
    .container .wrapper{
        font-size: 12pt;
        text-align: center;
    }
    h3{
    text-align: center;
    font-family: "Garuda";
    }
    h4{
    font-family: "Garuda";
    }
    p{
    font-family: "Garuda";
    }
    /* วันที่ */
    .date{
    position: relative;
    left: 60%;
    }
    #customers {
        font-family: Arial, Helvetica, sans-serif;
        border-collapse: collapse;
        width: 100%;
        font-family: "Garuda";
    }
    
    #customers td, #customers th {
        border: 1px solid #000;
        padding: 8px;
    }
    
    #customers tr:nth-child(even){background-color: #f2f2f2;}
    
    #customers tr:hover {background-color: #ddd;}
    
    #customers th {
        padding-top: 12px;
        padding-bottom: 12px;
        text-align: center;
        color: #000;
    }

    td{
        text-align: center;
    }
</style>';
$mpdf->WriteHTML($style);

$text = '
<div class = "container">
    <div class="wrapper">
        <p>รายงานข้อมูลน้ำตัวอย่าง</p>
        <table id = "customers">
            <tr>
                <th colspan="10"></th>
                <th colspan="2">Ca(OH)2 (g)</th>
                <th colspan="2">FeSO4 (g)</th>
                <th colspan="2">NaOCl (ml)</th>
                <th colspan="2">TDS (mg/l)</th>
            </tr>
            <tr>
                <th>Batch No.*</th>
                <th>Sump No.</th>
                <th>Treatment Date</th>
                <th>Vlume operation</th>
                <th>Total Cr</th>
                <th>Cu</th>
                <th>Mn</th>
                <th>Ni</th>
                <th>Pb</th>
                <th>Zn</th>
                <th>Model</th>
                <th>Lab</th>
                <th>Model</th>
                <th>Lab</th>
                <th>Model</th>
                <th>Lab</th>
                <th>Model</th>
                <th>Lab</th>
            </tr>';
$mpdf->WriteHTML($text);
switch ($page) {
    case "dashboard":
        $query = "SELECT Batch_No,
                Sump_No, 
                Treatment_Date,
                B.model AS camodel,
                B.lab AS calab,
                C.model AS femodel,
                C.lab AS felab,
                D.model AS namodel,
                D.lab AS nalab,
                E.model  AS tdsmodel,
                E.lab AS tdslab,
                F.Vlume AS Vlume,
                F.Total_Cr AS Total_Cr,
                F.Cu AS Cu,
                F.Mn AS Mn,
                F.Ni AS Ni,
                F.Pb AS Pb,
                F.Zn AS Zn
            FROM info AS A
            INNER JOIN ca AS B
            ON A.Ca = B.No
            INNER JOIN fe AS C
            ON A.Fe = C.No
            INNER JOIN na AS D
            ON A.Na = D.No
            INNER JOIN tds AS E
            ON A.TDS = E.No
            INNER JOIN input AS F
            ON A.tds = F.No";
        break;
    case "s2":
        $query = "SELECT Batch_No,
                Sump_No, 
                Treatment_Date,
                B.model AS camodel,
                B.lab AS calab,
                C.model AS femodel,
                C.lab AS felab,
                D.model AS namodel,
                D.lab AS nalab,
                E.model  AS tdsmodel,
                E.lab AS tdslab,
                F.Vlume AS Vlume,
                F.Total_Cr AS Total_Cr,
                F.Cu AS Cu,
                F.Mn AS Mn,
                F.Ni AS Ni,
                F.Pb AS Pb,
                F.Zn AS Zn
                FROM info AS A
                INNER JOIN ca AS B
                ON A.Ca = B.No
                INNER JOIN fe AS C
                ON A.Fe = C.No
                INNER JOIN na AS D
                ON A.Na = D.No
                INNER JOIN tds AS E
                ON A.TDS = E.No
                INNER JOIN input AS F
                ON A.tds = F.No
                WHERE A.Sump_No = 'S2'";
        break;
    case "s3":
        $query = "SELECT Batch_No,
                Sump_No, 
                Treatment_Date,
                B.model AS camodel,
                B.lab AS calab,
                C.model AS femodel,
                C.lab AS felab,
                D.model AS namodel,
                D.lab AS nalab,
                E.model  AS tdsmodel,
                E.lab AS tdslab,
                F.Vlume AS Vlume,
                F.Total_Cr AS Total_Cr,
                F.Cu AS Cu,
                F.Mn AS Mn,
                F.Ni AS Ni,
                F.Pb AS Pb,
                F.Zn AS Zn
                FROM info AS A
                INNER JOIN ca AS B
                ON A.Ca = B.No
                INNER JOIN fe AS C
                ON A.Fe = C.No
                INNER JOIN na AS D
                ON A.Na = D.No
                INNER JOIN tds AS E
                ON A.TDS = E.No
                INNER JOIN input AS F
                ON A.tds = F.No
                WHERE A.Sump_No = 'S3'";
        break;
    case "e1":
        $query = "SELECT Batch_No,
                Sump_No, 
                Treatment_Date,
                B.model AS camodel,
                B.lab AS calab,
                C.model AS femodel,
                C.lab AS felab,
                D.model AS namodel,
                D.lab AS nalab,
                E.model  AS tdsmodel,
                E.lab AS tdslab,
                F.Vlume AS Vlume,
                F.Total_Cr AS Total_Cr,
                F.Cu AS Cu,
                F.Mn AS Mn,
                F.Ni AS Ni,
                F.Pb AS Pb,
                F.Zn AS Zn
                FROM info AS A
                INNER JOIN ca AS B
                ON A.Ca = B.No
                INNER JOIN fe AS C
                ON A.Fe = C.No
                INNER JOIN na AS D
                ON A.Na = D.No
                INNER JOIN tds AS E
                ON A.TDS = E.No
                INNER JOIN input AS F
                ON A.tds = F.No
                WHERE A.Sump_No = 'e1'";
        break;
}
$result = $conn->query($query);
if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        $text2 = '
            <tr>
                <td>' . $row["Sump_No"] . $row["Batch_No"] . '</td>
                <td>' . $row["Sump_No"] . '</td>
                <td>' . $row["Treatment_Date"] . '</td>
                <td>' . $row["Vlume"] . '</td>
                <td>' . $row["Total_Cr"] . '</td>
                <td>' . $row["Cu"] . '</td>
                <td>' . $row["Mn"] . '</td>
                <td>' . $row["Ni"] . '</td>
                <td>' . $row["Pb"] . '</td>
                <td>' . $row["Zn"] . '</td>
                <td>' . $row["camodel"] . ' <br>(g/Volume operated)</td>
                <td>' . $row["calab"] . ' <br>(g/Volume operated)</td>
                <td>' . $row["femodel"] . ' <br>(g/Volume operated)</td>
                <td>' . $row["felab"] . ' <br>(g/Volume operated)</td>
                <td>' . $row["namodel"] . ' <br>(mL/Volume operated)</td>
                <td>' . $row["nalab"] . ' <br>(mL/Volume operated)</td>
                <td>' . number_format($row["tdsmodel"], 2) . '</td>
                <td>' . number_format($row["tdslab"], 2) . '</td>
            </tr>';
        $mpdf->WriteHTML($text2);
    }
}
$end = '
        </table>
    </div>
</div>';
$mpdf->WriteHTML($end);

$mpdf->Output();
$conn->close();
