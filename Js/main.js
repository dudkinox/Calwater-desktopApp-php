function Save(){
    var Treatment_Date = document.getElementById("Treatment_Date").value;
    var Batch_No = document.getElementById("Batch_No").value;
    var Sump_No = document.getElementById("Sump_No").value;
    var Volume = document.getElementById("Volume").value;
    var Total_Cr = document.getElementById("Total_Cr").value;
    var Cu = document.getElementById("Cu").value;
    var Mn = document.getElementById("Mn").value;
    var Ni = document.getElementById("Ni").value;
    var Pb = document.getElementById("Pb").value;
    var Zn = document.getElementById("Zn").value;
    window.location.href = "Router/?Treatment_Date=" + Treatment_Date + 
                            "&Batch_No=" + Batch_No + 
                            "&Sump_No=" + Sump_No +
                            "&Volume=" + Volume +
                            "&Total_Cr=" + Total_Cr +
                            "&Cu=" + Cu +
                            "&Mn=" + Mn +
                            "&Ni=" + Ni +
                            "&Pb=" + Pb +
                            "&Zn=" + Zn;
}