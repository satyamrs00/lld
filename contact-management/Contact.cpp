#include "bits/stdc++.h"

using namespace std;

class Contact {
protected:
    static int _prevId;
    int _id;
    string _firstName;
    string _lastName;
    string _phoneNumber;

public:
    Contact();
    string firstName() {
        return _firstName;
    }

    string lastName() {
        return _lastName;
    }

    string phoneNumber() {
        return _phoneNumber;
    }
    int id(){
        return _id;
    }

    void setFirstName(string s){
        _firstName = s;
    }

    void setLastName(string s){
        _lastName = s;
    }

    void setPhoneNumber(string s){
        _phoneNumber = s;
    }
    
    void print(){
        cout << "Id: " << _id << '\n';
        cout << "Name: " << _firstName << ' ' << _lastName << "\n";
        cout << "Phone: " << _phoneNumber << '\n';
        cout << '\n';
    }
};

int Contact::_prevId = 0;

Contact::Contact(){
    _id = _prevId+1;
    _firstName = "";
    _lastName = "";
    _phoneNumber = "";

    _prevId++;
}