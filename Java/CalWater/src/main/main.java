package main;


import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.EventQueue;
import Calculate.Calculate;

import java.awt.Color;
import javax.swing.JLabel;
import javax.swing.ImageIcon;
import javax.swing.JSeparator;
import java.awt.Toolkit;
import java.awt.Font;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.JButton;

public class main extends JFrame {

	private JPanel contentPane;
	private JTextField textField;

	/**
	 * Launch the application.
	 * @throws Exception 
	 */
	public static void main(String[] args) throws Exception{
		Calculate call = new Calculate();
		double sumTotal_metal = call.SumTotalMetal();
		double sumCa_OH_2 = call.Sum_Ca_OH_2();
		System.err.println("Total_metal => " + sumTotal_metal);
		System.err.println("Ca(OH)2 (g) => " + sumCa_OH_2);
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					main frame = new main();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame. 
 	 */
	public main() {
		setTitle("\u0E23\u0E30\u0E1A\u0E1A\u0E04\u0E33\u0E19\u0E27\u0E13\u0E23\u0E30\u0E1A\u0E1A\u0E19\u0E49\u0E33\u0E15\u0E31\u0E27\u0E2D\u0E22\u0E48\u0E32\u0E07");
		setIconImage(Toolkit.getDefaultToolkit().getImage("F:\\Desktop app\\flutter_desktopapp\\Java\\CalWater\\assets\\icon\\logo.png"));
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(150,20, 1280,768);
		contentPane = new JPanel();
		contentPane.setBackground(new Color(177, 177, 177));
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JLabel logo = new JLabel("");
		logo.setIcon(new ImageIcon("E:\\flutter desktop app\\desktop\\flutter_desktopapp\\Java\\CalWater\\assets\\icon\\logo4.png"));
		logo.setBounds(20, 10, 153, 118);
		contentPane.add(logo);
		
		JLabel logo_1 = new JLabel("");
		logo_1.setFont(new Font("Itim", Font.PLAIN, 18));
		logo_1.setIcon(new ImageIcon("E:\\flutter desktop app\\desktop\\flutter_desktopapp\\Java\\CalWater\\assets\\icon\\adddata1.png"));
		logo_1.setBounds(30, 130, 88, 118);
		contentPane.add(logo_1);
		
		JSeparator separator = new JSeparator();
		separator.setBounds(15, 130, 115, 2);
		contentPane.add(separator);
		
		JLabel logo_1_1 = new JLabel("");
		logo_1_1.setIcon(new ImageIcon("E:\\flutter desktop app\\desktop\\flutter_desktopapp\\Java\\CalWater\\assets\\icon\\chart1.png"));
		logo_1_1.setBounds(30, 272, 88, 103);
		contentPane.add(logo_1_1);
		
		JLabel lblNewLabel = new JLabel("Add data");
		lblNewLabel.setFont(new Font("Itim", Font.PLAIN, 18));
		lblNewLabel.setBounds(34, 226, 88, 47);
		contentPane.add(lblNewLabel);
		
		JLabel lblNewLabel_1 = new JLabel("Chart");
		lblNewLabel_1.setFont(new Font("Itim", Font.PLAIN, 18));
		lblNewLabel_1.setBounds(45, 371, 64, 41);
		contentPane.add(lblNewLabel_1);
		
		JPanel panel = new JPanel();
		panel.setBounds(166, 10, 1100, 711);
		contentPane.add(panel);
		panel.setLayout(null);
		
		JLabel lblNewLabel_2 = new JLabel("Test");
		lblNewLabel_2.setBounds(505, 5, 90, 58);
		lblNewLabel_2.setFont(new Font("Itim", Font.PLAIN, 48));
		panel.add(lblNewLabel_2);
		
		JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		tabbedPane.setBounds(52, 91, 136, 173);
		panel.add(tabbedPane);
		
		
		
		JButton btnNewButton = new JButton("GO");
		btnNewButton.setFont(new Font("Itim", Font.PLAIN, 34));
		btnNewButton.setBounds(305, 323, 90, 33);
		panel.add(btnNewButton);
		
		textField = new JTextField();
		textField.setFont(new Font("Itim", Font.PLAIN, 34));
		textField.setText("\u0E04\u0E49\u0E19\u0E2B\u0E32");
		textField.setBounds(74, 322, 221, 33);
		panel.add(textField);
		textField.setColumns(10);
		
		JLabel lblNewLabel_3 = new JLabel("ข้อมูลรายละเอียดน้ำ");
		lblNewLabel_3.setFont(new Font("Itim", Font.PLAIN, 24));
		lblNewLabel_3.setBounds(147, 276, 195, 51);
		panel.add(lblNewLabel_3);
	}
}
