class Solution {
    public List<Integer> findAnagrams(String s, String p) {

        HashMap <Character,Integer> originalMap = new HashMap<>();

        ArrayList<Integer> arr = new ArrayList<>();

        if(p.length()>s.length()){
            return arr;
        }

        //traverse p
        for(int i =0; i<p.length(); i++){
            originalMap.put(p.charAt(i),originalMap.getOrDefault(p.charAt(i),0)+1);
        }

        //two pointer
        int i = 0;
        int j = p.length()-1;
        

        HashMap<Character,Integer> map = new HashMap<>();
        //first window traversing
        for(int x = i; x<=j; x++){    

            map.put(s.charAt(x),map.getOrDefault(s.charAt(x),0)+1);
            
        }

        //checking if both the hashmap are equal
        boolean isEqual = originalMap.equals(map);
        //add pointer indices to array
        if(isEqual){
            arr.add(i);
        }

        //traversing the whole window
        while(j<s.length()-1){

            map.put(s.charAt(i),map.get(s.charAt(i))-1); 
            if(map.get(s.charAt(i))==0){
                              
           
                map.remove(s.charAt(i));
            }

            i++;
            j++;
            map.put(s.charAt(j),map.getOrDefault(s.charAt(j),0)+1);
            boolean isEqual2 = originalMap.equals(map);
            if(isEqual2){
                arr.add(i);
            }
        }
        return arr;
    }
}