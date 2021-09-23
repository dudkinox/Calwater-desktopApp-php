function CalculateS2(){
    var Volume = document.getElementById("VolumeS2").value;
    var Total_Cr = document.getElementById("Total_CrS2").value;
    var Cu = document.getElementById("CuS2").value;
    var Mn = document.getElementById("MnS2").value;
    var Ni = document.getElementById("NiS2").value;
    var Pb = document.getElementById("PbS2").value;
    var Zn = document.getElementById("ZnS2").value;
    // Total_metal
    var Total_metal = (Total_Cr/(1000*51.996)) + 
                      (Cu/(1000*63.55)) + 
                      (Mn/(1000*54.93)) + 
                      (Ni/(1000*58.93)) + 
                      (Pb/(1000*207.2)) + 
                      (Zn/(1000*65.4));
    var sumTotal_metal = Total_metal.toFixed(9);
    document.getElementById("ShowTotal_metal").innerHTML = sumTotal_metal;

    // Ca_OH_2
    var Ca_OH_2 = (((Total_Cr/(1000*51.996))*(1.5)*74.093)+(((Cu/(1000*63.55))+(Mn/(1000*54.93))+(Ni/(1000*58.93))+(Pb/(1000*207.2))+(Zn/(1000*65.4)))*74.093))*(100/93.15);
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
    var Fe_SO_4 = (((Total_Cr/(1000*51.996))*(1.5)*151.908)+
						(((Cu/(1000*63.55))+(Mn/(1000*54.93))+(Ni/(1000*58.93))+
						(Pb/(1000*207.2))+(Zn/(1000*65.4)))*151.908)*(100/98.5))*((278.014/151.908));
	var sumFe_SO_4 = Fe_SO_4.toFixed(9);
	var Model_L_Fe_SO_4 = sumFe_SO_4 * 5.771;
	var sumModel_L_Fe_SO_4 = Model_L_Fe_SO_4.toFixed(9);
	var Lab_L_Fe_SO_4 = sumFe_SO_4 * 5.068;
	var sumLab_L_Fe_SO_4 = Lab_L_Fe_SO_4.toFixed(9);
	var Model_G_Fe_SO_4 = sumModel_L_Fe_SO_4 * Volume;
	var sumModel_G_Fe_SO_4 = Model_G_Fe_SO_4.toFixed(9);
	var Lab_G_Fe_SO_4 = sumLab_L_Fe_SO_4 * Volume;
	var sumLab_G_Fe_SO_4 = Lab_G_Fe_SO_4.toFixed(9);
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
    document.getElementById("ModelNaOCl").innerHTML = volume_Opration_by_model;
    document.getElementById("ModelNa").innerHTML = sumModel;
    document.getElementById("LabNa").innerHTML = sumlabV;
    // TDS
    var m1 = (42.3 * sumModel_L_Ca_OH_2); 
    var f1 = number_format(m1, 7, '.', '');
    var m2 = (76.7 * sumModel_L_Fe_SO_4);
    f2 = number_format(m2, 8, '.', '');
    m3 = (173.2 * ModelN); 
    f3 = number_format(m3, 6, '.', '');
    m4 = (15.5 * ModelT);
    f4 = number_format(m4, 6, '.', '');
    m5 = (0.44 * sumModel_L_Fe_SO_4 * sumModel_L_Fe_SO_4); 
    f5 = number_format(m5, 7, '.', '');
    m6 = (2.36 * ModelN * ModelN); 
    f6 = number_format(m6, 6, '.', '');
    m7 = (0.1685 * ModelT * ModelT); 
    f7 = number_format(m7, 7, '.', '');
    m8 = (12.13 * sumModel_L_Ca_OH_2 * sumModel_L_Fe_SO_4); 
    f8 = number_format(m8, 6, '.', '');
    m9 = (1.41 * sumModel_L_Ca_OH_2 * ModelN); 
    f9 = number_format(m9, 7, '.', '');
    m10 = (0.302 * sumModel_L_Ca_OH_2 * ModelT); 
    f10 = number_format(m10, 7, '.', '');
    m11 = (3.52 * sumModel_L_Fe_SO_4 * ModelN); 
    f11 = number_format(m11, 8, '.', '');
    m12 = (0.492 * sumModel_L_Fe_SO_4 * ModelT); 
    f12 = number_format(m12, 7, '.', '');
    m13 = (0.606 * sumModel_L_Fe_SO_4 * ModelT); 
    f13 = number_format(m13, 7, '.', '');
    
    SumModelTDS = 6653 + (f1) - (f2) + (f3) - (f4) + (f5) + (f6) + (f7) + (f8) + (f9) - (f10) - (f11) - (f12) - (f13);
    sumModelTDS = number_format(SumModelTDS, 2, '.', '');
    //System.out.println("Model TED => " + sumModelTDS);
    
    t1 = (42.3*sumLab_L_Ca_OH_2);
    d1 = number_format(t1, 7, '.', '');
    t2 = (76.7*sumLab_L_Fe_SO_4);
    d2 = number_format(t2, 6, '.', '');
    t3 = (173.2*LabMl);
    d3 = number_format(t3, 7, '.', '');
    t4 = (15.5*LabT);
    d4 = number_format(t4, 7, '.', '');
    t5 = (0.44*(sumLab_L_Fe_SO_4*sumLab_L_Fe_SO_4));
    d5 = number_format(t5, 8, '.', '');
    t6 = (2.36*(LabMl*LabMl));
    d6 = number_format(t6, 6, '.', '');
    t7 = (0.1685* (LabT * LabT));
    d7 = number_format(t7, 6, '.', '');
    t8 = (12.13 * sumModel_L_Ca_OH_2 * sumLab_L_Fe_SO_4);
    d8 = number_format(t8, 6, '.', '');
    t9 = (1.41 * sumModel_L_Ca_OH_2 * LabMl);
    d9 = number_format(t9, 7, '.', '');
    t10 = (0.302 *sumLab_L_Ca_OH_2*LabT);
    d10 = number_format(t10, 6, '.', '');
    t11 = (3.52*sumLab_L_Fe_SO_4*LabMl);
    d11 = number_format(t11, 7, '.', '');
    t12 = (0.492*sumLab_L_Fe_SO_4*LabT);
    d12 = number_format(t12, 7, '.', '');
    t13 = (0.606*LabMl*LabT);
    d13 = number_format(t13, 6, '.', '');
    
    sumLab = 6653 + (d1) - (d2) + (d3) - (d4) + (d5) + (d6) + (d7) + (d8) + (d9) - (d10) - (d11) - (d12) - (d13);
    F = number_format(sumLab, 2, '.', '');
}

function CalculateS3(){
    var Volume = document.getElementById("VolumeS3").value;
    var Total_Cr = document.getElementById("Total_CrS3").value;
    var Cu = document.getElementById("CuS3").value;
    var Mn = document.getElementById("MnS3").value;
    var Ni = document.getElementById("NiS3").value;
    var Pb = document.getElementById("PbS3").value;
    var Zn = document.getElementById("ZnS3").value;
    // Total_metal
    var Total_metal = (Total_Cr/(1000*51.996)) +
                      (Cu/(1000*63.55)) + 
                      (Mn/(1000*54.93)) + 
                      (Ni/(1000*58.93)) + 
                      (Pb/(1000*207.2)) + 
                      (Zn/(65328));
    var sumTotal_metal = Total_metal.toFixed(8);
    document.getElementById("ShowTotal_metal").innerHTML = sumTotal_metal;
    
    // Ca_OH_2
    var Ca_OH_2 = (((Total_Cr/(1000*51.996))*(1.5)*74.093)+(((Cu/(1000*63.55))+(Mn/(1000*54.93))+(Ni/(1000*58.93))+(Pb/(1000*207.2))+(Zn/(65328)))*74.093))*(100/93.15);
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
	var Model_G = sumModel_L_Ca_OH_2 * Volume;	
	var sumModel_G_Fe_SO_4 = Model_G_Fe_SO_4.toFixed(8);
	var Lab_G_Fe_SO_4 = (sumLab_L_Fe_SO_4/1000) * 1000 * Volume;
	var sumLab_G_Fe_SO_4 = Lab_G_Fe_SO_4.toFixed(8);
	document.getElementById("TheoreticalFe").innerHTML = sumFe_SO_4;
    document.getElementById("ModelFe").innerHTML = sumModel_G_Fe_SO_4;
    document.getElementById("LabFe").innerHTML = sumLab_G_Fe_SO_4;
}

function CalculateE1(){
    var Total_CrE1 = document.getElementById("Total_CrE1").value;
    var CuE1 = document.getElementById("CuE1").value;
    var MnE1 = document.getElementById("MnE1").value;
    var NiE1 = document.getElementById("NiE1").value;
    var PbE1 = document.getElementById("PbE1").value;
    var ZnE1 = document.getElementById("ZnE1").value;
    // Total_metal
    Total_metalE1 = (Total_CrE1/(1000*51.996))+
                    (CuE1/(1000*63.55))+ 
                    (MnE1/(1000*54.93))+ 
                    (NiE1/(1000*58.93))+ 
                    (PbE1/(1000*207.2))+ 
                    (ZnE1/(1000*65.4));
    var sumTotal_metalE1 = Total_metalE1.toFixed(9);
    document.getElementById("ShowTotal_metal").innerHTML = sumTotal_metalE1;
}