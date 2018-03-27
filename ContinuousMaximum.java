/**
 * @Date 2018-03-27
 * @author ZhangydA
 * @SAU
 */
public class ContinuousMaximum {
	public int continuousMaxinum(int arr[]){
		int counter = 0;
		for (int i = 0;i < arr.length;i ++){
			if (arr[i] < 0) counter ++;
		}
		//如果所有的值都为负值，返回0
		if (counter == arr.length) return 0;
		int sum = 0,ans = Integer.MIN_VALUE,mins = 0;
		for (int i = 0;i < arr.length;i ++){
			sum += arr[i];
			if (sum - mins > ans)
				ans = sum - mins;
			if (mins > sum)
				mins = sum;
		}
		return ans;
	}
}
