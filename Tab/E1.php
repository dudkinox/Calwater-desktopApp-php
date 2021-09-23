<p class="h1 text-center">ข้อมูลตัวอย่างน้ำ E1</p>
<div class="row">
    <div class="card card-primary p-0 col-12">
        <div class="card-header">
            <h3 class="card-title">กรอกข้อมูล</h3>
        </div>
        <div class="card-body">
            <div class="form-group">
                <label>Treatment Date:</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="text" id="Treatment_DateE1" value="<?php echo date("m/d/Y"); ?>" class="form-control datetimepicker-input" data-target="#reservationdate">
                    <div class="input-group-append" data-target="#reservationdate" data-toggle="datetimepicker">
                        <div class="input-group-text"><i class="fa fa-calendar"></i></div>
                    </div>
                </div>
            </div>
            <div class="row">
                <?php 
                    $queryBatch_No = "SELECT Batch_No FROM info WHERE `Batch_No` LIKE '%E1%' ORDER BY Batch_No DESC";
                    $resultBatch_No = $conn->query($queryBatch_No);
                    if($resultBatch_No->num_rows > 0){
                        $rowBatch_No = $resultBatch_No->fetch_assoc();
                        $No = substr($rowBatch_No["Batch_No"], 2, ); 
                        $No++;
                        $Batch_NoE1 = "E1".$No;
                    }
                    else{
                        $Batch_NoE1 = "E1202101";
                    }
                ?>
                <div class="form-group col-6">
                    <label>Batch No.*</label>
                    <div class="input-group date" id="reservationdate" data-target-input="nearest">
                        <input type="text" id="Batch_NoE1" class="form-control" readonly value="<?php echo $Batch_NoE1; ?>">
                    </div>
                </div>
                <div class="form-group col-6">
                    <label>Sump No.</label>
                    <div class="input-group date" id="reservationdate" data-target-input="nearest">
                        <input type="text" id="Sump_NoE1" class="form-control" readonly value="E1">
                    </div>
                </div>
            </div>
            <div class = "row">
            <div class="form-group col-4">
                <label>Vlume operation</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" id="VolumeE1" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
            <div class="form-group col-4">
                <label>Total Cr</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" id="Total_CrE1" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
            <div class="form-group col-4">
                <label>Cu</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" id="CuE1" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
            <div class="form-group col-6">
                <label>Mn</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" id="MnE1" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
            <div class="form-group col-6">
                <label>Ni</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" id="NiE1" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
            <div class="form-group col-6">
                <label>Pb</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" id="PbE1" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
            <div class="form-group col-6">
                <label>Zn</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" id="ZnE1" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
            </div>
        </div>
        <div class="card-footer">
            <div class="row text-center">
                <div class="col-6">
                    <img src="assets/image/cal.png" onclick="CalculateE1()" style="cursor: pointer" width="50" alt="คำนวณ">
                    <p>คำนวณ</p>
                </div>
                <div class="col-6">
                    <img onclick="SaveE1()" src="assets/image/save.png" style="cursor: pointer" width="50" alt="บันทึก">
                    <p>บันทึก</p>
                </div>
            </div>
        </div>
    </div>
</div>