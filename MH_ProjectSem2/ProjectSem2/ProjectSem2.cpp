#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "logger.h"
#include "back.h"
#include "сredentials.h"

using namespace std;

bool Example2(const char* filename) {
    ifstream is(filename);

    if (!is) {
        cout << "Now there are no current offers for online purchase. Please contact the cinema box office directly." << endl << "Sorry for the inconvenience!";
        return false;
    }

    string str;

    while (getline(is, str)) {
        cout << str << endl;
    }

    is.close();
    return true;
}

string checkAnswer(const string& answer) {
    string lowercaseAnswer = answer;
    for (char& c : lowercaseAnswer) {
        c = tolower(c);
    }

    if (lowercaseAnswer == "yes")
        return "Reduced";
    if (lowercaseAnswer == "no")
        return "Standard";
}

bool checkAnswerLogic(const string& answer) {
    string lowercaseAnswer = answer;
    for (char& c : lowercaseAnswer) {
        c = tolower(c);
    }

    if (lowercaseAnswer == "yes")
        return 1;
    if (lowercaseAnswer == "no")
        return 0;
}

int main() {
    cout << "We are happy to welcome you. Log in to your account." << endl;

    сredentials creds("login.txt");

    std::string inputUsername;
    std::string inputPassword;

    std::cout << "Enter username: ";
    std::cin >> inputUsername;
    Klient klient(inputUsername);

    std::cout << "Enter password: ";
    std::cin >> inputPassword;

    if (inputUsername == creds.getUsername() && inputPassword == creds.getPassword()) {
        logger::log(logger::Level::INFO, "Access granted");
    }
    else {
        logger::log(logger::Level::ERROR, "Access denied");
        return 0;
    }

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    int choice;

line191:
    cout << "Hello, dear user! Welcome to the ticket purchasing system." << endl << "What would you like to do?" << endl;
    cout << "1.Get to know the repertoire" << endl;
    cout << "2.View your tickets" << endl;
    cout << "3.Move to the end" << endl;
    cin >> choice;

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    if (choice == 1) {
        ifstream Frepertuar;
        Frepertuar.open("repertuar.txt");

        Example2("repertuar.txt");

        string filename;
        cout << "Enter the event code: " << endl;
        cin >> filename;
        
        Wydarzenie event = Wydarzenie::findEventByKod(filename);

        filename += ".txt";

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        vector<std::string> lines;
        ifstream file(filename);

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                lines.push_back(line);
            }
            file.close();
        }
        else {
            cout << "File not open";
            return 1;
        }

        for (const auto& line : lines) {
            std::cout << line << "\n";
        }

        vector<string> original_lines = lines;

        int place;
        string ans1, ans2;

        cout << "Select where to purchase: ";
        cin >> place;

        cout << "Do you need a reduced ticket?" << endl;
        cout << "Enter the answer YES or NO." << endl;

        cin >> ans1;
        
        string isSpecial = checkAnswer(ans1);
        string placeSTR = to_string(place);
        Bilet bilet(event, isSpecial, placeSTR);

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        event.printEventInfo();
        cout << "Seat Code: " << bilet.getSeatCode() << endl;
        cout << "Ticket Type: " << bilet.getIsSpecial() << endl;
        cout << "Ticket Price: " << bilet.getTicketPrice(event, bilet.getIsSpecial()) << endl;

        cout << "Do you confirm purchasing the ticket?" << endl;
        cout << "Enter the answer YES or NO." << endl;

        cin >> ans2;
        bool ans2Logic = checkAnswerLogic(ans2);

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        if (ans2Logic == true) {

            int row = (place / 10) - 1;
            int col = (place % 10) - 1;
            int pos = col * 3;

            if (row < lines.size() && pos + 1 < lines[row].length()) {
                lines[row].replace(pos, 2, "X");
            }

            for (const auto& line : lines) {
                std::cout << line << "\n";
            }

            ofstream out_file(filename);
            for (const auto& line : lines) {
                out_file << line << "\n";
            }
            out_file.close();


            klient.addPurchasedTicket(bilet);
            cout << "Congratulations!" << endl;
            cout << "The ticket has been successfully added to your account." << endl;
            Bilet::saveTicketInfoToFile(bilet, event);

        }
        else {
            cout << "The ticket has been cancelled." << endl;
            
        }


        cout << "Select 1 to return to the main page." << endl;
        cin >> choice;

        if (choice == 1)
            goto line191;


#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        ofstream restore_file(filename);
        for (const auto& line : original_lines) {
            restore_file << line << "\n";
        }
        restore_file.close();
    }

    if (choice == 2) {
        std::ifstream userTicketsFile("UsersTickets.txt");

        if (!userTicketsFile.is_open()) {
            cout << "Now there are no current offers for online purchase. Please contact the cinema box office directly." << endl << "Sorry for the inconvenience!"<<endl<<"ERROR";
            return 1; 
        }

        std::string line;

        while (std::getline(userTicketsFile, line)) {
            cout << line << sendl;
        }
        userTicketsFile.close();
    

        cout << "Select 1 to return to the main page." << endl;
        cin >> choice;

        if (choice == 1)
            goto line191;

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }


    if (choice == 3)
        cout << "Thank you for using our ticket purchasing service." << endl;
        cout << "We will be pleased to see you again." << endl;
        cout << "We wish you a nice day!" << endl;
        return 0;
}
