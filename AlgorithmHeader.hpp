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

class GraphAndSearch
{
    void test();
};


#endif /* GraphAndSearch_hpp */


