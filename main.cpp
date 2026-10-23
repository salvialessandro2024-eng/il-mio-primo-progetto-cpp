// ==========================================
// PROGETTO: RUBRICA TELEFONICA AVANZATA IN C++
// ==========================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>   // Per tolower()
#include <cstdio>   // Per remove() e rename()

using namespace std;

// Struttura con nome, telefono, email e indirizzo
struct Contatto {
    string nome;
    string telefono;
    string email;
    string indirizzo;
};

// Funzione per convertire una stringa in minuscolo (per la ricerca intelligente)
string toLowerString(string s) {
    for (char &c : s) {
        c = tolower(c);
    }
    return s;
}

// Funzione di ordinamento alfabetico basata sul nome
bool confrontaContatti(const Contatto& a, const Contatto& b) {
    return a.nome < b.nome;
}

// Carica i contatti dal file gestendo i 4 campi separati da virgola
vector<Contatto> caricaContattiDaFile() {
    vector<Contatto> lista;
    ifstream file("rubrica.txt");
    string riga;

    if (file.is_open()) {
        while (getline(file, riga)) {
            size_t v1 = riga.find(',');
            if (v1 != string::npos) {
                size_t v2 = riga.find(',', v1 + 1);
                size_t v3 = riga.find(',', v2 + 1);

                Contatto c;
                if (v2 != string::npos && v3 != string::npos) {
                    c.nome = riga.substr(0, v1);
                    c.telefono = riga.substr(v1 + 1, v2 - v1 - 1);
                    c.email = riga.substr(v2 + 1, v3 - v2 - 1);
                    c.indirizzo = riga.substr(v3 + 1);
                } else {
                    // Compatibilità con vecchi contatti
                    c.nome = riga.substr(0, v1);
                    c.telefono = riga.substr(v1 + 1);
                    c.email = "-";
                    c.indirizzo = "-";
                }
                lista.push_back(c);
            }
        }
        file.close();
    }
    return lista;
}

// Salva e ordina la lista sul file
void salvaContattiSuFile(vector<Contatto>& lista) {
    sort(lista.begin(), lista.end(), confrontaContatti);

    ofstream file("rubrica.txt");
    if (file.is_open()) {
        for (const auto& c : lista) {
            file << c.nome << "," << c.telefono << "," << c.email << "," << c.indirizzo << endl;
        }
        file.close();
    }
}

// ==========================================
// 1. AGGIUNGI CONTATTO (Con s/n separati per Email e Indirizzo)
// ==========================================
void aggiungiContatto() {
    Contatto nuovo;
    char sceltaEmail, sceltaIndirizzo;
    
    cout << "\n--- AGGIUNGI NUMERO ---" << endl;
    cout << "Inserisci il nome: ";
    cin >> nuovo.nome;
    cout << "Inserisci il numero: ";
    cin >> nuovo.telefono;

    // Chiede se inserire l'email con s/n
    cout << "Vuoi inserire l'email? (s/n): ";
    cin >> sceltaEmail;
    if (sceltaEmail == 's' || sceltaEmail == 'S') {
        cout << "Inserisci l'email: ";
        cin >> nuovo.email;
    } else {
        nuovo.email = "-";
    }

    // Chiede se inserire l'indirizzo con s/n
    cout << "Vuoi inserire l'indirizzo? (s/n): ";
    cin >> sceltaIndirizzo;
    if (sceltaIndirizzo == 's' || sceltaIndirizzo == 'S') {
        cout << "Inserisci l'indirizzo: ";
        cin >> nuovo.indirizzo;
    } else {
        nuovo.indirizzo = "-";
    }

    vector<Contatto> lista = caricaContattiDaFile();
    lista.push_back(nuovo);
    salvaContattiSuFile(lista);

    cout << "-> Contatto salvato e rubrica ordinata con successo!" << endl;
}

// ==========================================
// 2. CERCA CONTATTO (Case-Insensitive)
// ==========================================
void cercaContatto() {
    string cercaNome;
    cout << "\n--- CERCA NUMERO ---" << endl;
    cout << "Inserisci il nome da cercare: ";
    cin >> cercaNome;

    string cercaLower = toLowerString(cercaNome);
    vector<Contatto> lista = caricaContattiDaFile();
    bool trovato = false;

    for (const auto& c : lista) {
        if (toLowerString(c.nome) == cercaLower) {
            cout << "\n[TROVATO]" << endl;
            cout << "Nome: " << c.nome << endl;
            cout << "Tel: " << c.telefono << endl;
            cout << "Email: " << c.email << endl;
            cout << "Indirizzo: " << c.indirizzo << endl;
            trovato = true;
        }
    }

    if (!trovato) {
        cout << "-> Nessun contatto trovato con questo nome." << endl;
    }
}

// ==========================================
// 3. VISUALIZZA TUTTI (Solo su richiesta)
// ==========================================
void visualizzaTutti() {
    cout << "\n--- LISTA CONTATTI (ORDINATA) ---" << endl;
    vector<Contatto> lista = caricaContattiDaFile();

    if (lista.empty()) {
        cout << "La rubrica e' vuota!" << endl;
        return;
    }

    for (size_t i = 0; i < lista.size(); i++) {
        cout << i + 1 << ". " << lista[i].nome 
             << " | Tel: " << lista[i].telefono 
             << " | Email: " << lista[i].email 
             << " | Indirizzo: " << lista[i].indirizzo << endl;
    }
}

// ==========================================
// 4. MODIFICA CONTATTO
// ==========================================
void modificaContatto() {
    string cercaNome, nuovoTelefono;
    cout << "\n--- MODIFICA CONTATTO ---" << endl;
    cout << "Inserisci il nome del contatto da modificare: ";
    cin >> cercaNome;
    cout << "Inserisci il nuovo numero di telefono: ";
    cin >> nuovoTelefono;

    string cercaLower = toLowerString(cercaNome);
    vector<Contatto> lista = caricaContattiDaFile();
    bool trovato = false;

    for (auto& c : lista) {
        if (toLowerString(c.nome) == cercaLower) {
            c.telefono = nuovoTelefono;
            trovato = true;
        }
    }

    if (trovato) {
        salvaContattiSuFile(lista);
        cout << "-> Contatto modificato con successo!" << endl;
    } else {
        cout << "-> Nessun contatto trovato con questo nome." << endl;
    }
}

// ==========================================
// 5. ELIMINA CONTATTO
// ==========================================
void eliminaContatto() {
    string cercaNome;
    cout << "\n--- ELIMINA CONTATTO ---" << endl;
    cout << "Inserisci il nome del contatto da eliminare: ";
    cin >> cercaNome;

    string cercaLower = toLowerString(cercaNome);
    vector<Contatto> lista = caricaContattiDaFile();
    vector<Contatto> nuovaLista;
    bool trovato = false;

    for (const auto& c : lista) {
        if (toLowerString(c.nome) == cercaLower) {
            trovato = true;
        } else {
            nuovaLista.push_back(c);
        }
    }

    if (trovato) {
        salvaContattiSuFile(nuovaLista);
        cout << "-> Contatto eliminato con successo!" << endl;
    } else {
        cout << "-> Nessun contatto trovato con questo nome." << endl;
    }
}

// ==========================================
// FUNZIONE PRINCIPALE (MENU PROTETTO)
// ==========================================
int main() {
    int scelta;

    do {
        cout << "\n=========================" << endl;
        cout << "   LA MIA RUBRICA C++    " << endl;
        cout << "=========================" << endl;
        cout << "1. Aggiungi numero" << endl;
        cout << "2. Cerca numero" << endl;
        cout << "3. Visualizza tutti (Ordinati)" << endl;
        cout << "4. Modifica contatto" << endl;
        cout << "5. Elimina contatto" << endl;
        cout << "6. Esci" << endl;
        cout << "Scegli un'opzione: ";
        
        // Protezione anti-crash se inserisci lettere nel menu
        if (!(cin >> scelta)) {
            cout << "\n[ERRORE] Inserisci un numero valido da 1 a 6, non lettere!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            scelta = 0;
            continue;
        }

        switch (scelta) {
            case 1:
                aggiungiContatto();
                break;
            case 2:
                cercaContatto();
                break;
            case 3:
                visualizzaTutti();
                break;
            case 4:
                modificaContatto();
                break;
            case 5:
                eliminaContatto();
                break;
            case 6:
                cout << "Uscita dal programma. A presto!" << endl;
                break;
            default:
                cout << "Scelta non valida! Inserisci un numero tra 1 e 6." << endl;
        }
        
    } while (scelta != 6);

    return 0;
}
