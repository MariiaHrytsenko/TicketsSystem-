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
        cout << "Teraz nie istnieje aktualnych ofert dla zakupu onlajn. Prosimy zwrocic sie bezposzrednio do kass kina." << endl << "Przepraszamy za utrudnienia!";
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
        return "Ulgowy";
    if (lowercaseAnswer == "no")
        return "Normalny";
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
    cout << "Cieszymy sie, ze mozemy Cie powitac. Zaloguj sie do swojego konta." << endl;

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
    cout << "Dzien dobry! Witamy w systemie zakupu biletow." << endl << "Co chcesz robic?" << endl;
    cout << "1.Zapoznaj się z repertuarem" << endl;
    cout << "2.Zobacz swoje bilety" << endl;
    cout << "3.Koniec" << endl;
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
        cout << "Podaj kod wydarzenia: " << endl;
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

        cout << "Wybierz miejsce zakupu: ";
        cin >> place;

        cout << "Czy potrzebujesz bilet ulgowy?" << endl;
        cout << "Wpisz odpowiedz TAK albo NIE." << endl;

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

        cout << "Czy potwiedzasz kupowanie biletu?" << endl;
        cout << "Wpisz odpowiedz TAK lub NIE." << endl;

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
            cout << "Witamy!" << endl;
            cout << "Bilet zostal pomyslnie dodany do Twojego konta." << endl;
            Bilet::saveTicketInfoToFile(bilet, event);

        }
        else {
            cout << "Bilet zostal anulowany." << endl;
            
        }


// чи можна тут прописати повне закінчення роботи із сервісом     if (choice == 3) return 0;
        cout << "Wybierz 1 dla powrotu do glownej strony." << endl;
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
            std::cerr << "Помилка відкриття файлу UsersTickets.txt!" << std::endl;
            return 1; 
        }

        std::string line;

        while (std::getline(userTicketsFile, line)) {
            std::cout << line << std::endl;
        }
        userTicketsFile.close();
    
 // чи можна тут прописати повне закінчення роботи із сервісом     if (choice == 3) return 0;
        cout << "Wybierz 1 dla powrotu do glownej strony." << endl;
        cin >> choice;

        if (choice == 1)
            goto line191;

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

//текст може не вивести
    if (choice == 3)
        cout << "Dziękujemy za skorzystanie z naszej usługi zakupu biletów." << endl;
        cout << "Będzie nam milo Cie ponownie zobaczyc." << endl;
        cout << "Zyczymy milego dnia!" << endl;
        return 0;
}
