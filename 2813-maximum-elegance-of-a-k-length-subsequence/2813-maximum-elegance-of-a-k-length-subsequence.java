class Solution {
    public long findMaximumElegance(int[][] items, int k) {
        Arrays.sort(items, (a,b)-> b[0]-a[0]);
        Stack<Integer> duplicates=new Stack<>();
        HashSet<Integer> selected_cats=new HashSet<>(k);

        long total_profit=0, elegance=0, size;
        for(int i=0;i<items.length;i++) {
            if(i<k){
                total_profit+=items[i][0];
                if(selected_cats.contains(items[i][1])) duplicates.add(items[i][0]);
            } else {
                if(duplicates.isEmpty()) break;
                if(!selected_cats.contains(items[i][1]))
                    total_profit+=items[i][0]-duplicates.pop();
            }
            selected_cats.add(items[i][1]);
            elegance=Math.max(elegance, total_profit+(size=selected_cats.size())*size);
        }
        
        return elegance;
    }
}