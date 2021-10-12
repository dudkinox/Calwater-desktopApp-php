<?php

require_once '../lib/PHPExcel-1.8/Classes/PHPExcel.php';
require('../Database/connection.php');

header('Content-Type: application/vnd-ms-excel');
header('Content-Disposition: attachment;filename="รายงานระบบน้ำตัวอย่าง.xls"');
$page = isset($_GET["page"]) ? $_GET["page"] : '';
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
?>

<table id="example1" class="table table-bordered table-striped text-center">
    <thead>
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
        </tr>
    </thead>
    <tbody>
        <?php
        $result = $conn->query($query);
        if ($result->num_rows > 0) {
            while ($row = $result->fetch_assoc()) {
        ?>
                <tr>
                    <td><?php echo $row["Sump_No"] . $row["Batch_No"]; ?></td>
                    <td><?php echo $row["Sump_No"]; ?></td>
                    <td><?php echo $row["Treatment_Date"]; ?></td>
                    <td><?php echo $row["Vlume"]; ?></td>
                    <td><?php echo $row["Total_Cr"]; ?></td>
                    <td><?php echo $row["Cu"]; ?></td>
                    <td><?php echo $row["Mn"]; ?></td>
                    <td><?php echo $row["Ni"]; ?></td>
                    <td><?php echo $row["Pb"]; ?></td>
                    <td><?php echo $row["Zn"]; ?></td>
                    <td><?php echo $row["camodel"]; ?> (g/Volume operated)</td>
                    <td><?php echo $row["calab"]; ?> (g/Volume operated)</td>
                    <td><?php echo $row["femodel"]; ?> (g/Volume operated)</td>
                    <td><?php echo $row["felab"]; ?> (g/Volume operated)</td>
                    <td><?php echo $row["namodel"]; ?> (mL/Volume operated)</td>
                    <td><?php echo $row["nalab"]; ?> (mL/Volume operated)</td>
                    <td><?php echo number_format($row["tdsmodel"], 2); ?></td>
                    <td><?php echo number_format($row["tdslab"], 2); ?></td>
                </tr>
            <?php
            }
        } else {
            ?>
            <tr></tr>
        <?php } ?>
    </tbody>
</table>