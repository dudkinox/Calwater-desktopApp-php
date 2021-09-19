package CalculateS3;


import java.text.DecimalFormat;

import ConnectDB.Connections;

public class CalculateS3 {
	Connections conn = new Connections();
	double Total_Cr = 21.4
			, Cu = 36.06
			, Mn = 4.920
			, Ni = 11.09
			, Pb = 0.452
			, Zn = 18.20
			, Volume = 5.00;
	
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
		double Total_metal = (Total_Cr/(1000*51.996))+ (Cu/(1000*63.55))+ (Mn/(1000*54.93))+ (Ni/(1000*58.93))+ (Pb/(1000*207.2))+ (Zn/(65328));
		double sumTotal_metal = FormatDecimal(Total_metal, 8);
		return sumTotal_metal;
	}
	
	public double Sum_Ca_OH_2() throws Exception {
		double Ca_OH_2 = (((Total_Cr/(1000*51.996))*(1.5)*74.093)+(((Cu/(1000*63.55))+(Mn/(1000*54.93))+(Ni/(1000*58.93))+(Pb/(1000*207.2))+(Zn/(65328)))*74.093))*(100/93.15);
		double sumCa_OH_2 = FormatDecimal(Ca_OH_2, 9);
		
		double Model_L = sumCa_OH_2 * 10.039;
		sumModel_L_Ca_OH_2 = FormatDecimal(Model_L, 9);
		System.out.println("Model_L_Ca_OH_2 => " + sumModel_L_Ca_OH_2);
		
		double Lab_L = sumCa_OH_2 * 16.449;
		sumLab_L_Ca_OH_2 = FormatDecimal(Lab_L, 10);
		System.out.println("Lab_L_Ca_OH_2 => " + sumLab_L_Ca_OH_2);
		
		double Model_G = sumModel_L_Ca_OH_2 * Volume;
		double sumModel_G_Ca_OH_2 = FormatDecimal(Model_G, 9);
		System.out.println("Model_G_Ca_OH_2 => " + sumModel_G_Ca_OH_2);
		
		double Lab_G = sumLab_L_Ca_OH_2 * Volume;
		double sumLab_G_Ca_OH_2 = FormatDecimal(Lab_G, 9);
		System.out.println("Lab_G_Ca_OH_2 => " + sumLab_G_Ca_OH_2);
		
		return sumCa_OH_2;
	}
	
	public double Sum_Fe_SO_4() throws Exception {
		double Fe_SO_4 = 0.492046694110654;
		double sumFe_SO_4 = FormatDecimal(Fe_SO_4, 8);
		
		double Model_L_Fe_SO_4 = sumFe_SO_4 * 11.668;
		sumModel_L_Fe_SO_4 = FormatDecimal(Model_L_Fe_SO_4, 9);
		System.out.println("Model_L_Fe_SO_4 => " + sumModel_L_Fe_SO_4);
		
		double Lab_L_Fe_SO_4 = sumFe_SO_4 * 7.375;
		sumLab_L_Fe_SO_4 = FormatDecimal(Lab_L_Fe_SO_4, 9);
		System.out.println("Lab_L_Fe_SO_4 => " + sumLab_L_Fe_SO_4);
		
		double Model_G_Fe_SO_4 = (sumModel_L_Fe_SO_4/1000)*1000*Volume;
		double sumModel_G_Fe_SO_4 = FormatDecimal(Model_G_Fe_SO_4, 8);
		System.out.println("Model_G_Fe_SO_4 => " + sumModel_G_Fe_SO_4);
		
		double Lab_G_Fe_SO_4 = (sumLab_L_Fe_SO_4/1000)*1000*Volume;
		double sumLab_G_Fe_SO_4 = FormatDecimal(Lab_G_Fe_SO_4, 8);
		System.out.println("Lab_G_Fe_SO_4 => " + sumLab_G_Fe_SO_4);
		
		return sumFe_SO_4; 
	}
	
	public double Sum_NaOCl() throws Exception {
		ModelN = 1.01;
		LabMl = 5;
		System.out.println("LabMl => " + LabMl);
		double volume_Opration_by_model = ModelN * Volume;
		double sumModel = FormatDecimal(volume_Opration_by_model, 9);
		System.out.println("volume Opration by Model => " + sumModel);
		
		double labV = LabMl * Volume;
		double sumlabV = FormatDecimal(labV, 9);
		System.out.println("volume Opration by Lab => " + sumlabV);
		
		ModelT = 120;
		LabT = 75;
		System.out.println("Time (min) model => " + ModelT);
		System.out.println("Time (min) lab => " + LabT);
		return ModelN;
	}
	
	public double Sum_TDS() throws Exception {
		double m1 = (199 * sumModel_L_Ca_OH_2); 
		double f1 = FormatDecimal(m1, 7);
		double m2 = (359.5 * sumModel_L_Fe_SO_4);
		double f2 = FormatDecimal(m2, 8);
		double m3 = (212.2 * ModelN); 
		double f3 = FormatDecimal(m3, 6);
		double m4 = (7.25 * ModelT);
		double f4 = FormatDecimal(m4, 6);
		double m5 = (74.1 * sumModel_L_Ca_OH_2 * sumModel_L_Ca_OH_2); 
		double f5 = FormatDecimal(m5, 7);
		double m6 = (49.22 * sumModel_L_Fe_SO_4 * sumModel_L_Fe_SO_4); 
		double f6 = FormatDecimal(m6, 6);
		double m7 = (1.17 * ModelN * ModelN); 
		double f7 = FormatDecimal(m7, 7);
		double m8 = (0.0453 * ModelT * ModelT); 
		double f8 = FormatDecimal(m8, 6);
		double m9 = (10 * sumModel_L_Ca_OH_2 * sumModel_L_Fe_SO_4); 
		double f9 = FormatDecimal(m9, 7);
		double m10 = (0 * sumModel_L_Ca_OH_2 * ModelN); 
		double f10 = FormatDecimal(m10, 7);
		double m11 = (0 * sumModel_L_Ca_OH_2 * ModelT); 
		double f11 = FormatDecimal(m11, 8);
		double m12 = (3.2 * sumModel_L_Fe_SO_4 * ModelN); 
		double f12 = FormatDecimal(m12, 7);
		double m13 = (0.653 * sumModel_L_Fe_SO_4 * ModelT); 
		double f13 = FormatDecimal(m13, 7);
		double m14 = (0.111 * ModelN * ModelT); 
		double f14 = FormatDecimal(m14, 7);
		
		double SumModelTDS = 4735 - (f1)- (f2) + (f3) - (f4) + (f5)+ (f6)
						 - (f7)+ (f8) - (f9)+ (f10) - (f11) -(f12)
						 + (f13)- (f14);
		double sumModelTDS = FormatDecimal(SumModelTDS, 2);
		System.out.println("Model TDS => " + sumModelTDS);
		
		
		double sumLab = 0.01;
		double F = FormatDecimal(sumLab, 2);
		System.out.println("Lab TDS => " + F);

		return 0;
	}
}
