#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Let {
    string destinacija;
    string vrijemePolaska;
    string vrijemeDolaska;

    Let(const string& dest, const string& polazak, const string& dolazak)
        : destinacija(dest), vrijemePolaska(polazak), vrijemeDolaska(dolazak) {}
};

bool imaSukob(const vector<Let>& letovi, const Let& noviLet) {
    for (const Let& let : letovi) {
        if (let.destinacija == noviLet.destinacija &&
            let.vrijemePolaska <= noviLet.vrijemeDolaska &&
            let.vrijemeDolaska >= noviLet.vrijemePolaska) {
            return true; // Pronađen sukob letova
        }
    }
    return false; // Nema sukoba
}

void prikaziLetove(const vector<Let>& letovi) {
    if (letovi.empty()) {
        cout << "Nema registrovanih letova." << endl;
        return;
    }

    cout << "Registrovani letovi:" << endl;
    for (const Let& let : letovi) {
        cout << "Destinacija: " << let.destinacija << endl;
        cout << "Vrijeme polaska: " << let.vrijemePolaska << endl;
        cout << "Vrijeme dolaska: " << let.vrijemeDolaska << endl;
        cout << "-----------------------------" << endl;
    }
}

void upisiFlightLog(const vector<Let>& letovi, const string& imeFajla) {
    ofstream izlazniFajl(imeFajla);
    if (!izlazniFajl) {
        cerr << "Greška prilikom otvaranja fajla." << endl;
        return;
    }

    for (const Let& let : letovi) {
        izlazniFajl << let.destinacija << " "
                    << let.vrijemePolaska << " "
                    << let.vrijemeDolaska << endl;
    }

    izlazniFajl.close();
}

int main() {
    vector<Let> registrovaniLetovi;

    // Čitanje letova iz tekstualnog fajla
    ifstream ulazniFajl("letovi.txt");
    if (!ulazniFajl) {
        cerr << "Greška prilikom otvaranja fajla." << endl;
        return 1;
    }

    string destinacija, vrijemePolaska, vrijemeDolaska;
    while (ulazniFajl >> destinacija >> vrijemePolaska >> vrijemeDolaska) {
        Let noviLet(destinacija, vrijemePolaska, vrijemeDolaska);

        if (imaSukob(registrovaniLetovi, noviLet)) {
            cout << "Pronađen sukob letova: "
                 << noviLet.destinacija << " u periodu "
                 << noviLet.vrijemePolaska << "-" << noviLet.vrijemeDolaska
                 << endl;
        } else {
            registrovaniLetovi.push_back(noviLet);
            cout << "Let registrovan: "
                 << noviLet.destinacija << " u periodu "
                 << noviLet.vrijemePolaska << "-" << noviLet.vrijemeDolaska
                 << endl;
        }
    }

    ulazniFajl.close();

    int izbor = 0;
    while (izbor != 3) {
        cout << "Meni:" << endl;
        cout << "1. Dodaj novi let" << endl;
        cout << "2. Prikazi sve registrovane letove" << endl;
        cout << "3. Izlaz" << endl;
        cout << "Unesite izbor (1-3): ";
        cin >> izbor;

        switch (izbor) {
            case 1: {
                string destinacija, vrijemePolaska, vrijemeDolaska;
                cout << "Unesite destinaciju: ";
                cin >> destinacija;
                cout << "Unesite vrijeme polaska: ";
                cin >> vrijemePolaska;
                cout << "Unesite vrijeme dolaska: ";
                cin >> vrijemeDolaska;

                Let noviLet(destinacija, vrijemePolaska, vrijemeDolaska);

                if (imaSukob(registrovaniLetovi, noviLet)) {
                    cout << "Pronađen sukob letova: "
                         << noviLet.destinacija << " u periodu "
                         << noviLet.vrijemePolaska << "-" << noviLet.vrijemeDolaska
                         << endl;
                } else {
                    registrovaniLetovi.push_back(noviLet);
                    cout << "Let registrovan: "
                         << noviLet.destinacija << " u periodu "
                         << noviLet.vrijemePolaska << "-" << noviLet.vrijemeDolaska
                         << endl;
                    upisiFlightLog(registrovaniLetovi, "letovi.txt");
                }

                break;
            }
            case 2:
                prikaziLetove(registrovaniLetovi);
                break;
            case 3:
                cout << "Izlaz iz programa..." << endl;
                upisiFlightLog(registrovaniLetovi, "letovi.txt");
                break;
            default:
                cout << "Nevažeći izbor. Molimo pokušajte ponovo." << endl;
                break;
        }

        cout << endl;
    }

    return 0;
}