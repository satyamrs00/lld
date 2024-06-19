#include "bits/stdc++.h"
#include "ContactBook.cpp"

using namespace std;

int main() {
    auto contactBook = ContactBook::getInstance();

    auto a = contactBook->addContact("satyam", "sagar", "9898989898");
    auto b = contactBook->addContact("atyapreet", "singh", "9898989898");
    auto c = contactBook->addContact("rohan", "glory", "9898989898");
    auto d = contactBook->addContact("all", "away", "9898989898");
    
    // b = contactBook->updateContact(b, "lala", "sand", "8787887888");

    auto resultsTuple = contactBook->search("989898");

    int count;
    vector<Contact *> results;
    tie(count, results) = resultsTuple;
    
    cout << "Count: " << count << '\n';
    for (auto x : results){
        x->print();
    }
}