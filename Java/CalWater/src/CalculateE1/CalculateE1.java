package CalculateE1;

import java.text.DecimalFormat;

import ConnectDB.Connections;

public class CalculateE1 {
	Connections conn = new Connections();
	double Total_Cr = 4188.000
			, Cu = 560.100
			, Mn = 10.400
			, Ni = 40.210
			, Pb = 0.101
			, Zn = 240.500
			, Volume = 3.00;
	
	static double sumModel_L_Ca_OH_2;
	static double sumModel_L_Fe_SO_4;
	static double ModelN;
	static double ModelT;
	static double sumLab_L_Ca_OH_2;
	static double sumLab_L_Fe_SO_4;
	static double LabMl;
	static double LabT;
	
	double FormatDecimal(double Number, int deciNumber) {
		String formatDeci = "";
		for (int i = 0; i < deciNumber; i++) {
			formatDeci += "0";
		}
		DecimalFormat decimal = new DecimalFormat("0." + formatDeci);
		String SumDecimal = decimal.format(Number);
		double sum = Double.parseDouble(SumDecimal); 
		return sum;
	}
	
	public double SumTotalMetal() throws Exception {
		double Total_metal = (Total_Cr/(1000*51.996))+ (Cu/(1000*63.55))+ (Mn/(1000*54.93))+ (Ni/(1000*58.93))+ (Pb/(1000*207.2))+ (Zn/(1000*65.4));
		double sumTotal_metal = FormatDecimal(Total_metal, 9);
		return sumTotal_metal;
	}
	
	public double Sum_Ca_OH_2() throws Exception {
		double Ca_OH_2 = 10.71633686;
		double sumCa_OH_2 = FormatDecimal(Ca_OH_2, 8);
		
		double Model_L = sumCa_OH_2 * 2.4456;
		sumModel_L_Ca_OH_2 = FormatDecimal(Model_L, 8);
		System.out.println("Model_L_Ca_OH_2 => " + sumModel_L_Ca_OH_2);
		
		double Lab_L = sumCa_OH_2 * 2.989;
		sumLab_L_Ca_OH_2 = FormatDecimal(Lab_L, 8);
		System.out.println("Lab_L_Ca_OH_2 => " + sumLab_L_Ca_OH_2);
		
		double Model_G = sumModel_L_Ca_OH_2 * Volume;
		double sumModel_G_Ca_OH_2 = FormatDecimal(Model_G, 8);
		System.out.println("Model_G_Ca_OH_2 => " + sumModel_G_Ca_OH_2);
		
		double Lab_G = sumLab_L_Ca_OH_2 * Volume;
		double sumLab_G_Ca_OH_2 = FormatDecimal(Lab_G, 9);
		System.out.println("Lab_G_Ca_OH_2 => " + sumLab_G_Ca_OH_2);
		
		return sumCa_OH_2;
	}
	
	public double Sum_Fe_SO_4() throws Exception {
		double Fe_SO_4 = 38.0261601;
		double sumFe_SO_4 = FormatDecimal(Fe_SO_4, 7);
		
		double Model_L_Fe_SO_4 = sumFe_SO_4 * 1.245;
		sumModel_L_Fe_SO_4 = FormatDecimal(Model_L_Fe_SO_4, 8);
		System.out.println("Model_L_Fe_SO_4 => " + sumModel_L_Fe_SO_4);
		
		double Lab_L_Fe_SO_4 = sumFe_SO_4 * 1.166;
		sumLab_L_Fe_SO_4 = FormatDecimal(Lab_L_Fe_SO_4, 8);
		System.out.println("Lab_L_Fe_SO_4 => " + sumLab_L_Fe_SO_4);
		
		double Model_G_Fe_SO_4 = sumModel_L_Fe_SO_4 * Volume;
		double sumModel_G_Fe_SO_4 = FormatDecimal(Model_G_Fe_SO_4, 6);
		System.out.println("Model_G_Fe_SO_4 => " + sumModel_G_Fe_SO_4);
		
		double Lab_G_Fe_SO_4 = sumLab_L_Fe_SO_4 * Volume;
		double sumLab_G_Fe_SO_4 = FormatDecimal(Lab_G_Fe_SO_4, 6);
		System.err.println("Lab_G_Fe_SO_4 => " + sumLab_G_Fe_SO_4);
		
		return sumFe_SO_4;
	}
	
	public double Sum_NaOCl() throws Exception {
		ModelN = 0;
		LabMl = 0;
		System.out.println("LabMl => " + LabMl);
		double volume_Opration_by_model = ModelN * Volume;
		double sumModel = FormatDecimal(volume_Opration_by_model, 9);
		System.out.println("volume Opration by Model => " + sumModel);
		
		double labV = LabMl * Volume;
		double sumlabV = FormatDecimal(labV, 9);
		System.out.println("volume Opration by Lab => " + sumlabV);
		
		ModelT = 43.63;
		LabT = 75;
		System.out.println("Time (min) model => " + ModelT);
		System.out.println("Time (min) lab => " + LabT);
		return ModelN;
	}
	
	public double Sum_TDS() throws Exception {
		double m1 = (1343 * sumModel_L_Ca_OH_2); 
		double f1 = FormatDecimal(m1, 7);
		double m2 = (1409 * sumModel_L_Fe_SO_4);
		double f2 = FormatDecimal(m2, 8);
		double m3 = (11 * ModelT); 
		double f3 = FormatDecimal(m3, 6);
		double m4 = (21.53 * sumModel_L_Ca_OH_2 * sumModel_L_Ca_OH_2);
		double f4 = FormatDecimal(m4, 6);
		double m5 = (12.5 * sumModel_L_Fe_SO_4 * sumModel_L_Fe_SO_4); 
		double f5 = FormatDecimal(m5, 7);
		double m6 = (0.025 * ModelT * ModelT); 
		double f6 = FormatDecimal(m6, 6);
		double m7 = (7.94 * sumModel_L_Ca_OH_2 * sumModel_L_Fe_SO_4); 
		double f7 = FormatDecimal(m7, 7);
		double m8 = (0.338 * sumModel_L_Ca_OH_2 * ModelT); 
		double f8 = FormatDecimal(m8, 6);
		double m9 = (0.18 * sumModel_L_Fe_SO_4 * ModelT); 
		double f9 = FormatDecimal(m9, 7);
		
		double SumModelTDS = 6393 - (f1) + (f2) - (f3) + (f4) - (f5)+ 
						   (f6) - (f7) + (f8) - (f9);
		double sumModelTDS = FormatDecimal(SumModelTDS, 2);
		System.out.println("Model TDS => " + sumModelTDS);
		
		double t1 = (1343*sumLab_L_Ca_OH_2);
		double d1 = FormatDecimal(t1, 7);
		double t2 = (1409*sumLab_L_Fe_SO_4);
		double d2 = FormatDecimal(t2, 6);
		double t3 = (11*LabT);
		double d3 = FormatDecimal(t3, 7);
		double t4 = (21.53*sumLab_L_Ca_OH_2*sumLab_L_Ca_OH_2);
		double d4 = FormatDecimal(t4, 7);
		double t5 = (12.5*sumLab_L_Fe_SO_4*sumLab_L_Fe_SO_4);
		double d5 = FormatDecimal(t5, 8);
		double t6 = (0.025*LabT*LabT);
		double d6 = FormatDecimal(t6, 6);
		double t7 = (7.94* (sumLab_L_Ca_OH_2 * sumLab_L_Fe_SO_4));
		double d7 = FormatDecimal(t7, 6);
		double t8 = (0.338 * sumLab_L_Ca_OH_2 * LabT);
		double d8 = FormatDecimal(t8, 6);
		double t9 = (0.18 * sumLab_L_Fe_SO_4 * LabT);
		double d9 = FormatDecimal(t9, 7);
	
		double sumLab = 6393 - (d1) + (d2) - (d3) + (d4) - (d5)+ (d6) - (d7) + (d8) - (d9);
					
		double F = FormatDecimal(sumLab, 2);
		System.out.println("Lab TDS => " + F);
		
		double sumEquation = (6393-(26855*1.66)+(28181*2.2)-(11*75)+(8611*(1.66*1.66))-(4980*(2.2*2.2))+
							(0.025*(75*75))-(3176*1.66*2.2)+(6.8*1.66*75)-(3.5*2.2*75));
		double SumEquation = FormatDecimal(sumEquation, 2);
		System.out.println("Equation => " + SumEquation);					
		
		double real = 11700;
		System.out.println("Real => " + real);	
		
		return 0;
	}
}
