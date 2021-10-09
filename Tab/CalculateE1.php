<div class="card card-success p-0 col-12">
    <div class="card-header">
        <h3 class="card-title">ผลคำนวณ</h3>
    </div>
    <div class="card-body">
        <div class="row text-center">
            <div class="col-12">
                <h5>Total metal <b class="text-danger"><span id="ShowTotal_metalE1"></span></b> (mol)</h5>
            </div>
            <div class="col-sm-3">
                <h4 class="text-center text-dark">Ca(OH)2 (g)</h4>
                <div class="color-palette-set mt-3">
                    <div class="bg-black color-palette">
                        <span id="ShowTheoreticalCaE1"></span>
                    </div>
                    <div class="bg-black disabled color-palette"><span>Theoretical</span></div>
                </div>
                <div class="color-palette-set mt-3">
                    <div class="bg-black color-palette">
                        <span id="ShowModelCaE1"></span>
                    </div>
                    <div class="bg-black disabled color-palette">
                        <span>Model</span>
                    </div>
                </div>
                <div class="color-palette-set mt-3">
                    <div class="bg-black color-palette">
                        <span id="ShowLabCaE1"></span>
                    </div>
                    <div class="bg-black disabled color-palette">
                        <span>Lab</span>
                    </div>
                </div>
            </div>
            <div class="col-sm-3">
                <h4 class="text-center text-primary">FeSO4 (g).</h4>
                <div class="color-palette-set mt-3">
                    <div class="bg-primary color-palette"><span id="TheoreticalFeE1"></span></div>
                    <div class="bg-primary disabled color-palette"><span>Theoretical</span></div>
                </div>
                <div class="color-palette-set mt-3">
                    <div class="bg-primary color-palette"><span id="ModelFeE1"></span></div>
                    <div class="bg-primary disabled color-palette"><span>Operation by model</span></div>
                </div>
                <div class="color-palette-set mt-3">
                    <div class="bg-primary color-palette"><span id="LabFeE1"></span></div>
                    <div class="bg-primary disabled color-palette"><span>Operation by lab</span></div>
                </div>
            </div>
            <div class="col-sm-3">
                <h4 class="text-center text-danger">NaOCl</h4>
                <div class="color-palette-set mt-3">
                    <div class="bg-danger color-palette"><span id="ModelNaOClE1"></span></div>
                    <div class="bg-danger disabled color-palette"><span>Model</span></div>
                </div>
                <div class="color-palette-set mt-3">
                    <div class="bg-danger color-palette"><span id="ModelNaE1"></span></div>
                    <div class="bg-danger disabled color-palette"><span>Model</span></div>
                </div>
                <div class="color-palette-set mt-3">
                    <div class="bg-danger color-palette"><span id="LabNaE1"></span></div>
                    <div class="bg-danger disabled color-palette"><span>Lab</span></div>
                </div>
            </div>
            <div class="col-sm-3">
                <h4 class="text-center text-warning">TDS</h4>

                <div class="color-palette-set mt-3">
                    <div class="bg-warning color-palette"><span id="ModelTDSE1"></span></div>
                    <div class="bg-warning disabled color-palette"><span>Model</span></div>
                </div>
                <div class="color-palette-set mt-3">
                    <div class="bg-warning color-palette"><span id="LabTDSE1"></span></div>
                    <div class="bg-warning disabled color-palette"><span>Lab</span></div>
                </div>
            </div>
        </div>
        
        <div class="card-body p-0 bg-light text-dark mt-5">
            <div class="card-header bg-success">
                <h3 class="card-title">ข้อมูลรายละเอียดน้ำ</h3>
            </div>
            <div class="card-body">
                <table id="example1" class="table table-bordered table-striped text-center">
                    <thead>
                        <tr>
                            <th colspan="3" class="bg-secondary"></th>
                            <th colspan="2" class="bg-info">Ca(OH)2 (g)</th>
                            <th colspan="2" class="bg-success">FeSO4 (g)</th>
                            <th colspan="2" class="bg-warning">NaOCl</th>
                            <th colspan="2" class="bg-danger">TDS</th>
                            <th class="bg-dark"></th>
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
                            <th class="bg-dark">Manage</th>
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
                            E.lab AS tdslab,
                            E.No AS id
                            FROM info AS A
                            INNER JOIN ca AS B
                            ON A.Ca = B.No
                            INNER JOIN fe AS C
                            ON A.Fe = C.No
                            INNER JOIN na AS D
                            ON A.Na = D.No
                            INNER JOIN tds AS E
                            ON A.TDS = E.No
                            WHERE A.Sump_No = 'E1'";
                        $result = $conn->query($query);
                        if ($result->num_rows > 0) {
                            while ($row = $result->fetch_assoc()) {
                        ?>
                                <tr>
                                    <td><?php echo $row["Batch_No"]; ?></td>
                                    <td><?php echo $row["Sump_No"]; ?></td>
                                    <td><?php echo $row["Treatment_Date"]; ?></td>
                                    <td><?php echo $row["camodel"]; ?></td>
                                    <td><?php echo $row["calab"]; ?></td>
                                    <td><?php echo $row["femodel"]; ?></td>
                                    <td><?php echo $row["felab"]; ?></td>
                                    <td><?php echo $row["namodel"]; ?></td>
                                    <td><?php echo $row["nalab"]; ?></td>
                                    <td><?php echo $row["tdsmodel"]; ?></td>
                                    <td><?php echo $row["tdslab"]; ?></td>
                                    <td>
                                        <img src="assets/image/bin.png" onclick="sendID('<?php echo $row['Batch_No']; ?>', '<?php echo $row['id']; ?>')" type="button" width="30" alt="ลบ">
                                    </td>
                                </tr>
                        <?php }
                        } ?>
                    </tbody>
                </table>
            </div>
        </div>
    </div>
</div>