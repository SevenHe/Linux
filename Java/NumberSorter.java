/*
 *	To sort numbers in a array!
 *	Another way is to put them into a map, and the logic is easy, 
 *	but the method calling and code complexity is difficult.	
 */
import java.util.*;

public class NumberSorter {

	public static void main(String[] args) {
		
		Scanner input = new Scanner(System.in);
		int amount = input.nextInt();
		int[] collection = new int[1000];
		int minNumber = 0;
		int maxCount = 0;
		if(amount > 1000)
			return;
		for(int i=0; i<amount; i++)
			collection[input.nextInt()]++;
		for(int j=0; j<amount; j++) {
			minNumber = 0;
			maxCount = 0;
			for(int i=0; i<1000; i++) 
				if(collection[i] != 0) {
					if(collection[i] > maxCount) {
						maxCount = collection[i];
						minNumber = i;
					}
					else if(collection[i] == maxCount)
						if(i < minNumber) {
							minNumber = i;
						}
				}
			if(maxCount != 0)
				System.out.println(minNumber + " " + maxCount);
			collection[minNumber] = 0;
		}
		input.close();
	}
}

