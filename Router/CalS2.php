<?php
function SumTotalMetalS2($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume)
{
	$Total_metal = ($Total_Cr / (1000 * 51.996)) + ($Cu / (1000 * 63.55)) + ($Mn / (1000 * 54.93)) + ($Ni / (1000 * 58.93)) + ($Pb / (1000 * 207.2)) + ($Zn / (1000 * 65.4));
	$sumTotal_metal = number_format($Total_metal, 9, '.', '');
	return $sumTotal_metal;
}

function Sum_Ca_OH_2S2($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume)
{
	$Ca_OH_2 = ((($Total_Cr / (1000 * 51.996)) * (1.5) * 74.093) + ((($Cu / (1000 * 63.55)) + ($Mn / (1000 * 54.93)) + ($Ni / (1000 * 58.93)) + ($Pb / (1000 * 207.2)) + ($Zn / (1000 * 65.4))) * 74.093)) * (100 / 93.15);
	$sumCa_OH_2 = number_format($Ca_OH_2, 9, '.', '');

	$Model_L = $sumCa_OH_2 * 14.659;
	$sumModel_L_Ca_OH_2 = number_format($Model_L, 9, '.', '');
	//System.out.println("Model_L_Ca_OH_2 => " + sumModel_L_Ca_OH_2);

	$Lab_L = $sumCa_OH_2 * 14.67;
	$sumLab_L_Ca_OH_2 = number_format($Lab_L, 9, '.', '');
	//System.out.println("Lab_L_Ca_OH_2 => " + sumLab_L_Ca_OH_2);

	$Model_G = $sumModel_L_Ca_OH_2 * $Volume;
	$sumModel_G_Ca_OH_2 = number_format($Model_G, 9, '.', '');
	//System.out.println("Model_G_Ca_OH_2 => " + sumModel_G_Ca_OH_2);

	$Lab_G = $sumLab_L_Ca_OH_2 * $Volume;
	$sumLab_G_Ca_OH_2 = number_format($Lab_G, 9, '.', '');
	//System.out.println("Lab_G_Ca_OH_2 => " + sumLab_G_Ca_OH_2);

	return $sumCa_OH_2;
}

function Sum_Fe_SO_4S2($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume)
{
	$Fe_SO_4 = ((($Total_Cr / (1000 * 51.996)) * (1.5) * 151.908) +
		((($Cu / (1000 * 63.55)) + ($Mn / (1000 * 54.93)) + ($Ni / (1000 * 58.93)) +
			($Pb / (1000 * 207.2)) + ($Zn / (1000 * 65.4))) * 151.908) * (100 / 98.5)) * ((278.014 / 151.908));
	$sumFe_SO_4 = number_format($Fe_SO_4, 9, '.', '');

	$Model_L_Fe_SO_4 = $sumFe_SO_4 * 5.771;
	$sumModel_L_Fe_SO_4 = number_format($Model_L_Fe_SO_4, 9, '.', '');
	//System.out.println("Model_L_Fe_SO_4 => " + sumModel_L_Fe_SO_4);

	$Lab_L_Fe_SO_4 = $sumFe_SO_4 * 5.068;
	$sumLab_L_Fe_SO_4 = number_format($Lab_L_Fe_SO_4, 9, '.', '');
	//System.out.println("Lab_L_Fe_SO_4 => " + sumLab_L_Fe_SO_4);

	$Model_G_Fe_SO_4 = $sumModel_L_Fe_SO_4 * $Volume;
	$sumModel_G_Fe_SO_4 = number_format($Model_G_Fe_SO_4, 9, '.', '');
	//System.out.println("Model_G_Fe_SO_4 => " + sumModel_G_Fe_SO_4);

	$Lab_G_Fe_SO_4 = $sumLab_L_Fe_SO_4 * $Volume;
	$sumLab_G_Fe_SO_4 = number_format($Lab_G_Fe_SO_4, 9, '.', '');
	//System.out.println("Lab_G_Fe_SO_4 => " + sumLab_G_Fe_SO_4);

	return $sumFe_SO_4;
}

function Sum_NaOClS2($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume)
{

	$ModelN = 13.33;
	$LabMl = 11;
	//System.out.println("LabMl => " + LabMl);
	$volume_Opration_by_model = $ModelN * $Volume;
	$sumModel = number_format($volume_Opration_by_model, 9, '.', '');
	//System.out.println("volume Opration by Model => " + sumModel);

	$labV = $LabMl * $$Volume;
	$sumlabV = number_format($labV, 9, '.', '');
	//System.out.println("volume Opration by Lab => " + sumlabV);

	$ModelT = 71.81;
	$LabT = 75;
	//System.out.println("Time (min) model => " + ModelT);
	//System.out.println("Time (min) lab => " + LabT);
	return $ModelN;
}

// function Sum_TDSS2($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume)
// {
// 	$m1 = (42.3 * $sumModel_L_Ca_OH_2);
// 	$f1 = number_format($m1, 7, '.', '');
// 	$m2 = (76.7 * $sumModel_L_Fe_SO_4);
// 	$f2 = number_format($m2, 8, '.', '');
// 	$m3 = (173.2 * $ModelN);
// 	$f3 = number_format($m3, 6, '.', '');
// 	$m4 = (15.5 * $ModelT);
// 	$f4 = number_format($m4, 6, '.', '');
// 	$m5 = (0.44 * $sumModel_L_Fe_SO_4 * $sumModel_L_Fe_SO_4);
// 	$f5 = number_format($m5, 7, '.', '');
// 	$m6 = (2.36 * $ModelN * $ModelN);
// 	$f6 = number_format($m6, 6, '.', '');
// 	$m7 = (0.1685 * $ModelT * $ModelT);
// 	$f7 = number_format($m7, 7, '.', '');
// 	$m8 = (12.13 * $sumModel_L_Ca_OH_2 * $sumModel_L_Fe_SO_4);
// 	$f8 = number_format($m8, 6, '.', '');
// 	$m9 = (1.41 * $sumModel_L_Ca_OH_2 * $ModelN);
// 	$f9 = number_format($m9, 7, '.', '');
// 	$m10 = (0.302 * $sumModel_L_Ca_OH_2 * $ModelT);
// 	$f10 = number_format($m10, 7, '.', '');
// 	$m11 = (3.52 * $sumModel_L_Fe_SO_4 * $ModelN);
// 	$f11 = number_format($m11, 8, '.', '');
// 	$m12 = (0.492 * $sumModel_L_Fe_SO_4 * $ModelT);
// 	$f12 = number_format($m12, 7, '.', '');
// 	$m13 = (0.606 * $sumModel_L_Fe_SO_4 * $ModelT);
// 	$f13 = number_format($m13, 7, '.', '');

// 	$SumModelTDS = 6653 + ($f1) - ($f2) + ($f3) - ($f4) + ($f5) + ($f6) + ($f7) + ($f8) + ($f9) - ($f10) - ($f11) - ($f12) - ($f13);
// 	$sumModelTDS = number_format($SumModelTDS, 2, '.', '');
// 	//System.out.println("Model TED => " + sumModelTDS);

// 	$t1 = (42.3 * $sumLab_L_Ca_OH_2);
// 	$d1 = number_format(t1, 7, '.', '');
// 	$t2 = (76.7 * $sumLab_L_Fe_SO_4);
// 	$d2 = number_format($t2, 6, '.', '');
// 	$t3 = (173.2 * $LabMl);
// 	$d3 = number_format($t3, 7, '.', '');
// 	$t4 = (15.5 * $LabT);
// 	$d4 = number_format($t4, 7, '.', '');
// 	$t5 = (0.44 * ($sumLab_L_Fe_SO_4 * $sumLab_L_Fe_SO_4));
// 	$d5 = number_format(t5, 8, '.', '');
// 	$t6 = (2.36 * ($LabMl * $LabMl));
// 	$d6 = number_format($t6, 6, '.', '');
// 	$t7 = (0.1685 * ($LabT * $LabT));
// 	$d7 = number_format($t7, 6, '.', '');
// 	$t8 = (12.13 * $sumModel_L_Ca_OH_2 * $sumLab_L_Fe_SO_4);
// 	$d8 = number_format($t8, 6, '.', '');
// 	$t9 = (1.41 * $sumModel_L_Ca_OH_2 * $LabMl);
// 	$d9 = number_format(t9, 7, '.', '');
// 	$t10 = (0.302 * $sumLab_L_Ca_OH_2 * $LabT);
// 	$d10 = number_format($t10, 6, '.', '');
// 	$t11 = (3.52 * $sumLab_L_Fe_SO_4 * $LabMl);
// 	$d11 = number_format($t11, 7, '.', '');
// 	$t12 = (0.492 * $sumLab_L_Fe_SO_4 * $LabT);
// 	$d12 = number_format($t12, 7, '.', '');
// 	$t13 = (0.606 * $LabMl * $LabT);
// 	$d13 = number_format($t13, 6, '.', '');

// 	$sumLab = 6653 + ($d1) - ($d2) + ($d3) - ($d4) + ($d5) + ($d6) + ($d7) + ($d8) + ($d9) - ($d10) - ($d11) - ($d12) - ($d13);
// 	$F = number_format($sumLab, 2, '.', '');
// 	//System.out.println("Lab TED => " + $F);

// 	return 0;
// }
