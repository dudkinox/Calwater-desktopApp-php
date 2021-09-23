<?php
function SumTotalMetalS3($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume){
    $Total_metal = ($Total_Cr/(1000*51.996))+ ($Cu/(1000*63.55))+ ($Mn/(1000*54.93))+ ($Ni/(1000*58.93))+ ($Pb/(1000*207.2))+ ($Zn/(65328));
    $sumTotal_metal = number_format($Total_metal, 8, '.', '');
    return $sumTotal_metal;
}
	
function Sum_Ca_OH_2S3($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume){
		$Ca_OH_2 = ((($Total_Cr/(1000*51.996))*(1.5)*74.093)+((($Cu/(1000*63.55))+($Mn/(1000*54.93))+($Ni/(1000*58.93))+($Pb/(1000*207.2))+($Zn/(65328)))*74.093))*(100/93.15);
		$sumCa_OH_2 = number_format($Ca_OH_2, 9, '.', '');
		
		$Model_L = $sumCa_OH_2 * 10.039;
		$sumModel_L_Ca_OH_2 = number_format($Model_L, 9, '.', '');
		// System.out.println("Model_L_Ca_OH_2 => " + $sumModel_L_Ca_OH_2);
		
		$Lab_L = $sumCa_OH_2 * 16.449;
		$sumLab_L_Ca_OH_2 = number_format(Lab_L, 10, '.', '');
		// System.out.println("Lab_L_Ca_OH_2 => " + $sumLab_L_Ca_OH_2);
		
		$Model_G = $sumModel_L_Ca_OH_2 * $Volume;
		$sumModel_G_Ca_OH_2 = number_format(Model_G, 9, '.', '');
		// System.out.println("Model_G_Ca_OH_2 => " + sumModel_G_Ca_OH_2);
		
		$Lab_G = $sumLab_L_Ca_OH_2 * $Volume;
		$sumLab_G_Ca_OH_2 = number_format(Lab_G, 9, '.', '');
		// System.out.println("Lab_G_Ca_OH_2 => " + sumLab_G_Ca_OH_2);
		
		return $sumCa_OH_2;
}

function Sum_Fe_SO_4S3($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume){
		$Fe_SO_4 = 0.492046694110654;
		$sumFe_SO_4 = number_format($Fe_SO_4, 8, '.', '');
		
		$Model_L_Fe_SO_4 = $sumFe_SO_4 * 11.668;
		$sumModel_L_Fe_SO_4 = number_format($Model_L_Fe_SO_4, 9, '.', '');
		// System.out.println("Model_L_Fe_SO_4 => " + $sumModel_L_Fe_SO_4);
		
		$Lab_L_Fe_SO_4 = $sumFe_SO_4 * 7.375;
		$sumLab_L_Fe_SO_4 = number_format($Lab_L_Fe_SO_4, 9, '.', '');
		// System.out.println("Lab_L_Fe_SO_4 => " + $sumLab_L_Fe_SO_4);
		
		$Model_G_Fe_SO_4 = ($sumModel_L_Fe_SO_4/1000)*1000*$Volume;
		$sumModel_G_Fe_SO_4 = number_format($Model_G_Fe_SO_4, 8, '.', '');
		// System.out.println("Model_G_Fe_SO_4 => " + sumModel_G_Fe_SO_4);
		
		$Lab_G_Fe_SO_4 = ($sumLab_L_Fe_SO_4/1000)*1000*$Volume;
		$sumLab_G_Fe_SO_4 = number_format($Lab_G_Fe_SO_4, 8, '.', '');
		// System.out.println("Lab_G_Fe_SO_4 => " + sumLab_G_Fe_SO_4);
		
		return $sumFe_SO_4; 
}
	
function Sum_NaOClS3($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume){
		$ModelN = 1.01;
		$LabMl = 5;
		// System.out.println("LabMl => " + LabMl);
		$volume_Opration_by_model = $ModelN * $Volume;
		$sumModel = number_format($volume_Opration_by_model, 9, '.', '');
		// System.out.println("volume Opration by Model => " + sumModel);
		
		$labV = $LabMl * $Volume;
		$sumlabV = number_format($labV, 9, '.', '');
		// System.out.println("volume Opration by Lab => " + sumlabV);
		
		$ModelT = 120;
		$LabT = 75;
		// System.out.println("Time (min) model => " + ModelT);
		// System.out.println("Time (min) lab => " + LabT);
		return $ModelN;
}
	
function Sum_TDSS3($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume){
		$m1 = (199 * $sumModel_L_Ca_OH_2); 
		$f1 = number_format($m1, 7, '.', '');
		$m2 = (359.5 * $sumModel_L_Fe_SO_4);
		$f2 = number_format($m2, 8, '.', '');
		$m3 = (212.2 * $ModelN); 
		$f3 = number_format($m3, 6, '.', '');
		$m4 = (7.25 * $ModelT);
		$f4 = number_format($m4, 6, '.', '');
		$m5 = (74.1 * $sumModel_L_Ca_OH_2 * $sumModel_L_Ca_OH_2); 
		$f5 = number_format($m5, 7, '.', '');
		$m6 = (49.22 * $sumModel_L_Fe_SO_4 * $sumModel_L_Fe_SO_4); 
		$f6 = number_format($m6, 6, '.', '');
		$m7 = (1.17 * $ModelN * $ModelN); 
		$f7 = number_format($m7, 7, '.', '');
		$m8 = (0.0453 * $ModelT * $ModelT); 
		$f8 = number_format($m8, 6, '.', '');
		$m9 = (10 * $sumModel_L_Ca_OH_2 * $sumModel_L_Fe_SO_4); 
		$f9 = number_format($m9, 7, '.', '');
		$m10 = (0 * $sumModel_L_Ca_OH_2 * $ModelN); 
		$f10 = number_format($m10, 7, '.', '');
		$m11 = (0 * $sumModel_L_Ca_OH_2 * $ModelT); 
		$f11 = number_format($m11, 8, '.', '');
		$m12 = (3.2 * $sumModel_L_Fe_SO_4 * $ModelN); 
		$f12 = number_format($m12, 7, '.', '');
		$m13 = (0.653 * $sumModel_L_Fe_SO_4 * $ModelT); 
		$f13 = number_format($m13, 7, '.', '');
		$m14 = (0.111 * $ModelN * $ModelT); 
		$f14 = number_format($m14, 7, '.', '');
		
		$SumModelTDS = 4735 - ($f1)- ($f2) + ($f3) - ($f4) + ($f5)+ ($f6)
						 - ($f7)+ ($f8) - ($f9)+ ($f10) - ($f11) -($f12)
						 + ($f13)- ($f14);
		$sumModelTDS = number_format($SumModelTDS, 2, '.', '');
		// System.out.println("Model TDS => " + sumModelTDS);
		
		
		$sumLab = 0.01;
		$F = number_format($sumLab, 2, '.', '');
		// System.out.println("Lab TDS => " + F);
		return 0;
}
