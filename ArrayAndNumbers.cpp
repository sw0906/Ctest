//
//  ArrayAndNumbers.cpp
//  Ctest
//
//  Created by admin on 9/1/17.
//  Copyright © 2017 admin. All rights reserved.
//
#include "AlgorithmHeader.hpp"

#pragma mark - Required - easy

#pragma mark -  Intersection of Two Arrays

/*
Given two arrays, write a function to compute their intersection.

Notice

Each element in the result must be unique.
The result can be in any order.
Have you met this question in a real interview? Yes
Example
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].
*/

vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
{
    vector<int> re;
    if( nums1.size()==0  || nums2.size()==0 )
        return re;
    
    unordered_map<int, bool>hash;
    for(int i=0; i<nums1.size(); i++)
    {
        int n = nums1[i];
        if(hash.find(n) == hash.end())
        {
            hash[n] = true;
        }
    }
    
    for(int i=0; i<nums2.size(); i++)
    {
        int n = nums2[i];
        if(hash.find(n) != hash.end() && hash[n] == true)
        {
            re.push_back(n);
            hash[n] = false;
        }
    }
    return re;
}


#pragma mark -  Subarray Sum

/*
Given an integer array, find a subarray where the sum of numbers is zero. Your code should return the index of the first number and the index of the last number.

Notice

There is at least one subarray that it's sum equals to zero.

Have you met this question in a real interview? Yes
Example
Given [-3, 1, 2, -3, 4], return [0, 2] or [1, 3].
 */

vector<int> subarraySum(vector<int> nums){
    unordered_map<int, int>hash;
    vector<int> result;
    
    //算法：hash[sum] = i(order),表示 i后面的到当前循环 sum += 0
    hash[0] = -1; //!!!最难的部分, insert from the  ||first
    int sum = 0;  //!!!
    for(int i=0; i<nums.size(); i++)
    {
        sum += nums[i];
        if(hash.find(sum) != hash.end()) //hash.find(sum) != hash.end()
        {
            result.push_back(hash[sum]+1);
            result.push_back(i);
            return result;
        }
        hash[sum] = i;
    }
    return result;
}


#pragma mark - Merge Sorted Array
/*
Given two sorted integer arrays A and B, merge B into A as one sorted array.

Notice

You may assume that A has enough space (size that is greater or equal to m + n) to hold additional elements from B. The number of elements initialized in A and B are m and n respectively.

Have you met this question in a real interview? Yes
Example
A = [1, 2, 3, empty, empty], B = [4, 5]

After merge, A will be filled as [1, 2, 3, 4, 5]
 */

void mergeSortedArray(int A[], int m, int B[], int n) {
    // move A to end
    if(n == 0)
        return;
    
    int begin = m+n-1;
    int end = begin-(m-1);
    for(int i = begin; i>= end; i--)
    {
        A[i] = A[i-n];
        A[i-n] = INT_MAX;
    }
    
    int a = n;//begin-m+1;
    int b = 0;
    
    for(int i=0; i<m+n; i++)
    {
        if(b == n)
            return;
        
        if(a < m+n)
        {
            if(A[a] > B[b])
            {
                A[i] = B[b];
                b++;
            }
            else
            {
                A[i] = A[a];
                a++;
            }
        }
        else
        {
            A[i] = B[b];
            b++;
        }
        
    }
}


#pragma mark - Maximum Subarray

/*
Given an array of integers, find a contiguous subarray which has the largest sum.

Notice

The subarray should contain at least one number.

Have you met this question in a real interview? Yes
Example
Given the array [−2,2,−3,4,−1,2,1,−5,3], the contiguous subarray [4,−1,2,1] has the largest sum = 6.
 */

int maxSubArray(vector<int> nums) {
    int maxV = nums[0];
    int sum = 0;
    for(int i=0; i<nums.size(); i++)
    {
        if(sum<0)
        {
            sum = 0;
        }
        sum += nums[i];
        maxV = max(maxV, sum);
    }
    return maxV;
}





#pragma mark - Required - mid


#pragma mark -  Two Sum

/*
Given an array of integers, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are NOT zero-based.

Notice

You may assume that each input would have exactly one solution

Have you met this question in a real interview? Yes
Example
numbers=[2, 7, 11, 15], target=9

return [1, 2]


*/

vector<int> twoSum(vector<int> &nums, int target) {
    // write your code here
    long sizeN = nums.size();
    unordered_map<int, int> hash;
    
    int a,b;
    
    vector<int> sum;
    for(int i=0; i<sizeN; i++)
    {
        int number1 = nums[i];
        int number2 = target-number1;
        
        if( hash.find(number2) != hash.end())
        {
            a = hash[number2];
            b = i;
            sum.push_back(a+1);
            sum.push_back(b+1);
            return sum;
        }
        //放在后面，要不然 一样的数值 冲突。
        hash[nums[i]] = i;
    }
    
    return sum;
}



#pragma mark - Two Sum Closest - 前后两指针法
/*
Given an array nums of n integers, find two integers in nums such that the sum is closest to a given number, target.

Return the difference between the sum of the two integers and the target.

Have you met this question in a real interview? Yes
Example
Given array nums = [-1, 2, 1, -4], and target = 4.

The minimum difference is 1. (4 - (2 + 1) = 1).
 */


int twoSumCloset(vector<int>& nums, int target) {
    
    // Write your code here
    sort(nums.begin(), nums.end());
    
    int i=0;
    long j=nums.size()-1;
    
    int gap = INT_MAX;
    while(i<j)
    {
        int iv = nums[i];
        int jv = nums[j];
        int sum = iv+jv;
        int dif = abs(target - sum);
        gap = min(gap, dif);
        
        if(gap == 0)
            return 0;
        
        if(sum > target)
        {
            j--;
        }
        else
        {
            i++;
        }
    }
    return gap;
}


#pragma mark - Subarray Sum Closest

/*
Given an integer array, find a subarray with sum closest to zero. Return the indexes of the first number and last number.

Have you met this question in a real interview? Yes
Example
Given [-3, 1, 1, -3, 5], return [0, 2], [1, 3], [1, 1], [2, 2] or [0, 4].
 */



vector<int> subarraySumClosest(vector<int> nums){
    vector<int> sums;
    unordered_map<int, int> hashMap;
    
    //init
    int sum = 0;
    sums.push_back(0);
    hashMap[0] = -1;
    
    //num
    for(int i=0; i<nums.size(); i++)
    {
        sum += nums[i];
        sums.push_back(sum);
        
        //exit
        if (hashMap.find(sum) != hashMap.end() )
        {
            vector<int> re;
            re.push_back(hashMap[sum]+1);
            re.push_back(i);
            return re;
        }
        
        hashMap[sum] = i;//!!
    }
    
    
    //get closest number
    vector<int> re;
    sort(sums.begin(), sums.end());//!!sort
    int minV = INT_MAX;
    
    for(int i=1; i<sums.size(); i++)
    {
        int gap = sums[i] - sums[i-1];//!! >=0
        if (gap <= minV)
        {
            int v1 = hashMap[sums[i]];
            int v2 = hashMap[sums[i-1]];
            re.clear();
            re.push_back(min(v1,v2)+1);
            re.push_back(max(v1, v2));
        }
        minV = min(minV, gap);
    }
    return re;
}


#pragma mark - Partition Array
/*
Given an array nums of integers and an int k, partition the array (i.e move the elements in "nums") such that:

All elements < k are moved to the left
All elements >= k are moved to the right
Return the partitioning index, i.e the first index i nums[i] >= k.

Notice

You should do really partition in array nums instead of just counting the numbers of integers smaller than k.

If all elements in nums are smaller than k, then return nums.length

Have you met this question in a real interview? Yes
Example
If nums = [3,2,2,1] and k=2, a valid answer is 1.

*/

int partitionArray(vector<int> &nums, int k) {
    if(nums.size()<2)
        return 0;
    
    int i = 0;
    long j = nums.size()-1;
    while(i<j)
    {
        // i <= j
        while(nums[i]<k && i<j)
        {
            i++;
        }
        
        while(nums[j]>=k && i<j )
        {
            j--;
        }
        
        if(i<j)
        {
            swap(nums[i], nums[j]);
            //不要忘记了，很容易忘记
            i++;
            j--;
        }
    }
    return i+1;
}



#pragma mark - Sort Colors - 这道题，出题的人希望你用，两点交换法
/*
 
 后面的0， 跟前面的1 or 2 换
 
 index 2 1 1 1 0 1 0
       换          换
 
 */

/*
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Notice

You are not suppose to use the library's sort function for this problem.
You should do it in-place (sort numbers in the original array).

Have you met this question in a real interview? Yes
Example
Given [1, 0, 1, 2], sort it in-place to [0, 1, 1, 2].
*/


void sortColors(vector<int> &nums) {
    // write your code here
    int count = 0;
    for(int i=0; i<nums.size(); i++)
    {
        count++;
        if(count == nums.size()+1)
            return;
        
        if(nums[i] == 0)
        {
            nums.erase(nums.begin()+i);
            nums.insert(nums.begin(), 0);
        }
        else if(nums[i] == 2)
        {
            nums.erase(nums.begin()+i);
            nums.push_back(2);
            i--;
        }
    }
}



#pragma mark - Required - hard

#pragma mark - Median of two Sorted Arrays

/*
 
There are two sorted arrays A and B of size m and n respectively. Find the median of the two sorted arrays.

Have you met this question in a real interview? Yes
Example
Given A=[1,2,3,4,5,6] and B=[2,3,4,5], the median is 3.5.

Given A=[1,2,3] and B=[4,5], the median is 3.

*/



/**
 * @param A: An integer array.
 * @param B: An integer array.
 * @return: a double whose format is *.5 or *.0
 *
 
 check again
 
 对于一个长度为n的已排序数列a，若n为奇数，中位数为a[n / 2 + 1] ,
 若n为偶数，则中位数(a[n / 2] + a[n / 2 + 1]) / 2
 如果我们可以在两个数列中求出第K小的元素，便可以解决该问题
 不妨设数列A元素个数为n，数列B元素个数为m，各自升序排序，求第k小元素
 取A[k / 2] B[k / 2] 比较，
 如果 A[k / 2] > B[k / 2] 那么，所求的元素必然不在B的前k / 2个元素中(证明反证法)
 反之，必然不在A的前k / 2个元素中，于是我们可以将A或B数列的前k / 2元素删去，求剩下两个数列的
 k - k / 2小元素，于是得到了数据规模变小的同类问题，递归解决
 如果 k / 2 大于某数列个数，所求元素必然不在另一数列的前k / 2个元素中，同上操作就好。
 */

double findKth(vector<int>& A, vector<int>& B, int A_st, int B_st, int k) {
    // 边界情况，任一数列为空
    if (A_st >= A.size()) {
        return B[B_st + k - 1];
    }
    if (B_st >= B.size()) {
        return A[A_st + k - 1];
    }
    // k等于1时表示取最小值，直接返回min
    if (k == 1) return min(A[A_st], B[B_st]);
    int A_key = A_st + k / 2 - 1 >= A.size() ? INT_MAX : A[A_st + k / 2 - 1];
    int B_key = B_st + k / 2 - 1 >= B.size() ? INT_MAX : B[B_st + k / 2 - 1];
    if (A_key < B_key){
        return findKth(A, B, A_st + k / 2, B_st, k - k / 2);//!!
    } else {
        return findKth(A, B, A_st, B_st + k / 2, k - k / 2);
    }
    
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int sum = nums1.size() + nums2.size();
    double ret;
    
    if (sum & 1) {
        ret = findKth(nums1, nums2, 0, 0, sum / 2 + 1);
    } else {
        ret = ((findKth(nums1, nums2, 0, 0, sum / 2)) +
               findKth(nums1, nums2, 0, 0, sum / 2 + 1)) / 2.0;
    }
    return ret;
}




#pragma mark - Optional - easy

#pragma mark -  Minimum Subarray
/*

Given an array of integers, find the subarray with smallest sum.

Return the sum of the subarray.

Notice

The subarray should contain one integer at least.

Have you met this question in a real interview? Yes
Example
For [1, -1, -2, 1], return -3.
 
 */


int minSubArray(vector<int> nums) {
    int minV = nums[0];
    int sum = 0;
    for(int i=0; i<nums.size(); i++)
    {
        sum += nums[i];
        minV = min(minV, sum);
        sum = min(sum, 0);//!!!去掉正数部分
    }
    return minV;
}

#pragma mark - Merge Two Sorted Arrays - 头指针法
/*
 
Merge two given sorted integer array A and B into a new sorted integer array.

Have you met this question in a real interview? Yes
Example
A=[1,2,3,4]

B=[2,4,5,6]

return [1,2,2,3,4,4,5,6]
 
 */


vector<int> mergeSortedArray(vector<int> &A, vector<int> &B) {
    // exit
    long sA = A.size();
    long sB = B.size();
    if(!sA)
        return B;
    if(!sB)
        return A;
    
    vector<int> c;
    int iA = 0;
    int iB = 0;
    
    //merge
    while(iA<sA && iB<sB)
    {
        if(A[iA]<B[iB])
        {
            c.push_back(A[iA]);
            iA++;
        }
        else
        {
            c.push_back(B[iB]);
            iB++;
        }
    }
    
    //add rest
    while(iA < sA)
    {
        c.push_back(A[iA]);
        iA++;
    }
    
    //add rest
    while( iB < sB )
    {
        c.push_back(B[iB]);
        iB++;
    }
    return c;
}



#pragma mark - Optional - mid

#pragma mark - Best Time to Buy and Sell Stock

/*
 
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Have you met this question in a real interview? Yes
Example
Given array [3,2,3,1,2], return 1.
*/

int maxProfit(vector<int> &prices) {
    if(prices.size()<2)
        return 0;
    
    int minV = INT_MAX;
    int result = 0;
    for(int i=0; i<prices.size(); i++)
    {
        int diff = prices[i] - minV;
        result = max(result, diff);
        minV = min(minV, prices[i]);
    }
    
    
    return result;
}


#pragma mark - Best Time to Buy and Sell Stock II

/*
 
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

Have you met this question in a real interview? Yes
Example
Given an example [2,1,2,0,1], return 2

*/

int maxProfit2(vector<int> &prices){
    int total = 0;
    for(int i=1; i<prices.size(); i++)
    {
        if(prices[i] > prices[i-1])//所有所有情况
        {
            int diff = prices[i] - prices[i-1];
            total += diff;
        }
    }
    return total;
}


#pragma mark - Best Time to Buy and Sell Stock III
/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Notice

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

Have you met this question in a real interview? Yes
Example
Given an example [4,4,6,1,1,4,2,5], return 6.
 
 */

//左右计算法 -- 从左往右， 从右边往左
int maxProfit3(vector<int> &prices) {
    if (prices.size() == 0) {
        return 0;
    }
    
    vector<int> profit(prices.size());
    int buy = 0;
    buy = prices[0];
    profit[0] = 0;//important
    for (int i = 1; i < prices.size(); i++) {
        profit[i] = max(profit[i - 1], prices[i] - buy);
        buy = min(buy, prices[i]);
    }
    
    int sell = prices[prices.size() - 1];
    int best = 0;
    for (long i = prices.size() - 2; i >= 0; i--) {
        best = max(best, sell - prices[i] + profit[i-1]);
        sell = max(sell, prices[i]);
    }
    
    return best;
}


#pragma mark - 3Sum - 前后指针法，解决2个sum
/*
 
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Notice

Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)

The solution set must not contain duplicate triplets.

Have you met this question in a real interview? Yes
Example
For example, given array S = {-1 0 1 2 -1 -4}, A solution set is:

(-1, 0, 1)
(-1, -1, 2)

*/


//不能用hash，比如说【-4，2，2】，用hash的话，就少了一个2，因为不要重复的值
vector<vector<int> > threeSum(vector<int> &nums) {
    // write your code here
    vector<vector<int>> re;
    vector<int> tmp;
    
    if(nums.size()<3)
        return re;
    
    sort(nums.begin(), nums.end());
    
    for(int i=0; i<nums.size()-2; i++)
    {
        //erase 前面 重复
        while (nums[i] == nums[i-1]) {
            i++;
        }
        int sum = 0-nums[i];
        int x = i+1;
        long y = nums.size()-1;
        while(x<y)
        {
            int xySum = nums[x] + nums[y];
            if(xySum == sum)
            {
                tmp.clear();
                tmp.push_back(nums[i]);
                tmp.push_back(nums[x]);
                tmp.push_back(nums[y]);
                x++;
                y--;
                //erase 后面重复
                if(!re.size() || re.back() != tmp)
                {
                    re.push_back(tmp);
                }
                
            }
            else if(xySum > sum)
            {
                y--;
            }
            else
            {
                x++;
            }
        }
        
    }
    return re;
}


#pragma mark -  Sort Letters by Case  - 头尾指针法 - 题目解法不够好
/*
 
Given a string which contains only letters. Sort it by lower case first and upper case second.

Notice

It's NOT necessary to keep the original order of lower-case letters and upper case letters.

Have you met this question in a real interview? Yes
Example
For "abAcD", a reasonable answer is "acbAD"

*/

void sortLetters(string &letters) {
    // write your code
    unsigned long length = letters.length();
    if(length <= 1)
    {
        return;
    }
    
    unsigned long loopCount = length;
    for(int i=0; i<loopCount; i++)
    {
        int gap = letters[i]- 'A';
        char tempChar;
        if(gap < 26 )
        {
            tempChar = letters[i];
            //cout <<  "erasing" << "~~~"<< endl;
            letters.erase(i,1);
            loopCount--;
            i--;
            letters.push_back(tempChar);
        }
        
    }
}


#pragma mark - Test
void ArrayAndNumbers::test()
{
    //    int re = testInt(4);
}