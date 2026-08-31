class Solution {
    public List<String> fizzBuzz(int n) {
        List<String> response = new ArrayList<>();
        for(int i = 1 ; i <= n ; i ++){
            if(i % 3 == 0 && i % 5 == 0){
                response.add("FizzBuzz");
            }else if(i % 3 == 0){
                response.add("Fizz");
            }else if(i % 5 == 0){
                response.add("Buzz");
            }else{
                response.add(String.valueOf(i));
            }
        }
        return response;
    }
}