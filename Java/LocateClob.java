import java.sql.*;
import java.io.*;
import java.util.*;
import java.math.*;


public class LocateClob
{
 static
    {   try
        {   
           /**************************************************/
           /* (2) Load the DB2Driver                         */
           /**************************************************/
           Class.forName ("com.ibm.db2.jcc.DB2Driver");  
        }
        catch (Exception e)
        {   System.exit(1);
        }
    }
  public static void main( String args[]) throws Exception
  {
   try {
   		String resume = null;
		String empnum = "000130";
		int startper = 0;
		int startper1, startdpt = 0;
		PreparedStatement stmt1, stmt2, stmt3 = null;
		String sql1, sql2, sql3 = null;
		String empno, resumefmt = null;
		Clob resumelob = null;
		ResultSet rs1, rs2, rs3 = null;
		sql1 = "SELECT POSSTR(RESUME,'Personal') "
				+ "FROM EMP_RESUME "
				+ "WHERE EMPNO = ? AND RESUME_FORMAT = 'ascii' ";
   		/* connect to the DB2 database  */
   		Connection con = DriverManager.getConnection("jdbc:db2://localhost:9527/SAMPLE", "owner", "hechanghong1001");
		stmt1 = con.prepareStatement (sql1);
		stmt1.setString (1, empnum);
		rs1 = stmt1.executeQuery();
		while (rs1.next()) {
				startper = rs1.getInt(1);
				System.out.println("SQL1 Startper:" + startper);
		} // end while

		sql2 = "SELECT POSSTR(RESUME,'Department') "
				+ "FROM EMP_RESUME "
				+ "WHERE EMPNO = ? AND RESUME_FORMAT = 'ascii' ";
		stmt2 = con.prepareStatement (sql2);
		stmt2.setString (1, empnum);
		rs2 = stmt2.executeQuery();
		while (rs2.next()) {
				startdpt = rs2.getInt(1);
				System.out.println("SQL2 Startdpt:" + startdpt);
		} // end while
		
		startper1 = startper - 1;
		sql3 = "SELECT EMPNO, RESUME_FORMAT, "
				+ "SUBSTR(RESUME,1,?)|| SUBSTR(RESUME,?) AS RESUME "
				+ "FROM EMP_RESUME "
				+ "WHERE EMPNO = ? AND RESUME_FORMAT = 'ascii' ";
		stmt3 = con.prepareStatement (sql3);
		stmt3.setInt (1, startper1);
		stmt3.setInt (2, startdpt);
		stmt3.setString (3, empnum);
		rs3 = stmt3.executeQuery();
		while (rs3.next()) {
				empno = rs3.getString(1);
				resumefmt = rs3.getString(2);
				resumelob = rs3.getClob(3);
				long len = resumelob.length();
				int len1 = (int)len;
				String resumeout = resumelob.getSubString(1, len1);
				System.out.println("SQL3 Empno:" + empno + ", Resumefmt:" + resumefmt + ", resumeout:" + resumeout);
		} // end while
   
   }  // End try
   catch (Exception e) {
		 System.out.println ("\n " + e.getMessage());
         e.printStackTrace(); 
         System.exit(1);
   }
  }

} 
