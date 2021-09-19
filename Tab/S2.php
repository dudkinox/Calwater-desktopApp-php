<p class="h1 text-center">ข้อมูลตัวอย่างน้ำ S2</p>
<div class="row">
    <div class="card card-primary p-0 col-3">
        <div class="card-header">
            <h3 class="card-title">กรอกข้อมูล</h3>
        </div>
        <div class="card-body">
            <div class="form-group">
                <label>Treatment Date:</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="text" value="<?php echo date("m/d/Y"); ?>" class="form-control datetimepicker-input" data-target="#reservationdate">
                    <div class="input-group-append" data-target="#reservationdate" data-toggle="datetimepicker">
                        <div class="input-group-text"><i class="fa fa-calendar"></i></div>
                    </div>
                </div>
            </div>
            <div class="row">
                <div class="form-group col-6">
                    <label>Batch No.*</label>
                    <div class="input-group date" id="reservationdate" data-target-input="nearest">
                        <input type="text" class="form-control" readonly value="S2202101">
                    </div>
                </div>
                <div class="form-group col-6">
                    <label>Sump No.</label>
                    <div class="input-group date" id="reservationdate" data-target-input="nearest">
                        <input type="text" class="form-control" readonly value="S2">
                    </div>
                </div>
            </div>
            <div class="form-group">
                <label>Vlume operation</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
            <div class="form-group">
                <label>Total Cr</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
            <div class="form-group">
                <label>Cu</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
            <div class="form-group">
                <label>Mn</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
            <div class="form-group">
                <label>Ni</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
            <div class="form-group">
                <label>Pb</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
            <div class="form-group">
                <label>Zn</label>
                <div class="input-group date" id="reservationdate" data-target-input="nearest">
                    <input type="number" class="form-control" placeholder="กรอกตัวเลขทศนิยมได้">
                </div>
            </div>
        </div>
        <div class="card-footer">
            <div class="row text-center">
                <div class="col-6 ">
                    <img src="assets/image/cal.png" style="cursor: pointer" width="50" alt="คำนวณ">
                    <p>คำนวณ</p>
                </div>
                <div class="col-6">
                    <img src="assets/image/save.png" style="cursor: pointer" width="50" alt="บันทึก">
                    <p>บันทึก</p>
                </div>
            </div>
        </div>
    </div>
    <div class="card card-success p-0 col-9">
        <div class="card-header">
            <h3 class="card-title">ผลคำนวณ</h3>
        </div>
        <div class="card-body">
            <div class="row text-center">
                <div class="col-12">
                    <h5>Total metal <b class="text-danger">0.006857626</b> (mol)</h5>
                </div>
                <div class="col-sm-3">
                    <h4 class="text-center text-dark">Ca(OH)2 (g)</h4>
                    <div class="color-palette-set mt-3">
                        <div class="bg-black color-palette">
                            <span>0.629833021</span>
                        </div>
                        <div class="bg-black disabled color-palette"><span> Theoretical</span></div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-black color-palette">
                            <span>92.32722257</span>
                        </div>
                        <div class="bg-black disabled color-palette">
                            <span>Model</span>
                        </div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-black color-palette">
                            <span>92.3965042</span>
                        </div>
                        <div class="bg-black disabled color-palette">
                            <span>Lab</span>
                        </div>
                    </div>
                </div>
                <div class="col-sm-3">
                    <h4 class="text-center text-primary">FeSO4 (g).</h4>
                    <div class="color-palette-set mt-3">
                        <div class="bg-primary color-palette"><span>2.221446155</span></div>
                        <div class="bg-primary disabled color-palette"><span>Theoretical</span></div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-primary color-palette"><span>128.1996576</span></div>
                        <div class="bg-primary disabled color-palette"><span>Operation by model</span></div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-primary color-palette"><span>112.5828911</span></div>
                        <div class="bg-primary disabled color-palette"><span>Operation by lab</span></div>
                    </div>
                </div>
                <div class="col-sm-3">
                    <h4 class="text-center text-danger">NaOCl</h4>
                    <div class="color-palette-set mt-3">
                        <div class="bg-danger color-palette"><span>133.3</span></div>
                        <div class="bg-danger disabled color-palette"><span>Model</span></div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-danger color-palette"><span>133.3</span></div>
                        <div class="bg-danger disabled color-palette"><span>Model</span></div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-danger color-palette"><span>110</span></div>
                        <div class="bg-danger disabled color-palette"><span>Lab</span></div>
                    </div>
                </div>
                <div class="col-sm-3">
                    <h4 class="text-center text-warning">TDS</h4>

                    <div class="color-palette-set mt-3">
                        <div class="bg-warning color-palette"><span>8,413.21</span></div>
                        <div class="bg-warning disabled color-palette"><span>Model</span></div>
                    </div>
                    <div class="color-palette-set mt-3">
                        <div class="bg-warning color-palette"><span>8,055.64</span></div>
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
</div>