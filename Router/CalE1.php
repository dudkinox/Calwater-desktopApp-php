<?php
function SumTotalMetalE1($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume){
    $Total_metal = ($Total_Cr/(1000*51.996))+ ($Cu/(1000*63.55))+ ($Mn/(1000*54.93))+ ($Ni/(1000*58.93))+ ($Pb/(1000*207.2))+ ($Zn/(1000*65.4));
    $sumTotal_metal = number_format($Total_metal, 9, '.', '');
    return $sumTotal_metal;
}
	
function Sum_Ca_OH_2E1($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume){
    $Ca_OH_2 = 10.71633686;
    $sumCa_OH_2 = number_format($Ca_OH_2, 8, '.', '');
    
    $Model_L = $sumCa_OH_2 * 2.4456;
    $sumModel_L_Ca_OH_2 = number_format($Model_L, 8, '.', '');
    // System.out.println("Model_L_Ca_OH_2 => " + sumModel_L_Ca_OH_2);
    
    $Lab_L = $sumCa_OH_2 * 2.989;
    $sumLab_L_Ca_OH_2 = number_format($Lab_L, 8, '.', '');
    // System.out.println("Lab_L_Ca_OH_2 => " + sumLab_L_Ca_OH_2);
    
    $Model_G = $sumModel_L_Ca_OH_2 * $Volume;
    $sumModel_G_Ca_OH_2 = number_format($Model_G, 8, '.', '');
    // System.out.println("Model_G_Ca_OH_2 => " + sumModel_G_Ca_OH_2);
    
    $Lab_G = $sumLab_L_Ca_OH_2 * $Volume;
    $sumLab_G_Ca_OH_2 = number_format($Lab_G, 9, '.', '');
    // System.out.println("Lab_G_Ca_OH_2 => " + sumLab_G_Ca_OH_2);
		
	return $sumCa_OH_2;
}
	
function Sum_Fe_SO_4E1($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume){
    $Fe_SO_4 = 38.0261601;
    $sumFe_SO_4 = number_format($Fe_SO_4, 7, '.', '');
    
    $Model_L_Fe_SO_4 = $sumFe_SO_4 * 1.245;
    $sumModel_L_Fe_SO_4 = number_format($Model_L_Fe_SO_4, 8, '.', '');
    // System.out.println("Model_L_Fe_SO_4 => " + sumModel_L_Fe_SO_4);
    
    $Lab_L_Fe_SO_4 = $sumFe_SO_4 * 1.166;
    $sumLab_L_Fe_SO_4 = number_format($Lab_L_Fe_SO_4, 8, '.', '');
    // System.out.println("Lab_L_Fe_SO_4 => " + sumLab_L_Fe_SO_4);
    
    $Model_G_Fe_SO_4 = $sumModel_L_Fe_SO_4 * $Volume;
    $sumModel_G_Fe_SO_4 = number_format($Model_G_Fe_SO_4, 6, '.', '');
    // System.out.println("Model_G_Fe_SO_4 => " + sumModel_G_Fe_SO_4);
    
    $Lab_G_Fe_SO_4 = $sumLab_L_Fe_SO_4 * $Volume;
    $sumLab_G_Fe_SO_4 = number_format($Lab_G_Fe_SO_4, 6, '.', '');
    // System.err.println("Lab_G_Fe_SO_4 => " + sumLab_G_Fe_SO_4);
    
    return $sumFe_SO_4;
}
	
function Sum_NaOClE1($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume){
		$ModelN = 0;
		$LabMl = 0;
		//System.out.println("LabMl => " + LabMl);
		$volume_Opration_by_model = $ModelN * $Volume;
		$sumModel = number_format($volume_Opration_by_model, 9, '.', '');
		//System.out.println("volume Opration by Model => " + sumModel);
		
		$labV = $LabMl * $Volume;
		$sumlabV = number_format($labV, 9, '.', '');
		//System.out.println("volume Opration by Lab => " + sumlabV);
		
		$ModelT = 43.63;
		$LabT = 75;
		//System.out.println("Time (min) model => " + ModelT);
		//System.out.println("Time (min) lab => " + LabT);
		return $ModelN;
}

function Sum_TDSE1($Total_Cr, $Cu, $Mn, $Ni, $Pb, $Zn, $Volume){
        $m1 = (1343 * $sumModel_L_Ca_OH_2); 
        $f1 = number_format($m1, 7, '.', '');
        $m2 = (1409 * $sumModel_L_Fe_SO_4);
        $f2 = number_format($m2, 8, '.', '');
        $m3 = (11 * $ModelT); 
        $f3 = number_format($m3, 6, '.', '');
        $m4 = (21.53 * $sumModel_L_Ca_OH_2 * $sumModel_L_Ca_OH_2);
        $f4 = number_format($m4, 6, '.', '');
        $m5 = (12.5 * $sumModel_L_Fe_SO_4 * $sumModel_L_Fe_SO_4); 
        $f5 = number_format($m5, 7, '.', '');
        $m6 = (0.025 * $ModelT * $ModelT); 
        $f6 = number_format($m6, 6, '.', '');
        $m7 = (7.94 * $sumModel_L_Ca_OH_2 * $sumModel_L_Fe_SO_4); 
        $f7 = number_format($m7, 7, '.', '');
        $m8 = (0.338 * $sumModel_L_Ca_OH_2 * $ModelT); 
        $f8 = number_format($m8, 6, '.', '');
        $m9 = (0.18 * $sumModel_L_Fe_SO_4 * $ModelT); 
        $f9 = number_format($m9, 7, '.', '');
        
        $SumModelTDS = 6393 - ($f1) + ($f2) - ($f3) + ($f4) - ($f5)+ 
                           ($f6) - ($f7) + ($f8) - ($f9);
        $sumModelTDS = number_format($SumModelTDS, 2, '.', '');
        //System.out.println("Model TDS => " + sumModelTDS);
        
        $t1 = (1343*$sumLab_L_Ca_OH_2);
        $d1 = number_format($t1, 7, '.', '');
        $t2 = (1409*$sumLab_L_Fe_SO_4);
        $d2 = number_format($t2, 6, '.', '');
        $t3 = (11*$LabT);
        $d3 = number_format($t3, 7, '.', '');
        $t4 = (21.53*$sumLab_L_Ca_OH_2*$sumLab_L_Ca_OH_2);
        $d4 = number_format($t4, 7, '.', '');
        $t5 = (12.5*$sumLab_L_Fe_SO_4*$sumLab_L_Fe_SO_4);
        $d5 = number_format($t5, 8, '.', '');
        $t6 = (0.025*$LabT*$LabT);
        $d6 = number_format($t6, 6, '.', '');
        $t7 = (7.94* ($sumLab_L_Ca_OH_2 * $sumLab_L_Fe_SO_4));
        $d7 = number_format($t7, 6, '.', '');
        $t8 = (0.338 * $sumLab_L_Ca_OH_2 * $LabT);
        $d8 = number_format($t8, 6, '.', '');
        $t9 = (0.18 * $sumLab_L_Fe_SO_4 * $LabT);
        $d9 = number_format($t9, 7, '.', '');
    
        $sumLab = 6393 - ($d1) + ($d2) - ($d3) + ($d4) - ($d5)+ ($d6) - ($d7) + ($d8) - ($d9);
                    
        $F = number_format($sumLab, 2, '.', '');
        //System.out.println("Lab TDS => " + F);
        
        $sumEquation = (6393-(26855*1.66)+(28181*2.2)-(11*75)+(8611*(1.66*1.66))-(4980*(2.2*2.2))+
                            (0.025*(75*75))-(3176*1.66*2.2)+(6.8*1.66*75)-(3.5*2.2*75));
        $SumEquation = number_format($sumEquation, 2, '.', '');
        //System.out.println("Equation => " + SumEquation);					
        
        $real = 11700;
        //System.out.println("Real => " + real);	
        
        return 0;
}
	
