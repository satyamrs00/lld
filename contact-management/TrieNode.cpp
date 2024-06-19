#include "bits/stdc++.h"

using namespace std;

class AbstractTrieNode {
public:
    vector<AbstractTrieNode*> _next;
    set<int> _ids;

    AbstractTrieNode(){}
};

class AlphabetTrieNode:AbstractTrieNode {
public:
    vector<AlphabetTrieNode*> _next;
    set<int> _ids;

    AlphabetTrieNode(){
        _next.resize(26, nullptr);
    }
};

class DigitTrieNode:AbstractTrieNode {
// private:
public:
    vector<DigitTrieNode*> _next;
    set<int> _ids;

    DigitTrieNode(){
        _next.resize(10, nullptr);
    }   
};