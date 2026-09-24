class Solution {
    public String frequencySort(String s) {

        HashMap<Character, Integer> map = new HashMap<>();

        // Count frequency
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);

            map.put(ch, map.getOrDefault(ch, 0) + 1);
        }

        // Convert characters to array
        Character[] arr = map.keySet().toArray(new Character[0]);

        // Sort according to frequency
        Arrays.sort(arr, (a, b) -> map.get(b) - map.get(a));

        // Build answer
        StringBuilder ans = new StringBuilder();

        for (char ch : arr) {

            for (int i = 0; i < map.get(ch); i++) {
                ans.append(ch);
            }
        }

        return ans.toString();
    }
}