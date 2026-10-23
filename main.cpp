// ==========================================
// PROGETTO: RUBRICA MULTI-FILE CON SCELTE DEDICATE
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

// Carica i contatti dal file specificato
vector<Contatto> caricaContattiDaFile(const string& nomeFile) {
    vector<Contatto> lista;
    ifstream file(nomeFile);
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

// Salva e ordina la lista sul file specificato
void salvaContattiSuFile(vector<Contatto>& lista, const string& nomeFile) {
    sort(lista.begin(), lista.end(), confrontaContatti);

    ofstream file(nomeFile);
    if (file.is_open()) {
        for (const auto& c : lista) {
            file << c.nome << "," << c.telefono << "," << c.email << "," << c.indirizzo << endl;
        }
        file.close();
    }
}

// ==========================================
// 1. AGGIUNGI CONTATTO
// ==========================================
void aggiungiContatto(const string& nomeFile) {
    Contatto nuovo;
    char sceltaEmail, sceltaIndirizzo;
    
    cout << "\n--- AGGIUNGI NUMERO (" << nomeFile << ") ---" << endl;
    cout << "Inserisci il nome: ";
    cin >> nuovo.nome;
    cout << "Inserisci il numero: ";
    cin >> nuovo.telefono;

    cout << "Vuoi inserire l'email? (s/n): ";
    cin >> sceltaEmail;
    if (sceltaEmail == 's' || sceltaEmail == 'S') {
        cout << "Inserisci l'email: ";
        cin >> nuovo.email;
    } else {
        nuovo.email = "-";
    }

    cout << "Vuoi inserire l'indirizzo? (s/n): ";
    cin >> sceltaIndirizzo;
    if (sceltaIndirizzo == 's' || sceltaIndirizzo == 'S') {
        cout << "Inserisci l'indirizzo: ";
        cin >> nuovo.indirizzo;
    } else {
        nuovo.indirizzo = "-";
    }

    vector<Contatto> lista = caricaContattiDaFile(nomeFile);
    lista.push_back(nuovo);
    salvaContattiSuFile(lista, nomeFile);

    cout << "-> Contatto salvato e rubrica ordinata con successo!" << endl;
}

// ==========================================
// 2. CERCA CONTATTO
// ==========================================
void cercaContatto(const string& nomeFile) {
    string cercaNome;
    cout << "\n--- CERCA NUMERO (" << nomeFile << ") ---" << endl;
    cout << "Inserisci il nome da cercare: ";
    cin >> cercaNome;

    string cercaLower = toLowerString(cercaNome);
    vector<Contatto> lista = caricaContattiDaFile(nomeFile);
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
// 3. VISUALIZZA TUTTI
// ==========================================
void visualizzaTutti(const string& nomeFile) {
    cout << "\n--- LISTA CONTATTI (" << nomeFile << ") ---" << endl;
    vector<Contatto> lista = caricaContattiDaFile(nomeFile);

    if (lista.empty()) {
        cout << "La rubrica e' vuota o il file non esiste ancora!" << endl;
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
void modificaContatto(const string& nomeFile) {
    string cercaNome, nuovoTelefono;
    cout << "\n--- MODIFICA CONTATTO (" << nomeFile << ") ---" << endl;
    cout << "Inserisci il nome del contatto da modificare: ";
    cin >> cercaNome;
    cout << "Inserisci il nuovo numero di telefono: ";
    cin >> nuovoTelefono;

    string cercaLower = toLowerString(cercaNome);
    vector<Contatto> lista = caricaContattiDaFile(nomeFile);
    bool trovato = false;

    for (auto& c : lista) {
        if (toLowerString(c.nome) == cercaLower) {
            c.telefono = nuovoTelefono;
            trovato = true;
        }
    }

    if (trovato) {
        salvaContattiSuFile(lista, nomeFile);
        cout << "-> Contatto modificato con successo!" << endl;
    } else {
        cout << "-> Nessun contatto trovato con questo nome." << endl;
    }
}

// ==========================================
// 5. ELIMINA CONTATTO
// ==========================================
void eliminaContatto(const string& nomeFile) {
    string cercaNome;
    cout << "\n--- ELIMINA CONTATTO (" << nomeFile << ") ---" << endl;
    cout << "Inserisci il nome del contatto da eliminare: ";
    cin >> cercaNome;

    string cercaLower = toLowerString(cercaNome);
    vector<Contatto> lista = caricaContattiDaFile(nomeFile);
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
        salvaContattiSuFile(nuovaLista, nomeFile);
        cout << "-> Contatto eliminato con successo!" << endl;
    } else {
        cout << "-> Nessun contatto trovato con questo nome." << endl;
    }
}

// ==========================================
// FUNZIONE PRINCIPALE (MENU COMPLETO)
// ==========================================
int main() {
    int scelta;
    string nomeFile = "rubrica.txt"; // File predefinito iniziale

    do {
        cout << "\n=========================" << endl;
        cout << " FILE ATTIVO: " << nomeFile << endl;
        cout << "=========================" << endl;
        cout << "1. Aggiungi numero" << endl;
        cout << "2. Cerca numero" << endl;
        cout << "3. Visualizza tutti (Ordinati)" << endl;
        cout << "4. Modifica contatto" << endl;
        cout << "5. Elimina contatto" << endl;
        cout << "6. Crea un nuovo file .txt (inserisci titolo)" << endl;
        cout << "7. Seleziona un file esistente" << endl;
        cout << "8. Esci" << endl;
        cout << "Scegli un'opzione: ";
        
        if (!(cin >> scelta)) {
            cout << "\n[ERRORE] Inserisci un numero valido da 1 a 8, non lettere!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            scelta = 0;
            continue;
        }

        switch (scelta) {
            case 1:
                aggiungiContatto(nomeFile);
                break;
            case 2:
                cercaContatto(nomeFile);
                break;
            case 3:
                visualizzaTutti(nomeFile);
                break;
            case 4:
                modificaContatto(nomeFile);
                break;
            case 5:
                eliminaContatto(nomeFile);
                break;
            case 6: {
                // Case 6: Crea un nuovo file .txt specificando il titolo
                string titolo;
                cout << "\n--- CREA NUOVO FILE .TXT ---" << endl;
                cout << "Inserisci il titolo del nuovo file: ";
                cin >> titolo;
                nomeFile = titolo + ".txt";
                // Crea un file vuoto iniziale o lo inizializza
                ofstream nuovoFile(nomeFile);
                nuovoFile.close();
                cout << "-> Creato e attivato con successo il file: " << nomeFile << endl;
                break;
            }
            case 7: {
                // Case 7: Apri/Seleziona un file esistente
                string titoloEsistente;
                cout << "\n--- SELEZIONA FILE ESISTENTE ---" << endl;
                cout << "Inserisci il nome del file .txt da aprire: ";
                cin >> titoloEsistente;
                nomeFile = titoloEsistente + ".txt";
                cout << "-> Ora stai usando il file: " << nomeFile << endl;
                break;
            }
            case 8:
                cout << "Uscita dal programma. A presto!" << endl;
                break;
            default:
                cout << "Scelta non valida! Inserisci un numero tra 1 e 8." << endl;
        }
        
    } while (scelta != 8);

    return 0;
}
