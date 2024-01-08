#include "back.h"

Wydarzenie::Wydarzenie(const string& Kod, const string& Date, const string& Time, const string& PriceNORM, const string& PriceSPEC, const string& Name)
    : Kod(Kod), Date(Date), Time(Time), PriceNORM(PriceNORM), PriceSPEC(PriceSPEC), Name(Name) {}


Wydarzenie Wydarzenie::findEventByKod(const string& Kod) {
    ifstream file("repertuar.txt");

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            istringstream iss(line);
            string repertuarKod;

            if (getline(iss, repertuarKod, '|') && repertuarKod == Kod) {
                string Date, Time, PriceNORM, PriceSPEC, Name;
                if (getline(iss, Date, '|') && getline(iss, Time, '|') &&
                    getline(iss, PriceNORM, '|') && getline(iss, PriceSPEC, '|') && getline(iss, Name)) {
                    return Wydarzenie(Kod, Date, Time, PriceNORM, PriceSPEC, Name);
                }
            }
        }
    }

    throw runtime_error("Event not found");
}

void Wydarzenie::printEventInfo() const { 
    cout << "Nazwa Wydarzenia: " << Name << endl;
    cout << "Data: " << Date << endl;
    cout << "Czas: " << Time << endl;
}

void Bilet::saveTicketInfoToFile(const Bilet& bilet, const Wydarzenie& event) {
    ofstream userTicketsFile("UsersTickets.txt", ios::app);

    if (!userTicketsFile.is_open()) {
        cerr << "Помилка відкриття файлу квитків користувача!" << endl;
        return;
    }

    // Записуємо інформацію про квиток у файл
    userTicketsFile << "Event Name: " << event.getEventName() << endl;
    userTicketsFile << "Date: " << event.getEventDate() << endl;
    userTicketsFile << "Time: " << event.getEventTime() << endl;
    userTicketsFile << "Seat Code: " << bilet.getSeatCode() << endl;
    userTicketsFile << "Ticket Type: " << bilet.getIsSpecial() << endl;
    userTicketsFile << "Ticket Price: " << bilet.getTicketPrice(event, bilet.getIsSpecial()) << endl;
    userTicketsFile << "------------------------" << endl;

    userTicketsFile.close();
}


string Wydarzenie::getEventKod() const {
    return Kod;
}

string Wydarzenie::getEventDate() const {
    return Date;
}

string Wydarzenie::getEventTime() const {
    return Time;
}

string Wydarzenie::getEventPriseNORM() const {
    return PriceNORM;
}

string Wydarzenie::getEventPriceSPEC() const {
    return PriceSPEC;
}

string Wydarzenie::getEventName() const {
    return Name;
}


Bilet::Bilet(const Wydarzenie& event, const string& isSpecial, string seatCode)
    : event(event), isSpecial(isSpecial), seatCode(seatCode) {}


const Wydarzenie& Bilet::getEvent() const {
    return event;
}

string Bilet::getIsSpecial() const {
    return isSpecial;
}

string Bilet::getTicketPrice(const Wydarzenie& event, const string& isSpecial) const {
    if (isSpecial == "Ulgowy") {
        return event.getEventPriceSPEC();
    }
    else if (isSpecial == "Normalny") {
        return event.getEventPriseNORM();
    }
}


string Bilet::getSeatCode() const {
    return seatCode;
}


Klient::Klient(const std::string& clientProfile)
    : clientProfile(clientProfile) {}

string Klient::getClientProfile() const {
    return clientProfile;
}

void Klient::addPurchasedTicket(const Bilet& ticket) {
    purchasedTickets.push_back(ticket);
}

const vector<Bilet>& Klient::getPurchasedTickets() const {
    return purchasedTickets;
}

