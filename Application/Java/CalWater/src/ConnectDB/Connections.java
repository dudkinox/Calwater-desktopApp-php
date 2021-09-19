package ConnectDB;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;


//import java.sql.Connection;

public class Connections {
	final String Database = "jdbc:mysql://localhost:3306/calwater";
	final String Username = "root";
	final String Password = "";
	public ResultSet GetResult(String query) throws Exception{
		try {
			Connection conn = DriverManager.getConnection(Database, Username, Password);
			PreparedStatement state = conn.prepareStatement(query);
			ResultSet result = state.executeQuery();
			return result;
		}catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
			return null;
		}
	}
}
