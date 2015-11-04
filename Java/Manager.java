/********************************************************/
/* This is the Manager of the DB2 SAMPLE tables.        */
/* You can insert by child selecting or use the buttons.*/
/* You also can update and get the result!              */
/* and more than one operation, better to use batch!    */ 
/********************************************************/
import java.sql.*;
import java.io.*;
import java.util.*;
import java.math.*;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;
import java.awt.event.*;
import java.awt.*;


public class Manager extends JFrame implements ActionListener, ListSelectionListener {

    private static Connection con = null;
    private int rowCount = 0;
    private int columnCount = 0;
    private JButton insert = null;
    private JButton update = null;
    private JLabel text = null;
    private JScrollPane scroll = null;
    private JButton subOK = null;
    private JButton subCancel = null;
    private JButton sqlQuery = null;
    private JTextArea SQLInput = null;
    private JButton submit = null;
    private JOptionPane toolPane = null;
    private JDialog insertWindow = null;
    private JTable output = null;
    private JScrollPane tagScroll = null;
    private JPanel linePanel = null;
    private JPanel buttonPanel = null;
    private ButtonGroup btGroup = null;
    private JLabel[] tags = null;
    private JTextField[] tagText = null;
    private Object[] submits = {new String(""), new String(""), new String(""),
				new String(""), new String(""), new String(""),
				java.sql.Date.valueOf("2015-10-12"), new String(""),
				new Short("0"), new String(""), java.sql.Date.valueOf("2015-10-12"), new BigDecimal("0"), new BigDecimal("0"), new BigDecimal("0")};

	//use db2dclgen to get type!
        //private int column;
        //private int row;

    private void putSubmit(int index, String content) {
		if(index < submits.length && index >= 0) {
			if(index < 6 || index == 7 || index == 9) {	
				submits[index] = new String(content);
			}
			else if(index == 6 || index == 10) {	
				submits[index] = java.sql.Date.valueOf(content);
			}
			else if(index == 8) {	
				submits[index] = new Short(content);
			}
			else if(index >= 11 && index <= 13) {
				submits[index] = new BigDecimal(content);
			}	
		}
    }	
				
  static
    {   try
        {   
              /*********************************************************/
              /* ( 2 ) Load the DB2 Driver                             */
              /*********************************************************/
              Class.forName ("com.ibm.db2.jcc.DB2Driver");
              con = DriverManager.getConnection("jdbc:db2://localhost:9527/SAMPLE","owner","hechanghong1001"); 
              con.setAutoCommit(false);
        }
        catch (Exception e)
        {   System.out.println ("\n  Error loading DB2 Driver...\n");
            System.out.println (e);
            System.exit(1);
        }
    }
  
	public Manager() {
		
		this.setTitle("HeChangHong");
        this.setLayout(null);
        this.setBounds(200, 50, 1000, 1000);
        insert = new JButton("Insert");
        insert.setSize(100, 50);
        insert.setLocation(880, 300);
   		insert.addActionListener(this);
		update = new JButton("Update");
		update.setBounds(880, 450, 100, 50);
		update.addActionListener(this);
		sqlQuery = new JButton("SQL query");
		sqlQuery.setBounds(880, 600, 100, 50);
		sqlQuery.addActionListener(this);

        subOK = new JButton("OK");
        subCancel = new JButton("Cancel");
        subOK.setBounds(70, 300, 100, 50);
        subCancel.setBounds(230, 300, 100, 50);
		subOK.addActionListener(this);
		subCancel.addActionListener(this);
		toolPane = new JOptionPane();
		//Nested in a html tag, and the "\n" is not useful for JLabel.
		text = new JLabel("<html><style type=\"text/css\">h2 {font-size: 20px;text-indent: 8cm;font-style:italic;white-space: nowrap;}</style><body><h2>DB2--SAMPLE--EMPLOYEE</h2></body></html>");
		text.setSize(800, 50);
		text.setLocation(0, 0);
		
		this.add(text);
		this.add(insert);
		this.add(update);
		this.add(sqlQuery);
	
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		
                insertWindow = new JDialog(this, "Insert    Lines", true);
                insertWindow.setBounds(400, 250, 400, 400);
                insertWindow.setLayout(null);
                insertWindow.add(subOK);
                insertWindow.add(subCancel);
		insertWindow.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		insertWindow.addWindowListener(new WindowAdapter(){
			public void windowClosed(WindowEvent e) {
				for(int i=0; i<tagText.length; i++) {
					tagText[i].setText("");
				}
			}
		});
	}


/**********************************************************************/
/* Main routine                                                       */
/**********************************************************************/
public static void main(String[] args)
{

	Manager MainFrame = new Manager();
	MainFrame.query();
	MainFrame.setVisible(true);

}
/**********************************************************************/
/* Define variable declarations for the variable which will be used   */
/* to pass data to and from the stored procedure:                     */
/* A character string for passing the department in.                  */
/* A double for returning the median salary.                          */
/* An integer for returning the number of employees.                  */
/**********************************************************************/

public void query() {
	
	int SQLCode;
	String SQLState;
	String sqlstmt = null;
	sqlstmt = "SELECT * FROM EMPLOYEE FOR UPDATE";
   /*   Print instruction lines                       */
   //System.out.println("This program will update the salaries for a department");  
   //System.out.println("\n");                                  
   //System.out.println("Please enter a department number: \n ");                         

   /*  Get the department number from the input data */
  
    

   /*  Issue Select statement  */
   //System.out.println("Statement stmt follows");
   try 
   {
     
     /************************ ?????????????????????? ***********************/
     /* ( 5 ) Create the PreparedStatment object name pstmt using the       */
     /* prepareStatement method                                             */
     /*                                                                     */
     /***********************************************************************/
     //PreparedStatement pstmt = sample.prepareStatement( sqlstmt );                  
		Statement stmt = con.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
		ResultSet rs1 = stmt.executeQuery(sqlstmt);
		ResultSetMetaData rsmd = rs1.getMetaData();

		int i = 0;
		while(rs1.next()) {
			i ++;
		}
		final ResultSet rs2 = stmt.executeQuery(sqlstmt);
		if(!rs1.isClosed()) {
			System.out.println("ResultSet to the end error!");
			return;
		}
		rowCount = i;
		columnCount = rsmd.getColumnCount();
      TableModel dataModel = new AbstractTableModel() 
        {
	  private int RS_RESET = 1; 
	  	  public boolean isCellEditable(int row, int col) { return true; }
          public int getColumnCount() { return columnCount; }
          public int getRowCount() { return rowCount;}
          public String getColumnName(int col) { 
          	try { 
          		return rsmd.getColumnName(col+1);
          	} catch (SQLException sqlex) {
     			toolPane.showMessageDialog(scroll, 
					"\nSQLCODE:  " + sqlex.getErrorCode() + 
  					 "\nSQLSTATE: " + sqlex.getSQLState() +
					  "\nSQLERRM:  " + sqlex.getMessage(),
					"Error in Querying!--3", toolPane.ERROR_MESSAGE);
		}
		return "null";
	 }
         // absolute() method can not use the wasNull(), it did not work!
	 // so my idea is to get the "null" value, and rewrite the variable.
	 // and you have to know the "result" is not a original String,
	 // so the operator "==" may did not work, but use equals() method,
	 // it will get the inner String to compare with, so it can work!
	 public Object getValueAt(int row, int col) { 
          	try {
			if(rs2.absolute(row+1)) {
				String result = rs2.getString(col+1);
//(row == 9) System.out.println(result + ", " + result.equals(" "));
				if(result.equals(" ")) result = "null";
				return result;
			}
			else
				return new String("error");
          	} catch (SQLException sqlex) {
     			toolPane.showMessageDialog(scroll, 
					"\nSQLCODE:  " + sqlex.getErrorCode() + 
  					 "\nSQLSTATE: " + sqlex.getSQLState() +
					  "\nSQLERRM:  " + sqlex.getMessage(),
				"Error in Querying!--2", toolPane.ERROR_MESSAGE);
          	}
          	return new String("null");
          }
        };
	
		DefaultCellEditor editor = new DefaultCellEditor(new JTextField());
		// double-clicked to strike!
		editor.setClickCountToStart(2);

      	this.output = new JTable(dataModel);
      	this.output.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);
      	this.output.setRowHeight(30);
		this.output.setCellEditor(editor);
		(this.output.getSelectionModel()).addListSelectionListener(this);
      	this.scroll = new JScrollPane(this.output);
      	this.scroll.setBounds(0, 50, 850, 925);
      	this.add(scroll);   	
	
	/*Sometimes, maybe this is correct, but some type do not have 
	  default constructor, so the newInstance will fail!
	this.submits = new Object[columnCount];
	try {
		for(int k=0; k<columnCount; k++) {
			//rsmd maybe cause the SQL exception.
			submits[k] = Class.forName(rsmd.getColumnClassName(k+1)).newInstance();
			System.out.println("Get data " + k + " type:" + submits[k]);
		}
	} catch (ClassNotFoundException e) {
		System.out.println("Class not found:" + e.getMessage());
	} catch (InstantiationException e) {
		System.out.println("Instantiate failed:" + e.getMessage());
	} catch (IllegalAccessException e) {
		System.out.println("Illegal access:" + e.getMessage());
	}
	*/
	
	this.linePanel = new JPanel(new GridLayout(rsmd.getColumnCount(), 2)); 
	this.btGroup = new ButtonGroup();
	tags = new JLabel[columnCount];
	tagText = new JTextField[columnCount];
	//The failure white-spcing of contorl in GUI, but it is not the problem of this method. 
	for(i=0; i<columnCount; i++) {
		tags[i] = new JLabel();
		String tag = rsmd.getColumnName(i+1);
		tag = tag.toLowerCase();
		tag = tag.substring(0, 1).toUpperCase() + tag.substring(1);
		/*
		tag += ":";
		for(int j=20-tag.length(); j<20; j++) {
			tag += " ";
		}	
		*/
		tags[i].setText(tag + ":");
	}
	for(i=0; i<columnCount; i++) {
		JPanel tagPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
		tagText[i] = new JTextField(12);
		if(i <= 8) {
			tagPanel.add(tags[i]);
			this.linePanel.add(tagPanel);
			this.linePanel.add(tagText[i]);
		}
		else if(i == 9) {
			JRadioButton male = new JRadioButton("M");
       			JRadioButton female = new JRadioButton("F");
        		male.addActionListener(this);
        		female.addActionListener(this);
		        this.btGroup.add(male);
       			this.btGroup.add(female);
		        this.buttonPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        		tagPanel.add(tags[i]);
		        this.buttonPanel.add(male);
		        this.buttonPanel.add(female);
			this.linePanel.add(tagPanel);
			this.linePanel.add(buttonPanel); 
		}
		else {
			tagPanel.add(tags[i]);
			this.linePanel.add(tagPanel);
			this.linePanel.add(tagText[i]);
		}
	}	
	tagScroll = new JScrollPane(this.linePanel, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);     
	tagScroll.setBounds(0, 0, 400, 275);

System.out.println("Column:" + columnCount + ", Row:" + rowCount);
     //pstmt.setInt(1, mydeptno);
 
     //int updateCount = pstmt.executeUpdate();


   }  // end try
   catch ( SQLException x )
   {
     /**********************************************************************/
     /*     An error has occurred.  Retrieve the SQLCode                   */
     /**********************************************************************/
     SQLCode = x.getErrorCode();
     SQLState = x.getSQLState();
     String Message = x.getMessage();
     toolPane.showMessageDialog(this, "\nSQLCODE:  " + SQLCode + 
  					 "\nSQLSTATE: " + SQLState +
					    "\nSQLERRM:  " + Message,
				"Error in Querying!--1", toolPane.ERROR_MESSAGE);
    }

 } // end conectToDB
 
 public void actionPerformed(ActionEvent ae) {
 
 	if(ae.getSource() instanceof JButton) {
		JButton tempButton = (JButton)ae.getSource();
		if(tempButton.getText() == "Insert") {	
			insertWindow.add(tagScroll);
                	insertWindow.setVisible(true);
		}
		else if(tempButton.getText() == "OK") {
			String names = "";
			String attributes = "";
			for(int t=0; t<tags.length; t++) {
				if(t != tags.length-1) {
					String name = tags[t].getText();
					name = name.substring(0, name.length()-1);
					names += name; 
					names += ", ";
					attributes += "?, ";
				}
				else {
					String name = tags[t].getText();
					name = name.substring(0, name.length()-1);
					names += name;
					attributes += "?";
				}
			}

			try {
				PreparedStatement pstmt = con.prepareStatement("insert into EMPLOYEE(" + names + ") values(" + attributes + ")"); 
System.out.println("insert into EMPLOYEE(" + names + ") values(" + attributes + ")");
				for(int p=0; p<submits.length; p++) {
					if(p != 9) putSubmit(p, tagText[p].getText());
					pstmt.setObject(p+1, submits[p]);	
				}
				if(pstmt.executeUpdate() != 0) {
					con.commit();
					refresh();
					toolPane.showConfirmDialog(insertWindow, "The operation is successful!\n" +
	"Do you want to insert one more line?", "Operation Result",toolPane.YES_NO_OPTION);
			System.out.println("GetValue:" + toolPane.getValue());						//next to refresh the scroll pane.
				}  
				else 
					System.out.println("Did not execute insert!");
		//next to put the object and update
			} catch (SQLException sqlex) {
     				toolPane.showMessageDialog(insertWindow, 
					"\nSQLCODE:  " + sqlex.getErrorCode() + 
  					 "\nSQLSTATE: " + sqlex.getSQLState() +
					  "\nSQLERRM:  " + sqlex.getMessage(),
				"Error in Querying!", toolPane.ERROR_MESSAGE);
			} catch (IllegalArgumentException iae) {
				toolPane.showMessageDialog(insertWindow,
							iae.getMessage(), 
						 	"IllegalArgument!",
							toolPane.ERROR_MESSAGE);
			}	
		}
		else if(tempButton.getText() == "Cancel") {
			insertWindow.setVisible(false);
			//The next method is to release the resource.
			insertWindow.dispose();
		}
		// Preparedstmt is required a complete String,
		// it means you can not assign it when the program is running.
		// the stmt can do this. 
		else if(tempButton.getText() == "Update") {
			try{	
				if(output.getSelectedRow() == -1) {
					toolPane.showMessageDialog(this, "You have not selected any value!");
				}
				else {
					String dataInput = toolPane.showInputDialog(this, "You select row:" + (output.getSelectedRow()+1) + ", column:" + (output.getSelectedColumn()+1) + ".\n Please input the newst value:");		
//System.out.println("dataInput:" + dataInput+".");
					String substance = tags[output.getSelectedColumn()].getText().toUpperCase().substring(0, tags[output.getSelectedColumn()].getText().length()-1);
					String psql = "UPDATE EMPLOYEE SET " + 
substance + " = " + dataInput + " WHERE EMPNO = " + output.getValueAt(output.getSelectedRow(), 0);  
System.out.println(psql);
					Statement upstmt = con.createStatement();
					if(dataInput != null && upstmt.executeUpdate(psql) != 0) {
						toolPane.showMessageDialog(this, "Update operation has completed!");
						con.commit();
						refresh();
					}
				}
			} catch (SQLException sqlex) {
                                toolPane.showMessageDialog(insertWindow,
                                        "\nSQLCODE:  " + sqlex.getErrorCode() +
                                         "\nSQLSTATE: " + sqlex.getSQLState() +
                                          "\nSQLERRM:  " + sqlex.getMessage(),
                                "Error in Querying!", toolPane.ERROR_MESSAGE);
			}
		}
		else if(tempButton.getText() == "SQL query") {
			JDialog sqlDialog = new JDialog(this, "SQL    Child     Query", true);
			JLabel sqlLabel = new JLabel("<html><h2>Please input your SQL:</h2></html>");
			SQLInput = new JTextArea(5, 20);
			SQLInput.setFont(new Font("Default", Font.BOLD, 15));
			submit = new JButton("submit");
			submit.addActionListener(this);
			submit.setBounds(150, 250, 100, 50);		
			sqlLabel.setBounds(0, 0, 400,  70);
			SQLInput.setBounds(0,  70, 400, 150);
			sqlDialog.setBounds(400, 300, 400, 330);
			sqlDialog.setLayout(null);
			sqlDialog.add(sqlLabel);
			sqlDialog.add(SQLInput);
			sqlDialog.add(submit);
			sqlDialog.addWindowListener(new WindowAdapter(){
				public void windowClosed() {
					SQLInput.setText("");
				}
			});
			sqlDialog.setVisible(true);
		}
		else if(tempButton.getText() == "submit") {
			String sql = SQLInput.getText();
			sql = sql.substring(0, 10);
			sql = sql.trim();
			sql = sql.toLowerCase();
			if(sql == "select") System.out.println("to refresh the frame!"); 
			else {
				try {
					sql = SQLInput.getText();
					Statement stmt = con.createStatement();
					int reback = stmt.executeUpdate(sql);
					toolPane.showMessageDialog(this,							"Influenced lines:" + reback);
				} catch (SQLException sqlex) {
                               		toolPane.showMessageDialog(insertWindow, "\nSQLCODE:  " + sqlex.getErrorCode() +
    "\nSQLSTATE: " + sqlex.getSQLState() +
       "\nSQLERRM:  " + sqlex.getMessage(),
          "Error in Querying!", toolPane.ERROR_MESSAGE);
                       		}
			}
		}
    	}
	else if(ae.getSource() instanceof JRadioButton) {
		JRadioButton tempButton = (JRadioButton)ae.getSource();
		if(tempButton.getText() == "M") {
			putSubmit(9, tempButton.getText());
		}
		else if(tempButton.getText() == "F") {
			putSubmit(9, tempButton.getText());
		}
	}
 
 }
 
 /*
 	if you do not use the adjusting method, it would call twice.
 	one is to change to, and the other is that the state is still.
 */
 public void valueChanged(ListSelectionEvent e) {
 	
 	if (e.getValueIsAdjusting()) {
 		System.out.println("Select row:" + output.getSelectedRow() + 
			", column:" + output.getSelectedColumn() + 
			", value:" + output.getValueAt(output.getSelectedRow(), output.getSelectedColumn()));
 	}
 
 }// end valueChanged.
 // to refresh the main window!
 public void refresh() {
	String sqlstmt = "SELECT * FROM EMPLOYEE";
	try {	
		Statement stmt = con.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
		final ResultSet rs2 = stmt.executeQuery(sqlstmt);
		ResultSetMetaData rsmd = rs2.getMetaData();
	  // There should also need a customized CellEditor to make no difference.
      TableModel dataModel = new AbstractTableModel() 
        {
	  	  public boolean isCellEditable(int row, int col) { return true; }
          public int getColumnCount() { return columnCount; }
          public int getRowCount() { return rowCount;}
          public String getColumnName(int col) { 
          	try { 
          		return rsmd.getColumnName(col+1);
          	} catch (SQLException sqlex) {
     			toolPane.showMessageDialog(scroll, 
					"\nSQLCODE:  " + sqlex.getErrorCode() + 
  					 "\nSQLSTATE: " + sqlex.getSQLState() +
					  "\nSQLERRM:  " + sqlex.getMessage(),
					"Error in Querying!--ri", toolPane.ERROR_MESSAGE);
		}
		return "null";
	 }
         // absolute() method can not use the wasNull(), it did not work!
	 // so my idea is to get the "null" value, and rewrite the variable.
	 // and you have to know the "result" is not a original String,
	 // so the operator "==" may did not work, but use equals() method,
	 // it will get the inner String to compare with, so it can work!
	 public Object getValueAt(int row, int col) { 
          	try {
			if(rs2.absolute(row+1)) {
				String result = rs2.getString(col+1);
//(row == 9) System.out.println(result + ", " + result.equals(" "));
				if(result.equals(" ")) result = "null";
				return result;
			}
			else
				return new String("error");
          	} catch (SQLException sqlex) {
     			toolPane.showMessageDialog(scroll, 
					"\nSQLCODE:  " + sqlex.getErrorCode() + 
  					 "\nSQLSTATE: " + sqlex.getSQLState() +
					  "\nSQLERRM:  " + sqlex.getMessage(),
				"Error in Querying!--ri2", toolPane.ERROR_MESSAGE);
          	}
          	return new String("null");
          }
        };
	this.output.setModel(dataModel);
	    } catch (SQLException sqlex) {
     			toolPane.showMessageDialog(scroll, 
					"\nSQLCODE:  " + sqlex.getErrorCode() + 
  					 "\nSQLSTATE: " + sqlex.getSQLState() +
					  "\nSQLERRM:  " + sqlex.getMessage(),
				"Error in Querying!--r", toolPane.ERROR_MESSAGE);
	    }
 }//end of refresh	

}  // end of kegstaff class


