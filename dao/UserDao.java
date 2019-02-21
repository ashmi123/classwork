package dao;

import java.sql.*;

import pojos.Customer;

import static utils.DBUtils.*;

public class UserDao {
	private Connection cn;
	private PreparedStatement pst1;

	// constr
	public UserDao() throws Exception {
		cn = getConnection();
		pst1 = cn.prepareStatement("select * from users where email=? and password=?");

		System.out.println("dao created");
	}

	// clean up
	public void cleanUp() throws Exception {
		if (pst1 != null)
			pst1.close();
		if (cn != null)
			cn.close();
		System.out.println("dao cleaned up");
	}

	// CRUD
	public Customer validateCustomer(String email, String pass) throws Exception {
		// set IN params
		pst1.setString(1, email);
		pst1.setString(2, pass);
		try (ResultSet rst = pst1.executeQuery()) {
			if (rst.next())
				return new Customer(rst.getInt(1), rst.getString(2), email, pass, rst.getString(5), rst.getDouble(6),
						rst.getDate(7));
		}
		return null;
	}

}
