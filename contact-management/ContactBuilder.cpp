#include "bits/stdc++.h"
#include "Contact.cpp"

using namespace std;

class AbstractContactBuilder {
protected:
    Contact *_contact;

public: 
    AbstractContactBuilder(){}
    void reset(){}
    void useContact(Contact *prevContact){}
    void contact(){}
    void setName(string first, string last){}
    void setPhoneNumber(string s){}
};

class ContactBuilder : AbstractContactBuilder {
protected:
    Contact *_contact;

public: 
    ContactBuilder(){
        _contact = new Contact();
    }
    void reset(){
        _contact = new Contact();
    }
    void useContact(Contact *prevContact){
        _contact = prevContact;
    }
    Contact *contact(){
        auto contactTemp = _contact;
        _contact = new Contact;
        return contactTemp;
    }
    void setName(string first, string last){
        _contact->setFirstName(first);
        _contact->setLastName(last);
    }
    void setPhoneNumber(string s){
        _contact->setPhoneNumber(s);
    }
};