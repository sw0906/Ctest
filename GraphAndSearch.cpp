//
//  GraphAndSearch.cpp
//  Ctest
//
//  Created by admin on 9/1/17.
//  Copyright © 2017 admin. All rights reserved.
//

#include "AlgorithmHeader.hpp"



int testInt(int good)
{
    return good+1;
}


#pragma mark -  Six Degrees
//Six degrees of separation is the theory that everyone and everything is six or fewer steps away, by way of introduction, from any other person in the world, so that a chain of "a friend of a friend" statements can be made to connect any two people in a maximum of six steps.
//
//Given a friendship relations, find the degrees of two people, return -1 if they can not been connected by friends of friends.
//
//Example
//Gien a graph:
//
//1------2-----4
//\          /
//\        /
//\--3--/
//{1,2,3#2,1,4#3,1,4#4,2,3} and s = 1, t = 4 return 2
//
//Gien a graph:
//
//1      2-----4
///
///
//3
//{1#2,4#3,4#4,2,3} and s = 1, t = 4 return -1
int sixDegrees(vector<UndirectedGraphNode*> graph,
               UndirectedGraphNode* s,
               UndirectedGraphNode* t) {
    //edge
    if(s == t)
        return 0;
    
    if(!s->neighbors.size() || !t->neighbors.size())
        return -1;
    
    //dp recored - height , not using bool
    unordered_map<int, int> hash;
    queue<UndirectedGraphNode*> q;
    
    
    //init
    hash[s->label] = 0;
    q.push(s);
    
    
    //main
    while(q.size())
    {
        UndirectedGraphNode *n = q.front();
        q.pop();
        for(int i=0; i< n->neighbors.size();i++)
        {
            UndirectedGraphNode *tmp = n->neighbors[i];
            
            if(hash.find(tmp->label) == hash.end())
            {
                hash[tmp->label] = hash[n->label]+1;
                q.push(tmp);
            }
            
            if(tmp == t)
            {
                return hash[t->label];
            }
            
            
        }
    }
    return -1;
}




#pragma mark - Topological Sorting

//Given an directed graph, a topological order of the graph nodes is defined as follow:
//
//For each directed edge A -> B in graph, A must before B in the order list.
//The first node in the order can be any node in the graph with no nodes direct to it.
//Find any topological order for the given graph.
//
//Notice
//
//You can assume that there is at least one topological order in the graph.
//
//Have you met this question in a real interview? Yes
//Clarification
//Learn more about representation of graphs
//
//Example
//For graph as follow:
//
//picture
//
//The topological order can be:
//
//[0, 1, 2, 3, 4, 5]
//[0, 2, 3, 1, 5, 4]
//...

// /  1  \
//0 - 2 - 4
// \  3 /_ 5  , 2-5

vector<DirectedGraphNode*> topSort(vector<DirectedGraphNode*> graph) {
    map<DirectedGraphNode*, int> hash; //!! count -- int
    vector<DirectedGraphNode*> re;
    queue<DirectedGraphNode *> q;
    
    //！！不能遍历节点本身，所有子节点
    for(int i=0; i<graph.size(); i++)
    {
        DirectedGraphNode *node = graph[i];
        for(int j=0; j<node->neighbors.size(); j++)
        {
            DirectedGraphNode *ne = node->neighbors[j];
            if(hash.find(ne) != hash.end())
            {
                hash[ne] += 1;
            }else
            {
                hash[ne] = 1;
            }
        }
    }
    
    //找到根节点
    for(int i=0; i<graph.size(); i++)
    {
        DirectedGraphNode *n = graph[i];
        if(hash.find(n) == hash.end())
        {
            q.push(n);
            re.push_back(n);//!!root - 只有一个
        }
    }
    
    //pop - hash[x] = 0;
    while(q.size())
    {
        DirectedGraphNode *node = q.front();
        q.pop();
        for(int j=0; j<node->neighbors.size(); j++)//!! not root
        {
            DirectedGraphNode *ne = node->neighbors[j];
            hash[ne] -= 1;
            if(hash[ne] == 0)
            {
                re.push_back(ne);
                q.push(ne);
            }
        }
    }
    return re;
}

#pragma mark -  Find the Connected Component in the Undirected Graph
//Find the number connected component in the undirected graph. Each node in the graph contains a label and a list of its neighbors. (a connected component (or just component) of an undirected graph is a subgraph in which any two vertices are connected to each other by paths, and which is connected to no additional vertices in the supergraph.)
//
//Notice
//
//Each connected component should sort by label.
//
//Have you met this question in a real interview? Yes
//Clarification
//Learn more about representation of graphs
//
//Example
//Given graph:
//
//A------B  C
//\     |  |
//\    |  |
//\   |  |
//\  |  |
//D   E
//Return {A,B,D}, {C,E}. Since there are two connected component which is {A,B,D}, {C,E}

//hash + queue(while)  = bfs
vector<vector<int>> connectedSet(vector<UndirectedGraphNode*>& nodes) {
    vector<vector<int>> re;
    unordered_map<int, bool> hash;
    
    
    for(int i=0; i<nodes.size(); i++)
    {
        //exit
        UndirectedGraphNode *n = nodes[i];
        if(hash.find(n->label) != hash.end())
            continue;
        
        // init
        vector<int> sub;
        queue<UndirectedGraphNode *>q;
        
        q.push(n);
        hash[n->label] = true;
        sub.push_back(n->label);
        
        while(q.size())
        {
            UndirectedGraphNode *qNode = q.front();
            q.pop();
            long size = qNode->neighbors.size();
            
            //neighors
            for(int i=0; i<size; i++)
            {
                //exit
                UndirectedGraphNode *tmp = qNode->neighbors[i];
                if(hash.find(tmp->label)!= hash.end())
                    continue;
                
                sub.push_back(tmp->label);
                q.push(tmp);
                hash[tmp->label] = true;
                
            }
        }
        sort(sub.begin(), sub.end());
        re.push_back(sub);
    }
    return re;
}



#pragma mark -  Clone Graph
//Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.
//
//How we serialize an undirected graph:
//
//Nodes are labeled uniquely.
//
//We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
//
//As an example, consider the serialized graph {0,1,2#1,2#2,2}.
//
//The graph has a total of three nodes, and therefore contains three parts as separated by #.
//
//First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
//Second node is labeled as 1. Connect node 1 to node 2.
//Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
//Visually, the graph looks like the following:
//
//1
/// \
///   \
//0 --- 2
/// \
//\_/


UndirectedGraphNode *clone(UndirectedGraphNode *node, map<int, UndirectedGraphNode*> &hashMap)
{
    if(node == NULL)
        return NULL;
    
    if(hashMap.find(node->label) != hashMap.end())
        return hashMap[node->label];
    
    UndirectedGraphNode *newnode = new UndirectedGraphNode(node->label);
    hashMap[newnode->label] = newnode;
    
    for(int i=0;i<node->neighbors.size();i++)
    {
        UndirectedGraphNode *nodeN = node->neighbors[i];
        UndirectedGraphNode *tempNode = clone(nodeN, hashMap);
        newnode->neighbors.push_back(tempNode);
    }
    return newnode;
}

UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    map<int, UndirectedGraphNode*>hashMap;
    return clone(node, hashMap);
}


#pragma mark - Combination Sum
//Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
//
//The same repeated number may be chosen from C unlimited number of times.
//
//
//
//For example, given candidate set 2,3,6,7 and target 7,
//A solution set is:
//[7]
//[2, 2, 3]
//
//Notice
//
//All numbers (including target) will be positive integers.
//Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
//The solution set must not contain duplicate combinations.
//Have you met this question in a real interview? Yes
//Example
//given candidate set 2,3,6,7 and target 7,
//A solution set is:
//[7]
//[2, 2, 3]

void helperS(vector<int> &candidates, int target,
             int startIndex, vector<int> &sub, vector<vector<int> > &re)
{
    if(target == 0)
    {
        re.push_back(sub);
        return;
    }
    
    //从小到大
    for (int i = startIndex; i<candidates.size(); i++) {
        if (target < candidates[i]) //sort 以后，小的不可能，大的就更加不可能了
            break;//!!
        
        //去掉重复的 [1,2,2]
        if(i>0 && candidates[i] == candidates[i-1])
            continue;//!!
        
        
        int diff = target - candidates[i];
        sub.push_back(candidates[i]);
        helperS(candidates, diff, i, sub, re);//控制顺序
        sub.pop_back();
    }
    
}

//不需要用 hash，可重复
vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
    vector<vector<int> > re;
    vector<int> sub;
    
    //exit
    sort(candidates.begin(), candidates.end());
    
    int i = 0;
    helperS(candidates, target, i, sub, re);
    return re;
}



#pragma mark - Palindrome Partitioning
//Given a string s, partition s such that every substring of the partition is a palindrome.
//
//Return all possible palindrome partitioning of s.
//
//Have you met this question in a real interview? Yes
//Example
//Given s = "aab", return:
//
//[
// ["aa","b"],
// ["a","a","b"]
// ]

bool isPali(string s, int start, int end,
            vector<vector<int>> &a)
{
    //exit  - find
    if(a[start][end] != -1)
        return a[start][end];
    
    //exit - same
    if(start == end)
    {
        a[start][end] = 1;
        return true;
    }
    
    //main
    while(start < end)
    {
        if(s[start] == s[end])
        {
            start++;
            end--;
        }
        else
        {
            a[start][end] = false;
            return false;
        }
    }
    a[start][end] = true;
    return true;
}

void helperPali(vector<vector<string>> &re, vector<string> &sub,
                string s, int start, vector<vector<int>> &a)
{
    //exit
    if(start == s.size())
    {
        re.push_back(sub);
        return;
    }
    
    //order can't change
    for(int i = start+1; i<=s.size(); i++)//i-1 get last object
    {
        if(!isPali(s,start, i-1, a))
            continue;
        
        int subL = i - start;
        string subS = s.substr(start,subL);
        
        sub.push_back(subS);
        helperPali(re, sub, s, i, a);
        sub.pop_back();
        
    }
}
vector<vector<string>> partition(string s) {
    //exit
    vector<vector<string>> re;
    vector<string> sub;
    if(s.size() == 0 )
        return re;
    
    
    long length = s.size();
    
    //init
    vector<vector<int>> hash(length,vector<int>(length, -1));
    
    //main
    helperPali(re, sub, s, 0, hash);
    return re;
}



#pragma mark - N-Queens II
//Description
//Notes
//Testcase
//Judge
//Follow up for N-Queens problem.
//
//Now, instead outputting board configurations, return the total number of distinct solutions.
//
//Have you met this question in a real interview? Yes
//Example
//For n=4, there are 2 distinct solutions.
int sum;
bool canPut(int col, vector<int> &cols) {
    long row = cols.size();
    for (int i = 0; i < row; i++) {
        if (cols[i] - i == col - row) {
            return false;
        }
        if (cols[i] + i == col + row) {
            return false;
        }
        if (cols[i] == col) {
            return false;
        }
    }
    return true;
}

void dfsNQ(int n,  vector<int> &cols) {
    if (cols.size() == n) {
        sum++;
        return;
    }
    
    for (int i = 0; i < n; i++) {
        if (!canPut(i, cols)) {
            continue;
        }
        
        cols.push_back(i);
        dfsNQ(n, cols);
        cols.pop_back();
    }
}

int totalNQueens(int n) {
    vector<int> cols;
    
    sum = 0;
    dfsNQ(n, cols);
    return sum;
}

#pragma mark - Subsets

//Given a set of distinct integers, return all possible subsets.
//
//Notice
//
//Elements in a subset must be in non-descending order.
//The solution set must not contain duplicate subsets.
//Have you met this question in a real interview? Yes
//Example
//If S = [1,2,3], a solution is:
//
//[
// [3],
// [1],
// [2],
// [1,2,3],
// [1,3],
// [2,3],
// [1,2],
// []
// ]


void helperSubset(vector<vector<int> > &results, vector<int> subset, vector<int> &nums, int start)
{
    results.push_back(subset);
    for(int i=start; i<nums.size(); i++)
    {
        subset.push_back(nums[i]);
        helperSubset(results, subset, nums, i+1);
        subset.pop_back();
    }
}

vector<vector<int> > subsets(vector<int> &nums) {
    // write your code here
    vector<vector<int> > sets;
    vector<int> set;
    
    helperSubset(sets, set, nums, 0);
    return sets;
}



#pragma mark - Subsets II

//Given a list of numbers that may has duplicate numbers, return all possible subsets
//
//Notice
//
//Each element in a subset must be in non-descending order.
//The ordering between two subsets is free.
//The solution set must not contain duplicate subsets.
//Example
//If S = [1,2,2], a solution is:
//
//[
// [2],
// [1],
// [1,2,2],
// [2,2],
// [1,2],
// []
// ]


void helperSub(vector<vector<int> > &results, vector<int> &subset,
               const vector<int> &nums, int start, vector<bool> &hash)
{
    results.push_back(subset);
    for(int i=start; i<nums.size(); i++)
    {
        //ignore duplicate,只保留第一种情况 - eg, 1,2(1),2(2) / 1, 2(2), 2(1) -- 1,2(1),2(2)
        if(i>0 && nums[i-1] == nums[i] && hash[i-1] == false)
        {
            continue;
        }
        
        hash[i] = true;
        subset.push_back(nums[i]);
        
        helperSub(results, subset, nums, i+1, hash);
        
        hash[i] = false;
        subset.pop_back();
    }
    
}

//hash solution 2
vector<vector<int> > subsetsWithDup( vector<int> &num) {
    // write your code here
    vector<vector<int> > sets;
    vector<int> set;
    vector<bool> isVisited(num.size(), false);//记录当前数， 有没有使用过
    
    
    //要注意先sort
    sort(num.begin(), num.end());
    
    helperSub(sets, set, num, 0, isVisited);
    
    return sets;
}


#pragma mark - Permutations

//Given a list of numbers, return all possible permutations.
//
//Notice
//
//You can assume that there is no duplicate numbers in the list.
//
//Have you met this question in a real interview? Yes
//Example
//For nums = [1,2,3], the permutations are:
//
//[
// [1,2,3],
// [1,3,2],
// [2,1,3],
// [2,3,1],
// [3,1,2],
// [3,2,1]
// ]

void helperP1(vector<vector<int> > &result,vector<int> sub, vector<int> nums, unordered_map<int, bool> &hashSub)
{
    //跟 subsets 的区别
    if(sub.size() == nums.size())
    {
        result.push_back(sub);
        return;//!!! return 一般用在退出循环的地方
    }
    
    for(int i=0; i<nums.size(); i++)
    {
        int num = nums[i];
        if(hashSub[num])
        {
            continue;//!!!important, 如果存在，就下一个数,不能用return
        }
        
        sub.push_back(num);
        hashSub[num] = true;
        
        helperP1(result, sub, nums, hashSub);
        
        //important
        sub.pop_back();
        hashSub[num] = false;
    }
}

vector<vector<int> > permute(vector<int> nums) {
    // write your code here
    vector<vector<int>> result;
    vector<int> sublist;
    unordered_map<int, bool> hashSub;
    
    helperP1(result, sublist, nums, hashSub);
    return result;
}




#pragma mark - Permutations II

//Given a list of numbers with duplicate number in it. Find all unique permutations.
//
//Have you met this question in a real interview? Yes
//Example
//For numbers [1,2,2] the unique permutations are:
//
//[
// [1,2,2],
// [2,1,2],
// [2,2,1]
// ]


void helperP(vector<vector<int> > &result,vector<int> sub,
             vector<int> nums, unordered_map<int, bool> &hashSub)
{
    if(sub.size() == nums.size())
    {
        result.push_back(sub);
        return;
    }
    
    for(int i=0; i<nums.size(); i++)
    {
        int num = nums[i];
        
        //这部分太难了。。。。。。
        if (hashSub[i]) {
            continue;
        }
        if (i > 0 && hashSub[i - 1] == false && nums[i] == nums[i-1]) {
            continue;
        }
        
        sub.push_back(num);
        hashSub[i] = true;
        
        helperP(result, sub, nums, hashSub);
        
        //important
        sub.pop_back();
        hashSub[i] = false;
    }
}


vector<vector<int> > permuteUnique(vector<int> &nums) {
    // write your code here
    vector<vector<int>> result;
    vector<int> sublist;
    unordered_map<int, bool> hashSub;
    
    //必须要sort，才对
    sort(nums.begin(), nums.end());
    helperP(result, sublist, nums, hashSub);
    return result;
}



#pragma mark - String Permutation II
//Given a string, find all permutations of it without duplicates.
//
//Have you met this question in a real interview? Yes
//Example
//Given "abb", return ["abb", "bab", "bba"].
//
//Given "aabb", return ["aabb", "abab", "baba", "bbaa", "abba", "baab"].
void helperSP(vector<string> &re, string& str,  string sub,
             unordered_map<int, bool> &hash)
{
    //exit
    if(sub.size()  == str.size())
    {
        re.push_back(sub);
        return;
    }
    
    
    for(int i=0; i<str.size(); i++)//0 顺序可变
    {
        // igonore
        if(hash[i])
            continue;
        
        if (i > 0 && hash[i - 1] == false && str[i] == str[i-1]) //check重复的
            continue;
        
        sub += + str[i];
        hash[i] = true;
        
        helperSP(re, str, sub, hash);
        
        sub.erase(sub.end()-1);
        hash[i] = false;
    }
}




vector<string> stringPermutation2(string& str) {
    //不可以重复取值
    unordered_map<int, bool> hash;
    
    vector<string> re;
    long length = str.size();
    
    //exit
    if(length <= 1)
    {
        re.push_back(str);
        return re;
    }
    
    sort(str.begin(), str.end());
    
    string s;
    helperSP(re, str, s, hash);
    return re;
}




#pragma mark - Word Ladder
//
//Given two words (start and end), and a dictionary, find the length of shortest transformation sequence from start to end, such that:
//
//Only one letter can be changed at a time
//Each intermediate word must exist in the dictionary
//Notice
//
//Return 0 if there is no such transformation sequence.
//All words have the same length.
//All words contain only lowercase alphabetic characters.
//Have you met this question in a real interview? Yes
//Example
//Given:
//start = "hit"
//end = "cog"
//dict = ["hot","dot","dog","lot","log"]
//As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
//return its length 5.


// s-1
int ladderLength1(string start, string end, unordered_set<string> &dict) {
    if (start == end) {
        return 1;
    }
    long n = start.size();
    if (n < 1 || n != end.size()) {
        return 0;
    }
    
    queue<string> Q;
    Q.push(start);
    dict.erase(start);
    int length = 2;
    
    while (!Q.empty()) {
        long size = Q.size();
        for (int i = 0; i < size; i++) {
            string word = Q.front(); Q.pop();
            for (int i = 0; i < n; i++) {
                
                //关键，控制只修改一次， 比起number统计要好的多
                char oldChar = word[i];
                
                
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == oldChar)
                        continue;
                    
                    word[i] = c;
                    
                    if (word == end) {
                        return length;
                    }
                    
                    if (dict.find(word) != dict.end()) {
                        Q.push(word);
                        dict.erase(word);
                    }
                }
                
                //关键，控制只修改一次
                word[i] = oldChar;
            }
        } // for size
        length++;
    }
    return 0;
}



// s-2
int bfsWord(unordered_set<string> &dict,
            string start, string end)
{
    map<string, int> hash;
    queue<string> q;
    q.push(start);
    dict.erase(start);
    hash[start] = 1;
    int count = 2;
    while(q.size())
    {
        long sizeQ = q.size();
        for(int i=0; i<sizeQ; i++)
        {
            string s = q.front();
            q.pop();
            for(int i=0; i<s.size(); i++)
            {
                char tmp = s[i];
                for(char c = 'a'; c<='z'; c++)
                {
                    if (c == tmp)
                        continue;
                    
                    s[i] = c;
                    
                    if(s == end)
                    {
                        //hash[end] == count;
                        return count;
                    }
                    
                    if (dict.find(s) != dict.end())
                    {
                        hash[s] = count;
                        q.push(s);
                        dict.erase(s);
                    }
                    
                }
                s[i] = tmp;
            }
            
        }
        count++;
    }
    return count;
}

int ladderLength(string start, string end, unordered_set<string> &dict) {
    if (start == end) {
        return 1;
    }
    long n = start.size();
    if (n < 1 || n != end.size()) {
        return 0;
    }
    
    return bfsWord(dict, start, end);
}


#pragma mark - Word Ladder II
//Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start to end, such that:
//
//Only one letter can be changed at a time
//Each intermediate word must exist in the dictionary
//Notice
//
//All words have the same length.
//All words contain only lowercase alphabetic characters.
//Have you met this question in a real interview? Yes
//Example
//Given:
//start = "hit"
//end = "cog"
//dict = ["hot","dot","dog","lot","log"]
//Return
//[
// ["hit","hot","dot","dog","cog"],
// ["hit","hot","lot","log","cog"]
// ]

vector<string> expandWord(string crt, unordered_set<string> &dict) {
    vector<string> expansion;
    for (int i = 0; i < crt.length(); i++) {
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (ch != crt[i]) {
                string expanded = crt.substr(0, i) + ch
                + crt.substr(i + 1);
                if (dict.find(expanded) != dict.end()) {
                    expansion.push_back(expanded);
                }
            }
        }
    }
    return expansion;
}

void bfsWord2(map<string, vector<string>> &mapS, map<string, int> &distance,
         string start, string end,  unordered_set<string> &dict) {
    queue<string> q;;
    q.push(start);
    distance[start] = 0;
    for (auto i= dict.begin(); i !=  dict.end(); i++) {
        string s = *i;
        vector<string> vectorS;
        mapS[s] = vectorS;
    }
    
    while (q.size()) {
        string crt = q.front();
        q.pop();
        vector<string> nextList = expandWord(crt, dict);
        for (int i=0; i<nextList.size(); i++) {
            string next = nextList[i];
            mapS[crt].push_back(next);
            if (distance.find(next) == distance.end()) {
                distance[next] = distance[crt] + 1;
                q.push(next);
            }
        }
    }
}




void dfsWord2(vector<vector<string>> &re, vector<string> path, string crt,
         string end, map<string, int> &distance,
         map<string, vector<string>> &mapS) {
    path.push_back(crt);
    if (crt == end) {
        re.push_back(path);
    } else {
        vector<string> stringS = mapS[crt];
        for(int i=0; i< stringS.size(); i++)
        {
            string next = stringS[i];
            if (distance.find(crt)!= distance.end() && distance[crt] == distance[next] - 1)
            {
                dfsWord2(re, path, next, end, distance, mapS);
            }
        }
    }
    path.pop_back();
}


vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
    vector<vector<string>> re;
    vector<string> sub;
    map<string, vector<string>> hash;
    map<string, int> height;
    
    if(start == end)
    {
        sub.push_back(start);
        re.push_back(sub);
    }
    
    if(start.length() != end.length() || !start.size())
        return re;
    
    
    dict.insert(start);
    dict.insert(end);
    bfsWord2(hash, height, start, end, dict);
    dfsWord2( re, sub,  start, end, height, hash);
    return re;
}


#pragma mark - k Sum II

//Given n unique integers, number k (1<=k<=n) and target.
//
//Find all possible k integers where their sum is target.
//
//Have you met this question in a real interview? Yes
//Example
//Given [1,2,3,4], k = 2, target = 5. Return:
//
//[
// [1,4],
// [2,3]
// ]

void helperSum(vector<vector<int> > &re, vector<int> &sub,
            vector<int> &A, int sum, int target, int index, int k)
{
    //exit
    if(sum == target && sub.size() == k)
    {
        re.push_back(sub);
        return;
    }
    
    for(int i= index; i< A.size(); i++)
    {
        int number = A[i] + sum;
        if(number > target)
            return;
        
        sub.push_back(A[i]);
        helperSum(re, sub, A, number, target, i+1, k);//i+1
        sub.pop_back();
    }
}

vector<vector<int> > kSumII(vector<int> A, int k, int target) {
    // write your code here
    sort(A.begin(), A.end());
    vector<vector<int> > re;
    vector<int> sub;
    
    helperSum(re, sub, A, 0, target, 0,  k);
    return re;
}

#pragma mark -  N-Queens

//The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.
//
//Given an integer n, return all distinct solutions to the n-queens puzzle.
//
//Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.
//
//Have you met this question in a real interview? Yes
//Example
//There exist two distinct solutions to the 4-queens puzzle:
//
//[
// // Solution 1
// [".Q..",
//  "...Q",
//  "Q...",
//  "..Q."
//  ],
// // Solution 2
// ["..Q.",
//  "Q...",
//  "...Q",
//  ".Q.."
//  ]
// ]



string intToString(long num, long size)
{
    string s;
    for(int i=0; i<size; i++)
    {
        if(num == i)
        {
            s += "Q";
        }
        else
        {
            s += ".";
        }
    }
    return s;
}

vector<string> intVToStringV(vector<int> &v)
{
    vector<string> re;
    for(int i=0; i<v.size(); i++)
    {
        re.push_back(intToString(v[i], v.size()));
    }
    return re;
}

bool isValidQueen(vector<int> nums, int col,
                  unordered_map<int, bool> &hashSub)
{
    if(hashSub[col])
        return false;
    
    long size = nums.size();
    for(int i=0; i<size; i++)
    {
        if(nums[i]+i == size + col)//top right - left
        {
            return false;
        }
        
        if(nums[i]-i == col - size)//top left - right
        {
            return false;
        }
    }
    return true;
}


void helperQueen(vector<int> sub,
                 int n,
                 unordered_map<int, bool> &hashSub,
                 vector<vector<string> > &resultS)
{
    //exit
    if(sub.size() == n )
    {
        vector<string> re;
        re = intVToStringV(sub);
        resultS.push_back(re);
        return;
    }
    
    //main
    for(int i=0; i< n; i++)
    {
        //exit
        if(!isValidQueen(sub, i, hashSub))
            continue;
        
        //important
        sub.push_back(i);
        hashSub[i] = true;
        
        helperQueen( sub,n, hashSub, resultS);
        
        sub.pop_back();
        hashSub[i] = false;
        
    }
}

vector<vector<string> > solveNQueens(int n) {
    // write your code here
    vector<int> sublist;
    unordered_map<int, bool> hashSub;
    vector<int> nums;
    
    vector<vector<string>>  resultS;
    if(n==0 || n==2 || n==3)
    {
        // resultS.push_back(vector<string>());
        return resultS;
    }
    
    
    helperQueen(sublist, n, hashSub,resultS);
    return resultS;
}




#pragma mark - test

void GraphAndSearch::test()
{
    int re = testInt(4);
}




