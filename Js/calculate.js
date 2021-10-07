function CalculateS2() {
  var Volume = document.getElementById("VolumeS2").value;
  var Total_Cr = document.getElementById("Total_CrS2").value;
  var Cu = document.getElementById("CuS2").value;
  var Mn = document.getElementById("MnS2").value;
  var Ni = document.getElementById("NiS2").value;
  var Pb = document.getElementById("PbS2").value;
  var Zn = document.getElementById("ZnS2").value;
  // Total_metal
  var Total_metal =
    Total_Cr / (1000 * 51.996) +
    Cu / (1000 * 63.55) +
    Mn / (1000 * 54.93) +
    Ni / (1000 * 58.93) +
    Pb / (1000 * 207.2) +
    Zn / (1000 * 65.4);
  var sumTotal_metal = Total_metal.toFixed(9);
  document.getElementById("ShowTotal_metal").innerHTML = sumTotal_metal;

  // Ca_OH_2
  var Ca_OH_2 =
    ((Total_Cr / (1000 * 51.996)) * 1.5 * 74.093 +
      (Cu / (1000 * 63.55) +
        Mn / (1000 * 54.93) +
        Ni / (1000 * 58.93) +
        Pb / (1000 * 207.2) +
        Zn / (1000 * 65.4)) *
        74.093) *
    (100 / 93.15);
  var sumCa_OH_2 = Ca_OH_2.toFixed(9);
  var Model_L = sumCa_OH_2 * 14.659;
  var sumModel_L_Ca_OH_2 = Model_L.toFixed(9);
  var Lab_L = sumCa_OH_2 * 14.67;
  var sumLab_L_Ca_OH_2 = Lab_L.toFixed(9);
  var Model_G = sumModel_L_Ca_OH_2 * Volume;
  var sumModel_G_Ca_OH_2 = Model_G.toFixed(8);
  var Lab_G = sumLab_L_Ca_OH_2 * Volume;
  var sumLab_G_Ca_OH_2 = Lab_G.toFixed(7);
  document.getElementById("ShowTheoreticalCa").innerHTML = sumCa_OH_2;
  document.getElementById("ShowModelCa").innerHTML = sumModel_G_Ca_OH_2;
  document.getElementById("ShowLabCa").innerHTML = sumLab_G_Ca_OH_2;
  // Fe_SO_4
  var Fe_SO_4 =
    ((Total_Cr / (1000 * 51.996)) * 1.5 * 151.908 +
      (Cu / (1000 * 63.55) +
        Mn / (1000 * 54.93) +
        Ni / (1000 * 58.93) +
        Pb / (1000 * 207.2) +
        Zn / (1000 * 65.4)) *
        151.908 *
        (100 / 98.5)) *
    (278.014 / 151.908);
  var sumFe_SO_4 = Fe_SO_4.toFixed(9);
  var Model_L_Fe_SO_4 = sumFe_SO_4 * 5.771;
  var sumModel_L_Fe_SO_4 = Model_L_Fe_SO_4.toFixed(9);
  var Lab_L_Fe_SO_4 = sumFe_SO_4 * 5.068;
  var sumLab_L_Fe_SO_4 = Lab_L_Fe_SO_4.toFixed(9);
  var Model_G_Fe_SO_4 = sumModel_L_Fe_SO_4 * Volume;
  var sumModel_G_Fe_SO_4 = Model_G_Fe_SO_4.toFixed(7);
  var Lab_G_Fe_SO_4 = sumLab_L_Fe_SO_4 * Volume;
  var sumLab_G_Fe_SO_4 = Lab_G_Fe_SO_4.toFixed(7);
  document.getElementById("TheoreticalFe").innerHTML = sumFe_SO_4;
  document.getElementById("ModelFe").innerHTML = sumModel_G_Fe_SO_4;
  document.getElementById("LabFe").innerHTML = sumLab_G_Fe_SO_4;
  // NaOCl
  var ModelN = 13.33;
  var LabMl = 11;
  var volume_Opration_by_model = ModelN * Volume;
  var sumModel = volume_Opration_by_model.toFixed(9);
  var labV = LabMl * Volume;
  var sumlabV = labV.toFixed(9);
  var ModelT = 71.81;
  var LabT = 75;
  document.getElementById("ModelNaOCl").innerHTML = ModelN;
  document.getElementById("ModelNa").innerHTML = sumModel;
  document.getElementById("LabNa").innerHTML = sumlabV;
  // TDS
  var m1 = 42.3 * sumModel_L_Ca_OH_2;
  var f1 = m1.toFixed(7);
  var m2 = 76.7 * sumModel_L_Fe_SO_4;
  var f2 = m2.toFixed(7);
  var m3 = 173.2 * ModelN;
  var f3 = m3.toFixed(6);
  var m4 = 15.5 * ModelT;
  var f4 = m4.toFixed(2);
  var m5 = 0.44 * sumModel_L_Fe_SO_4 * sumModel_L_Fe_SO_4;
  var f5 = m5.toFixed(2);
  var m6 = 2.36 * ModelN * ModelN;
  var f6 = m6.toFixed(2);
  var m7 = 0.1685 * ModelT * ModelT;
  var f7 = m7.toFixed(7);
  var m8 = 12.13 * sumModel_L_Ca_OH_2 * sumModel_L_Fe_SO_4;
  var f8 = m8.toFixed(6);
  var m9 = 1.41 * sumModel_L_Ca_OH_2 * ModelN;
  var f9 = m9.toFixed(7);
  var m10 = 0.302 * sumModel_L_Ca_OH_2 * ModelT;
  var f10 = m10.toFixed(7);
  var m11 = 3.52 * sumModel_L_Fe_SO_4 * ModelN;
  var f11 = m11.toFixed(8);
  var m12 = 0.492 * sumModel_L_Fe_SO_4 * ModelT;
  var f12 = m12.toFixed(7);
  var m13 = 0.606 * sumModel_L_Fe_SO_4 * ModelT;
  var f13 = m13.toFixed(7);
  console.log("f1", f1);
  console.log("f2", f2);
  console.log("f3", f3);
  console.log("f4", f4);
  console.log("f5", f5);
  console.log("f6", f6);
  console.log("f7", f7);
  console.log("f8", f8);
  console.log("f9", f9);
  console.log("f10", f10);
  console.log("f11", f11);
  console.log("f12", f12);
  console.log("f13", f13);
  var SumModelTDS =
    6653 +
    Number(f1) -
    Number(f2) +
    Number(f3) -
    Number(f4) +
    Number(f5) +
    Number(f6) +
    Number(f7) +
    Number(f8) +
    Number(f9) -
    Number(f10) -
    Number(f11) -
    Number(f12) -
    Number(f13);
  var sumModelTDS = SumModelTDS.toFixed(2);
  document.getElementById("ModelTDS").innerHTML = sumModelTDS;

  var t1 = 42.3 * sumLab_L_Ca_OH_2;
  var d1 = t1.toFixed(7);
  var t2 = 76.7 * sumLab_L_Fe_SO_4;
  var d2 = t2.toFixed(6);
  var t3 = 173.2 * LabMl;
  var d3 = t3.toFixed(7);
  var t4 = 15.5 * LabT;
  var d4 = t4.toFixed(7);
  var t5 = 0.44 * (sumLab_L_Fe_SO_4 * sumLab_L_Fe_SO_4);
  var d5 = t5.toFixed(8);
  var t6 = 2.36 * (LabMl * LabMl);
  var d6 = t6.toFixed(6);
  var t7 = 0.1685 * (LabT * LabT);
  var d7 = t7.toFixed(6);
  var t8 = 12.13 * sumModel_L_Ca_OH_2 * sumLab_L_Fe_SO_4;
  var d8 = t8.toFixed(6);
  var t9 = 1.41 * sumModel_L_Ca_OH_2 * LabMl;
  var d9 = t9.toFixed(7);
  var t10 = 0.302 * sumLab_L_Ca_OH_2 * LabT;
  var d10 = t10.toFixed(6);
  var t11 = 3.52 * sumLab_L_Fe_SO_4 * LabMl;
  var d11 = t11.toFixed(7);
  var t12 = 0.492 * sumLab_L_Fe_SO_4 * LabT;
  var d12 = t12.toFixed(7);
  var t13 = 0.606 * LabMl * LabT;
  var d13 = t13.toFixed(6);

  var sumLab =
    6653 +
    Number(d1) -
    Number(d2) +
    Number(d3) -
    Number(d4) +
    Number(d5) +
    Number(d6) +
    Number(d7) +
    Number(d8) +
    Number(d9) -
    Number(d10) -
    Number(d11) -
    Number(d12) -
    Number(d13);
  var F = sumLab.toFixed(2);
  document.getElementById("LabTDS").innerHTML = F;
}

function CalculateS3() {
  var Volume = document.getElementById("VolumeS3").value;
  var Total_Cr = document.getElementById("Total_CrS3").value;
  var Cu = document.getElementById("CuS3").value;
  var Mn = document.getElementById("MnS3").value;
  var Ni = document.getElementById("NiS3").value;
  var Pb = document.getElementById("PbS3").value;
  var Zn = document.getElementById("ZnS3").value;
  // Total_metal
  var Total_metal =
    Total_Cr / (1000 * 51.996) +
    Cu / (1000 * 63.55) +
    Mn / (1000 * 54.93) +
    Ni / (1000 * 58.93) +
    Pb / (1000 * 207.2) +
    Zn / 65328;
  var sumTotal_metal = Total_metal.toFixed(8);
  document.getElementById("ShowTotal_metal").innerHTML = sumTotal_metal;

  // Ca_OH_2
  var Ca_OH_2 =
    ((Total_Cr / (1000 * 51.996)) * 1.5 * 74.093 +
      (Cu / (1000 * 63.55) +
        Mn / (1000 * 54.93) +
        Ni / (1000 * 58.93) +
        Pb / (1000 * 207.2) +
        Zn / 65328) *
        74.093) *
    (100 / 93.15);
  var sumCa_OH_2 = Ca_OH_2.toFixed(9);
  var Model_L = sumCa_OH_2 * 10.039;
  var sumModel_L_Ca_OH_2 = Model_L.toFixed(9);
  var Lab_L = sumCa_OH_2 * 16.449;
  var sumLab_L_Ca_OH_2 = Lab_L.toFixed(10);
  var Model_G = sumModel_L_Ca_OH_2 * Volume;
  var sumModel_G_Ca_OH_2 = Model_G.toFixed(9);
  var Lab_G = sumLab_L_Ca_OH_2 * Volume;
  var sumLab_G_Ca_OH_2 = Lab_G.toFixed(8);
  document.getElementById("ShowTheoreticalCa").innerHTML = sumCa_OH_2;
  document.getElementById("ShowModelCa").innerHTML = sumModel_G_Ca_OH_2;
  document.getElementById("ShowLabCa").innerHTML = sumLab_G_Ca_OH_2;

  // Fe_SO_4
  var Fe_SO_4 = 0.492046694110654;
  var sumFe_SO_4 = Fe_SO_4.toFixed(8);
  var Model_L_Fe_SO_4 = sumFe_SO_4 * 11.668;
  var sumModel_L_Fe_SO_4 = Model_L_Fe_SO_4.toFixed(9);
  var Lab_L_Fe_SO_4 = sumFe_SO_4 * 7.375;
  var sumLab_L_Fe_SO_4 = Lab_L_Fe_SO_4.toFixed(9);
  var Model_G_Fe_SO_4 = (sumModel_L_Fe_SO_4 / 1000) * 1000 * Volume;
  var sumModel_G_Fe_SO_4 = Model_G_Fe_SO_4.toFixed(8);
  var Lab_G_Fe_SO_4 = (sumLab_L_Fe_SO_4 / 1000) * 1000 * Volume;
  var sumLab_G_Fe_SO_4 = Lab_G_Fe_SO_4.toFixed(8);
  document.getElementById("TheoreticalFe").innerHTML = sumFe_SO_4;
  document.getElementById("ModelFe").innerHTML = sumModel_G_Fe_SO_4;
  document.getElementById("LabFe").innerHTML = sumLab_G_Fe_SO_4;

  // NaOCl
  var ModelN = 1.01;
  var LabMl = 5;
  var volume_Opration_by_model = ModelN * Volume;
  var sumModel = volume_Opration_by_model.toFixed(9);
  var labV = LabMl * Volume;
  var sumlabV = labV.toFixed(9);
  var ModelT = 120;
  var LabT = 75;
  document.getElementById("ModelNaOCl").innerHTML = ModelN;
  document.getElementById("ModelNa").innerHTML = sumModel;
  document.getElementById("LabNa").innerHTML = sumlabV;

  // TDS
  var m1 = 199 * sumModel_L_Ca_OH_2;
  var f1 = m1.toFixed(7);
  var m2 = 359.5 * sumModel_L_Fe_SO_4;
  var f2 = m2.toFixed(8);
  var m3 = 212.2 * ModelN;
  var f3 = m3.toFixed(6);
  var m4 = 7.25 * ModelT;
  var f4 = m4.toFixed(6);
  var m5 = 74.1 * sumModel_L_Ca_OH_2 * sumModel_L_Ca_OH_2;
  var f5 = m5.toFixed(7);
  var m6 = 49.22 * sumModel_L_Fe_SO_4 * sumModel_L_Fe_SO_4;
  var f6 = m6.toFixed(6);
  var m7 = 1.17 * ModelN * ModelN;
  var f7 = m7.toFixed(7);
  var m8 = 0.0453 * ModelT * ModelT;
  var f8 = m8.toFixed(6);
  var m9 = 10 * sumModel_L_Ca_OH_2 * sumModel_L_Fe_SO_4;
  var f9 = m9.toFixed(7);
  var m10 = 0 * sumModel_L_Ca_OH_2 * ModelN;
  var f10 = m10.toFixed(7);
  var m11 = 0 * sumModel_L_Ca_OH_2 * ModelT;
  var f11 = m11.toFixed(8);
  var m12 = 3.2 * sumModel_L_Fe_SO_4 * ModelN;
  var f12 = m12.toFixed(7);
  var m13 = 0.653 * sumModel_L_Fe_SO_4 * ModelT;
  var f13 = m13.toFixed(7);
  var m14 = 0.111 * ModelN * ModelT;
  var f14 = m14.toFixed(7);

  var SumModelTDS =
    4735 -
    Number(f1) -
    Number(f2) +
    Number(f3) -
    Number(f4) +
    Number(f5) +
    Number(f6) -
    Number(f7) +
    Number(f8) -
    Number(f9) +
    Number(f10) -
    Number(f11) -
    Number(f12) +
    Number(f13) -
    Number(f14);
  var sumModelTDS = SumModelTDS.toFixed(2);
  var sumLab = 0.01;
  document.getElementById("ModelTDS").innerHTML = sumModelTDS;
  var F = sumLab.toFixed(2);
  document.getElementById("LabTDS").innerHTML = F;
}

function CalculateE1() {
  var Volume = document.getElementById("VolumeE1").value;
  var Total_Cr = document.getElementById("Total_CrE1").value;
  var Cu = document.getElementById("CuE1").value;
  var Mn = document.getElementById("MnE1").value;
  var Ni = document.getElementById("NiE1").value;
  var Pb = document.getElementById("PbE1").value;
  var Zn = document.getElementById("ZnE1").value;
  // Total_metal
  var Total_metal =
    Total_Cr / (1000 * 51.996) +
    Cu / (1000 * 63.55) +
    Mn / (1000 * 54.93) +
    Ni / (1000 * 58.93) +
    Pb / (1000 * 207.2) +
    Zn / (1000 * 65.4);
  var sumTotal_metal = Total_metal.toFixed(9);
  document.getElementById("ShowTotal_metal").innerHTML = sumTotal_metal;

  // Ca_OH_2
  var Ca_OH_2 = 10.71633686;
  var sumCa_OH_2 = Ca_OH_2.toFixed(8);
  var Model_L = sumCa_OH_2 * 2.4456;
  var sumModel_L_Ca_OH_2 = Model_L.toFixed(8);
  var Lab_L = sumCa_OH_2 * 2.989;
  var sumLab_L_Ca_OH_2 = Lab_L.toFixed(8);
  var Model_G = sumModel_L_Ca_OH_2 * Volume;
  var sumModel_G_Ca_OH_2 = Model_G.toFixed(8);
  var Lab_G = sumLab_L_Ca_OH_2 * Volume;
  var sumLab_G_Ca_OH_2 = Lab_G.toFixed(9);
  document.getElementById("ShowTheoreticalCa").innerHTML = sumCa_OH_2;
  document.getElementById("ShowModelCa").innerHTML = sumModel_G_Ca_OH_2;
  document.getElementById("ShowLabCa").innerHTML = sumLab_G_Ca_OH_2;

  // Fe_SO_4
  var Fe_SO_4 = 38.0261601;
  var sumFe_SO_4 = Fe_SO_4.toFixed(7);
  var Model_L_Fe_SO_4 = sumFe_SO_4 * 1.245;
  var sumModel_L_Fe_SO_4 = Model_L_Fe_SO_4.toFixed(8);
  var Lab_L_Fe_SO_4 = sumFe_SO_4 * 1.166;
  var sumLab_L_Fe_SO_4 = Lab_L_Fe_SO_4.toFixed(8);
  var Model_G_Fe_SO_4 = sumModel_L_Fe_SO_4 * Volume;
  var sumModel_G_Fe_SO_4 = Model_G_Fe_SO_4.toFixed(6);
  var Lab_G_Fe_SO_4 = sumLab_L_Fe_SO_4 * Volume;
  var sumLab_G_Fe_SO_4 = Lab_G_Fe_SO_4.toFixed(6);
  document.getElementById("TheoreticalFe").innerHTML = sumFe_SO_4;
  document.getElementById("ModelFe").innerHTML = sumModel_G_Fe_SO_4;
  document.getElementById("LabFe").innerHTML = sumLab_G_Fe_SO_4;

  // NaOCl
  var ModelN = 0;
  var LabMl = 0;
  var volume_Opration_by_model = ModelN * Volume;
  var sumModel = volume_Opration_by_model.toFixed(9);
  var labV = LabMl * Volume;
  var sumlabV = labV.toFixed(9);
  var ModelT = 43.63;
  var LabT = 75;
  document.getElementById("ModelNaOCl").innerHTML = ModelN;
  document.getElementById("ModelNa").innerHTML = sumModel;
  document.getElementById("LabNa").innerHTML = sumlabV;

  // TDS
  var m1 = 1343 * sumModel_L_Ca_OH_2;
  var f1 = m1.toFixed(7);
  var m2 = 1409 * sumModel_L_Fe_SO_4;
  var f2 = m2.toFixed(8);
  var m3 = 11 * ModelT;
  var f3 = m3.toFixed(6);
  var m4 = 21.53 * sumModel_L_Ca_OH_2 * sumModel_L_Ca_OH_2;
  var f4 = m4.toFixed(6);
  var m5 = 12.5 * sumModel_L_Fe_SO_4 * sumModel_L_Fe_SO_4;
  var f5 = m5.toFixed(7);
  var m6 = 0.025 * ModelT * ModelT;
  var f6 = m6.toFixed(6);
  var m7 = 7.94 * sumModel_L_Ca_OH_2 * sumModel_L_Fe_SO_4;
  var f7 = m7.toFixed(7);
  var m8 = 0.338 * sumModel_L_Ca_OH_2 * ModelT;
  var f8 = m8.toFixed(6);
  var m9 = 0.18 * sumModel_L_Fe_SO_4 * ModelT;
  var f9 = m9.toFixed(7);
  var SumModelTDS =
    6393 -
    Number(f1) +
    Number(f2) -
    Number(f3) +
    Number(f4) -
    Number(f5) +
    Number(f6) -
    Number(f7) +
    Number(f8) -
    Number(f9);
  var sumModelTDS = SumModelTDS.toFixed(2);
  document.getElementById("ModelTDS").innerHTML = sumModelTDS;

  var t1 = 1343 * sumLab_L_Ca_OH_2;
  var d1 = t1.toFixed(7);
  var t2 = 1409 * sumLab_L_Fe_SO_4;
  var d2 = t2.toFixed(6);
  var t3 = 11 * LabT;
  var d3 = t3.toFixed(7);
  var t4 = 21.53 * sumLab_L_Ca_OH_2 * sumLab_L_Ca_OH_2;
  var d4 = t4.toFixed(7);
  var t5 = 12.5 * sumLab_L_Fe_SO_4 * sumLab_L_Fe_SO_4;
  var d5 = t5.toFixed(8);
  var t6 = 0.025 * LabT * LabT;
  var d6 = t6.toFixed(6);
  var t7 = 7.94 * (sumLab_L_Ca_OH_2 * sumLab_L_Fe_SO_4);
  var d7 = t7.toFixed(6);
  var t8 = 0.338 * sumLab_L_Ca_OH_2 * LabT;
  var d8 = t8.toFixed(6);
  var t9 = 0.18 * sumLab_L_Fe_SO_4 * LabT;
  var d9 = t9.toFixed(7);
  var sumLab =
    6393 -
    Number(d1) +
    Number(d2) -
    Number(d3) +
    Number(d4) -
    Number(d5) +
    Number(d6) -
    Number(d7) +
    Number(d8) -
    Number(d9);
  var F = sumLab.toFixed(2);
  document.getElementById("LabTDS").innerHTML = F;

  var sumEquation =
    6393 -
    26855 * 1.66 +
    28181 * 2.2 -
    11 * 75 +
    8611 * (1.66 * 1.66) -
    4980 * (2.2 * 2.2) +
    0.025 * (75 * 75) -
    3176 * 1.66 * 2.2 +
    6.8 * 1.66 * 75 -
    3.5 * 2.2 * 75;
  var SumEquation = sumEquation.toFixed(2);
  var real = 11700;
}
