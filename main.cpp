// ==========================================
// PROGETTO: RUBRICA TELEFONICA IN C++
// Versione ottimizzata con gestione file,
// ricerca esatta, modifica ed eliminazione.
// ==========================================

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> // Libreria standard C per le funzioni remove() e rename()

using namespace std;

// ==========================================
// 1. FUNZIONE: AGGIUNGI CONTATTO
// ==========================================
void aggiungiContatto() {
    string nome, telefono;
    
    cout << "\n--- AGGIUNGI NUMERO ---" << endl;
    cout << "Inserisci il nome: ";
    cin >> nome;
    cout << "Inserisci il numero: ";
    cin >> telefono;

    // 'ofstream' apre il file in scrittura. 
    // 'ios::app' (append) aggiunge il nuovo contatto in fondo SENZA cancellare i precedenti.
    ofstream file("rubrica.txt", ios::app);
    
    if (file.is_open()) {
        // Scriviamo nel formato "Nome,Telefono" separati da una virgola
        file << nome << "," << telefono << endl;
        file.close(); // Chiusura fondamentale per liberare il file
        cout << "-> Numero salvato con successo!" << endl;
    } else {
        cout << "ERRORE: Impossibile aprire il file in scrittura!" << endl;
    }
}

// ==========================================
// 2. FUNZIONE: CERCA CONTATTO
// ==========================================
void cercaContatto() {
    string cercaNome;
    
    cout << "\n--- CERCA NUMERO ---" << endl;
    cout << "Inserisci il nome da cercare: ";
    cin >> cercaNome;

    // 'ifstream' apre il file in sola lettura
    ifstream file("rubrica.txt");
    string riga;
    bool trovato = false;

    if (file.is_open()) {
        // Leggiamo il file riga per riga
        while (getline(file, riga)) {
            // Cerchiamo la posizione della virgola che separa nome e numero
            size_t virgola = riga.find(',');
            
            if (virgola != string::npos) {
                // Estraiamo il nome (da inizio riga fino alla virgola)
                string nome = riga.substr(0, virgola);
                // Estraiamo il telefono (dopo la virgola fino alla fine)
                string tel = riga.substr(virgola + 1);
                
                // Controllo esatto: se il nome coincide perfettamente
                if (nome == cercaNome) {
                    cout << "Trovato! -> Nome: " << nome << " | Tel: " << tel << endl;
                    trovato = true;
                }
            }
        }
        file.close(); // Chiusura del file

        if (!trovato) {
            cout << "-> Nessun contatto trovato con questo nome." << endl;
        }
    } else {
        cout << "-> La rubrica e' vuota o il file non esiste ancora." << endl;
    }
}

// ==========================================
// 3. FUNZIONE: MODIFICA CONTATTO
// ==========================================
void modificaContatto() {
    string cercaNome, nuovoTelefono;
    
    cout << "\n--- MODIFICA CONTATTO ---" << endl;
    cout << "Inserisci il nome del contatto da modificare: ";
    cin >> cercaNome;
    cout << "Inserisci il nuovo numero di telefono: ";
    cin >> nuovoTelefono;

    // TRUCCO DEI FILE: Apriamo il file originale in lettura e un file temporaneo in scrittura
    ifstream file("rubrica.txt");
    ofstream temp("temp.txt"); 
    bool trovato = false;
    string riga;

    if (file.is_open() && temp.is_open()) {
        while (getline(file, riga)) {
            size_t virgola = riga.find(',');
            if (virgola != string::npos) {
                string nome = riga.substr(0, virgola);
                
                if (nome == cercaNome) {
                    // Se è il contatto da modificare, scriviamo sul file temp i dati aggiornati
                    temp << nome << "," << nuovoTelefono << endl;
                    trovato = true;
                } else {
                    // Per tutti gli altri contatti, ricopiamo la riga originale intatta
                    temp << riga << endl;
                }
            }
        }
        
        // Chiudiamo entrambi i file prima di manipolarli a livello di sistema operativo
        file.close();
        temp.close();

        // Sostituzione del file vecchio con quello nuovo aggiornato
        remove("rubrica.txt");              // Elimina il file vecchio
        rename("temp.txt", "rubrica.txt");  // Rinomina il temp nel nome ufficiale

        if (trovato) {
            cout << "-> Contatto modificato con successo!" << endl;
        } else {
            cout << "-> Nessun contatto trovato con questo nome." << endl;
        }
    } else {
        cout << "ERRORE nell'apertura dei file!" << endl;
    }
}

// ==========================================
// 4. FUNZIONE: ELIMINA CONTATTO
// ==========================================
void eliminaContatto() {
    string cercaNome;
    
    cout << "\n--- ELIMINA CONTATTO ---" << endl;
    cout << "Inserisci il nome del contatto da eliminare: ";
    cin >> cercaNome;

    // Anche qui usiamo il file temporaneo di appoggio
    ifstream file("rubrica.txt");
    ofstream temp("temp.txt");
    bool trovato = false;
    string riga;

    if (file.is_open() && temp.is_open()) {
        while (getline(file, riga)) {
            size_t virgola = riga.find(',');
            if (virgola != string::npos) {
                string nome = riga.substr(0, virgola);
                
                if (nome == cercaNome) {
                    // SE è il contatto da eliminare, NON lo scriviamo nel file temporaneo (lo saltiamo)
                    trovato = true;
                } else {
                    // Tutti gli altri contatti vengono salvati normalmente
                    temp << riga << endl;
                }
            }
        }
        
        file.close();
        temp.close();

        // Sostituiamo il file originale con quello ripulito
        remove("rubrica.txt");
        rename("temp.txt", "rubrica.txt");

        if (trovato) {
            cout << "-> Contatto eliminato con successo!" << endl;
        } else {
            cout << "-> Nessun contatto trovato con questo nome." << endl;
        }
    } else {
        cout << "ERRORE nell'apertura dei file!" << endl;
    }
}

// ==========================================
// FUNZIONE PRINCIPALE (MENU CON SWITCH)
// ==========================================
int main() {
    int scelta;

    // Il ciclo do-while ripete il menu finché l'utente non sceglie di uscire (opzione 5)
    do {
        cout << "\n=========================" << endl;
        cout << "   LA MIA RUBRICA C++    " << endl;
        cout << "=========================" << endl;
        cout << "1. Aggiungi numero" << endl;
        cout << "2. Cerca numero" << endl;
        cout << "3. Modifica contatto" << endl;
        cout << "4. Elimina contatto" << endl;
        cout << "5. Esci" << endl;
        cout << "Scegli un'opzione: ";
        
        cin >> scelta;

        // Gestione delle scelte tramite switch-case pulito e ordinato
        switch (scelta) {
            case 1:
                aggiungiContatto();
                break;
            case 2:
                cercaContatto();
                break;
            case 3:
                modificaContatto();
                break;
            case 4:
                eliminaContatto();
                break;
            case 5:
                cout << "Uscita dal programma. A presto!" << endl;
                break;
            default:
                // Scatta se l'utente inserisce un numero non previsto nel menu
                cout << "Scelta non valida! Inserisci un numero da 1 a 5." << endl;
        }
        
    } while (scelta != 5);

    return 0; // Termine pulito del programma
}
