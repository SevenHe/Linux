/*
 * 赫柏在绝域之门击败鲁卡斯后，从鲁卡斯身上掉落了一本高级技能书，赫柏打开后惊喜地发现这是一个早已失传的上古技能---禁忌雷炎。
 该 技能每次发动只需扣很少的精神值，而且输出也非常高。                                                                   *
 具体魔法描述如下：
 把地图抽象为一个二维坐标，技能发动者位于(0,0)位置。以技能发动者为中心，做一个半径为r的圆，满足r^2=S，如果敌人位于这个圆上，且位置为整点坐标，这个敌人将收到该技能的输出伤害。
 */
/*
 * float just has 23 bits' numbers, so when the number > 10000000(seven of 0), should be the double.
 */

 #include <iostream>
 #include <iomanip>
 #include <cmath>
 using namespace std;

 int main()
 {
	 int S;
	 while(cin >> S)
	 {
		 int ret = 0;
		 double rRadius = sqrt((double)S);
		 int radius = sqrt(S);
		 cout << setprecision(3) << rRadius << endl;
		 cout << radius << endl;
		 cout << (rRadius == radius) << endl;
		 if(rRadius > radius)
		 {
			 for(int i=1; i<=radius; i++)
			 {
				 double rJ = sqrt(S-i*i);
				 int j = sqrt(S-i*i);
				 if(rJ == j)
				 {
					 ret ++;
					 //cout << i << " -- " << endl;
				 }
			 }
			ret *= 4;
		 }
		 else if(rRadius == radius)
		 {
			 for(int i=1; i<radius; i++)
			 {
				 double rJ = sqrt(S-i*i);
				 int j = sqrt(S-i*i);
				 if(rJ == j)
					 ret ++;
			 }

			ret *= 4;
			ret += 4;
		 }
		 cout << ret << endl;
	 }

	 return 0;
}
