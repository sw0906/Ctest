//
//  GraphAndSearch.hpp
//  Ctest
//
//  Created by admin on 9/1/17.
//  Copyright © 2017 admin. All rights reserved.
//

#ifndef GraphAndSearch_hpp
#define GraphAndSearch_hpp

#include <stdio.h>

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <queue>
#include <map>
#include <unordered_set>


using namespace std;


class TreeNode {
public:
    int val;
    TreeNode *left, *right;
    TreeNode(int val) {
        this->val = val;
        this->left = this->right = NULL;
    }
};

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};


struct DirectedGraphNode {
     int label;
     vector<DirectedGraphNode *> neighbors;
     DirectedGraphNode(int x) : label(x) {};
};


class ListNode {
public:
    int val;
    ListNode *next;
    ListNode(int val) {
        this->val = val;
        this->next = NULL;
    }
};


//ArrayAndNumbers
class ArrayAndNumbers
{
    void test();
};

class DataStructure
{
    void test();
};


class GraphAndSearch
{
    void test();
};



class BinaryTreeAndDC
{
public:
    void test();
};

#endif /* GraphAndSearch_hpp */


