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
import javax.swing.JScrollPane;
import javax.swing.SwingConstants;
import javax.swing.JScrollBar;

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
		setIconImage(Toolkit.getDefaultToolkit().getImage("E:\\flutter desktop app\\desktop\\flutter_desktopapp\\Java\\CalWater\\assets\\icon\\logo.png"));
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
		panel.setBounds(153, 10, 1100, 711);
		contentPane.add(panel);
		panel.setLayout(null);
		
		JLabel lblNewLabel_2 = new JLabel("\u0E23\u0E30\u0E1A\u0E1A\u0E1A\u0E04\u0E33\u0E19\u0E27\u0E13\u0E23\u0E30\u0E1A\u0E1A\u0E19\u0E49\u0E33\u0E15\u0E31\u0E27\u0E2D\u0E22\u0E48\u0E32\u0E07");
		lblNewLabel_2.setBounds(280, 10, 618, 58);
		lblNewLabel_2.setFont(new Font("Itim", Font.PLAIN, 48));
		panel.add(lblNewLabel_2);
		
		
		
		JButton btnNewButton = new JButton("GO");
		btnNewButton.setBounds(309, 335, 90, 33);
		btnNewButton.setFont(new Font("Itim", Font.PLAIN, 34));
		panel.add(btnNewButton);
		
		textField = new JTextField();
		textField.setBounds(25, 334, 274, 33);
		textField.setFont(new Font("Itim", Font.PLAIN, 34));
		textField.setText("\u0E04\u0E49\u0E19\u0E2B\u0E32");
		panel.add(textField);
		textField.setColumns(10);
		
		JLabel lblNewLabel_3 = new JLabel("\u0E02\u0E49\u0E2D\u0E21\u0E39\u0E25\u0E23\u0E32\u0E22\u0E25\u0E30\u0E40\u0E2D\u0E35\u0E22\u0E14\u0E19\u0E49\u0E33");
		lblNewLabel_3.setBounds(163, 286, 195, 51);
		lblNewLabel_3.setFont(new Font("Itim", Font.PLAIN, 24));
		panel.add(lblNewLabel_3);
		
		JPanel panel_1 = new JPanel();
		panel_1.setBackground(new Color(123,144,169));
		panel_1.setBounds(25, 81, 143, 196);
		
		panel.add(panel_1);
		panel_1.setLayout(null);
		
		JLabel lblNewLabel_4 = new JLabel("S2");
		lblNewLabel_4.setBounds(48, 0, 39, 44);
		lblNewLabel_4.setFont(new Font("Itim", Font.PLAIN, 36));
		lblNewLabel_4.setHorizontalAlignment(SwingConstants.CENTER);
		panel_1.add(lblNewLabel_4);
		
		JLabel lblNewLabel_5 = new JLabel("2,200 \u0E02\u0E49\u0E2D\u0E21\u0E39\u0E25");
		lblNewLabel_5.setBounds(-5, 54, 123, 23);
		lblNewLabel_5.setVerticalAlignment(SwingConstants.BOTTOM);
		lblNewLabel_5.setHorizontalAlignment(SwingConstants.TRAILING);
		lblNewLabel_5.setFont(new Font("Itim", Font.PLAIN, 18));
		panel_1.add(lblNewLabel_5);
		
		JLabel lblNewLabel_6 = new JLabel("\u0E2D\u0E31\u0E1E\u0E40\u0E14\u0E15\u0E25\u0E48\u0E32\u0E2A\u0E38\u0E14");
		lblNewLabel_6.setFont(new Font("Itim", Font.PLAIN, 18));
		lblNewLabel_6.setBounds(28, 74, 141, 30);
		panel_1.add(lblNewLabel_6);
		
		JLabel lblNewLabel_6_1 = new JLabel("08/10/2564");
		lblNewLabel_6_1.setFont(new Font("Itim", Font.PLAIN, 18));
		lblNewLabel_6_1.setBounds(26, 100, 97, 30);
		panel_1.add(lblNewLabel_6_1);
		
		JPanel panel_1_1 = new JPanel();
		panel_1_1.setLayout(null);
		panel_1_1.setBackground(new Color(123, 144, 169));
		panel_1_1.setBounds(188, 81, 143, 196);
		panel.add(panel_1_1);
		
		JLabel lblNewLabel_4_1 = new JLabel("S3");
		lblNewLabel_4_1.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel_4_1.setFont(new Font("Itim", Font.PLAIN, 36));
		lblNewLabel_4_1.setBounds(48, 0, 45, 44);
		panel_1_1.add(lblNewLabel_4_1);
		
		JLabel lblNewLabel_5_1 = new JLabel("2,200 \u0E02\u0E49\u0E2D\u0E21\u0E39\u0E25");
		lblNewLabel_5_1.setVerticalAlignment(SwingConstants.BOTTOM);
		lblNewLabel_5_1.setHorizontalAlignment(SwingConstants.TRAILING);
		lblNewLabel_5_1.setFont(new Font("Itim", Font.PLAIN, 18));
		lblNewLabel_5_1.setBounds(-5, 54, 123, 23);
		panel_1_1.add(lblNewLabel_5_1);
		
		JLabel lblNewLabel_6_2 = new JLabel("\u0E2D\u0E31\u0E1E\u0E40\u0E14\u0E15\u0E25\u0E48\u0E32\u0E2A\u0E38\u0E14");
		lblNewLabel_6_2.setFont(new Font("Itim", Font.PLAIN, 18));
		lblNewLabel_6_2.setBounds(28, 74, 141, 30);
		panel_1_1.add(lblNewLabel_6_2);
		
		JLabel lblNewLabel_6_1_1 = new JLabel("08/10/2564");
		lblNewLabel_6_1_1.setFont(new Font("Itim", Font.PLAIN, 18));
		lblNewLabel_6_1_1.setBounds(28, 100, 97, 30);
		panel_1_1.add(lblNewLabel_6_1_1);
		
		JPanel panel_1_2 = new JPanel();
		panel_1_2.setLayout(null);
		panel_1_2.setBackground(new Color(123, 144, 169));
		panel_1_2.setBounds(352, 81, 143, 196);
		panel.add(panel_1_2);
		
		JLabel lblNewLabel_4_2 = new JLabel("E1");
		lblNewLabel_4_2.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel_4_2.setFont(new Font("Itim", Font.PLAIN, 36));
		lblNewLabel_4_2.setBounds(48, 0, 39, 44);
		panel_1_2.add(lblNewLabel_4_2);
		
		JLabel lblNewLabel_5_2 = new JLabel("2,200 \u0E02\u0E49\u0E2D\u0E21\u0E39\u0E25");
		lblNewLabel_5_2.setVerticalAlignment(SwingConstants.BOTTOM);
		lblNewLabel_5_2.setHorizontalAlignment(SwingConstants.TRAILING);
		lblNewLabel_5_2.setFont(new Font("Itim", Font.PLAIN, 18));
		lblNewLabel_5_2.setBounds(-5, 54, 123, 23);
		panel_1_2.add(lblNewLabel_5_2);
		
		JLabel lblNewLabel_6_3 = new JLabel("\u0E2D\u0E31\u0E1E\u0E40\u0E14\u0E15\u0E25\u0E48\u0E32\u0E2A\u0E38\u0E14");
		lblNewLabel_6_3.setFont(new Font("Itim", Font.PLAIN, 18));
		lblNewLabel_6_3.setBounds(28, 74, 141, 30);
		panel_1_2.add(lblNewLabel_6_3);
		
		JLabel lblNewLabel_6_1_2 = new JLabel("08/10/2564");
		lblNewLabel_6_1_2.setFont(new Font("Itim", Font.PLAIN, 18));
		lblNewLabel_6_1_2.setBounds(26, 100, 97, 30);
		panel_1_2.add(lblNewLabel_6_1_2);
	}
}
