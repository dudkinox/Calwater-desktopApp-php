<?php
require('Router/order.php');
?>
<div class="col-11 mt-3 border-raduis">
    <div class="card text-center text-dark rounded">
        <p class="mt-3 h1 text-shadow">ระบบคำนวณระบบน้ำตัวอย่าง</p>
    </div>
    <div class="row">
        <div class="col-lg-4 col-6">
            <div class="small-box bg-info">
                <div class="inner">
                    <h3>S2</h3>
                    <p><?php echo number_format(Order('S2')); ?> ข้อมูล</p>
                </div>
                <a href="#" class="small-box-footer">อัพเดตล่าสุด <i class="fas fa-arrow-circle-right"></i> <?php echo UpdateDate('S2'); ?></a>
            </div>
        </div>
        <div class="col-lg-4 col-6">
            <div class="small-box bg-success">
                <div class="inner">
                    <h3>S3</h3>
                    <p><?php echo number_format(Order('S3')); ?> ข้อมูล</p>
                </div>
                <a href="#" class="small-box-footer">อัพเดตล่าสุด <i class="fas fa-arrow-circle-right"></i> <?php echo UpdateDate('S3'); ?></a>
            </div>
        </div>
        <div class="col-lg-4 col-6">
            <div class="small-box bg-warning">
                <div class="inner">
                    <h3>E1</h3>
                    <p><?php echo number_format(Order('E1')); ?> ข้อมูล</p>
                </div>
                <a href="#" class="small-box-footer">อัพเดตล่าสุด <i class="fas fa-arrow-circle-right"></i> <?php echo UpdateDate('E1'); ?></a>
            </div>
        </div>
    </div>
    <div class="card card-danger">
        <div class="card-header">
            <h3 class="card-title">จำนวนข้อมูลน้ำ</h3>
            <div class="card-tools">
                <button type="button" class="btn btn-tool" data-card-widget="collapse">
                    <i class="fas fa-minus"></i>
                </button>
            </div>
        </div>
        <div class="card-body">
            <div class="chartjs-size-monitor">
                <div class="chartjs-size-monitor-expand">
                    <div class=""></div>
                </div>
                <div class="chartjs-size-monitor-shrink">
                    <div class=""></div>
                </div>
            </div>
            <canvas id="donutChart" style="min-height: 250px; height: 250px; max-height: 250px; max-width: 100%; display: block;" width="391" height="250" class="chartjs-render-monitor"></canvas>
        </div>
    </div>
    <div class="card text-dark">
        <div class="card-header bg-success">
            <h3 class="card-title">ข้อมูลรายละเอียดน้ำ</h3>
        </div>
        <!-- /.card-header -->
        <div class="card-body">
            <table id="example1" class="table table-bordered table-striped text-center">
                <thead>
                    <tr>
                        <th colspan="3" class="bg-secondary"></th>
                        <th colspan="2" class="bg-info">Ca(OH)2 (g)</th>
                        <th colspan="2" class="bg-success">FeSO4 (g)</th>
                        <th colspan="2" class="bg-warning">NaOCl (ml)</th>
                        <th colspan="2" class="bg-danger">TDS (mg/l)</th>
                    </tr>
                    <tr>
                        <th class="bg-warning">Batch No.*</th>
                        <th class="bg-warning">Sump No.</th>
                        <th class="bg-warning">Treatment Date</th>
                        <th class="bg-info">Model</th>
                        <th class="bg-info">Lab</th>
                        <th class="bg-success">Model</th>
                        <th class="bg-success">Lab</th>
                        <th class="bg-warning">Model</th>
                        <th class="bg-warning">Lab</th>
                        <th class="bg-danger">Model</th>
                        <th class="bg-danger">Lab</th>
                    </tr>
                </thead>
                <tbody>
                    <?php
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
                                     E.lab AS tdslab
                                FROM info AS A
                                INNER JOIN ca AS B
                                ON A.Ca = B.No
                                INNER JOIN fe AS C
                                ON A.Fe = C.No
                                INNER JOIN na AS D
                                ON A.Na = D.No
                                INNER JOIN tds AS E
                                ON A.TDS = E.No";
                    $result = $conn->query($query);
                    if ($result->num_rows > 0) {
                        while ($row = $result->fetch_assoc()) {
                    ?>
                            <tr>
                                <td><?php echo $row["Sump_No"] . $row["Batch_No"]; ?></td>
                                <td><?php echo $row["Sump_No"]; ?></td>
                                <td><?php echo $row["Treatment_Date"]; ?></td>
                                <td><?php echo $row["camodel"]; ?> <br>(g/Volume operated)</td>
                                <td><?php echo $row["calab"]; ?> <br>(g/Volume operated)</td>
                                <td><?php echo $row["femodel"]; ?> <br>(g/Volume operated)</td>
                                <td><?php echo $row["felab"]; ?> <br>(g/Volume operated)</td>
                                <td><?php echo $row["namodel"]; ?> <br>(mL/Volume operated)</td>
                                <td><?php echo $row["nalab"]; ?> <br>(mL/Volume operated)</td>
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
        </div>
        <!-- /.card-body -->
    </div>
</div>