<input type="text" style="display: none;" value="" id="totalmetal">
<input type="text" style="display: none;" value="" id="ca">
<input type="text" style="display: none;" value="" id="modelca">
<input type="text" style="display: none;" value="" id="labca">
<input type="text" style="display: none;" value="" id="fe">
<input type="text" style="display: none;" value="" id="modelfe">
<input type="text" style="display: none;" value="" id="labfe">
<input type="text" style="display: none;" value="" id="na">
<input type="text" style="display: none;" value="" id="modelna">
<input type="text" style="display: none;" value="" id="labna">
<input type="text" style="display: none;" value="" id="modeltds">
<input type="text" style="display: none;" value="" id="labtds">
<p class="h1 text-center">ข้อมูลตัวอย่างน้ำ S3</p>
<div class="row">
    <div class="card card-primary p-0 col-12">
        <div class="card-header">
            <h3 class="card-title">กรอกข้อมูล</h3>
        </div>
        <div class="card-body">
            <div class="form-group">
                <label>Treatment Date:</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="text" id="Treatment_DateS3" value="<?php echo date("m/d/Y"); ?>" class="form-control datetimepicker-input" data-target="#reservationdate">
                    <div class="input-group-append" data-target="#reservationdate" data-toggle="datetimepicker">
                        <div class="input-group-text"><i class="fa fa-calendar"></i></div>
                    </div>
                </div>
            </div>
            <div class="row">
                <?php
                $queryBatch_No = "SELECT Batch_No FROM info ORDER BY Batch_No DESC";
                $resultBatch_No = $conn->query($queryBatch_No);
                if ($resultBatch_No->num_rows > 0) {
                    $rowBatch_No = $resultBatch_No->fetch_assoc();
                    $No = $rowBatch_No["Batch_No"];
                    $No++;
                    $Batch_NoS3 = $No;
                } else {
                    $Batch_NoS3 = "2021001";
                }
                ?>
                <div class="form-group col-6">
                    <label>Batch No.*</label>
                    <div class="input-group date" id="reservationdate" data-target-input="nearest">
                        <input type="text" id="Batch_NoS3" class="form-control" value="<?php echo 'S3' . $Batch_NoS3; ?>">
                    </div>
                </div>
                <div class="form-group col-6">
                    <label>Sump No.</label>
                    <div class="input-group date" id="reservationdate" data-target-input="nearest">
                        <input type="text" id="Sump_NoS3" class="form-control" readonly value="S3">
                    </div>
                </div>
            </div>
            <div class="row">
                <div class="form-group col-4">
                    <label>Vlume operation (L)</label>
                    <div class="input-group date" id="reservationdate" data-target-input="nearest">
                        <input type="number" id="VolumeS3" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                    </div>
                </div>
                <div class="form-group col-4">
                    <label>Total Cr</label>
                    <div class="input-group date" id="reservationdate" data-target-input="nearest">
                        <input type="number" id="Total_CrS3" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                    </div>
                </div>
                <div class="form-group col-4">
                    <label>Cu</label>
                    <div class="input-group date" id="reservationdate" data-target-input="nearest">
                        <input type="number" id="CuS3" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                    </div>
                </div>
                <div class="form-group col-6">
                    <label>Mn</label>
                    <div class="input-group date" id="reservationdate" data-target-input="nearest">
                        <input type="number" id="MnS3" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                    </div>
                </div>
                <div class="form-group col-6">
                    <label>Ni</label>
                    <div class="input-group date" id="reservationdate" data-target-input="nearest">
                        <input type="number" id="NiS3" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                    </div>
                </div>
                <div class="form-group col-6">
                    <label>Pb</label>
                    <div class="input-group date" id="reservationdate" data-target-input="nearest">
                        <input type="number" id="PbS3" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                    </div>
                </div>
                <div class="form-group col-6">
                    <label>Zn</label>
                    <div class="input-group date" id="reservationdate" data-target-input="nearest">
                        <input type="number" id="ZnS3" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                    </div>
                </div>
            </div>
        </div>
        <div class="card-footer">
            <div class="row text-center">
                <div class="col-6">
                    <img src="assets/image/cal.png" onclick="CalculateS3()" style="cursor: pointer" width="50" alt="คำนวณ">
                    <p>คำนวณ</p>
                </div>
                <div class="col-6">
                    <img onclick="SaveS3()" src="assets/image/save.png" style="cursor: pointer" width="50" alt="บันทึก">
                    <p>บันทึก</p>
                </div>
            </div>
        </div>
    </div>
</div>