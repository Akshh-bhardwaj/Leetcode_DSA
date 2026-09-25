class Solution {
    public long countIntersectingIntervals(int[][] intervals) {
                int n=intervals.length;
        int[][]events=new int[2*n][2];
        int idx=0;
        for(int []e:intervals){
            int a=e[0];
            int b=e[1];
            events[idx][0]=a;
            events[idx][1]=0;
            idx++;
            events[idx][0]=b;
            events[idx][1]=1;
            idx++;
        }
        Arrays.sort(events,(a,b)->{
            if(a[0]!=b[0]){
                return Integer.compare(a[0],b[0]);
            }
            return Integer.compare(a[1],b[1]);
        });
        long act=0;
        long ans=0;
        for(int []e:events){
            int ty=e[1];
            if(ty==0){
                ans+=act;
                act++;
            }
            else{
                act--;
            }
        }
        return ans;
    }
}