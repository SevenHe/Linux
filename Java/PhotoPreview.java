import java.sql.*;
import java.io.*;
import java.util.*;
import java.math.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.filechooser.*;
import javax.imageio.*;
import javax.imageio.stream.*;


public class PhotoPreview extends JFrame implements ActionListener {

	static private Connection con = null;
	private MyPanel photoPane = null;
	private JLabel title = new JLabel();
	private String[] info = null;
	private String[] photoFormats = null;
	private int pIndex = 0;
	private ArrayList<Image> images = null;
 	static {
		try
        {   
           Class.forName ("com.ibm.db2.jcc.DB2Driver");  
		   con = DriverManager.getConnection("jdbc:db2://localhost:9527/SAMPLE", "owner", "hechanghong1001");
        }
        catch (Exception e)
        {  
			 System.exit(1);
        }
    }

	public PhotoPreview() {
		JButton next = new JButton(">>");
		JButton previous = new JButton("<<");
		JButton insert = new JButton("Insert");
		insert.setPreferredSize(new Dimension(100, 50));
		next.addActionListener(this);
		previous.addActionListener(this);
		insert.addActionListener(this);
		
		this.setTitle("HeChangHong");
		this.setBounds(200, 50, 700, 700);	
		this.setLayout(new BorderLayout());
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);

		this.add(next, BorderLayout.EAST);
		this.add(previous, BorderLayout.WEST);
		this.add(insert, BorderLayout.SOUTH);
	}

	public static void main(String[] args) {
		PhotoPreview window = new PhotoPreview();
		window.preview();
		window.setVisible(true);
	}

	public void preview() {
		String sql = "select EMPNO, PHOTO_FORMAT from EMP_PHOTO";
		try {
				Statement stmt = con.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
				ResultSet rs = stmt.executeQuery(sql);			
				//get row count
				rs.last();
				int rowCount = rs.getRow();
System.out.println("Get row count:" + rowCount);
				rs.beforeFirst();
				//initialization
				title.setHorizontalAlignment(JLabel.CENTER);
				info = new String[rowCount];
				photoFormats = new String[rowCount];
				images = new ArrayList<Image>();
				boolean more = rs.next();
				int index = 0;
				//get datum!
				while(more) {
						info[index] = "<html><h3>" + rs.getString(1) + "</h3></html>";
						photoFormats[index] = rs.getString(2);
System.out.println("Get empno:" + info[index]);
						more = rs.next();
						index ++;
				}
				rs = con.createStatement().executeQuery("select PICTURE from EMP_PHOTO");
				//reset the indexes.
				index = 0;
				more = rs.next();
				while(more) {		
						//input bytes and convert it to a ImageInputStream.
						BufferedInputStream bis = new BufferedInputStream(rs.getBinaryStream("PICTURE"));
						/* limited to the  java image formats!
						Iterator<?> readers = ImageIO.getImageReadersByFormatName(photoFormats[index]);
						ImageReader reader = null;
						if(readers.hasNext()) {
							reader = (ImageReader)readers.next();
						} else if(photoFormats[index] == "bitmap") {
							readers = ImageIO.getImageReadersByFormatName("bmp");
							reader = (ImageReader)readers.next();
						}
						//get read param!
						reader.setInput(iis,true);
						ImageReadParam param = reader.getDefaultReadParam();
						Object source = bais;
						ImageInputStream iis = ImageIO.createImageInputStream(source);
						*/
						//Get a image!
						images.add(index, ImageIO.read(bis));
//System.out.println("Read:" + images[index] + bis);
					
						more = rs.next();
						index ++;
				}		
				photoPane = new MyPanel(images);
				title.setText(info[pIndex]);
				this.add(title, BorderLayout.NORTH);
				this.add(photoPane, BorderLayout.CENTER);
		} catch (SQLException e) {
				System.out.println("SQLCode:" + e.getErrorCode());
				System.out.println("SQLState:" + e.getSQLState());
				System.out.println("SQLMessage:" + e.getMessage());
		} catch (IOException ioe) {
				ioe.printStackTrace();
		}	
	}
	
	class MyPanel extends JPanel {
		
		ArrayList<Image> images = null;	
		boolean mNewImageNotify = false;
		int mIndex = 0;

		MyPanel(ArrayList<Image> images) {
				this.images = images;
		}
		
		public void notifyIncrement() {
				if(mIndex != images.size()-1) mIndex ++;
				else mIndex = 0;
				repaint();
		}

		public void notifyDecrement() {
				if(mIndex != 0) mIndex --;
				else mIndex = images.size() - 1;
				repaint();
		}

		public void notifyNewImage(Image newImage) {
				this.images.add(newImage);
				mNewImageNotify = true;
				repaint();
		}

		@Override
		public void paintComponent(Graphics g) {
				super.paintComponent(g);
				if(!mNewImageNotify) {
						int parentWidth = this.getWidth();
						int parentHeight = this.getHeight();
						int childWidth  = images.get(mIndex).getWidth(this);
						int childHeight = images.get(mIndex).getHeight(this);
						if(parentWidth > childWidth && parentHeight > childHeight) {
								g.drawImage(images.get(mIndex), parentWidth/2 - childWidth/2, parentHeight/2 - childHeight/2, this);
						}
						else
								g.drawImage(images.get(mIndex), 0, 0, this);
				}
				else g.drawImage(images.get(images.size()-1), 0, 0, this);
		}
	}

	// after remove, you must repaint()!
	public void actionPerformed(ActionEvent ae) {
			if(ae.getSource() instanceof JButton) {
					JButton tempButton = (JButton)ae.getSource();
					if(tempButton.getText() == ">>") {
							photoPane.notifyIncrement();
							if(pIndex != images.size()-1) pIndex ++;
							else pIndex = 0;
							title.setText(info[pIndex]);
					}
					else if(tempButton.getText() == "<<") {
							photoPane.notifyDecrement();
							if(pIndex != 0) pIndex --;
							else pIndex = images.size()-1;
							title.setText(info[pIndex]);
					}
					else if(tempButton.getText() == "Insert") {
							JFileChooser jfc = new JFileChooser();
							FileNameExtensionFilter fnef = new FileNameExtensionFilter("image files", "jpg", "jpeg", "png", "gif");
							jfc.setFileFilter(fnef);
							jfc.showOpenDialog(this);
							File sf = jfc.getSelectedFile();
							try {
									FileInputStream fis = new FileInputStream(sf);
									BufferedInputStream bis = new BufferedInputStream(fis);
									Image newImage = ImageIO.read(fis);
									photoPane.notifyNewImage(newImage);
							} catch (Exception e) {
									System.out.println(e.getMessage());
							}
							title.setText("<html><h3>" + sf.getPath() + "</h3></html>");
							this.repaint();
					}
			}
	}

}
