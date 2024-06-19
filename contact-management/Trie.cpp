#include "bits/stdc++.h"
#include "TrieNode.cpp"

using namespace std;

class Trie{
private:
    AbstractTrieNode *_root;

public:
    Trie(){}
    set<int> search(string query){}
    void insert(Contact *contact){}
    void erase(Contact *contact){}
};

class AlphabetTrie:Trie {
private:
    AlphabetTrieNode *_root;

public:
    AlphabetTrie(){
        _root = new AlphabetTrieNode();
    }
    void insert(string word, int id){
        auto r = _root;
        for (char c : word){
            if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';

            if (!r->_next[c-'a']) r->_next[c-'a'] = new AlphabetTrieNode();
            r = r->_next[c-'a'];
        }
        r->_ids.insert(id);
    }
    void erase(string word, int id){
        auto r = _root;
        for (char c : word){
            if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';

            if (r->_next[c-'a']) r = r->_next[c-'a'];
            else return;
        }
        r->_ids.erase(id);
    }
    set<int> search(string query){
        auto r = _root;
        set<int> result;

        for (auto c : query){
            if (c >= '0' && c <= '9') return {};
            if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';

            r = r->_next[c-'a'];
            if (!r) return {};
        }

        stack<AlphabetTrieNode *> s;
        s.push(r);
        while(!s.empty()){
            auto t = s.top(); s.pop();
            if (t->_ids.size() > 0){
                for (auto it = t->_ids.begin(); it != t->_ids.end(); it++){
                    result.insert(*it);
                }
            }
            for (auto x : t->_next){
                if (x) s.push(x);
            }
        }
        return result;
    }
};

class DigitTrie:Trie {
private:
    DigitTrieNode *_root;

public:
    DigitTrie(){
        _root = new DigitTrieNode();
    }
    void insert(string word, int id){
        auto r = _root;
        for (char c : word){
            if (!r->_next[c-'0']) r->_next[c-'0'] = new DigitTrieNode();
            r = r->_next[c-'0'];
        }
        r->_ids.insert(id);
    }
    void erase(string word, int id){
        auto r = _root;
        for (char c : word){
            if (r->_next[c-'0']) r = r->_next[c-'0'];
            else return;
        }
        r->_ids.erase(id);
    }
    set<int> search(string query){
        auto r = _root;
        set<int> result;

        for (auto c : query){
            if (!(c >= '0' && c <= '9')) return {};

            r = r->_next[c-'0'];
            if (!r) return {};
        }

        stack<DigitTrieNode *> s;
        s.push(r);
        while(!s.empty()){
            auto t = s.top(); s.pop();
            if (t->_ids.size() > 0){
                for (auto it = t->_ids.begin(); it != t->_ids.end(); it++){
                    result.insert(*it);
                }
            }
            for (auto x : t->_next){
                if (x) s.push(x);
            }
        }
        return result;
    }
};