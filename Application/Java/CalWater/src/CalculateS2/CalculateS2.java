package CalculateS2;

import java.text.DecimalFormat;

import ConnectDB.Connections;

public class CalculateS2 {
	Connections conn = new Connections();
	double Total_Cr = 110.3
			, Cu = 54.43
			, Mn = 2.239
			, Ni = 44.94
			, Pb = 0.001
			, Zn = 201.2
			, Volume = 10;
	
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
		double Ca_OH_2 = (((Total_Cr/(1000*51.996))*(1.5)*74.093)+(((Cu/(1000*63.55))+(Mn/(1000*54.93))+(Ni/(1000*58.93))+(Pb/(1000*207.2))+(Zn/(1000*65.4)))*74.093))*(100/93.15);
		double sumCa_OH_2 = FormatDecimal(Ca_OH_2, 9);
		
		double Model_L = sumCa_OH_2 * 14.659;
		sumModel_L_Ca_OH_2 = FormatDecimal(Model_L, 9);
		System.out.println("Model_L_Ca_OH_2 => " + sumModel_L_Ca_OH_2);
		
		double Lab_L = sumCa_OH_2 * 14.67;
		sumLab_L_Ca_OH_2 = FormatDecimal(Lab_L, 9);
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
		double Fe_SO_4 = (((Total_Cr/(1000*51.996))*(1.5)*151.908)+
						(((Cu/(1000*63.55))+(Mn/(1000*54.93))+(Ni/(1000*58.93))+
						(Pb/(1000*207.2))+(Zn/(1000*65.4)))*151.908)*(100/98.5))*((278.014/151.908));
		double sumFe_SO_4 = FormatDecimal(Fe_SO_4, 9);
		
		double Model_L_Fe_SO_4 = sumFe_SO_4 * 5.771;
		sumModel_L_Fe_SO_4 = FormatDecimal(Model_L_Fe_SO_4, 9);
		System.out.println("Model_L_Fe_SO_4 => " + sumModel_L_Fe_SO_4);
		
		double Lab_L_Fe_SO_4 = sumFe_SO_4 * 5.068;
		sumLab_L_Fe_SO_4 = FormatDecimal(Lab_L_Fe_SO_4, 9);
		System.out.println("Lab_L_Fe_SO_4 => " + sumLab_L_Fe_SO_4);
		
		double Model_G_Fe_SO_4 = sumModel_L_Fe_SO_4 * Volume;
		double sumModel_G_Fe_SO_4 = FormatDecimal(Model_G_Fe_SO_4, 9);
		System.out.println("Model_G_Fe_SO_4 => " + sumModel_G_Fe_SO_4);
		
		double Lab_G_Fe_SO_4 = sumLab_L_Fe_SO_4 * Volume;
		double sumLab_G_Fe_SO_4 = FormatDecimal(Lab_G_Fe_SO_4, 9);
		System.out.println("Lab_G_Fe_SO_4 => " + sumLab_G_Fe_SO_4);
		
		return sumFe_SO_4;
	}
	
	public double Sum_NaOCl() throws Exception {
		ModelN = 13.33;
		LabMl = 11;
		System.out.println("LabMl => " + LabMl);
		double volume_Opration_by_model = ModelN * Volume;
		double sumModel = FormatDecimal(volume_Opration_by_model, 9);
		System.out.println("volume Opration by Model => " + sumModel);
		
		double labV = LabMl * Volume;
		double sumlabV = FormatDecimal(labV, 9);
		System.out.println("volume Opration by Lab => " + sumlabV);
		
		ModelT = 71.81;
		LabT = 75;
		System.out.println("Time (min) model => " + ModelT);
		System.out.println("Time (min) lab => " + LabT);
		return ModelN;
	}
	
	public double Sum_TDS() throws Exception {
		double m1 = (42.3 * sumModel_L_Ca_OH_2); 
		double f1 = FormatDecimal(m1, 7);
		double m2 = (76.7 * sumModel_L_Fe_SO_4);
		double f2 = FormatDecimal(m2, 8);
		double m3 = (173.2 * ModelN); 
		double f3 = FormatDecimal(m3, 6);
		double m4 = (15.5 * ModelT);
		double f4 = FormatDecimal(m4, 6);
		double m5 = (0.44 * sumModel_L_Fe_SO_4 * sumModel_L_Fe_SO_4); 
		double f5 = FormatDecimal(m5, 7);
		double m6 = (2.36 * ModelN * ModelN); 
		double f6 = FormatDecimal(m6, 6);
		double m7 = (0.1685 * ModelT * ModelT); 
		double f7 = FormatDecimal(m7, 7);
		double m8 = (12.13 * sumModel_L_Ca_OH_2 * sumModel_L_Fe_SO_4); 
		double f8 = FormatDecimal(m8, 6);
		double m9 = (1.41 * sumModel_L_Ca_OH_2 * ModelN); 
		double f9 = FormatDecimal(m9, 7);
		double m10 = (0.302 * sumModel_L_Ca_OH_2 * ModelT); 
		double f10 = FormatDecimal(m10, 7);
		double m11 = (3.52 * sumModel_L_Fe_SO_4 * ModelN); 
		double f11 = FormatDecimal(m11, 8);
		double m12 = (0.492 * sumModel_L_Fe_SO_4 * ModelT); 
		double f12 = FormatDecimal(m12, 7);
		double m13 = (0.606 * sumModel_L_Fe_SO_4 * ModelT); 
		double f13 = FormatDecimal(m13, 7);
		
		double SumModelTDS = 6653 + (f1) - (f2) + (f3) - (f4) + (f5) + (f6) + (f7) + (f8) + (f9) - (f10) - (f11) - (f12) - (f13);
		double sumModelTDS = FormatDecimal(SumModelTDS, 2);
		System.out.println("Model TED => " + sumModelTDS);
		
		double t1 = (42.3*sumLab_L_Ca_OH_2);
		double d1 = FormatDecimal(t1, 7);
		double t2 = (76.7*sumLab_L_Fe_SO_4);
		double d2 = FormatDecimal(t2, 6);
		double t3 = (173.2*LabMl);
		double d3 = FormatDecimal(t3, 7);
		double t4 = (15.5*LabT);
		double d4 = FormatDecimal(t4, 7);
		double t5 = (0.44*(sumLab_L_Fe_SO_4*sumLab_L_Fe_SO_4));
		double d5 = FormatDecimal(t5, 8);
		double t6 = (2.36*(LabMl*LabMl));
		double d6 = FormatDecimal(t6, 6);
		double t7 = (0.1685* (LabT * LabT));
		double d7 = FormatDecimal(t7, 6);
		double t8 = (12.13 * sumModel_L_Ca_OH_2 * sumLab_L_Fe_SO_4);
		double d8 = FormatDecimal(t8, 6);
		double t9 = (1.41 * sumModel_L_Ca_OH_2 * LabMl);
		double d9 = FormatDecimal(t9, 7);
		double t10 = (0.302 *sumLab_L_Ca_OH_2*LabT);
		double d10 = FormatDecimal(t10, 6);
		double t11 = (3.52*sumLab_L_Fe_SO_4*LabMl);
		double d11 = FormatDecimal(t11, 7);
		double t12 = (0.492*sumLab_L_Fe_SO_4*LabT);
		double d12 = FormatDecimal(t12, 7);
		double t13 = (0.606*LabMl*LabT);
		double d13 = FormatDecimal(t13, 6);
		
		double sumLab = 6653 + (d1) - (d2) + (d3) - (d4) + (d5) + (d6) + (d7) + (d8) + (d9) - (d10) - (d11) - (d12) - (d13);
		double F = FormatDecimal(sumLab, 2);
		System.out.println("Lab TED => " + F);

		return 0;
	}
}
