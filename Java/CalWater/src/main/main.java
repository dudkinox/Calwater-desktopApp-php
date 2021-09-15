package main;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.Color;
import javax.swing.JSplitPane;
import javax.swing.JToolBar;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.ImageIcon;
import javax.swing.JSeparator;
import java.awt.Toolkit;
import javax.swing.JTextField;
import java.awt.Font;

public class main extends JFrame {

	private JPanel contentPane;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
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
		panel.setBounds(151, 10, 1100, 711);
		contentPane.add(panel);
		
		JLabel lblNewLabel_2 = new JLabel("\u0E23\u0E30\u0E1A\u0E1A\u0E04\u0E33\u0E19\u0E27\u0E13\u0E23\u0E30\u0E1A\u0E1A\u0E19\u0E49\u0E33\u0E15\u0E31\u0E27\u0E2D\u0E22\u0E48\u0E32\u0E07");
		lblNewLabel_2.setFont(new Font("Itim", Font.PLAIN, 48));
		panel.add(lblNewLabel_2);
	}
}
