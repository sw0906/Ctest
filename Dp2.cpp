//
//  Dp2.cpp
//  Ctest
//
//  Created by admin on 9/1/17.
//  Copyright © 2017 admin. All rights reserved.
//

#include "AlgorithmHeader.hpp"

#pragma mark - Required - Mid

#pragma mark -  Longest Common Substring

/*
 
Given two strings, find the longest common substring.

Return the length of it.

Notice

The characters in substring should occur continuously in original string. This is different with subsequence.

Have you met this question in a real interview? Yes
Example
Given A = "ABCD", B = "CBCE", return 2.

*/

int longestCommonSubstring(string &A, string &B) {
    int la = A.size()+1;
    int lb = B.size()+1;
    
    if(la==1 || lb==1)
        return 0;
    
    //states
    int a[la][lb];
    
    //init
    for(int i=0;i<la;i++)
    {
        a[i][0] = 0;
    }
    for(int i=0; i<lb; i++)
    {
        a[0][i] = 0;
    }
    
    //dp - func
    int maxV = 0;
    for(int i = 1; i<la; i++){
        for(int j=1; j<lb; j++){
            if(A[i-1]==B[j-1])  //增加的条件 +1
            {
                a[i][j] = a[i-1][j-1]+1; //!!!斜角+1
                maxV = max(a[i][j], maxV);
            }
            else
            {
                a[i][j] = 0;//!!! diff with 1
            }
        }
    }
    return maxV;
}


#pragma mark - Longest Common Subsequence

/*
 
Given two strings, find the longest common subsequence (LCS).

Your code should return the length of LCS.

Have you met this question in a real interview? Yes
Clarification
What's the definition of Longest Common Subsequence?

https://en.wikipedia.org/wiki/Longest_common_subsequence_problem
http://baike.baidu.com/view/2020307.htm
Example
For "ABCD" and "EDCA", the LCS is "A" (or "D", "C"), return 1.

For "ABCD" and "EACB", the LCS is "AC", return 2.
 
*/


int longestCommonSubsequence(string A, string B) {
    // write your code here
    int lA = A.size();
    int lB = B.size();
    int a[lA+1][lB+1];
    
    if(lA == 0 && lB == 0)
        return 0;
    
    //init
    for(int i=0; i<=lA+1; i++){
        a[i][0] = 0;
    }
    for(int i=0; i<=lB+1; i++){
        a[0][i] = 0;
    }
    
    for(int i=1; i<=lA; i++){
        int maxV = 0;
        for(int j=1; j<=lB; j++){
            maxV = max(a[i-1][j], a[i][j-1]);
            if(A[i-1] == B[j-1])
            {
                maxV = max(a[i-1][j-1]+1, maxV);
            }
            a[i][j] = maxV;
        }
    }
    return a[lA][lB];
}



#pragma mark - test
void Dp2::test()
{
    
}