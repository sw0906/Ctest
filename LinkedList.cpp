//
//  LinkedList.cpp
//  Ctest
//
//  Created by admin on 9/1/17.
//  Copyright © 2017 admin. All rights reserved.
//

#include "AlgorithmHeader.hpp"



#pragma mark - Required - easy

#pragma mark -  Remove Nth Node From End of List

/*
 
Given a linked list, remove the nth node from the end of list and return its head.

Notice

The minimum number of nodes in list is n.

Have you met this question in a real interview? Yes
Example
Given linked list: 1->2->3->4->5->null, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5->null.


*/

ListNode *removeNthFromEnd(ListNode *head, int n) {
    // write your code
    ListNode *checkNode = head;
    for(int i=0; i<n; i++)
    {
        checkNode = checkNode->next;
        if(i==n-1 && checkNode == NULL)
        {
            return head->next;
        }
    }
    
    ListNode *deleteNode = head;
    while(checkNode->next)
    {
        checkNode = checkNode->next;
        deleteNode  = deleteNode->next;
    }
    
    deleteNode->next = deleteNode->next->next;
    return head;
}


#pragma mark - Partition List
/*
Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

Have you met this question in a real interview? Yes
Example
Given 1->4->3->2->5->2->null and x = 3,
return 1->2->2->4->3->5->null.
 
 
 1 2 2 - 4 3 5
 */


ListNode *partition(ListNode *head, int x) {
    ListNode *preL = new ListNode(0);
    ListNode *preR = new ListNode(0);
    ListNode *tailL = preL;
    ListNode *tailR = preR;
    
    //add l/r
    while(head)
    {
        if(head->val < x)
        {
            tailL->next = head;
            tailL = tailL->next;
        }
        else
        {
            tailR->next = head;
            tailR = tailR->next;
        }
        head = head->next;
    }
    
    //connect l and r
    tailR->next = NULL;
    tailL->next = preR->next;
    return preL->next;
}


#pragma mark - Required - Mid

#pragma mark -  Reverse Linked List II

/*
 
Reverse a linked list from position m to n.

Notice

Given m, n satisfy the following condition: 1 ≤ m ≤ n ≤ length of list.

Have you met this question in a real interview? Yes
Example
Given 1->2->3->4->5->NULL, m = 2 and n = 4, return 1->4->3->2->5->NULL.
 
 
 */

void reverse(ListNode *head, ListNode *foot)
{
    if(!head)
        return;
    
    ListNode *pre = NULL;
    ListNode *cur = head;
    while(cur!=foot)
    {
        ListNode *next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
}

ListNode *findNode(int m, ListNode *head)
{
    ListNode *po = head;
    while(m > 0)
    {
        po = po->next;
        --m;
    }
    return po;
}


ListNode *reverseBetween(ListNode *head, int m, int n) {
    // write your code here
    if(!head || !head->next || m==n)
        return head;
    
    ListNode *d = new ListNode(-1);
    d->next = head;
    
    //!!preBegin -- need dummy node
    ListNode *preBegin = findNode(m-1, d);
    ListNode *begin = preBegin->next;
    ListNode *end = findNode(n, d);
    ListNode *endNext = end->next;
    
    // end->next = NULL;
    reverse(begin, end->next);
    
    //connect
    begin->next = endNext;
    preBegin->next = end;
    
    return d->next;
    
}






#pragma mark -  Reorder List

/*
 
 Given a singly linked list L: L0 → L1 → … → Ln-1 → Ln
 
 reorder it to: L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …
 
 Have you met this question in a real interview? Yes
 Example
 Given 1->2->3->4->null, reorder it to 1->4->2->3->null.
 
 
 */


void reorderList2(ListNode *head) {
    //exit
    if(!head || !head->next)
        return;
    
    //add nodes to vector
    vector<ListNode *>nodes;
    while(head)
    {
        nodes.push_back(head);
        head = head->next;
    }
    
    //connect new nodes
    ListNode *dummy = new ListNode(-1);
    while(nodes.size())
    {
        dummy->next = nodes.front();
        nodes.erase(nodes.begin());
        dummy = dummy->next;
        
        if(nodes.size())
        {
            dummy->next = nodes.back();
            nodes.pop_back();
            dummy = dummy->next;
        }
    }
    dummy->next = NULL;
    
}



#pragma mark - Copy List with Random Pointer
/*
 
 A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.
 
 Return a deep copy of the list.
 
 */


struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};


RandomListNode *copyRandomList(RandomListNode *head) {
    //exit
    if(!head)
        return NULL;
    
    RandomListNode *preNode = head;//save head
    unordered_map<RandomListNode*, RandomListNode*> old2new;
    
    //copy node - save hash
    while(head)
    {
        RandomListNode *newN = new RandomListNode(head->label);
        old2new[head] = newN;
        head = head->next;
    }
    
    //link new node
    head = preNode;
    while(head)
    {
        RandomListNode *newN = old2new[head];
        newN->next = old2new[head->next];
        newN->random = old2new[head->random];
        head = head->next;
    }
    return old2new[preNode];
}






#pragma mark - Sort List


/*
 
Sort a linked list in O(n log n) time using constant space complexity.

Have you met this question in a real interview? Yes
Example
Given 1->3->2->null, sort it to 1->2->3->null.
 
*/


ListNode *findMidNode(ListNode *s, ListNode *e)
{
    if( s == NULL ||s->next == e )
        return s;
    
    ListNode *m = s;
    while(s != e)
    {
        if(s->next != e && s->next->next != e)
        {
            s = s->next->next;
            m = m->next;
        }
        else
        {
            return m;
        }
    }
    return m;
}

ListNode *merge2List(ListNode *l, ListNode *r)
{
    ListNode *dummyN = new ListNode(-1);
    ListNode *preN = dummyN;
    
    while(l && r)
    {
        if(l->val < r->val)
        {
            preN->next = l;
            l = l->next;
        }
        else
        {
            preN->next = r;
            r = r->next;
        }
        preN = preN->next;
    }
    
    if(l)
        preN->next = l;
    else
        preN->next = r;
    
    return dummyN->next;
}


ListNode *mergeSort(ListNode *begin, ListNode *end)
{
    //important!!!
    if ( !begin || begin == end) {
        return begin;
    }
    
    ListNode *mid  = findMidNode(begin, end);
    
    
    ListNode *r = mergeSort(mid->next, end);
    mid->next = NULL;//important
    ListNode *l = mergeSort(begin, mid);
    
    return merge2List(l, r);
}


ListNode *sortList(ListNode *head) {
    return mergeSort(head, NULL);
}





#pragma mark -  Merge k Sorted Lists

/*
 
Merge k sorted linked lists and return it as one sorted list.

Analyze and describe its complexity.

Have you met this question in a real interview? Yes
Example
Given lists:

[
 2->4->null,
 null,
 -1->null
 ],
return -1->2->4->null.

*/


//     priority_queue 对于基本类型的使用方法相对简单。他的模板声明带有三个参数，priority_queue<Type, Container, Functional>
// Type 为数据类型， Container 为保存数据的容器，Functional 为元素比较方式。
// Container 必须是用数组实现的容器，比如 vector, deque 但不能用 list.
// STL里面容器默认用的是 vector. 比较方式默认用 operator< , 所以如果你把后面俩个参数 缺省的话，优先队列就是大顶堆，队头元素最大。


//solution 1
struct Comparator
{
    bool operator () (const ListNode *lhs, const ListNode *rhs)
    {
        return lhs->val > rhs->val;
    }
};

ListNode *mergeKLists(vector<ListNode *> &lists) {
    //exit
    if(lists.size() == 0)
        return NULL;
    else if(lists.size() == 1)
        return lists[0];
    
    //queue
    priority_queue<ListNode *,vector<ListNode *>, Comparator> pq;
    
    //add to queue
    for(int i=0; i<lists.size(); i++)
    {
        while(lists[i])
        {
            pq.push(lists[i]);
            lists[i] = lists[i]->next;
        }
    }
    
    //pop queue
    ListNode *tail = new ListNode(-1);
    ListNode *preN = tail;
    while(pq.size())
    {
        tail->next = pq.top();
        pq.pop();
        tail = tail->next;
    }
    return preN->next;
}


//solution 2

ListNode *mergeHelper(vector<ListNode *> &lists, long start, long end)
{
    if(end == start)
        return lists[start];
    
    long mid = start + (end-start)/2;
    ListNode *l = mergeHelper(lists, start, mid);
    ListNode *r = mergeHelper(lists, mid+1, end);
    return merge2List(l, r);
}

ListNode *mergeKLists2(vector<ListNode *> &lists) {
    // write your code here
    if(lists.size() == 0)
        return NULL;
    
    if(lists.size() == 1)
        return lists[0];
    
    return mergeHelper(lists, 0, lists.size()-1);
}





#pragma mark -  Remove Duplicates from Sorted List II

/*
 
 Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
 
 Have you met this question in a real interview? Yes
 Example
 Given 1->2->3->3->4->4->5, return 1->2->5.
 Given 1->1->1->2->3, return 2->3.
 
 */


ListNode * deleteDuplicates(ListNode *head) {
    if(!head)
        return head;
    // write your code here
    ListNode *pre = new ListNode(INT_MIN);
    pre->next = head;
    ListNode *dummy = pre;
    while (dummy->next != NULL && dummy->next->next != NULL)
    {
        int val = dummy->next->val;
        if(dummy->next->next->val == val)
        {
            while(dummy->next != NULL && val == dummy->next->val)
            {
                dummy->next = dummy->next->next;
            }
        }
        else
        {
            dummy = dummy->next;
        }
    }
    return pre->next;
}


#pragma mark - Convert Sorted List to Balanced BST

/*
 
 Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
 
 Have you met this question in a real interview? Yes
 Example
 2
 1->2->3  =>   / \
 1   3
 */


TreeNode *sortedListToBSTHelper(ListNode *s, ListNode *e)
{
    if(s == e)
    {
        return NULL;
    }
    else if(s->next == e)
    {
        return new TreeNode(s->val);
    }
    
    ListNode *m = findMidNode(s, e);
    TreeNode *t = new TreeNode(m->val);
    
    t->left = sortedListToBSTHelper(s,m);
    t->right = sortedListToBSTHelper(m->next, e);
    return t;
}

TreeNode *sortedListToBST(ListNode *head) {
    return sortedListToBSTHelper(head, NULL);
}





#pragma mark - Required - Hard

#pragma mark - Linked List Cycle II

/*
 
Given a linked list, return the node where the cycle begins.

If there is no cycle, return null.

Have you met this question in a real interview? Yes
Example
Given -21->10->4->5, tail connects to node index 1，return 10

*/

ListNode *detectCycle(ListNode *head) {
    //exit
    if(!head || !head->next)
        return NULL;
    
    //fast - slow pointer
    ListNode *fast = head->next;
    ListNode *slow = head;
    while(fast !=  slow)
    {
        if(!fast || !fast->next || !fast->next->next)
            return NULL;
        
        fast = fast->next->next;
        slow = slow->next;
    }
    
    
    while(head != slow->next)
    {
        head = head->next;
        slow = slow->next;
    }
    return head;
}




#pragma mark - Optional - easy

#pragma mark -  Middle of Linked List

/*
 
Find the middle node of a linked list.

Have you met this question in a real interview? Yes
Example
Given 1->2->3, return the node with value 2.

Given 1->2, return the node with value 1.

*/

ListNode *middleNode(ListNode *head) {
    if(!head || !head->next )
        return head;
    
    ListNode *mid = head;
    while(head && head->next && head->next->next)//!!!
    {
        head = head->next->next;
        mid = mid->next;
    }
    return mid;
    
//    return findMidNode(head, NULL);
}


#pragma mark -  Insertion Sort List

/*
 
Sort a linked list using insertion sort.

Have you met this question in a real interview? Yes
Example
Given 1->3->2->0->null, return 0->1->2->3->null.

*/


ListNode *insertionSortList(ListNode *head) {
    if(!head)
        return head;
    
    ListNode *du = new ListNode(-1);
    du->next = new ListNode(head->val);
    head = head->next;
    
    while(head)
    {
        ListNode *pre = du;
        while(pre && pre->next && pre->next->val < head->val)//!!注意为空的empt
        {
            pre = pre->next;
        }
        ListNode *next = pre->next;
        pre->next = new ListNode(head->val);
        pre->next->next = next;
        head = head->next;
    }
    return du->next;
}


#pragma mark - Reverse Linked List

/*
 
Reverse a linked list.

Have you met this question in a real interview? Yes
Example
For linked list 1->2->3, the reversed linked list is 3->2->1

*/

ListNode *reverse(ListNode *head) {
    ListNode *dummy = new ListNode(-1);
    while(head)
    {
        ListNode *headNext = head->next;
        ListNode *dNext = dummy->next;
        dummy->next = head;
        dummy->next->next = dNext;
        head = headNext;
    }
    return dummy->next;
}



#pragma mark - Add Two Numbers

/*
 
You have two numbers represented by a linked list, where each node contains a single digit. The digits are stored in reverse order, such that the 1's digit is at the head of the list. Write a function that adds the two numbers and returns the sum as a linked list.

Have you met this question in a real interview?
Which company asked you this question? Airbnb Alibaba Amazon Apple Baidu Bloomberg Cisco Dropbox Ebay Facebook Google Hulu Intel Linkedin Microsoft NetEase Nvidia Oracle Pinterest Snapchat Tencent Twitter Uber Xiaomi Yahoo Yelp Zenefits
Example
Given 7->1->6 + 5->9->2. That is, 617 + 295.

Return 2->1->9. That is 912.

Given 3->1->5 and 5->9->2, return 8->0->8.


*/


int nodeToNumber(ListNode *l)
{
    int n = 0;
    while(l)
    {
        if(l->next)
        {
            n = (n + l->val) * 10;
        }
        else
        {
            n += l->val;
        }
        l = l->next;
    }
    return n;
}

ListNode *numberToNode(int number)
{
    if(number == 0)
        return new ListNode(0);
    
    ListNode *dummy = new ListNode(-1);
    while(number)
    {
        int n = number;
        number = number/10;
        ListNode *tmp = new ListNode(n);
        ListNode *next = dummy->next;
        dummy->next = tmp;
        tmp->next = next;
    }
    return dummy->next;
}

ListNode *addLists2(ListNode *l1, ListNode *l2) {
    int n1 = nodeToNumber( reverse(l1) );
    int n2 = nodeToNumber( reverse(l2) );
    int total = n1 + n2;
    return reverse( numberToNode(total) );
}




#pragma mark - Optional - mid

#pragma mark -  Rotate List

/*
Given a list, rotate the list to the right by k places, where k is non-negative.

Have you met this question in a real interview? Yes
Example
Given 1->2->3->4->5 and k = 2, return 4->5->1->2->3.

*/
//solution 1
int getListLength(ListNode *head)
{
    ListNode *checkN = head;
    int length = 0;
    while(checkN != NULL)
    {
        checkN = checkN->next;
        length++;
    }
    return length;
}


ListNode *rotateRight(ListNode *head, int k) {
    // write your code here
    if(head == NULL || head->next == NULL)
    {
        return head;
    }
    
    int length = getListLength(head);
    k = k % length;
    
    if(k == 0)
        return head;
    
    k = length - k;
    ListNode *newHead = findNode(k, head);
    ListNode *newBack = findNode(k-1, head);
    ListNode *preBack = findNode(length-1, head);
    ListNode *preHead = head;
    preBack->next = preHead;
    newBack->next = NULL;
    return newHead;
}


//solution 2
ListNode *findAndMoveNode(ListNode *head, int k)
{
    //calculate move steps
    ListNode *checkN = head;
    int length = 0;
    while(checkN != NULL)
    {
        checkN = checkN->next;
        length++;
    }
    
    k = k%length;
    
    
    //
    ListNode *preNode = head;
    ListNode *rNode = head;
    while(k)
    {
        head = head->next;
        k--;
    }
    
    while(head->next)
    {
        head=head->next;
        rNode = rNode->next;
    }
    
    head->next = preNode;
    ListNode *tmpN = rNode->next;
    rNode->next = NULL;
    
    return tmpN;
}


ListNode *rotateRight2(ListNode *head, int k) {
    // write your code here
    if(head == NULL || head->next == NULL)
    {
        return head;
    }
    return findAndMoveNode(head, k);
}




#pragma mark - Palindrome Linked List

/*
 
Implement a function to check if a linked list is a palindrome.

Have you met this question in a real interview? Yes
Example
Given 1->2->1, return true


*/


ListNode *reverseAndCopy(ListNode *n)
{
    ListNode *dummy = new ListNode(-1);
    ListNode *headN, *duN; // = head->next;
    ListNode *head = n;
    while(head)
    {
        ListNode *newN = new ListNode(head->val);//!!不要影响
        
        duN = dummy->next;
        headN = head->next;
        
        dummy->next = newN;
        newN->next = duN;
        
        head = headN;
    }
    return dummy->next;
}

bool isPalindrome(ListNode* head) {
    // Write your code here
    if(!head || !head->next)
        return true;
    
    ListNode *r = reverseAndCopy(head);
    
    while(r)
    {
        if(r->val != head->val)
            return false;
        
        r = r->next;
        head = head->next;
    }
    return true;
}


#pragma mark -  Linked List Cycle

/*
 
Given a linked list, determine if it has a cycle in it.



Have you met this question in a real interview? Yes
Example
Given -21->10->4->5, tail connects to node index 1, return true

*/
bool hasCycle(ListNode *head) {
    if(!head)
        return NULL;
    
    ListNode *slow = head;
    while(head && head->next)
    {
        head = head->next->next;
        slow = slow->next;
        if(head == slow)
            return true;
    }
    return false;
}

#pragma mark - Test
void LinkedList::test()
{
    //    int re = testInt(4);
}

