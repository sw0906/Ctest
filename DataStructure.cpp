//
//  DataStructure.cpp
//  Ctest
//
//  Created by admin on 9/1/17.
//  Copyright © 2017 admin. All rights reserved.
//

#include "AlgorithmHeader.hpp"

#pragma mark - Hash Function

//In data structure Hash, hash function is used to convert a string(or any other type) into an integer smaller than hash size and bigger or equal to zero. The objective of designing a hash function is to "hash" the key as unreasonable as possible. A good hash function can avoid collision as less as possible. A widely used hash function algorithm is using a magic number 33, consider any string as a 33 based big integer like follow:
//
//hashcode("abcd") = (ascii(a) * 333 + ascii(b) * 332 + ascii(c) *33 + ascii(d)) % HASH_SIZE
//
//= (97* 333 + 98 * 332 + 99 * 33 +100) % HASH_SIZE
//
//= 3595978 % HASH_SIZE
//
//here HASH_SIZE is the capacity of the hash table (you can assume a hash table is like an array with index 0 ~ HASH_SIZE-1).
//
//Given a string as a key and the size of hash table, return the hash value of this key.f
//
//
//
//Have you met this question in a real interview? Yes
//Clarification
//For this problem, you are not necessary to design your own hash algorithm or consider any collision issue, you just need to implement the algorithm as described.
//
//Example
//For key="abcd" and size=100, return 78
int hashCode(string key,int HASH_SIZE) {
    int ans = 0;
    for(int i = 0; i < key.size();i++) {
        ans = (1LL * ans * 33 + key[i]) % HASH_SIZE;
    }
    return ans;
}


#pragma mark -  Top k Largest Numbers

//Given an integer array, find the top k largest numbers in it.
//
//Have you met this question in a real interview? Yes
//Example
//Given [3,10,1000,-99,4,100] and k = 3.
//Return [1000, 100, 10].

vector<int> topk(vector<int>& nums, int k) {
    // Write your code here
    sort(nums.begin(), nums.end());
    long order = nums.size()-k;
    
    vector<int> sub;
    for(long i = order; i<nums.size(); i++)
    {
        sub.insert(sub.begin(),nums[i]);
    }
    return sub;
}


#pragma mark - Merge k Sorted Arrays
/*
 Given k sorted integer arrays, merge them into one sorted array.
 
 Have you met this question in a real interview? Yes
 Example
 Given 3 sorted arrays:
 
 [
 [1, 3, 5, 7],
 [2, 4, 6],
 [0, 8, 9, 10, 11]
 ]
 return [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11].
 */

vector<int> mergekSortedArrays(vector<vector<int>>& arrays) {
    // Write your code here
    vector<int> result;
    for(int i=0; i< arrays.size(); i++)
    {
        for(int j=0; j< arrays[i].size(); j++)
        {
            result.push_back(arrays[i][j]);
        }
    }
    sort(result.begin(), result.end());
    return result;
}

#pragma mark - Rehashing
/*
 The size of the hash table is not determinate at the very beginning. If the total size of keys is too large (e.g. size >= capacity / 10), we should double the size of the hash table and rehash every keys. Say you have a hash table looks like below:
 
 size=3, capacity=4
 
 [null, 21, 14, null]
 ↓    ↓
 9   null
 ↓
 null
 The hash function is:
 
 int hashcode(int key, int capacity) {
 return key % capacity;
 }
 here we have three numbers, 9, 14 and 21, where 21 and 9 share the same position as they all have the same hashcode 1 (21 % 4 = 9 % 4 = 1). We store them in the hash table by linked list.
 
 rehashing this hash table, double the capacity, you will get:
 
 size=3, capacity=8
 
 index:   0    1    2    3     4    5    6   7
 hash : [null, 9, null, null, null, 21, 14, null]
 Given the original hash table, return the new hash table after rehashing .
 
 Notice
 
 For negative integer in hash table, the position can be calculated as follow:
 
 C++/Java: if you directly calculate -4 % 3 you will get -1. You can use function: a % b = (a % b + b) % b to make it is a non negative integer.
 Python: you can directly use -1 % 3, you will get 2 automatically.
 Have you met this question in a real interview? Yes
 Example
 Given [null, 21->9->null, 14->null, null],
 
 return [null, 9->null, null, null, null, 21->null, 14->null, null]
 
 */

long getIndex(long number, long c)
{
    long r = number%c;
    if(r<0)
    {
        r += c;
    }
    return r;
}

vector<ListNode*> rehashing(vector<ListNode*> hashTable) {
    long c = hashTable.size();
    long newC = 2*c;
    vector<ListNode *>rehash(newC, NULL);
    for(int i=0; i<c; i++)
    {
        ListNode *tmpN = hashTable[i];
        while(tmpN)
        {
            long indexN = getIndex(tmpN->val, newC);
            ListNode *rHeader = rehash[indexN];
            if(!rHeader)
            {
                rehash[indexN] = tmpN;
                tmpN = tmpN->next;
                rehash[indexN]->next = NULL;
            }
            else
            {
                while(rHeader->next)
                {
                    rHeader = rHeader->next;
                }
                rHeader->next = tmpN;
                tmpN = tmpN->next;
                rHeader->next->next = NULL;
            }
        }
    }
    return rehash;
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






// example 2
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






#pragma mark -  Implement Queue by Two Stacks
/*
 
 As the title described, you should only use two stacks to implement a queue's actions.
 
 The queue should support push(element), pop() and top() where pop is pop the first(a.k.a front) element in the queue.
 
 Both pop and top methods should return the value of first element.
 
 Have you met this question in a real interview? Yes
 Example
 push(1)
 pop()     // return 1
 push(2)
 push(3)
 top()     // return 2
 pop()     // return 2
 
 
 */


class Queue {
public:
    stack<int> stack1;
    stack<int> stack2;
    
    Queue() {
        // do intialization if necessary
    }
    
    void push(int element) {
        // write your code here
        stack1.push(element);
    }
    
    void adjust()
    {
        if(stack2.empty())
        {
            while(!stack1.empty())
            {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
    }
    
    int pop() {
        // write your code here
        adjust();
        
        int number = stack2.top();
        stack2.pop();
        return number;
    }
    
    int top() {
        // write your code here
        adjust();
        
        return stack2.top();
    }
};


#pragma mark -  Min Stack
/*
 
 Implement a stack with min() function, which will return the smallest number in the stack.
 
 It should support push, pop and min operation all in O(1) cost.
 
 Notice
 
 min operation will never be called if there is no number in the stack.
 
 Have you met this question in a real interview? Yes
 Example
 push(1)
 pop()   // return 1
 push(2)
 push(3)
 min()   // return 2
 push(1)
 min()   // return 1
 
 */

class MinStack {
public:
    stack<int> stk, minStk;
    
    MinStack() {
        // do initialization if necessary
    }
    
    void push(int number) {
        // write your code here
        stk.push(number);
        if( !minStk.empty() )
        {
            if(number <= minStk.top())
            {
                minStk.push(number);
            }
        }
        else
        {
            minStk.push(number);
        }
    }
    
    int pop() {
        // write your code here
        int popN = stk.top();
        stk.pop();
        if(popN == minStk.top())
        {
            minStk.pop();
        }
        return popN;
    }
    
    int min() {
        // write your code here
        return minStk.top();
    }
};



#pragma mark -  Stack Sorting

/*
 
 Sort a stack in ascending order (with biggest terms on top).
 
 You may use at most one additional stack to hold items, but you may not copy the elements into any other data structure (e.g. array).
 
 Have you met this question in a real interview? Yes
 Example
 Given stack =
 
 | |
 |3|
 |1|
 |2|
 |4|
 -
 return:
 
 | |
 |4|
 |3|
 |2|
 |1|
 -
 The data will be serialized to [4,2,1,3]. The last element is the element on the top of the stack.
 
 
 */
void stackSorting(stack<int>& stk) {
    // Write your code here
    stack<int> newS;
    
    while(stk.size())
    {
        int v = stk.top();
        stk.pop();
        if(!newS.size())
        {
            newS.push(v);
        }
        else
        {
            while(newS.size() && newS.top()<v)
            {
                int nv = newS.top();
                stk.push(nv);
                newS.pop();
            }
            newS.push(v);
        }
    }
    
    while(newS.size())
    {
        int v = newS.top();
        stk.push(v);
        newS.pop();
    }
}


#pragma mark -  Ugly Number II
/*
 
 Ugly number is a number that only have factors 2, 3 and 5.
 
 Design an algorithm to find the nth ugly number. The first 10 ugly numbers are 1, 2, 3, 4, 5, 6, 8, 9, 10, 12...
 
 Notice
 
 Note that 1 is typically treated as an ugly number.
 
 Have you met this question in a real interview? Yes
 Example
 If n=9, return 10.
 */

int nthUglyNumber(int n) {
    int *uglys = new int[n];
    uglys[0] = 1;
    int next = 1;
    int *p2 = uglys;
    int *p3 = uglys;
    int *p5 = uglys;
    while(next < n)
    {
        int m = min(min(*p2 * 2, *p3 * 3), *p5 * 5);
        uglys[next] = m;
        if(m == *p2 * 2)
        {
            *p2++;
        }
        if(m == *p3 * 3)
        {
            *p3++;
        }
        if( m == *p5 * 5)
        {
            *p5++;
        }
        next++;
    }
    
    int uglyNumber = uglys[n-1];
    delete[] uglys;
    return uglyNumber;
}

#pragma mark -  Super Ugly Number
/*
 Write a program to find the nth super ugly number.
 
 Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k. For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32] is the sequence of the first 12 super ugly numbers given primes = [2, 7, 13, 19] of size 4.
 
 Notice
 
 1 is a super ugly number for any given primes.
 The given numbers in primes are in ascending order.
 0 < k ≤ 100, 0 < n ≤ 10^6, 0 < primes[i] < 1000
 Have you met this question in a real interview? Yes
 Example
 Given n = 6, primes = [2, 7, 13, 19] return 13
 
 */

int nthSuperUglyNumber(int n, vector<int>& primes) {
    // Write your code here
    if( primes.size() == 0 )
    {
        if(n>1)
        {
            return -1;
        }
    }
    
    long length = primes.size();
    vector<int> times(length, 0);
    vector<int> uglys(n, INT_MAX);
    uglys[0] = 1;
    for(int i=1; i<n; i++)
    {
        // set uglys
        for(int j=0; j<length; j++)
        {
            uglys[i] = min(uglys[i], primes[j]*uglys[times[j]]);
        }
        
        //find min
        for(int j = 0; j<length; j++)
        {
            if(uglys[i] == primes[j]*uglys[times[j]])
            {
                times[j]++;
            }
        }
    }
    return uglys[n-1];
}

#pragma mark - LRU Cache
/*
 
 Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.
 
 get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
 set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
 
 */

class KeyValue {
public:
    int key;
    int value;
    KeyValue *pre;
    KeyValue *next;
    
    
    KeyValue(int key, int value) {
        next = NULL;
        this->key = key;
        this->value = value;
    }
    KeyValue() {
        this->next = NULL;
        this->pre = NULL;
        this->key = 0;
        this->value = 0;
    }
};

class LRUCache{
private:
    void moveToTail(KeyValue *node) {
        KeyValue *nodePre = node->pre;
        KeyValue *nodeNext = node->next;
        if(node->next == tail)
            return;
        
        //remove node
        nodePre->next = nodeNext;
        nodeNext->pre = nodePre;
        
        //add node to tail
        addToTail(node);
    }
    
    void addToTail(KeyValue *node)
    {
        KeyValue *tailPre = tail->pre;
        node->pre = tailPre;
        node->next = tail;
        tailPre->next = node;
        tail->pre = node;
        hash[node->key] = node;
    }
    
public:
    //important
    unordered_map<int, KeyValue *> hash;
    KeyValue *head, *tail; //head->next, tail->pre 是为了利用这两个值
    int capacity;
    
    
    LRUCache(int c) {
        capacity = c;
        head = new KeyValue();
        tail = new KeyValue();
        head->next = tail;
        tail->pre = head;
        hash.clear();
    }
    
    
    int get(int key) {
        if(hash.find(key) == hash.end())
            return -1;
        
        KeyValue *v = hash[key];
        moveToTail(v);
        return v->value;
    }
    
    void set(int key, int value) {
        if(get(key) != -1)
        {
            //重设 value 的 值
            hash[key]->value = value;
            return;
        }
        
        //remove - head next
        if(hash.size() == capacity)
        {
            hash.erase(head->next->key);
            head->next = head->next->next;
            head->next->pre = head;
        }
        
        //add new node to - tail
        KeyValue *newNode = new KeyValue(key, value);
        addToTail(newNode);
    }
};

#pragma mark - Largest Rectangle in Histogram
/*
 
 
 Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.
 
 histogram
 
 Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].
 
 histogram
 
 The largest rectangle is shown in the shaded area, which has area = 10 unit.
 
 Have you met this question in a real interview? Yes
 Example
 Given height = [2,1,5,6,2,3],
 return 10.
 
 */

int largestRectangleArea(vector<int> &height) {
    // write your code here
    stack<int> helpS;
    if(height.size() == 0 )
    {
        return 0;
    }
    
    int area = 0;
    height.push_back(-1);
    
    for (int i = 0; i < height.size(); i++) {
        
        int curt = height[i];
        //比较    <  就 pop
        while (!helpS.empty() && curt <= height[helpS.top()]) {
            int h = height[helpS.top()];
            helpS.pop();
            int w = helpS.empty() ? i : i - helpS.top() - 1;
            area = max(area, h * w);
        }
        //存储 index
        helpS.push(i);
    }
    return area;
}

#pragma mark - Top k Largest Numbers II
/*
 
 Implement a data structure, provide two interfaces:
 
 add(number). Add a new number in the data structure.
 topk(). Return the top k largest numbers in this data structure. k is given when we create the data structure.
 Have you met this question in a real interview? Yes
 Example
 s = new Solution(3);
 >> create a new data structure.
 s.add(3)
 s.add(10)
 s.topk()
 >> return [10, 3]
 s.add(1000)
 s.add(-99)
 s.topk()
 >> return [1000, 10, 3]
 s.add(4)
 s.topk()
 >> return [1000, 10, 4]
 s.add(100)
 s.topk()
 >> return [1000, 100, 10]
 
 
 */


bool cmp(const int& a, const int& b) {
    return a > b;
}

class Solution {
private:
    priority_queue<int, vector<int>, greater<int>> queue;
    int k;
    
public:
    Solution(int k) {
        this->k = k;
    }
    
    void add(int num) {
        if (queue.size() < k) {
            queue.push(num);
        } else if (queue.top() < num) {
            queue.pop();
            queue.push(num);
        }
    }
    
    vector<int> topk() {
        vector<int> topk;
        long n = queue.size();
        for (int i = 0; i < k && i < n ; ++i) {
            topk.insert(topk.begin(), queue.top());
            queue.pop();
        }
        
        for (int i = 0; i < n; ++i)
            queue.push(topk[i]);
        
        // sort(topk.begin(), topk.end(), cmp);
        return topk;
    }
    
};


#pragma mark - Heapify

/*

 Given an integer array, heapify it into a min-heap array.
 
 For a heap array A, A[0] is the root of heap, and for each A[i], A[i * 2 + 1] is the left child of A[i] and A[i * 2 + 2] is the right child of A[i].
 Have you met this question in a real interview? Yes
 Clarification
 What is heap?
 
 Heap is a data structure, which usually have three methods: push, pop and top. where "push" add a new element the heap, "pop" delete the minimum/maximum element in the heap, "top" return the minimum/maximum element.
 
 What is heapify?
 Convert an unordered integer array into a heap array. If it is min-heap, for each element A[i], we will get A[i * 2 + 1] >= A[i] and A[i * 2 + 2] >= A[i].
 
 What if there is a lot of solutions?
 Return any of them.
 Example
 Given [3,2,1,4,5], return [1,2,3,4,5] or any legal heap array.
 

 
 
 */

void min_heapify(vector<int> &A, int i, int len){
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int minV = i;
    if( l < len)
        if(A[l] < A[i])
            minV = l;
    
    if( r < len )
        if( A[r] < A[minV])
            minV = r;
    
    if(minV != i) {
        swap(A[i], A[minV]);
        min_heapify(A, minV, len);
    }
}
void heapify(vector<int> &A) {
    // write your code here
    long len = A.size();
    for(int i = len / 2; i >= 0;i--)
        min_heapify(A, i, len);
}


#pragma mark - Test
void DataStructure::test()
{
    //    int re = testInt(4);
}