/*

	According to a, b, c and y1, y2, output the date that is at every year between y1 and y2, month a ,week b and day c.
	Thinking and infering!
	
	The best structure is to add methods for year, month, and week, day!
	
*/
import java.util.*;

public class Festival {

	public static void main(String[] args) {
			Scanner input = new Scanner(System.in);
            //For one more month to minus.
			int[] countPre = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
			int[] data = new int[5];
			int[] output = new int[3];
			int dayPrcd = 1;
			//Get the Input
			for(int i=0; i<5; i++)
				data[i] = input.nextInt();
			//Judge arguments is out of bound or not.
			if(data[3] > 2050 || data[4] > 2050 || data[3] < 1850 || data[4] < 1850 || data[0] <= 0 || data[0] > 12 || data[1] > 5 || data[1] <= 0 || data[2] > 7 || data[2] <= 0)
				return;
			if(data[3] > data[4]) {
				int temp = data[4]; 
				data[4] = data[3];
				data[3] = temp;
			}
			int difference = data[4] - data[3];
			//Get the year1 Dec 31st day is which day of a week.
			//Get the day that is the last day in last year. 
			for(int i=0; i<data[3] - 1850; i++) {
				if(isLeapYear(1850+i)) 
					dayPrcd = (dayPrcd + 366) % 7 == 0 ? 7 : (dayPrcd + 366) % 7;
				else
					dayPrcd = (dayPrcd + 365) % 7 == 0 ? 7 : (dayPrcd + 365) % 7;
//System.out.println((1850+i) + ":" + dayPrcd);
			}
			//to use the ternary expression for augmenting the readability of the code.
			//this is for better expansibility.
			for(int i=0; i<=difference; i++) {
				output[0] = data[3] + i;
				output[1] = data[0];
                //For exact days in current month.
                // And for provision!
                // or say that is taking precautions!
				output[2] = 0;
				int oldDay = dayPrcd;
//System.out.println("oldDay:" + oldDay);
				//If it is a leap year, then do following.
				if(isLeapYear(data[3] + i)) {
					if(data[0] >= 3)
						dayPrcd = (countPre[data[0]-1] + 1 + dayPrcd) % 7 == 0 ? 7 : (countPre[data[0]-1] + 1 + dayPrcd) % 7;
					else
						dayPrcd = (countPre[data[0]-1] + dayPrcd) % 7 == 0 ? 7 : (countPre[data[0]-1] + dayPrcd) % 7;
//System.out.println("last day:" + dayPrcd);
					if(dayPrcd < 7 && data[1]-2 >= 0 && 7 - dayPrcd + (data[1]-2) * 7 + data[2] <= countPre[data[0]] - countPre[data[0]-1]) {
						output[2] = (7 - dayPrcd) + (data[1]-2) * 7 + data[2];
					}
					else if(dayPrcd < 7 && data[1]-2 < 0 && 7 - dayPrcd + (data[1]-2) * 7 + data[2] <= countPre[data[0]] - countPre[data[0]-1]) {
						output[2] = data[2] > dayPrcd ? data[2] - dayPrcd : 0;
					}
					else if(dayPrcd == 7 && (data[1]-1) * 7 + data[2] <= countPre[data[0]] - countPre[data[0]-1]) {
						output[2] =(data[1]-1) * 7 + data[2];
					}
					dayPrcd = (oldDay + countPre[12] + 1) % 7 == 0 ? 7 : (oldDay + countPre[12] + 1) % 7;	
				}
				//or not, it's below.
				else {
					dayPrcd = (countPre[data[0]-1] + dayPrcd) % 7 == 0 ? 7 : (countPre[data[0]-1] + dayPrcd) % 7;
					if(dayPrcd < 7 && data[1]-2 >= 0 && 7 - dayPrcd + (data[1]-2) * 7 + data[2] <= countPre[data[0]] - countPre[data[0]-1]) {
						output[2] = (7 - dayPrcd) + (data[1]-2) * 7 + data[2];
					}
					else if(dayPrcd < 7 && data[1]-2 < 0 && 7 - dayPrcd + (data[1]-2) * 7 + data[2] <= countPre[data[0]] - countPre[data[0]-1]) {
						output[2] = data[2] > dayPrcd ? data[2] - dayPrcd : 0;
					}
					else if(dayPrcd == 7 && (data[1]-1) * 7 + data[2] <= countPre[data[0]] - countPre[data[0]-1]) {
						output[2] = (data[1]-1) * 7 + data[2];
					}
					dayPrcd = (oldDay + countPre[12]) % 7 == 0 ? 7 : (oldDay + countPre[12]) % 7;
				}
				//Output judging!
				if(output[2] != 0) {
                    String concatenate = output[1] >= 10 ? output[0] + "/" + output[1] : output[0] + "/0" + output[1];
                    concatenate += output[2] >= 10 ? "/" + output[2] : "/0" + output[2];
                    System.out.println(concatenate);
                }
                else
					System.out.println("none");
                                                                 
			}
			input.close();
			
	}
	
	public static boolean isLeapYear(int year) {
	
			return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
			
	}

}//END
					
					
							
							
						
						
						
						
						
						
						
						
						
						
						
				
	