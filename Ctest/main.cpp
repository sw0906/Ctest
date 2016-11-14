//
//  main.cpp
//  Ctest
//
//  Created by admin on 28/9/16.
//  Copyright © 2016 admin. All rights reserved.
//

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <queue>
#include <map>
#include <unordered_set>
using namespace::std;
struct DirectedGraphNode {
    int label;
    vector<DirectedGraphNode *> neighbors;
    DirectedGraphNode(int x) : label(x) {};
};


//vector<string> topKFrequentWords1(vector<string>& words, int k) {
//    // Write your code here
//    unordered_map<string, int> hash;
//    for(int i=0; i<words.size(); i++)
//    {
//        string s = words[i];
//        if(hash.find(s) == hash.end() )
//        {
//            hash[s] = 1;
//        }
//        else
//        {
//            hash[s] += 1;
//        }
//    }
//    
//    vector<string> result;
//    for (unordered_map<string,int>::iterator it=hash.begin(); it!=hash.end(); ++it)
//    {
//        if(it->second == k)
//        {
//            cout << it->first << endl;
//            result.push_back(it->first);
//        }
//    }
//    return result;
//}
//
//
//class PoCount{
//    int index;
//    string words;
//};
//
//vector<string> topKFrequentWords(vector<string>& words, int k) {
//    sort(words.begin(), words.end());
//    
//    unordered_map<string, int> hash;
//    vector<int>
//    for(int i=0; i<words.size(); i++)
//    {
//        string s = words[i];
//
//        if(hash.find(s) == hash.end() )
//        {
//            hash[s] = 1;
//        }
//        else
//        {
//            hash[s] += 1;
//        }
//        
//        if (i<words.size()-2 && s != words[i+1]) {
//            
//        }
//    }
//    
//}
//
//void testK()
//{
////    ["yes","lint","code","yes","code",  "baby","you","baby","chrome","safari",
////    "lint","code","body","lint","code"]
//    vector<string> words;
//    words.push_back("yes");
//    words.push_back("lint");
//    words.push_back("code");
//    words.push_back("yes");
//    words.push_back("code");
//    
//    words.push_back("baby");
//    words.push_back("you");
//    words.push_back("baby");
//    words.push_back("chrome");
//    words.push_back("safari");
//    
//    words.push_back("lint");
//    words.push_back("code");
//    words.push_back("body");
//    words.push_back("lint");
//    words.push_back("code");
//    vector<string> result;
//    result = topKFrequentWords(words, 3);
//}





void helperS(vector<string> &re, string& str,  string sub,
             unordered_map<int, bool> &hash)
{
    
    if(sub.size()  == str.size())
    {
        re.push_back(sub);
        sub = "";
        return;
    }


    for(int i=0; i<str.size(); i++)
    {
        cout << "i - is - " << i << endl;
        
        if(hash[i])
        {
            continue;
        }
        
        if (i > 0 && hash[i - 1] == false && str[i] == str[i-1]) {
            continue;
        }
        
        sub = sub + str[i];
        hash[i] = true;
        
        helperS(re, str, sub, hash);
        
        
        sub.erase(sub.end()-1);
        cout << "i is - " << i << endl;
        hash[i] = false;
    }

}

vector<string> stringPermutation2(string& str) {
    // Write your code here
    unordered_map<int, bool> hash;
    
    
    vector<string> re;
    int length = str.size();
    
    if(length == 0)
    return re;
    
    if(length == 1)
    {
        re.push_back(str);
        return re;
    }
    
    string s;
    helperS(re, str, s, hash);
    return re;
}

void testStringP()
{
    string s = "abb";
    vector<string> re = stringPermutation2(s);
}






//!!!!!


void helper(vector<vector<int> > &result,vector<int> sub,
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
        
        helper(result, sub, nums, hashSub);
        
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
    
    if(nums.size() == 0)
    {
        result.push_back(vector<int>());
        return result;
    }
    
    //必须要sort，才对
    sort(nums.begin(), nums.end());
    helper(result, sublist, nums, hashSub);
    return result;
}

void testP()
{
    vector<int> re;
    re.push_back(1);
    re.push_back(2);
    re.push_back(2);
    vector<vector<int> > r = permuteUnique(re);
}

//~~~~~~~

int bfs(unordered_set<string> &dict,
        string start, string end, map<string, vector<string>> &hash)
{
    queue<string> q;
    q.push(start);
    dict.erase(start);
    bool endFlag = false;
    // hash[start] = 1;
    int count = 2;
    while(q.size() || endFlag)
    {
        int sizeQ = q.size();
        for(int i=0; i<sizeQ; i++)
        {
            string preS = q.front();
            string s = q.front();
            q.pop();
            for(int i=0; i<s.size(); i++)
            {
                char tmp = s[i];
                for(char c = 'a'; c<='z'; c++)
                {
                    s[i] = c;
                    
                    if(s == end)
                    {
                        vector<string> strings;
                        if (preS != s ) {
                            
                            if (hash.find(preS) != hash.end()) {
                                strings = hash[preS];
                                
                            }
                            strings.push_back(s);
                            if (preS != s ) {
                                hash[preS] = strings;
                            }
                            cout << "preS is - " << preS << " / s is -" << s << " / string size - " << strings.size() << endl;
                        }
                        endFlag = true;
                    }
                    else if (dict.find(s) != dict.end())
                    {
                        q.push(s);
                        dict.erase(s);
                        vector<string> strings;
                        if (hash.find(preS) != hash.end()) {
                            strings = hash[preS];
                            
                        }
                        strings.push_back(s);
                        cout << "preS is - " << preS << " / s is -" << s << " / string size - " << strings.size() << endl;
                        hash[preS] = strings;
                    }
                    
                }
                s[i] = tmp;
            }
            
        }
        if (endFlag) {
            return count;
        }
        count++;
    }
    return count;
}


vector<string> anagrams(vector<string> &strs) {
    map<string, vector<string>> hash;
    vector<string> re;
    
    int countEmpty = 0;
    
    if(strs.size() < 2)
        return re;
    
    if(strs.size() == 2)
        return strs;
    
    for(int i=0; i<strs.size(); i++)
    {
        string tmpS = strs[i];
        if(!tmpS.size())
            countEmpty++;
        
        sort(tmpS.begin(), tmpS.end());
        hash[tmpS].push_back(strs[i]);
        
    }
    
    for(map<string, vector<string>>::iterator it; it!=hash.end(); it++)
    {
        vector<string> re = it->second;
        long size = re.size();//it->second.size();
        if(size < 2)
            continue;
        
        for(int i=0; i<size; i++)
        {
            vector<string> listS = it->second;
            re.push_back(listS[i]);
        }
        
    }
    
    if(countEmpty > 1)
    {
        while(countEmpty)
        {
            re.push_back("");
            countEmpty--;
        }
    }
    return re;
}

void testAnag()
{
    vector<string> strs = {"tea","and","ate","eat","den"};
    vector<string> re = anagrams(strs);
}


int dropEggs2(int m, int n, vector<vector<int>> &hash)
{
    if(hash[m][n] != -1)
        return hash[m][n];
    
    int minV = INT_MAX;
    for(int i=2; i<=n; i++)
    {
        int v1 = dropEggs2(m-1, n-1, hash);
        int v2 = dropEggs2(m, n-i,hash);
        int tmp = max(v1, v2);//!!worse case
        minV = min(tmp, minV);
    }
    hash[m][n] = minV + 1;
    return minV+1;
}
int dropEggs2(int m, int n) {
    
    //state
    vector<vector<int>> hash(m+1, vector<int>(n+1, -1));
    
    //init - state
    for(int i=0; i<=m; i++)
    {
        for(int j=0; j<= min(1,n); j++)
        {
            hash[i][j] = j;
        }
    }
    
    for(int i=1; i<=n; i++)
    {
        hash[1][i] = i;
    }
    
    
    int re =  dropEggs2(m,n,hash);
    return re;
}



int largestRectangleArea(vector<int> &height) {
    if(height.size() == 0 )
        return 0;
    
    stack<int> helpS;
    int area = height[0];
    helpS.push(area);
    
    height.push_back(-1);//!!pop all
    for(int i=1; i<height.size(); i++)
    {
        int currentH = height[i];
        int width = 0;
        if( helpS.empty() || currentH >= helpS.top())
        {
            helpS.push(currentH);
        }
        else
        {
            while(!helpS.empty() && currentH < helpS.top() )
            {
                width++;
                int height = helpS.top();
                helpS.pop();
                area = max(width*height, area);//!!smart way to handle
            }
        }
        
    }
    
    return area;
}

void testHist()
{
    vector<int> hist = {5,4,1,2};
    largestRectangleArea(hist);
}

class ParentTreeNode {
public:
    int val;
    ParentTreeNode *parent, *left, *right;
    ParentTreeNode(int v, ParentTreeNode *p, ParentTreeNode *l, ParentTreeNode *r)
    {
        val = v;
        parent = p;
        left = l;
        right = r;
    }
};

ParentTreeNode *lowestCommonAncestorII(ParentTreeNode *root,
                                       ParentTreeNode *A,
                                       ParentTreeNode *B) {
    if(root == A || root == B)
        return root;
    
    
    stack<ParentTreeNode *> sa;
    stack<ParentTreeNode *> sb;
    
    
    while(A)
    {
        sa.push(A);
        A = A->parent;
    }
    
    while(B)
    {
        sb.push(B);
        B = B->parent;
    }
    
    while(sa.size() && sb.size())
    {
        ParentTreeNode *node = sa.top();
        if(sa.top() == sb.top())
        {
            sa.pop();
            sb.pop();
            if( !sa.size() || !sb.size()  )
            {
                return node;
            }
            
            if( sa.top() != sb.top())
                return node;
        }
    }
    return NULL;
}

void testParent()
{
    ParentTreeNode *left = new ParentTreeNode(1, NULL, NULL, NULL);
    ParentTreeNode *right = new ParentTreeNode(3, NULL, NULL, NULL);
    ParentTreeNode *root = new ParentTreeNode(-2, NULL, left, right);
    left->parent = root;
    right->parent = root;
    
    lowestCommonAncestorII(root, left, right);
}



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    testParent();
    return 0;
}
