class Solution {
public int findNumbers(int[] nums) {
int count = 0;
for (int num : nums) {
int digits = (num == 0) ? 1 : 0;
int n = num;
while (n > 0) {
n /= 10;
digits++;
}
if (digits % 2 == 0) count++;
}
return count;
}
}