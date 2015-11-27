/**********************************************************************/
/* labupdate.java                                                     */
/* Sample Java program for "DB2 UDB PROGRAMMING USING JAVA"           */
/*                          ( CG11 )                                  */
/*                                                                    */
/*                                                                    */
/* Last update = 01/01/2003                                           */
/*                                                                    */
/**********************************************************************/
/*  Notes:                                                            */
/*                                                                    */
/*  Update the salary of all the employees of a department.           */
/*                                                                    */
/*  This program is intended to be completed with the lab guide       */
/*  as a reference.  The lab guide is the set of instructions that    */
/*  should be followed.  The comments in this program are intended    */
/*  to clarify statements made in the lab guide.                      */
/**********************************************************************/

/*********************??????????????????*******************************/
/*  ( 1 ) Import Java Classes                                         */
/**********************************************************************/
import java.sql.*;
import java.io.*;
import java.util.*;
import java.math.*;
import javax.swing.*;
import javax.swing.table.*;
import java.awt.event.*;
import java.awt.Font;



/**********************************************************************/
/* Class definition                                                   */
/**********************************************************************/
public class labupdate extends JFrame
{
/**********************************************************************/
/* Register the class with the db2 Driver                             */
/**********************************************************************/

	private JButton update = null;
	private JLabel text = null;
	//private JButton subOK = null;
	//private JButton subCancel = null;
	
	private JOptionPane toolPane = null;
	//private JDialog updateDialog = null;
	
	//private JTable output = null;
	
	//private int column;
	//private int row;
  static
    {   try
        {   
              /*********************??????????????????????**************/
              /* ( 2 ) Load the DB2 Driver                             */
              /*********************************************************/
              Class.forName ("com.ibm.db2.jcc.DB2Driver");
        }
        catch (Exception e)
        {   System.out.println ("\n  Error loading DB2 Driver...\n");
            System.out.println (e);
            System.exit(1);
        }
    }
  
	public labupdate() {
		
		super.setSize(500, 500);
		this.setTitle("HeChangHong");
		this.setLayout(null);
		this.setBounds(250, 100, 500, 500);
		update = new JButton("Update");
		update.setSize(100, 50);
		update.setLocation(200, 350);

		//subOK = new JButton("OK");
		//subCancel = new JButton("Cancel");
		toolPane = new JOptionPane();
		//Nested in a html tag, and the "\n" is not useful for JLabel.
		text = new JLabel("<html>This program will update the salaries for a department.<br>"
						+ "<br>"
						+ "Please click the update button.<br>"
						+ "</html>");
		//for JTextArea---text.setEditable(false);
		text.setFont(new Font(null, Font.BOLD, 15));
		text.setSize(400, 300);
		text.setLocation(0, 0);
		//updateDialog = toolPane.createDialog(this, "Update Tables");
		//updateDialog.setLayout(null);
		//subInput = new JTextField();
		
		/*
		TableModel dataModel = new AbstractTableModel() {
          public int getColumnCount() { return 10; }
          public int getRowCount() { return 10;}
          public Object getValueAt(int row, int col) { return new Integer(row*col); }
      	};
      	output = new JTable(dataModel);
      	output.setSize(500, 400);
      	output.setRowHeight(40);
      	output.setRowMargin(40);
      	*/
		
		update.addActionListener(new ActionListener(){
			
					public void actionPerformed(ActionEvent ae) {
						String input = JOptionPane.showInputDialog(null, "Enter a department number:");
						try {
							connectToDB(input);
						} catch(Exception e) {
							JOptionPane.showMessageDialog(null, "Input Error!", "Alert", toolPane.ERROR_MESSAGE);
						}
					}
				});
	
		this.add(text);
		this.add(update);
		//this.add(output);
		//updateDialog.add(subOK);
		//updateDialog.add(subCancel);
		//updateDialog.add(subInput);
	
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}


/**********************************************************************/
/* Main routine                                                       */
/**********************************************************************/
public static void main(String[] args)
{

	labupdate MainFrame = new labupdate();
	MainFrame.setVisible(true);

}
/***************************************** ****************************/
/* Define variable declarations for the variable which will be used   */
/* to pass data to and from the stored procedure:                     */
/* A character string for passing the department in.                  */
/* A double for returning the median salary.                          */
/* An integer for returning the number of employees.                  */
/**********************************************************************/

public void connectToDB(String input) throws Exception {

	String name = "";
	short id = 0;
	double salary = 0;
	String job = "";
	short NumEmp = 0;
	String sqlstmt = "UPDATE STAFF SET SALARY = SALARY * 1.05 WHERE DEPT = ?";
	String s = " ";
	int mydeptno = 0;
	int SQLCode = 0;
	String SQLState = "     ";


   /*  Establish connection and set default context  */
   //System.out.println("Connect statement follows:");

   /************************** ???????????????? ************************/
   /* ( 3 ) Code a statement that will connect to the database SAMPLE. */
   /*       Define the connection object named sample.                 */
   /*       Use the userid udba and the password udba                  */
   /********************************************************************/

   Connection sample = DriverManager.getConnection("jdbc:db2://localhost:9527/SAMPLE","owner","hechanghong1001");  
   //System.out.println("Connect completed");

   /************************** ???????????????? ************************/
   /* ( 4 ) Turn autocommit to off                                     */
   /*                                                                  */
   /********************************************************************/

   sample.setAutoCommit(false);
 

   /*   Print instruction lines                       */
   //System.out.println("This program will update the salaries for a department");  
   //System.out.println("\n");                                  
   //System.out.println("Please enter a department number: \n ");                         

   /*  Get the department number from the input data */
  
    mydeptno = Integer.parseInt(input);
    

   /*  Issue Select statement  */
   //System.out.println("Statement stmt follows");
   try 
   {
     
     /************************ ?????????????????????? ***********************/
     /* ( 5 ) Create the PreparedStatment object name pstmt using the       */
     /* prepareStatement method                                             */
     /*                                                                     */
     /***********************************************************************/
     PreparedStatement pstmt = sample.prepareStatement( sqlstmt );                  
         
     
     /********************** ????????????????? ******************************/
     /* (6) Set the parameter marker to be value of the department.         */
     /*     This value is placed in the field deptno                        */
     /*                                                                     */
     /***********************************************************************/
     pstmt.setInt(1, mydeptno);
 
     /********************** ????????????????? ******************************/
     /* (7) Execute the SQL statement                                       */
     /*     The number of rows modified by the update statment should be    */
     /*     saved in the variable named updateCount                         */
     /***********************************************************************/
     int updateCount = pstmt.executeUpdate();


   }  // end try
   catch ( SQLException x )
   {
     /********************** ??????????????????  ***************************/
     /* (8) An error has occurred.  Retrieve the SQLCode                   */
     /**********************************************************************/
     SQLCode = x.getErrorCode();
     SQLState = x.getSQLState();
     String Message = x.getMessage();
     System.out.println("\nSQLCODE:  " + SQLCode );
     System.out.println("\nSQLSTATE: " + SQLState);
     System.out.println("\nSQLERRM:  " + Message);
    }

  System.exit(0);
 } // end conectToDB

}  // end of kegstaff class





