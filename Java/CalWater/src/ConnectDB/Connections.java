package ConnectDB;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;


//import java.sql.Connection;

public class Connections {
	public void Test() throws Exception{
		try {
			Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/calwater", "root", "");
			PreparedStatement state = conn.prepareStatement("SELECT * FROM info");
			ResultSet result = state.executeQuery();
			while(result.next()) {				
				System.out.println("Volume => " + result.getString(2));
			}
		}catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}
}
