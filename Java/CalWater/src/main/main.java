package main;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.Group;
import javafx.scene.chart.PieChart;
import javafx.stage.Stage;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.GraphicsEnvironment;
import CalculateE1.CalculateE1;
import CalculateS2.CalculateS2;
import CalculateS3.CalculateS3;

import java.awt.EventQueue;
import java.awt.Color;
import java.awt.Component;

import javax.swing.JLabel;
import javax.swing.ImageIcon;
import javax.swing.JSeparator;
import java.awt.Toolkit;
import java.io.File;
import java.io.IOException;
import java.util.Observable;
import java.awt.Font;
import java.awt.FontFormatException;

import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.JScrollPane;
import javax.swing.SwingConstants;
import javax.swing.JScrollBar;
import javax.swing.JTable;
import javax.swing.JTextPane;
import javax.swing.UIManager;
import java.awt.SystemColor;

import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import javax.swing.border.LineBorder;
import javax.swing.ListSelectionModel;

@SuppressWarnings("deprecation")
public class main extends JFrame {

	private JPanel contentPane;
	private JTextField Search;
	Font Itim;
	private JTable table;

	/**
	 * Launch the application.
	 * @throws Exception 
	 */
	public static void main(String[] args) throws Exception{
		CalculateE1 call = new CalculateE1();
		double sumTotal_metal = call.SumTotalMetal();
		double sumCa_OH_2 = call.Sum_Ca_OH_2();
		double sum_Fe_SO_4 = call.Sum_Fe_SO_4();
		double sum_NaOCl = call.Sum_NaOCl();
		double sum_TDS = call.Sum_TDS();
		System.out.println("Total_metal => " + sumTotal_metal);
		System.out.println("Ca(OH)2 (g) => " + sumCa_OH_2);
		System.out.println("FeSO4 (g) => " + sum_Fe_SO_4);
		System.out.println("NaOCl model => " + sum_NaOCl);
		System.out.println("TDS => " + sum_TDS);
		
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
		setIconImage(Toolkit.getDefaultToolkit().getImage("E:\\Flutter\\flutter_desktopapp\\Java\\CalWater\\assets\\icon\\logo.png"));
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(150,20, 1280,768);
		contentPane = new JPanel();
		contentPane.setBackground(new Color(177, 177, 177));
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JLabel logo = new JLabel("");
		logo.setBounds(20, 14, 153, 118);
		logo.setIcon(new ImageIcon("E:\\Flutter\\flutter_desktopapp\\Java\\CalWater\\assets\\icon\\logo4.png"));
		contentPane.add(logo);
		
		JLabel logo_1 = new JLabel("");
		logo_1.setBounds(30, 130, 88, 118);
		logo_1.setIcon(new ImageIcon("E:\\Flutter\\flutter_desktopapp\\Java\\CalWater\\assets\\icon\\adddata1.png"));
		contentPane.add(logo_1);
		
		JSeparator separator = new JSeparator();
		separator.setBounds(15, 130, 115, 2);
		contentPane.add(separator);
		
		JLabel lblNewLabel = new JLabel("Add data");
		lblNewLabel.setBounds(34, 226, 88, 47);
		lblNewLabel.setFont(new Font("Tahoma", Font.PLAIN, 18));
		contentPane.add(lblNewLabel);
		
		JPanel panel = new JPanel();
		panel.setBounds(153, 10, 1100, 711);
		contentPane.add(panel);
		panel.setLayout(null);
		
		JLabel lblNewLabel_2 = new JLabel("ระบบคำนวณระบบน้ำตัวอย่าง");
		lblNewLabel_2.setBounds(352, 11, 434, 58);
		lblNewLabel_2.setFont(new Font("Tahoma", Font.BOLD, 30));
		panel.add(lblNewLabel_2);
		
		JButton btnNewButton = new JButton("ค้นหา");
		btnNewButton.setBounds(309, 332, 90, 33);
		btnNewButton.setBackground(SystemColor.window);
		btnNewButton.setFont(new Font("Tahoma", Font.PLAIN, 20));
		panel.add(btnNewButton);
		
		Search = new JTextField();
		Search.setBounds(25, 334, 274, 33);
		Search.setFont(new Font("Tahoma", Font.PLAIN, 25));
		panel.add(Search);
		Search.setColumns(10);
		
		JLabel lblNewLabel_3 = new JLabel("\u0E02\u0E49\u0E2D\u0E21\u0E39\u0E25\u0E23\u0E32\u0E22\u0E25\u0E30\u0E40\u0E2D\u0E35\u0E22\u0E14\u0E19\u0E49\u0E33");
		lblNewLabel_3.setBounds(163, 286, 207, 51);
		lblNewLabel_3.setFont(new Font("Tahoma", Font.PLAIN, 24));
		panel.add(lblNewLabel_3);
		
		JPanel panel_1 = new JPanel();
		panel_1.setBounds(25, 81, 143, 196);
		panel_1.setForeground(SystemColor.desktop);
		panel_1.setBackground(new Color(123,144,169));
		
		panel.add(panel_1);
		panel_1.setLayout(null);
		
		JLabel lblNewLabel_4 = new JLabel("S2");
		lblNewLabel_4.setBounds(42, 0, 52, 63);
		lblNewLabel_4.setFont(new Font("Tahoma", Font.PLAIN, 36));
		lblNewLabel_4.setHorizontalAlignment(SwingConstants.CENTER);
		panel_1.add(lblNewLabel_4);
		
		JLabel lblNewLabel_5 = new JLabel("2,200 \u0E02\u0E49\u0E2D\u0E21\u0E39\u0E25");
		lblNewLabel_5.setBounds(0, 71, 123, 23);
		lblNewLabel_5.setVerticalAlignment(SwingConstants.BOTTOM);
		lblNewLabel_5.setHorizontalAlignment(SwingConstants.TRAILING);
		lblNewLabel_5.setFont(new Font("Tahoma", Font.PLAIN, 18));
		panel_1.add(lblNewLabel_5);
		
		JLabel lblNewLabel_6 = new JLabel("\u0E2D\u0E31\u0E1E\u0E40\u0E14\u0E15\u0E25\u0E48\u0E32\u0E2A\u0E38\u0E14");
		lblNewLabel_6.setFont(new Font("Tahoma", Font.PLAIN, 18));
		lblNewLabel_6.setBounds(28, 109, 141, 30);
		panel_1.add(lblNewLabel_6);
		
		JLabel lblNewLabel_6_1 = new JLabel("08/10/2564");
		lblNewLabel_6_1.setFont(new Font("Itim", Font.PLAIN, 18));
		lblNewLabel_6_1.setBounds(28, 155, 97, 30);
		panel_1.add(lblNewLabel_6_1);
		
		JPanel panel_1_1 = new JPanel();
		panel_1_1.setBounds(188, 81, 143, 196);
		panel_1_1.setLayout(null);
		panel_1_1.setBackground(new Color(123, 144, 169));
		panel.add(panel_1_1);
		
		JLabel lblNewLabel_4_1 = new JLabel("S3");
		lblNewLabel_4_1.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel_4_1.setFont(new Font("Tahoma", Font.PLAIN, 36));
		lblNewLabel_4_1.setBounds(47, 11, 45, 44);
		panel_1_1.add(lblNewLabel_4_1);
		
		JLabel lblNewLabel_5_1 = new JLabel("2,200 ข้อมูล");
		lblNewLabel_5_1.setVerticalAlignment(SwingConstants.BOTTOM);
		lblNewLabel_5_1.setHorizontalAlignment(SwingConstants.TRAILING);
		lblNewLabel_5_1.setFont(new Font("Tahoma", Font.PLAIN, 18));
		lblNewLabel_5_1.setBounds(0, 71, 123, 23);
		panel_1_1.add(lblNewLabel_5_1);
		
		JLabel lblNewLabel_6_2 = new JLabel("อัพเดตล่าสุด");
		lblNewLabel_6_2.setFont(new Font("Tahoma", Font.PLAIN, 18));
		lblNewLabel_6_2.setBounds(28, 109, 141, 30);
		panel_1_1.add(lblNewLabel_6_2);
		
		JLabel lblNewLabel_6_1_1 = new JLabel("08/10/2564");
		lblNewLabel_6_1_1.setFont(new Font("Dialog", Font.PLAIN, 18));
		lblNewLabel_6_1_1.setBounds(28, 155, 97, 30);
		panel_1_1.add(lblNewLabel_6_1_1);
		
		JPanel panel_1_2 = new JPanel();
		panel_1_2.setBounds(352, 81, 143, 196);
		panel_1_2.setLayout(null);
		panel_1_2.setBackground(new Color(123, 144, 169));
		panel.add(panel_1_2);
		
		JLabel lblNewLabel_4_1_1 = new JLabel("E1");
		lblNewLabel_4_1_1.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel_4_1_1.setFont(new Font("Tahoma", Font.PLAIN, 36));
		lblNewLabel_4_1_1.setBounds(55, 11, 45, 44);
		panel_1_2.add(lblNewLabel_4_1_1);
		
		JLabel lblNewLabel_5_2 = new JLabel("2,200 ข้อมูล");
		lblNewLabel_5_2.setVerticalAlignment(SwingConstants.BOTTOM);
		lblNewLabel_5_2.setHorizontalAlignment(SwingConstants.TRAILING);
		lblNewLabel_5_2.setFont(new Font("Tahoma", Font.PLAIN, 18));
		lblNewLabel_5_2.setBounds(0, 71, 123, 23);
		panel_1_2.add(lblNewLabel_5_2);
		
		JLabel lblNewLabel_6_3 = new JLabel("อัพเดตล่าสุด");
		lblNewLabel_6_3.setFont(new Font("Tahoma", Font.PLAIN, 18));
		lblNewLabel_6_3.setBounds(28, 109, 141, 30);
		panel_1_2.add(lblNewLabel_6_3);
		
		JLabel lblNewLabel_6_1_2 = new JLabel("08/10/2564");
		lblNewLabel_6_1_2.setFont(new Font("Dialog", Font.PLAIN, 18));
		lblNewLabel_6_1_2.setBounds(28, 155, 97, 30);
		panel_1_2.add(lblNewLabel_6_1_2);
		
		JLabel lblNewLabel_7 = new JLabel("");
		lblNewLabel_7.setBounds(419, 324, 52, 54);
		lblNewLabel_7.setIcon(new ImageIcon("E:\\Flutter\\flutter_desktopapp\\Java\\CalWater\\assets\\icon\\arrow2.png"));
		panel.add(lblNewLabel_7);
		
		JLabel lblNewLabel_8 = new JLabel("");
		lblNewLabel_8.setBounds(481, 324, 58, 54);
		lblNewLabel_8.setIcon(new ImageIcon("E:\\Flutter\\flutter_desktopapp\\Java\\CalWater\\assets\\icon\\arrorw3.png"));
		panel.add(lblNewLabel_8);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(25, 402, 1065, 298);
		panel.add(scrollPane);
		
		DefaultTableCellRenderer righttext = new DefaultTableCellRenderer();
		table = new JTable();
		table.setSurrendersFocusOnKeystroke(true);
		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		table.setFont(new Font("Tahoma", Font.PLAIN, 11));
		table.setBorder(UIManager.getBorder("DesktopIcon.border"));
		table.setRowHeight(50);
		table.setModel(new DefaultTableModel(
			new Object[][] {
				{"     S2202101", "S2", "19 \u0E01\u0E31\u0E19\u0E22\u0E32\u0E22\u0E19 2564", "10.111111111", "10.111111111", "10.111111111", "10.111111111", "10.111111111", "10.111111111", "10.111111111", "10.111111111", "ลบ"},
			},
			new String[] {
				"Batch  No.*", "Sump No.", "Treatment Date", "Model", "Lab", "Model", "Lab", "Model", "Lab", "Model", "Lab", "Manage"
			}
		));
		table.getColumnModel().getColumn(2).setPreferredWidth(106);
		table.getColumnModel().getColumn(3).setPreferredWidth(87);
		table.getColumnModel().getColumn(4).setPreferredWidth(83);
		table.getColumnModel().getColumn(5).setPreferredWidth(80);
		table.getColumnModel().getColumn(6).setPreferredWidth(78);
		table.getColumnModel().getColumn(9).setPreferredWidth(77);
		scrollPane.setViewportView(table);
		
		JPanel panel_2 = new JPanel();
		panel_2.setBorder(new LineBorder(new Color(0, 0, 0)));
		panel_2.setForeground(UIManager.getColor("Button.focus"));
		panel_2.setBackground(SystemColor.window);
		panel_2.setBounds(25, 378, 84, 24);
		panel.add(panel_2);
		
		JLabel lblNewLabel_1 = new JLabel("New label");
		panel_2.add(lblNewLabel_1);
		
		ObservableList<PieChart.Data> pieData = FXCollections.observableArrayList(
				 new PieChart.Data("IT", 40),
				 new PieChart.Data("ENG", 20),
				 new PieChart.Data("DOC", 30),
				 new PieChart.Data("FIN", 5),
				 new PieChart.Data("CHE", 5)
				);
		PieChart pChart = new PieChart(pieData);
			
		JButton btnNewButton_1 = new JButton("Pie Chart");
		
		btnNewButton_1.setBackground(SystemColor.window);
		btnNewButton_1.setForeground(Color.BLACK);
		btnNewButton_1.setBounds(549, 80, 90, 33);
		panel.add(btnNewButton_1);
		
	}
}
