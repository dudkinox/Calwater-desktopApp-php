function SaveS2() {
    var Treatment_Date = document.getElementById("Treatment_DateS2").value;
    var Batch_No = document.getElementById("Batch_NoS2").value;
    var Sump_No = document.getElementById("Sump_NoS2").value;
    var Volume = document.getElementById("VolumeS2").value;
    var Total_Cr = document.getElementById("Total_CrS2").value;
    var Cu = document.getElementById("CuS2").value;
    var Mn = document.getElementById("MnS2").value;
    var Ni = document.getElementById("NiS2").value;
    var Pb = document.getElementById("PbS2").value;
    var Zn = document.getElementById("ZnS2").value;
    var totalmetal = document.getElementById("totalmetal").value;
    var ca = document.getElementById("ca").value;
    var modelca = document.getElementById("modelca").value;
    var labca = document.getElementById("labca").value;
    var fe = document.getElementById("fe").value;
    var modelfe = document.getElementById("modelfe").value;
    var labfe = document.getElementById("labfe").value;
    var na = document.getElementById("na").value;
    var modelna = document.getElementById("modelna").value;
    var labna = document.getElementById("labna").value;
    var modeltds = document.getElementById("modeltds").value;
    var labtds = document.getElementById("labtds").value;
    window.location.href = "Router/?Treatment_Date=" + Treatment_Date +
        "&Batch_No=" + Batch_No +
        "&Sump_No=" + Sump_No +
        "&Volume=" + Volume +
        "&Total_Cr=" + Total_Cr +
        "&Cu=" + Cu +
        "&Mn=" + Mn +
        "&Ni=" + Ni +
        "&Pb=" + Pb +
        "&totalmetal=" + totalmetal +
        "&ca=" + ca +
        "&modelca=" + modelca +
        "&labca=" + labca +
        "&fe=" + fe +
        "&modelfe=" + modelfe +
        "&labfe=" + labfe +
        "&na=" + na +
        "&modelna=" + modelna +
        "&labna=" + labna +
        "&modeltds=" + modeltds +
        "&labtds=" + labtds +
        "&Zn=" + Zn;
}

function SaveS3() {
    var Treatment_Date = document.getElementById("Treatment_DateS3").value;
    var Batch_No = document.getElementById("Batch_NoS3").value;
    var Sump_No = document.getElementById("Sump_NoS3").value;
    var Volume = document.getElementById("VolumeS3").value;
    var Total_Cr = document.getElementById("Total_CrS3").value;
    var Cu = document.getElementById("CuS3").value;
    var Mn = document.getElementById("MnS3").value;
    var Ni = document.getElementById("NiS3").value;
    var Pb = document.getElementById("PbS3").value;
    var Zn = document.getElementById("ZnS3").value;
    var totalmetal = document.getElementById("totalmetal").value;
    var ca = document.getElementById("ca").value;
    var modelca = document.getElementById("modelca").value;
    var labca = document.getElementById("labca").value;
    var fe = document.getElementById("fe").value;
    var modelfe = document.getElementById("modelfe").value;
    var labfe = document.getElementById("labfe").value;
    var na = document.getElementById("na").value;
    var modelna = document.getElementById("modelna").value;
    var labna = document.getElementById("labna").value;
    var modeltds = document.getElementById("modeltds").value;
    var labtds = document.getElementById("labtds").value;
    window.location.href = "Router/?Treatment_Date=" + Treatment_Date +
        "&Batch_No=" + Batch_No +
        "&Sump_No=" + Sump_No +
        "&Volume=" + Volume +
        "&Total_Cr=" + Total_Cr +
        "&Cu=" + Cu +
        "&Mn=" + Mn +
        "&Ni=" + Ni +
        "&Pb=" + Pb +
        "&totalmetal=" + totalmetal +
        "&ca=" + ca +
        "&modelca=" + modelca +
        "&labca=" + labca +
        "&fe=" + fe +
        "&modelfe=" + modelfe +
        "&labfe=" + labfe +
        "&na=" + na +
        "&modelna=" + modelna +
        "&labna=" + labna +
        "&modeltds=" + modeltds +
        "&labtds=" + labtds +
        "&Zn=" + Zn;
}

function SaveE1() {
    var Treatment_Date = document.getElementById("Treatment_DateE1").value;
    var Batch_No = document.getElementById("Batch_NoE1").value;
    var Sump_No = document.getElementById("Sump_NoE1").value;
    var Volume = document.getElementById("VolumeE1").value;
    var Total_Cr = document.getElementById("Total_CrE1").value;
    var Cu = document.getElementById("CuE1").value;
    var Mn = document.getElementById("MnE1").value;
    var Ni = document.getElementById("NiE1").value;
    var Pb = document.getElementById("PbE1").value;
    var Zn = document.getElementById("ZnE1").value;
    var totalmetal = document.getElementById("totalmetal").value;
    var ca = document.getElementById("ca").value;
    var modelca = document.getElementById("modelca").value;
    var labca = document.getElementById("labca").value;
    var fe = document.getElementById("fe").value;
    var modelfe = document.getElementById("modelfe").value;
    var labfe = document.getElementById("labfe").value;
    var na = document.getElementById("na").value;
    var modelna = document.getElementById("modelna").value;
    var labna = document.getElementById("labna").value;
    var modeltds = document.getElementById("modeltds").value;
    var labtds = document.getElementById("labtds").value;
    window.location.href = "Router/?Treatment_Date=" + Treatment_Date +
        "&Batch_No=" + Batch_No +
        "&Sump_No=" + Sump_No +
        "&Volume=" + Volume +
        "&Total_Cr=" + Total_Cr +
        "&Cu=" + Cu +
        "&Mn=" + Mn +
        "&Ni=" + Ni +
        "&Pb=" + Pb +
        "&totalmetal=" + totalmetal +
        "&ca=" + ca +
        "&modelca=" + modelca +
        "&labca=" + labca +
        "&fe=" + fe +
        "&modelfe=" + modelfe +
        "&labfe=" + labfe +
        "&na=" + na +
        "&modelna=" + modelna +
        "&labna=" + labna +
        "&modeltds=" + modeltds +
        "&labtds=" + labtds +
        "&Zn=" + Zn;
}

function sendID(id, no) {
    console.log(id,no);
    document.getElementById("deleteID").value = id;
    document.getElementById("noID").value = no;
    $('#exampleModal').modal('show');
}

function deleteID() {
    var id = document.getElementById("deleteID").value;
    var no = document.getElementById("noID").value;
    console.log(id, no);
    window.location.href = "Router/delete.php?delete=" + id + "&no=" + no;
}