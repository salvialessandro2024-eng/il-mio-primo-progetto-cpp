// ==========================================
// PROGETTO: RUBRICA TELEFONICA IN C++ (Con Ordine Alfabetico)
// ==========================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>     // Necessario per usare i vettori (liste dinamiche)
#include <algorithm>  // Necessario per usare la funzione sort()
#include <cstdio>     // Per remove() e rename()

using namespace std;

// Definiamo una STRUTTURA (struct) per raggruppare nome e telefono di un contatto
struct Contatto {
    string nome;
    string telefono;
};

// Funzione di supporto per ordinare alfabeticamente i contatti in base al nome
bool confrontaContatti(const Contatto& a, const Contatto& b) {
    return a.nome < b.nome; // Restituisce vero se il nome 'a' viene prima di 'b' nell'alfabeto
}

// Funzione di supporto per caricare tutti i contatti dal file a un vettore in memoria
vector<Contatto> caricaContattiDaFile() {
    vector<Contatto> lista;
    ifstream file("rubrica.txt");
    string riga;

    if (file.is_open()) {
        while (getline(file, riga)) {
            size_t virgola = riga.find(',');
            if (virgola != string::npos) {
                Contatto c;
                c.nome = riga.substr(0, virgola);
                c.telefono = riga.substr(virgola + 1);
                lista.push_back(c); // Aggiunge il contatto alla lista
            }
        }
        file.close();
    }
    return lista;
}

// Funzione di supporto per salvare e ordinare la lista sul file
void salvaContattiSuFile(vector<Contatto>& lista) {
    // Prima di salvare, ordiniamo la lista alfabeticamente!
    sort(lista.begin(), lista.end(), confrontaContatti);

    ofstream file("rubrica.txt"); // Apre in scrittura (sovrascrive ordinato)
    if (file.is_open()) {
        for (const auto& c : lista) {
            file << c.nome << "," << c.telefono << endl;
        }
        file.close();
    }
}

// ==========================================
// 1. AGGIUNGI CONTATTO (Già ordinato)
// ==========================================
void aggiungiContatto() {
    Contatto nuovo;
    cout << "\n--- AGGIUNGI NUMERO ---" << endl;
    cout << "Inserisci il nome: ";
    cin >> nuovo.nome;
    cout << "Inserisci il numero: ";
    cin >> nuovo.telefono;

    // Carichiamo la lista attuale, aggiungiamo il nuovo, ordiniamo e salviamo
    vector<Contatto> lista = caricaContattiDaFile();
    lista.push_back(nuovo);
    salvaContattiSuFile(lista);

    cout << "-> Numero salvato e rubrica ordinata con successo!" << endl;
}

// ==========================================
// 2. CERCA CONTATTO
// ==========================================
void cercaContatto() {
    string cercaNome;
    cout << "\n--- CERCA NUMERO ---" << endl;
    cout << "Inserisci il nome da cercare: ";
    cin >> cercaNome;

    vector<Contatto> lista = caricaContattiDaFile();
    bool trovato = false;

    for (const auto& c : lista) {
        if (c.nome == cercaNome) {
            cout << "Trovato! -> Nome: " << c.nome << " | Tel: " << c.telefono << endl;
            trovato = true;
        }
    }

    if (!trovato) {
        cout << "-> Nessun contatto trovato con questo nome." << endl;
    }
}

// ==========================================
// 3. VISUALIZZA TUTTI (In ordine alfabetico)
// ==========================================
void visualizzaTutti() {
    cout << "\n--- LISTA CONTATTI (ORDINATA) ---" << endl;
    vector<Contatto> lista = caricaContattiDaFile();

    if (lista.empty()) {
        cout << "La rubrica e' vuota!" << endl;
        return;
    }

    for (size_t i = 0; i < lista.size(); i++) {
        cout << i + 1 << ". " << lista[i].nome << " -> " << lista[i].telefono << endl;
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

    vector<Contatto> lista = caricaContattiDaFile();
    bool trovato = false;

    for (auto& c : lista) {
        if (c.nome == cercaNome) {
            c.telefono = nuovoTelefono;
            trovato = true;
        }
    }

    if (trovato) {
        salvaContattiSuFile(lista); // Salva e riordina
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

    vector<Contatto> lista = caricaContattiDaFile();
    vector<Contatto> nuovaLista; // Lista di appoggio senza quello eliminato
    bool trovato = false;

    for (const auto& c : lista) {
        if (c.nome == cercaNome) {
            trovato = true; // Lo saltiamo (quindi viene eliminato)
        } else {
            nuovaLista.push_back(c);
        }
    }

    if (trovato) {
        salvaContattiSuFile(nuovaLista); // Salva la lista ripulita (rimane ordinata)
        cout << "-> Contatto eliminato con successo!" << endl;
    } else {
        cout << "-> Nessun contatto trovato con questo nome." << endl;
    }
}

// ==========================================
// FUNZIONE PRINCIPALE (MENU)
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
        
        cin >> scelta;

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
                cout << "Uscita dal programma. Ciao!" << endl;
                break;
            default:
                cout << "Scelta non valida! Inserisci un numero da 1 a 6." << endl;
        }
        
    } while (scelta != 6);

    return 0;
}
