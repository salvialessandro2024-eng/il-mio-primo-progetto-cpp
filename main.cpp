#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Funzione per aggiungere un numero
void aggiungiContatto() {
    string nome, telefono;
    
    cout << "\n--- AGGIUNGI NUMERO ---" << endl;
    cout << "Inserisci il nome: ";
    cin >> nome;
    
    cout << "Inserisci il numero: ";
    cin >> telefono;

    // Apre il file in modalita' di scrittura (aggiunge in fondo)
    ofstream file("rubrica.txt", ios::app);
    
    if (file.is_open()) {
        file << nome << "," << telefono << endl;
        file.close();
        cout << "-> Numero salvato con successo!" << endl;
    } else {
        cout << "Errore nell'apertura del file!" << endl;
    }
}

// Funzione per cercare un numero
void cercaContatto() {
    string cercaNome;
    
    cout << "\n--- CERCA NUMERO ---" << endl;
    cout << "Inserisci il nome da cercare: ";
    cin >> cercaNome;

    // Apre il file in lettura
    ifstream file("rubrica.txt");
    string riga;
    bool trovato = false;

    if (file.is_open()) {
        while (getline(file, riga)) {
            // Cerchiamo la virgola che separa nome e numero
            size_t virgola = riga.find(',');
            
            if (virgola != string::npos) {
                // Estraiamo il nome prima della virgola
                string nome = riga.substr(0, virgola);
                // Estraiamo il telefono dopo la virgola
                string tel = riga.substr(virgola + 1);
                
                // Confrontiamo se il nome nel file è uguale a quello cercato
                if (nome == cercaNome) {
                    cout << "Trovato! -> Nome: " << nome << " | Tel: " << tel << endl;
                    trovato = true;
                }
            }
        }
        file.close();

        if (!trovato) {
            cout << "Nessun contatto trovato con questo nome." << endl;
        }
    } else {
        cout << "Nessun contatto salvato finora." << endl;
    }
}

int main() {
    int scelta;

    do {
        cout << "\n=========================" << endl;
        cout << "   LA MIA RUBRICA C++    " << endl;
        cout << "=========================" << endl;
        cout << "1. Aggiungi numero" << endl;
        cout << "2. Cerca numero" << endl;
        cout << "3. Esci" << endl;
        cout << "Scegli un'opzione: ";
        
        cin >> scelta;

        // Gestione del menu con lo switch
        switch (scelta) {
            case 1:
                aggiungiContatto();
                break;
            case 2:
                cercaContatto();
                break;
            case 3:
                cout << "Uscita dal programma. Ciao!" << endl;
                break;
            default:
                cout << "Scelta non valida! Inserisci 1, 2 o 3." << endl;
        }
        
    } while (scelta != 3);

    return 0;
}
