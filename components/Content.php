<div class="col-11 mt-3 border-raduis">
    <div class="card text-center text-dark rounded">
        <p class="mt-3 h1 text-shadow">ระบบคำนวณระบบน้ำตัวอย่าง</p>
    </div>
    <div class="row">
        <div class="col-lg-4 col-6">
            <div class="small-box bg-info">
                <div class="inner">
                    <h3>S2</h3>
                    <p>2,200 ข้อมูล</p>
                </div>
                <a href="#" class="small-box-footer">อัพเดตล่าสุด <i class="fas fa-arrow-circle-right"></i> 20 ก.ย. 2564</a>
            </div>
        </div>
        <div class="col-lg-4 col-6">
            <div class="small-box bg-success">
                <div class="inner">
                    <h3>S3</h3>
                    <p>2,200 ข้อมูล</p>
                </div>
                <a href="#" class="small-box-footer">อัพเดตล่าสุด <i class="fas fa-arrow-circle-right"></i> 20 ก.ย. 2564</a>
            </div>
        </div>
        <div class="col-lg-4 col-6">
            <div class="small-box bg-warning">
                <div class="inner">
                    <h3>E1</h3>
                    <p>2,200 ข้อมูล</p>
                </div>
                <a href="#" class="small-box-footer">อัพเดตล่าสุด <i class="fas fa-arrow-circle-right"></i> 20 ก.ย. 2564</a>
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
                        <th colspan="2" class="bg-warning">NaOCl</th>
                        <th colspan="2" class="bg-danger">TDS</th>
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
                    </tr>
                </tbody>
            </table>
        </div>
        <!-- /.card-body -->
    </div>
</div>