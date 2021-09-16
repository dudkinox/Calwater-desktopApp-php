package Calculate;

import java.text.DecimalFormat;

import ConnectDB.Connections;

public class Calculate {
	Connections conn = new Connections();
	DecimalFormat decimal = new DecimalFormat("0.000000000");
	double Total_Cr = 110.3
			, Cu = 54.43
			, Mn = 2.239
			, Ni = 44.94
			, Pb = 0.001
			, Zn = 201.2;
	
	public double SumTotalMetal() throws Exception {
		double Total_metal = (Total_Cr/(1000*51.996))+ (Cu/(1000*63.55))+ (Mn/(1000*54.93))+ (Ni/(1000*58.93))+ (Pb/(1000*207.2))+ (Zn/(1000*65.4));
		String SumTM = decimal.format(Total_metal);
		double sum = Double.parseDouble(SumTM); 
		return sum;
	}
	
	public double Sum_Ca_OH_2() throws Exception {
		double Ca_OH_2 = (((Total_Cr/(1000*51.996))*(3/2)*74.093)+(((Cu/(1000*63.55))+(Mn/(1000*54.93))+(Ni/(1000*58.93))+(Pb/(1000*207.2))+(Zn/(1000*65.4)))*74.093))*(100/93.15);
		String SumCaOH2 = decimal.format(Ca_OH_2);
		double sum = Double.parseDouble(SumCaOH2); 
		return sum;
	}
}
