#include "bits/stdc++.h"

using namespace std;

class Airport {
private:
    int id; // 1xx
    string code;
    string city;

public:
    Airport() {}
    Airport(int _id, string _code, string _city){
        id = _id;
        code = _code;
        city = _city;
    }
    int getId(){
        return id;
    }
    string getCode(){
        return code;
    }
    void setCode(string _code){
        code = _code;
    }
    string getCity(){
        return city;
    }
    void setCity(string _city){
        city = _city;
    }
};

class User {
private:
    int id; // 1xxxx

public:
    User(){}
    User(int _id){
        id = _id;
    }
    int getId() {
        return id;
    }
};

class Flight {
private:
    int id; // 1xxx
    vector<User *> passengers;
    Airport *source;
    Airport *destination;

public:
    Flight(){}
    Flight(int _id, Airport *_source, Airport *_destination){
        id = _id;
        source = _source;
        destination = _destination;
        passengers = vector<User *> (0);
    }

    void addPassenger(User *_user){
        passengers.push_back(_user);
    }
    void removePassenger(User *_user){
        for (int i = 0; i < passengers.size(); i++){
            if (passengers[i]->getId() == _user->getId()){
                passengers.erase(passengers.begin() + i);
                break;
            }
        }
    }
    int getId() {
        return id;
    }
    Airport *getSource(){
        return source;
    }
    Airport *getDestination(){
        return destination;
    }

    void print(){
        cout << "FLIGHT DETAILS\nid: " << id << "\nsource: " << source->getId() << "\ndestination: " << destination->getId() << "\npassengers: ";
        for (int i = 0; i < passengers.size(); i++){
            if (i > 0) cout << ", ";
            cout << passengers[i]->getId();
        }
        cout << '\n';
    }

};

class Ticket {
private:
    int id; // 1xxxxx
    User *user;
    Flight *flight;
    string status; // should be enum // confirmed, canceled

public:
    Ticket(){}
    Ticket(int _id, User *_user, Flight *_flight){
        id = _id;
        user = _user;
        flight = _flight;
        status = "confirmed";
    }

    void cancelTicket(){
        status = "canceled";
    }
    Flight *getFlight(){
        return flight;
    }
    User *getUser(){
        return user;
    }
};

class FlightBookingService {
private:
    map<int, Airport *> airports;
    map<int, Flight *> flights;
    map<int, User *> users;
    map<int, Ticket *> tickets;

public:
    FlightBookingService(){
        airports = map<int, Airport *> {};
        flights = map<int, Flight *> {};
        users = map<int, User *> {};
        tickets = map<int, Ticket *> {};
    }

    void createAirport(int _id, string _code, string _city){
        Airport *airport = new Airport(_id, _code, _city);
        airports[_id] = airport;

        cout << "Airport " << _id << " created at " << _city << "\n";
    }
    void createFlight(int _id, int _source, int _destination){
        Airport *sourceAirport = airports[_source];
        Airport *destinationAirport = airports[_destination];

        Flight *flight = new Flight(_id, sourceAirport, destinationAirport);
        flights[_id] = flight;

        cout << "New flight created from " << _source << " to " << _destination << "\n";
    }

    void createUser(int _id){
        User *user = new User(_id);
        users[_id] = user;

        cout << "User " << _id << " created\n";
    }

    int createBooking(int userId, int flightId){
        Flight *flight = flights[flightId];
        User *user = users[userId];

        flight->addPassenger(user);

        int newTicketId = 100000 + tickets.size()+1;
        Ticket *newTicket = new Ticket(newTicketId, user, flight);
        tickets[newTicketId] = newTicket;

        cout << "User " << userId << " booked a flight from " << flight->getSource()->getId() << " to " << flight->getDestination()->getId() << "\n";

        return newTicketId;
    }

    void cancelBooking(int ticketId){
        Ticket *ticket = tickets[ticketId];

        ticket->cancelTicket();
        ticket->getFlight()->removePassenger(ticket->getUser());

        cout << "User " << ticket->getUser()->getId() << " canceled a booking from " << ticket->getFlight()->getSource()->getId() << " to " << ticket->getFlight()->getDestination()->getId() << "\n";
    }

    void printFlightDetails(int _id){
        Flight *flight = flights[_id];
        flight->print();
    }
};

int main(){
    FlightBookingService *flightBookingService = new FlightBookingService();

    flightBookingService->createAirport(101, "DEL", "Delhi");
    flightBookingService->createAirport(102, "MUM", "Mumbai");
    flightBookingService->createAirport(103, "BAN", "Bangalore");

    flightBookingService->createFlight(1001, 101, 102);
    flightBookingService->createFlight(1002, 102, 103);

    flightBookingService->createUser(10001);

    int ticket = flightBookingService->createBooking(10001, 1001);
    
    flightBookingService->printFlightDetails(1001);

    flightBookingService->cancelBooking(ticket);

    flightBookingService->printFlightDetails(1001);

    return 0;
}