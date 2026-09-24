int xorAfterQueries(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    for(int i = 0; i < queriesSize; i++){
		int start = queries[i][0];
		int end = queries[i][1];
		int step = queries[i][2];
		int times = queries[i][3];
		for(int j = start; j <= end; j += step){
			nums[j] = ((long long) nums[j] * times) % 1000000007;
		}
	}
	int r = 0;
	for(int i = 0; i < numsSize; i++){
		if(i == 0){
			r = nums[i];
		} else {
			r ^= nums[i];
		}
	}
	return r;
}