class Solution {

    // Find Mid node 
    public ListNode findmid(ListNode head){
        ListNode slow = head;  
        ListNode fast = head;

        while(fast !=null && fast.next !=null){
            slow = slow.next;
            fast = fast.next.next;
        }

        return slow;
    }

    //Check if palindrome or not
    public boolean isPalindrome(ListNode head){

        // Edge case if there is only one or no element in the linked list
        if(head == null || head.next == null){
            return true;
        }

        // reverse the second half of the linked list
        ListNode prev = null;
        ListNode curr = findmid(head);
        ListNode next;

        while(curr != null){
            next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        ListNode righthead = prev;
        ListNode lefthead = head;
        
        // check for palindrom
        while (righthead != null){
            if(righthead.val != lefthead.val){
                return false;
            }

            lefthead = lefthead.next;
            righthead = righthead.next;
        }

        return true;
    }
}