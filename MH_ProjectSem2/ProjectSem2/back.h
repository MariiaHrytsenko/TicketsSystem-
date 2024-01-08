#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "logger.h"
using namespace std;

class Wydarzenie {
private:
    string Kod;
    string Date;
    string Time;
    string PriceNORM;
    string PriceSPEC;
    string Name;

public:
    Wydarzenie(const string& Kod, const string& Date, const string& Time, const string& PriceNORM, const string& PriceSPEC, const string& Name);
    static Wydarzenie findEventByKod(const string& Kod);
    void printEventInfo() const;

    string getEventKod() const;
    string getEventDate() const;
    string getEventTime() const;
    string getEventPriseNORM() const;
    string getEventPriceSPEC() const;
    string getEventName() const;
};

class Bilet {
private:
    const Wydarzenie& event;
    string isSpecial;
    string seatCode;

public:
    Bilet(const Wydarzenie& event, const string& isSpecial, string seatCode);

    const Wydarzenie& getEvent() const;
    string getIsSpecial() const;
    string getTicketPrice(const Wydarzenie& event, const string& isSpecial) const;
    string getSeatCode() const;
    static void saveTicketInfoToFile(const Bilet& bilet, const Wydarzenie& event);
};

class Klient {
private:
    string clientProfile;
    vector<Bilet> purchasedTickets;

public:
    Klient(const string& clientProfile);

    string getClientProfile() const;
    const vector<Bilet>& getPurchasedTickets() const;
    void addPurchasedTicket(const Bilet& ticket);
    void removePurchasedTicket(const Bilet& ticket);
};


