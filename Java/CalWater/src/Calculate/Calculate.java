package Calculate;

import java.text.DecimalFormat;

import ConnectDB.Connections;

public class Calculate {
	Connections conn = new Connections();
	DecimalFormat decimal = new DecimalFormat("0.000000000");
	DecimalFormat decimal2 = new DecimalFormat("0.00");
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
	
	double FormatDecimal(double Number) {
		String SumDecimal = decimal.format(Number);
		double sum = Double.parseDouble(SumDecimal); 
		return sum;
	}
	
	double FormatDecimal2(double Number) {
		String SumDecimal = decimal2.format(Number);
		double sum = Double.parseDouble(SumDecimal); 
		return sum;
	}
	
	public double SumTotalMetal() throws Exception {
		double Total_metal = (Total_Cr/(1000*51.996))+ (Cu/(1000*63.55))+ (Mn/(1000*54.93))+ (Ni/(1000*58.93))+ (Pb/(1000*207.2))+ (Zn/(1000*65.4));
		double sumTotal_metal = FormatDecimal(Total_metal);
		return sumTotal_metal;
	}
	
	public double Sum_Ca_OH_2() throws Exception {
		double Ca_OH_2 = (((Total_Cr/(1000*51.996))*(1.5)*74.093)+(((Cu/(1000*63.55))+(Mn/(1000*54.93))+(Ni/(1000*58.93))+(Pb/(1000*207.2))+(Zn/(1000*65.4)))*74.093))*(100/93.15);
		double sumCa_OH_2 = FormatDecimal(Ca_OH_2);
		
		double Model_L = sumCa_OH_2 * 14.659;
		sumModel_L_Ca_OH_2 = FormatDecimal(Model_L);
		System.out.println("Model_L_Ca_OH_2 => " + sumModel_L_Ca_OH_2);
		
		double Lab_L = sumCa_OH_2 * 14.67;
		sumLab_L_Ca_OH_2 = FormatDecimal(Lab_L);
		System.out.println("Lab_L_Ca_OH_2 => " + sumLab_L_Ca_OH_2);
		
		double Model_G = sumModel_L_Ca_OH_2 * Volume;
		double sumModel_G_Ca_OH_2 = FormatDecimal(Model_G);
		System.out.println("Model_G_Ca_OH_2 => " + sumModel_G_Ca_OH_2);
		
		double Lab_G = sumLab_L_Ca_OH_2 * Volume;
		double sumLab_G_Ca_OH_2 = FormatDecimal(Lab_G);
		System.out.println("Lab_G_Ca_OH_2 => " + sumLab_G_Ca_OH_2);
		
		return sumCa_OH_2;
	}
	
	public double Sum_Fe_SO_4() throws Exception {
		double Fe_SO_4 = (((Total_Cr/(1000*51.996))*(1.5)*151.908)+
						(((Cu/(1000*63.55))+(Mn/(1000*54.93))+(Ni/(1000*58.93))+
						(Pb/(1000*207.2))+(Zn/(1000*65.4)))*151.908)*(100/98.5))*((278.014/151.908));
		double sumFe_SO_4 = FormatDecimal(Fe_SO_4);
		
		double Model_L_Fe_SO_4 = sumFe_SO_4 * 5.771;
		sumModel_L_Fe_SO_4 = FormatDecimal(Model_L_Fe_SO_4);
		System.out.println("Model_L_Fe_SO_4 => " + sumModel_L_Fe_SO_4);
		
		double Lab_L_Fe_SO_4 = sumFe_SO_4 * 5.068;
		sumLab_L_Fe_SO_4 = FormatDecimal(Lab_L_Fe_SO_4);
		System.out.println("Lab_L_Fe_SO_4 => " + sumLab_L_Fe_SO_4);
		
		double Model_G_Fe_SO_4 = sumModel_L_Fe_SO_4 * Volume;
		double sumModel_G_Fe_SO_4 = FormatDecimal(Model_G_Fe_SO_4);
		System.out.println("Model_G_Fe_SO_4 => " + sumModel_G_Fe_SO_4);
		
		double Lab_G_Fe_SO_4 = sumLab_L_Fe_SO_4 * Volume;
		double sumLab_G_Fe_SO_4 = FormatDecimal(Lab_G_Fe_SO_4);
		System.out.println("Lab_G_Fe_SO_4 => " + sumLab_G_Fe_SO_4);
		
		return sumFe_SO_4;
	}
	
	public double Sum_NaOCl() throws Exception {
		ModelN = 13.33;
		LabMl = 11;
		System.out.println("LabMl => " + LabMl);
		double volume_Opration_by_model = ModelN * Volume;
		double sumModel = FormatDecimal(volume_Opration_by_model);
		System.out.println("volume Opration by Model => " + sumModel);
		
		double labV = LabMl * Volume;
		double sumlabV = FormatDecimal(labV);
		System.out.println("volume Opration by Lab => " + sumlabV);
		
		ModelT = 71.81;
		LabT = 75;
		System.out.println("Time (min) model => " + ModelT);
		System.out.println("Time (min) lab => " + LabT);
		return ModelN;
	}
	
	public double Sum_TDS() throws Exception {
		double m1 = 6653 + (42.3 * sumModel_L_Ca_OH_2); 
		double f1 = FormatDecimal2(m1);
//		- 
		double m2 = (76.7 * sumModel_L_Fe_SO_4);
		double f2 = FormatDecimal2(m2);
//		+ 
		double m3 = (173.2 * ModelN); 
		double f3 = FormatDecimal2(m3);
//		- 
		double m4 = (15.5 * ModelT); 
		double f4 = FormatDecimal2(m4);
//		+ 
		double m5 = (0.44 * sumModel_L_Fe_SO_4 * sumModel_L_Fe_SO_4); 
		double f5 = FormatDecimal2(m5);
//		+
		double m6 = (2.36 * ModelN * ModelN); 
		double f6 = FormatDecimal2(m6);
//		+ 
		double m7 = (0.1685 * ModelT * ModelT); 
		double f7 = FormatDecimal2(m7);
//		+ 
		double m8 = (12.13 * sumModel_L_Ca_OH_2 * sumModel_L_Fe_SO_4); 
		double f8 = FormatDecimal2(m8);
//		+ 
		double m9 = (1.41 * sumModel_L_Ca_OH_2 * ModelN); 
		double f9 = FormatDecimal2(m9);
//		- 
		double m10 = (0.302 * sumModel_L_Ca_OH_2 * ModelT); 
		double f10 = FormatDecimal2(m10);
//		-
		double m11 = (0.302 * sumModel_L_Ca_OH_2 * ModelT); 
		double f11 = FormatDecimal2(m11);
//		-
		double m12 = (3.52 * sumModel_L_Fe_SO_4 * ModelN); 
		double f12 = FormatDecimal2(m12);
// 		-
		double m13 = (0.492 * sumModel_L_Fe_SO_4 * ModelT); 
		double f13 = FormatDecimal2(m13);

		System.err.println(f1);
		
				   		
		double t1 = 6653 + (42.3*sumLab_L_Ca_OH_2);
		double d1 = FormatDecimal2(t1);
		
		double t2 = (76.7*sumLab_L_Fe_SO_4);
		double d2 = FormatDecimal2(t2);
//					    -  
//                      + 
		double t3 = (173.2*LabMl);
		double d3 = FormatDecimal2(t3);
//						- 
		double t4 = (15.5*LabT);
		double d4 = FormatDecimal2(t4);
//					 	+ 
		double t5 = (15.5*LabT);
		double d5 = FormatDecimal2(t5);
//		                +
		double t6 = (0.44*(sumLab_L_Fe_SO_4*sumLab_L_Fe_SO_4));
		double d6 = FormatDecimal2(t6);
//						+
		double t7 = (2.36*(LabMl*LabMl));
		double d7 = FormatDecimal2(t7);
//						+
		double t8 = (0.1685* (LabT * LabT));
		double d8 = FormatDecimal2(t8);
//						+ 
		double t9 = (12.13*LabMl*sumLab_L_Fe_SO_4);
		double d9 = FormatDecimal2(t9);
//						+
		double t10 = (1.41*sumModel_L_Ca_OH_2*LabMl);
		double d10 = FormatDecimal2(t10);
//						-
		double t11 = (0.302 *sumLab_L_Ca_OH_2*LabT);
		double d11 = FormatDecimal2(t11);
//						- 
		double t12 = (3.52*sumLab_L_Fe_SO_4*LabMl);
		double d12 = FormatDecimal2(t12);
//						- 
		double t13 = (0.492*sumLab_L_Fe_SO_4*LabT);
		double d13 = FormatDecimal2(t13);
//						- 
		double t14 = (0.606*LabMl*LabT);
		double d14 = FormatDecimal2(t14);

		return 0;
	}
}
