#include "bits/stdc++.h"
#include "ContactBuilder.cpp"
#include "Trie.cpp"

using namespace std;

class ContactBook {
private:
    static ContactBook *_contactBook;
    ContactBuilder *_contactBuilder;

    unordered_map<int, Contact *> _contacts;
    AlphabetTrie *_firstNameTrie;
    AlphabetTrie *_lastNameTrie;
    DigitTrie *_phoneNumberTrie;

    ContactBook(){
        _firstNameTrie = new AlphabetTrie();
        _lastNameTrie = new AlphabetTrie();
        _phoneNumberTrie = new DigitTrie();
        _contactBuilder = new ContactBuilder();
    }

public:
    ContactBook(ContactBook *c) = delete;
    
    void operator=(ContactBook *c) = delete;

    static ContactBook *getInstance();

    Contact *addContact(string firstName, string lastName, string phoneNumber){
        _contactBuilder->setName(firstName, lastName);
        _contactBuilder->setPhoneNumber(phoneNumber);
        Contact *c = _contactBuilder->contact();

        _contacts[c->id()] = c;

        _firstNameTrie->insert(c->firstName(), c->id());
        _lastNameTrie->insert(c->lastName(), c->id());
        _phoneNumberTrie->insert(c->phoneNumber(), c->id());

        return c;
    }

    Contact *updateContact(Contact *contact, string firstName, string lastName, string phoneNumber){
        _firstNameTrie->erase(contact->firstName(), contact->id());
        _lastNameTrie->erase(contact->lastName(), contact->id());
        _phoneNumberTrie->erase(contact->phoneNumber(), contact->id());

        _contactBuilder->useContact(contact);
        _contactBuilder->setName(firstName, lastName);
        _contactBuilder->setPhoneNumber(phoneNumber);
        Contact *c = _contactBuilder->contact();

        _contacts[c->id()] = c;

        _firstNameTrie->insert(c->firstName(), c->id());
        _lastNameTrie->insert(c->lastName(), c->id());
        _phoneNumberTrie->insert(c->phoneNumber(), c->id());

        return c;
    }

    tuple<int, vector<Contact *>> search(string query){
        set<int> result;

        auto resultsByFirstName = _firstNameTrie->search(query);
        auto resultsByLastName = _lastNameTrie->search(query);
        auto resultsByPhoneNumber = _phoneNumberTrie->search(query);

        result.insert(resultsByFirstName.begin(), resultsByFirstName.end());
        result.insert(resultsByLastName.begin(), resultsByLastName.end());
        result.insert(resultsByPhoneNumber.begin(), resultsByPhoneNumber.end());
        
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