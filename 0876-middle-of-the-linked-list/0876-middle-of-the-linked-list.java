
class Solution {
    public ListNode middleNode(ListNode head) {
        
        ListNode temp=head,t=head;
        int c=0;
        while(temp!=null){
            c++;
            temp=temp.next;
        }
        for(int i=0;i<c/2;i++){
            t=t.next;
        }
        return t;
    }
}