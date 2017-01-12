//
//  BinaryTreeAndDC.cpp
//  Ctest
//
//  Created by admin on 9/1/17.
//  Copyright © 2017 admin. All rights reserved.
//

#include "AlgorithmHeader.hpp"






#pragma mark - Binary Tree Path Sum

/*
Given a binary tree, find all paths that sum of the nodes in the path equals to a given number target.

A valid path is from root node to any of the leaf nodes.

Have you met this question in a real interview? Yes
Example
Given a binary tree, and target = 5:

1
/ \
2   4
/ \
2   3
return

[
 [1, 2, 2],
 [1, 4]
 ]

*/




TreeNode *getTree()
{
    TreeNode *root = new TreeNode(1);
    TreeNode *l = new TreeNode(1);
    TreeNode *r = new TreeNode(1);
    TreeNode *ll = new TreeNode(3);
    TreeNode *lr = new TreeNode(4);
    TreeNode *rl = new TreeNode(4);
    TreeNode *rr = new TreeNode(3);
    root->left = l;
    root->right = r;
    l->left = ll;
    l->right = lr;
    r->left = rl;
    r->right = rr;
    return root;
}


int getTotal(vector<int> &sub)
{
    int total = 0;
    for(int i=0; i<sub.size(); i++)
    {
        total += sub[i];
    }
    return total;
}
void binaryTreePathSum(TreeNode *root, int target, vector<vector<int>> &re, vector<int> sub)
{
    if(!root)
        return;
    
    sub.push_back(root->val);
    int curV = getTotal(sub);
    if(  curV >= target)
    {
        if(curV == target)
        {
            re.push_back(sub);
        }
        return;
    }
    
    binaryTreePathSum(root->left, target, re, sub);
    binaryTreePathSum(root->right, target, re, sub);
}



vector<vector<int>> binaryTreePathSum(TreeNode *root, int target) {
    vector<vector<int>> re = vector<vector<int>>();
    vector<int> sub = vector<int>();
    if(!root)
        return re;
    binaryTreePathSum(root, target, re, sub);
    return re;
}


void testPathSum()
{
    TreeNode *root = getTree();
    vector<vector<int>> re = binaryTreePathSum(root, 6);
    
}

#pragma mark - test
void BinaryTreeAndDC::test()
{
    testPathSum();
}

