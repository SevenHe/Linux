/*

	To handle a problem that rotate a matrix by 90 degree counterclockwise!
	
*/


import java.util.*;

public class InverseMatrix {
	
	public static void main(String[] args) {
		
		new InverseMatrix().run();
	
	}
	
	public void run() {
		
		Scanner input = new Scanner(System.in);
		int row = input.nextInt();
		int column = input.nextInt();
		int[][] Mx = new int[column][row];
		if(row <= 1000 && column >= 1)
			for(int i=0; i<row; i++)
				for(int j=column-1; j>=0; j--)
					Mx[j][i] = input.nextInt();
		for(int i=0; i<column; i++) {
			for(int j=0; j<row; j++)
				System.out.print(Mx[i][j] + " ");
			System.out.println();
		}
		input.close();
		
	}
	
}
				
		