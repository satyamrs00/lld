#include "bits/stdc++.h"
#include "ContactBuilder.cpp"
#include "TrieNode.cpp"

using namespace std;

class ContactBook {
private:
    static ContactBook *_contactBook;
    ContactBuilder *_contactBuilder;

    unordered_map<int, Contact *> _contacts;
    AlphabetTrieNode *_firstNameTrie;
    AlphabetTrieNode *_lastNameTrie;
    DigitTrieNode *_phoneNumberTrie;

    ContactBook(){
        _firstNameTrie = new AlphabetTrieNode();
        _lastNameTrie = new AlphabetTrieNode();
        _phoneNumberTrie = new DigitTrieNode();
        _contactBuilder = new ContactBuilder();
    }

public:
    ContactBook(ContactBook *c) = delete;
    
    void operator=(ContactBook *c) = delete;

    static ContactBook *getInstance();

    void insertIntoAlphabetTrie(AlphabetTrieNode *root, Contact *contact){
        auto r = root;
        for (char c : contact->firstName()){
            if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';

            if (!r->_next[c-'a']) r->_next[c-'a'] = new AlphabetTrieNode();
            r = r->_next[c-'a'];
        }
        r->_ids.insert(contact->id());
    }
    void removeFromAlphabetTrie(AlphabetTrieNode *root, Contact *contact){
        auto r = root;
        for (char c : contact->firstName()){
            if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';

            if (r->_next[c-'a']) r = r->_next[c-'a'];
            else return;
        }
        r->_ids.erase(contact->id());
    }
    void insertIntoDigitTrie(DigitTrieNode *root, Contact *contact){
        auto r = root;
        for (char c : contact->phoneNumber()){
            if (!r->_next[c-'0']) r->_next[c-'0'] = new DigitTrieNode();
            r = r->_next[c-'0'];
        }
        r->_ids.insert(contact->id());
    }
    void removeFromDigitTrie(DigitTrieNode *root, Contact *contact){
        auto r = root;
        for (char c : contact->phoneNumber()){
            if (r->_next[c-'0']) r = r->_next[c-'0'];
            else return;
        }
        r->_ids.erase(contact->id());
    }

    void searchInAlphabetTrie(AlphabetTrieNode *root, set<int>& result, string query){
        auto r = root;
        for (auto c : query){
            if (c >= '0' && c <= '9') return;
            if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';

            r = r->_next[c-'a'];
            if (!r) return;
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
    }
    void searchInDigitTrie(DigitTrieNode *root, set<int>& result, string query){
        auto r = root;
        for (auto c : query){
            if (!(c >= '0' && c <= '9')) return;

            r = r->_next[c-'0'];
            if (!r) return;
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
    }

    Contact *addContact(string firstName, string lastName, string phoneNumber){
        _contactBuilder->setName(firstName, lastName);
        _contactBuilder->setPhoneNumber(phoneNumber);
        Contact *c = _contactBuilder->contact();

        _contacts[c->id()] = c;

        insertIntoAlphabetTrie(_firstNameTrie, c);
        insertIntoAlphabetTrie(_lastNameTrie, c);
        insertIntoDigitTrie(_phoneNumberTrie, c);

        return c;
    }

    Contact *updateContact(Contact *contact, string firstName, string lastName, string phoneNumber){
        removeFromAlphabetTrie(_firstNameTrie, contact);
        removeFromAlphabetTrie(_lastNameTrie, contact);
        removeFromDigitTrie(_phoneNumberTrie, contact);

        _contactBuilder->useContact(contact);
        _contactBuilder->setName(firstName, lastName);
        _contactBuilder->setPhoneNumber(phoneNumber);
        Contact *c = _contactBuilder->contact();

        _contacts[c->id()] = c;

        insertIntoAlphabetTrie(_firstNameTrie, c);
        insertIntoAlphabetTrie(_lastNameTrie, c);
        insertIntoDigitTrie(_phoneNumberTrie, c);

        return c;
    }

    tuple<int, vector<Contact *>> search(string query){
        set<int> result;

        searchInAlphabetTrie(_firstNameTrie, result, query);
        searchInAlphabetTrie(_lastNameTrie, result, query);
        searchInDigitTrie(_phoneNumberTrie, result, query);

        vector<Contact *> ans;
        for (auto it = result.begin(); it != result.end(); it++){
            ans.push_back(_contacts[*it]);
        }

        return {ans.size(), ans};
    }
};

ContactBook *ContactBook::_contactBook = nullptr;

ContactBook *ContactBook::getInstance(){
    if (_contactBook == nullptr){
        _contactBook =  new ContactBook();
    }
    return _contactBook;
};