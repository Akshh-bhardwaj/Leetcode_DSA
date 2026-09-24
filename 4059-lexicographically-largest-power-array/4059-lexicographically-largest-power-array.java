class Solution {
    public int[] largestPower(int[] nums) {
        int n = nums.length;
        int[] power = new int[15];

        List<List<Integer>> groups = new ArrayList<>();
        List<Integer> initial = new ArrayList<>();

        for (int num : nums) {
            initial.add(num);
        }

        groups.add(initial);

        for (int bit = 14; bit >= 0; bit--) {
            List<List<Integer>> newGroups = new ArrayList<>();
            int runningTotal = 0;
            boolean stopped = false;

            for (List<Integer> group : groups) {
                if (stopped) {
                    newGroups.add(group);
                    continue;
                }

                List<Integer> matched = new ArrayList<>();
                List<Integer> unmatched = new ArrayList<>();

                for (int num : group) {
                    if (((num >> bit) & 1) != 0) {
                        matched.add(num);
                    } else {
                        unmatched.add(num);
                    }
                }

                if (unmatched.isEmpty()) {

                    runningTotal += group.size();
                    newGroups.add(group);

                } else if (matched.isEmpty()) {

                    newGroups.add(group);
                    stopped = true;

                } else {

                    runningTotal += matched.size();

                    newGroups.add(matched);
                    newGroups.add(unmatched);

                    stopped = true;
                }
            }

            power[14 - bit] = runningTotal;
            groups = newGroups;
        }

        return power;
    }
}