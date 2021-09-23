<div class="card card-success p-0 col-12">
        <div class="card-header">
            <h3 class="card-title">ผลคำนวณ</h3>
        </div>
        <div class="card-body">
            <div class="row text-center">
                <div class="col-12">
                    <h5>Total metal <b class="text-danger"><span id = "ShowTotal_metal"></span></b> (mol)</h5>
                </div>
                <div class="col-sm-3">
                    <h4 class="text-center text-dark">Ca(OH)2 (g)</h4>
                    <div class="color-palette-set mt-3">
                        <div class="bg-black color-palette">
                            <span id = "ShowTheoreticalCa"></span>
                        </div>
                        <div class="bg-black disabled color-palette"><span>Theoretical</span></div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-black color-palette">
                            <span id = "ShowModelCa"></span>
                        </div>
                        <div class="bg-black disabled color-palette">
                            <span>Model</span>
                        </div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-black color-palette">
                            <span id = "ShowLabCa"></span>
                        </div>
                        <div class="bg-black disabled color-palette">
                            <span>Lab</span>
                        </div>
                    </div>
                </div>
                <div class="col-sm-3">
                    <h4 class="text-center text-primary">FeSO4 (g).</h4>
                    <div class="color-palette-set mt-3">
                        <div class="bg-primary color-palette"><span id = "TheoreticalFe"></span></div>
                        <div class="bg-primary disabled color-palette"><span>Theoretical</span></div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-primary color-palette"><span id = "ModelFe"></span></div>
                        <div class="bg-primary disabled color-palette"><span>Operation by model</span></div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-primary color-palette"><span id = "LabFe"></span></div>
                        <div class="bg-primary disabled color-palette"><span>Operation by lab</span></div>
                    </div>
                </div>
                <div class="col-sm-3">
                    <h4 class="text-center text-danger">NaOCl</h4>
                    <div class="color-palette-set mt-3">
                        <div class="bg-danger color-palette"><span id = "ModelNaOCl"></span></div>
                        <div class="bg-danger disabled color-palette"><span>Model</span></div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-danger color-palette"><span id = "ModelNa"></span></div>
                        <div class="bg-danger disabled color-palette"><span>Model</span></div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-danger color-palette"><span id = "LabNa"></span></div>
                        <div class="bg-danger disabled color-palette"><span>Lab</span></div>
                    </div>
                </div>
                <div class="col-sm-3">
                    <h4 class="text-center text-warning">TDS</h4>

                    <div class="color-palette-set mt-3">
                        <div class="bg-warning color-palette"><span id = "ModelTDS"></span></div>
                        <div class="bg-warning disabled color-palette"><span>Model</span></div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-warning color-palette"><span id = "LabTDS"></span></div>
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
                            $query = "SELECT Batch_No, Sump_No, Volume, B.
                                        FROM info AS A
                                        INNER JOIN raw_waste_water_analysis
                                        ON A.RWWA_ID = B.ID";
                            ?>
                            <tr>
                                <td>Other browsers</td>
                                <td>All others</td>
                                <td>-</td>
                                <td>-</td>
                                <td>U</td>
                                <td>U</td>
                                <td>U</td>
                                <td>U</td>
                                <td>U</td>
                                <td>U</td>
                                <td>U</td>
                                <td>
                                    <img src="assets/image/bin.png" style="cursor: pointer" width="30" alt="ลบ">
                                </td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    </div>