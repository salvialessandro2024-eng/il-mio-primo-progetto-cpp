// Includiamo la libreria standard per gestire l'input (cin) e l'output (cout) a schermo
#include <iostream>

// Includiamo la libreria 'fstream' che serve per creare, scrivere e leggere i file sul PC
#include <fstream>

// Includiamo la libreria 'string' per poter usare le parole e i testi
#include <string>

// Usiamo lo spazio dei nomi standard per evitare di scrivere sempre std:: prima di cout o cin
using namespace std;

// ==========================================
// FUNZIONE 1: Aggiunge un numero e lo salva sul PC
// ==========================================
void aggiungiContatto() {
    // Dichiariamo due variabili di tipo stringa per memorizzare nome e telefono inseriti dall'utente
    string nome, telefono;
    
    cout << "\n--- AGGIUNGI NUMERO ---" << endl;
    cout << "Inserisci il nome: ";
    cin >> nome; // Legge il nome da tastiera
    
    cout << "Inserisci il numero: ";
    cin >> telefono; // Legge il numero da tastiera

    // 'ofstream' serve per aprire un file in SCRITTURA. 
    // "rubrica.txt" è il nome del file che verrà creato sul computer.
    // 'ios::app' (append) è fondamentale: dice a C++ di aggiungere il nuovo contatto 
    // in fondo al file SENZA cancellare quelli vecchi che avevamo salvato prima!
    ofstream file("rubrica.txt", ios::app);

    // Controlliamo se il file si è aperto correttamente sul PC
    if (file.is_open()) {
        // Scriviamo nel file il nome e il telefono separati da una virgola (es: "Mario,3331234567")
        file << nome << "," << telefono << endl;
        
        // Chiudiamo il file per liberare la memoria del computer (buona abitudine)
        file.close();
        
        cout << "-> Numero salvato con successo sul tuo PC!" << endl;
    } else {
        // Se c'è un problema (es. disco pieno o permessi negati), avvisiamo l'utente
        cout << "Errore nell'apertura del file!" << endl;
    }
}

// ==========================================
// FUNZIONE 2: Cerca un numero salvato nel file
// ==========================================
void cercaContatto() {
    // Variabile per memorizzare il nome che l'utente vuole cercare
    string cercaNome;
    
    cout << "\n--- CERCA NUMERO ---" << endl;
    cout << "Inserisci il nome da cercare: ";
    cin >> cercaNome;

    // 'ifstream' serve per aprire un file in LETTURA (leggiamo dal PC)
    ifstream file("rubrica.txt");
    
    // Variabile che conterrà una riga alla volta del file
    string riga;
    
    // Un interruttore (flag) per ricordarci se abbiamo trovato il contatto o no
    bool trovato = false;

    // Verifichiamo che il file esista e si apra correttamente
    if (file.is_open()) {
        // Leggiamo il file riga per riga finché ci sono dati dentro (grazie a getline)
        while (getline(file, riga)) {
            
            // riga.find() cerca se all'interno della riga c'è il nome cercato.
            // string::npos significa "se la ricerca ha dato esito positivo".
            if (riga.find(cercaNome) != string::npos) {
                
                // Troviamo la posizione della virgola che divide nome e telefono
                size_t virgola = riga.find(',');
                
                if (virgola != string::npos) {
                    // Estraiamo il nome (da inizio riga fino alla virgola)
                    string nome = riga.substr(0, virgola);
                    // Estraiamo il telefono (dopo la virgola fino alla fine)
                    string tel = riga.substr(virgola + 1);
                    
                    // Stampiamo a schermo il risultato in modo bello e pulito
                    cout << "Trovato! -> Nome: " << nome << " | Tel: " << tel << endl;
                }
                // Segnamo che abbiamo trovato almeno un contatto corrispondente
                trovato = true;
            }
        }
        
        // Chiudiamo il file dopo aver finito la lettura
        file.close();

        // Se dopo aver letto tutto il file non abbiamo trovato nulla, avvisiamo l'utente
        if (!trovato) {
            cout << "Nessun contatto trovato con questo nome." << endl;
        }
        
    } else {
        // Se il file non esiste ancora (perché non è stato aggiunto nessun numero), lo segnaliamo
        cout << "La rubrica e' vuota o il file non esiste. Aggiungi prima un numero!" << endl;
    }
}

// ==========================================
// FUNZIONE PRINCIPALE (MAIN)
// ==========================================
int main() {
    // Variabile numerica per memorizzare la scelta del menu fatta dall'utente
    int scelta;

    // Usiamo un ciclo 'do-while': il blocco viene eseguito almeno una volta 
    // e si ripete finché l'utente non decide di uscire (premendo 3)
    do {
        // Mostriamo il menu a schermo
        cout << "\n=========================" << endl;
        cout << "   LA MIA RUBRICA C++    " << endl;
        cout << "=========================" << endl;
        cout << "1. Aggiungi numero" << endl;
        cout << "2. Cerca numero" << endl;
        cout << "3. Esci" << endl;
        cout << "Scegli un'opzione: ";
        
        // Leggiamo il numero scelto dall'utente
        cin >> scelta;

        // Struttura condizionale 'switch' per indirizzare l'utente in base alla sua scelta
        switch (scelta) {
            case 1:
                // Se l'utente preme 1, richiamiamo la funzione per aggiungere il contatto
                aggiungiContatto();
                break; // 'break' interrompe lo switch e non fa eseguire gli altri casi
                
            case 2:
                // Se l'utente preme 2, richiamiamo la funzione per cercare
                cercaContatto();
                break;
                
            case 3:
                // Se l'utente preme 3, usciamo dal programma
                cout << "Uscita dal programma. Ciao!" << endl;
                break;
                
            default:
                // 'default' scatta se l'utente inserisce un numero diverso da 1, 2 o 3 (es. 8 o 99)
                cout << "Scelta non valida! Usa 1 per aggiungere o 2 per cercare." << endl;
        }
        
    } while (scelta != 3); // Il ciclo continua finché la scelta è diversa da 3

    // Restituisce 0 per indicare che il programma è terminato senza errori
    return 0;
}// Includiamo la libreria standard per gestire l'input (cin) e l'output (cout) a schermo
#include <iostream>

// Includiamo la libreria 'fstream' che serve per creare, scrivere e leggere i file sul PC
#include <fstream>

// Includiamo la libreria 'string' per poter usare le parole e i testi
#include <string>

// Usiamo lo spazio dei nomi standard per evitare di scrivere sempre std:: prima di cout o cin
using namespace std;

// ==========================================
// FUNZIONE 1: Aggiunge un numero e lo salva sul PC
// ==========================================
void aggiungiContatto() {
    // Dichiariamo due variabili di tipo stringa per memorizzare nome e telefono inseriti dall'utente
    string nome, telefono;
    
    cout << "\n--- AGGIUNGI NUMERO ---" << endl;
    cout << "Inserisci il nome: ";
    cin >> nome; // Legge il nome da tastiera
    
    cout << "Inserisci il numero: ";
    cin >> telefono; // Legge il numero da tastiera

    // 'ofstream' serve per aprire un file in SCRITTURA. 
    // "rubrica.txt" è il nome del file che verrà creato sul computer.
    // 'ios::app' (append) è fondamentale: dice a C++ di aggiungere il nuovo contatto 
    // in fondo al file SENZA cancellare quelli vecchi che avevamo salvato prima!
    ofstream file("rubrica.txt", ios::app);

    // Controlliamo se il file si è aperto correttamente sul PC
    if (file.is_open()) {
        // Scriviamo nel file il nome e il telefono separati da una virgola (es: "Mario,3331234567")
        file << nome << "," << telefono << endl;
        
        // Chiudiamo il file per liberare la memoria del computer (buona abitudine)
        file.close();
        
        cout << "-> Numero salvato con successo sul tuo PC!" << endl;
    } else {
        // Se c'è un problema (es. disco pieno o permessi negati), avvisiamo l'utente
        cout << "Errore nell'apertura del file!" << endl;
    }
}

// ==========================================
// FUNZIONE 2: Cerca un numero salvato nel file
// ==========================================
void cercaContatto() {
    // Variabile per memorizzare il nome che l'utente vuole cercare
    string cercaNome;
    
    cout << "\n--- CERCA NUMERO ---" << endl;
    cout << "Inserisci il nome da cercare: ";
    cin >> cercaNome;

    // 'ifstream' serve per aprire un file in LETTURA (leggiamo dal PC)
    ifstream file("rubrica.txt");
    
    // Variabile che conterrà una riga alla volta del file
    string riga;
    
    // Un interruttore (flag) per ricordarci se abbiamo trovato il contatto o no
    bool trovato = false;

    // Verifichiamo che il file esista e si apra correttamente
    if (file.is_open()) {
        // Leggiamo il file riga per riga finché ci sono dati dentro (grazie a getline)
        while (getline(file, riga)) {
            
            // riga.find() cerca se all'interno della riga c'è il nome cercato.
            // string::npos significa "se la ricerca ha dato esito positivo".
            if (riga.find(cercaNome) != string::npos) {
                
                // Troviamo la posizione della virgola che divide nome e telefono
                size_t virgola = riga.find(',');
                
                if (virgola != string::npos) {
                    // Estraiamo il nome (da inizio riga fino alla virgola)
                    string nome = riga.substr(0, virgola);
                    // Estraiamo il telefono (dopo la virgola fino alla fine)
                    string tel = riga.substr(virgola + 1);
                    
                    // Stampiamo a schermo il risultato in modo bello e pulito
                    cout << "Trovato! -> Nome: " << nome << " | Tel: " << tel << endl;
                }
                // Segnamo che abbiamo trovato almeno un contatto corrispondente
                trovato = true;
            }
        }
        
        // Chiudiamo il file dopo aver finito la lettura
        file.close();

        // Se dopo aver letto tutto il file non abbiamo trovato nulla, avvisiamo l'utente
        if (!trovato) {
            cout << "Nessun contatto trovato con questo nome." << endl;
        }
        
    } else {
        // Se il file non esiste ancora (perché non è stato aggiunto nessun numero), lo segnaliamo
        cout << "La rubrica e' vuota o il file non esiste. Aggiungi prima un numero!" << endl;
    }
}

// ==========================================
// FUNZIONE PRINCIPALE (MAIN)
// ==========================================
int main() {
    // Variabile numerica per memorizzare la scelta del menu fatta dall'utente
    int scelta;

    // Usiamo un ciclo 'do-while': il blocco viene eseguito almeno una volta 
    // e si ripete finché l'utente non decide di uscire (premendo 3)
    do {
        // Mostriamo il menu a schermo
        cout << "\n=========================" << endl;
        cout << "   LA MIA RUBRICA C++    " << endl;
        cout << "=========================" << endl;
        cout << "1. Aggiungi numero" << endl;
        cout << "2. Cerca numero" << endl;
        cout << "3. Esci" << endl;
        cout << "Scegli un'opzione: ";
        
        // Leggiamo il numero scelto dall'utente
        cin >> scelta;

        // Struttura condizionale 'switch' per indirizzare l'utente in base alla sua scelta
        switch (scelta) {
            case 1:
                // Se l'utente preme 1, richiamiamo la funzione per aggiungere il contatto
                aggiungiContatto();
                break; // 'break' interrompe lo switch e non fa eseguire gli altri casi
                
            case 2:
                // Se l'utente preme 2, richiamiamo la funzione per cercare
                cercaContatto();
                break;
                
            case 3:
                // Se l'utente preme 3, usciamo dal programma
                cout << "Uscita dal programma. Ciao!" << endl;
                break;
                
            default:
                // 'default' scatta se l'utente inserisce un numero diverso da 1, 2 o 3 (es. 8 o 99)
                cout << "Scelta non valida! Usa 1 per aggiungere o 2 per cercare." << endl;
        }
        
    } while (scelta != 3); // Il ciclo continua finché la scelta è diversa da 3

    // Restituisce 0 per indicare che il programma è terminato senza errori
    return 0;
}// Includiamo la libreria standard per gestire l'input (cin) e l'output (cout) a schermo
#include <iostream>

// Includiamo la libreria 'fstream' che serve per creare, scrivere e leggere i file sul PC
#include <fstream>

// Includiamo la libreria 'string' per poter usare le parole e i testi
#include <string>

// Usiamo lo spazio dei nomi standard per evitare di scrivere sempre std:: prima di cout o cin
using namespace std;

// ==========================================
// FUNZIONE 1: Aggiunge un numero e lo salva sul PC
// ==========================================
void aggiungiContatto() {
    // Dichiariamo due variabili di tipo stringa per memorizzare nome e telefono inseriti dall'utente
    string nome, telefono;
    
    cout << "\n--- AGGIUNGI NUMERO ---" << endl;
    cout << "Inserisci il nome: ";
    cin >> nome; // Legge il nome da tastiera
    
    cout << "Inserisci il numero: ";
    cin >> telefono; // Legge il numero da tastiera

    // 'ofstream' serve per aprire un file in SCRITTURA. 
    // "rubrica.txt" è il nome del file che verrà creato sul computer.
    // 'ios::app' (append) è fondamentale: dice a C++ di aggiungere il nuovo contatto 
    // in fondo al file SENZA cancellare quelli vecchi che avevamo salvato prima!
    ofstream file("rubrica.txt", ios::app);

    // Controlliamo se il file si è aperto correttamente sul PC
    if (file.is_open()) {
        // Scriviamo nel file il nome e il telefono separati da una virgola (es: "Mario,3331234567")
        file << nome << "," << telefono << endl;
        
        // Chiudiamo il file per liberare la memoria del computer (buona abitudine)
        file.close();
        
        cout << "-> Numero salvato con successo sul tuo PC!" << endl;
    } else {
        // Se c'è un problema (es. disco pieno o permessi negati), avvisiamo l'utente
        cout << "Errore nell'apertura del file!" << endl;
    }
}

// ==========================================
// FUNZIONE 2: Cerca un numero salvato nel file
// ==========================================
void cercaContatto() {
    // Variabile per memorizzare il nome che l'utente vuole cercare
    string cercaNome;
    
    cout << "\n--- CERCA NUMERO ---" << endl;
    cout << "Inserisci il nome da cercare: ";
    cin >> cercaNome;

    // 'ifstream' serve per aprire un file in LETTURA (leggiamo dal PC)
    ifstream file("rubrica.txt");
    
    // Variabile che conterrà una riga alla volta del file
    string riga;
    
    // Un interruttore (flag) per ricordarci se abbiamo trovato il contatto o no
    bool trovato = false;

    // Verifichiamo che il file esista e si apra correttamente
    if (file.is_open()) {
        // Leggiamo il file riga per riga finché ci sono dati dentro (grazie a getline)
        while (getline(file, riga)) {
            
            // riga.find() cerca se all'interno della riga c'è il nome cercato.
            // string::npos significa "se la ricerca ha dato esito positivo".
            if (riga.find(cercaNome) != string::npos) {
                
                // Troviamo la posizione della virgola che divide nome e telefono
                size_t virgola = riga.find(',');
                
                if (virgola != string::npos) {
                    // Estraiamo il nome (da inizio riga fino alla virgola)
                    string nome = riga.substr(0, virgola);
                    // Estraiamo il telefono (dopo la virgola fino alla fine)
                    string tel = riga.substr(virgola + 1);
                    
                    // Stampiamo a schermo il risultato in modo bello e pulito
                    cout << "Trovato! -> Nome: " << nome << " | Tel: " << tel << endl;
                }
                // Segnamo che abbiamo trovato almeno un contatto corrispondente
                trovato = true;
            }
        }
        
        // Chiudiamo il file dopo aver finito la lettura
        file.close();

        // Se dopo aver letto tutto il file non abbiamo trovato nulla, avvisiamo l'utente
        if (!trovato) {
            cout << "Nessun contatto trovato con questo nome." << endl;
        }
        
    } else {
        // Se il file non esiste ancora (perché non è stato aggiunto nessun numero), lo segnaliamo
        cout << "La rubrica e' vuota o il file non esiste. Aggiungi prima un numero!" << endl;
    }
}

// ==========================================
// FUNZIONE PRINCIPALE (MAIN)
// ==========================================
int main() {
    // Variabile numerica per memorizzare la scelta del menu fatta dall'utente
    int scelta;

    // Usiamo un ciclo 'do-while': il blocco viene eseguito almeno una volta 
    // e si ripete finché l'utente non decide di uscire (premendo 3)
    do {
        // Mostriamo il menu a schermo
        cout << "\n=========================" << endl;
        cout << "   LA MIA RUBRICA C++    " << endl;
        cout << "=========================" << endl;
        cout << "1. Aggiungi numero" << endl;
        cout << "2. Cerca numero" << endl;
        cout << "3. Esci" << endl;
        cout << "Scegli un'opzione: ";
        
        // Leggiamo il numero scelto dall'utente
        cin >> scelta;

        // Struttura condizionale 'switch' per indirizzare l'utente in base alla sua scelta
        switch (scelta) {
            case 1:
                // Se l'utente preme 1, richiamiamo la funzione per aggiungere il contatto
                aggiungiContatto();
                break; // 'break' interrompe lo switch e non fa eseguire gli altri casi
                
            case 2:
                // Se l'utente preme 2, richiamiamo la funzione per cercare
                cercaContatto();
                break;
                
            case 3:
                // Se l'utente preme 3, usciamo dal programma
                cout << "Uscita dal programma. Ciao!" << endl;
                break;
                
            default:
                // 'default' scatta se l'utente inserisce un numero diverso da 1, 2 o 3 (es. 8 o 99)
                cout << "Scelta non valida! Usa 1 per aggiungere o 2 per cercare." << endl;
        }
        
    } while (scelta != 3); // Il ciclo continua finché la scelta è diversa da 3

    // Restituisce 0 per indicare che il programma è terminato senza errori
    return 0;
}// Includiamo la libreria standard per gestire l'input (cin) e l'output (cout) a schermo
#include <iostream>

// Includiamo la libreria 'fstream' che serve per creare, scrivere e leggere i file sul PC
#include <fstream>

// Includiamo la libreria 'string' per poter usare le parole e i testi
#include <string>

// Usiamo lo spazio dei nomi standard per evitare di scrivere sempre std:: prima di cout o cin
using namespace std;

// ==========================================
// FUNZIONE 1: Aggiunge un numero e lo salva sul PC
// ==========================================
void aggiungiContatto() {
    // Dichiariamo due variabili di tipo stringa per memorizzare nome e telefono inseriti dall'utente
    string nome, telefono;
    
    cout << "\n--- AGGIUNGI NUMERO ---" << endl;
    cout << "Inserisci il nome: ";
    cin >> nome; // Legge il nome da tastiera
    
    cout << "Inserisci il numero: ";
    cin >> telefono; // Legge il numero da tastiera

    // 'ofstream' serve per aprire un file in SCRITTURA. 
    // "rubrica.txt" è il nome del file che verrà creato sul computer.
    // 'ios::app' (append) è fondamentale: dice a C++ di aggiungere il nuovo contatto 
    // in fondo al file SENZA cancellare quelli vecchi che avevamo salvato prima!
    ofstream file("rubrica.txt", ios::app);

    // Controlliamo se il file si è aperto correttamente sul PC
    if (file.is_open()) {
        // Scriviamo nel file il nome e il telefono separati da una virgola (es: "Mario,3331234567")
        file << nome << "," << telefono << endl;
        
        // Chiudiamo il file per liberare la memoria del computer (buona abitudine)
        file.close();
        
        cout << "-> Numero salvato con successo sul tuo PC!" << endl;
    } else {
        // Se c'è un problema (es. disco pieno o permessi negati), avvisiamo l'utente
        cout << "Errore nell'apertura del file!" << endl;
    }
}

// ==========================================
// FUNZIONE 2: Cerca un numero salvato nel file
// ==========================================
void cercaContatto() {
    // Variabile per memorizzare il nome che l'utente vuole cercare
    string cercaNome;
    
    cout << "\n--- CERCA NUMERO ---" << endl;
    cout << "Inserisci il nome da cercare: ";
    cin >> cercaNome;

    // 'ifstream' serve per aprire un file in LETTURA (leggiamo dal PC)
    ifstream file("rubrica.txt");
    
    // Variabile che conterrà una riga alla volta del file
    string riga;
    
    // Un interruttore (flag) per ricordarci se abbiamo trovato il contatto o no
    bool trovato = false;

    // Verifichiamo che il file esista e si apra correttamente
    if (file.is_open()) {
        // Leggiamo il file riga per riga finché ci sono dati dentro (grazie a getline)
        while (getline(file, riga)) {
            
            // riga.find() cerca se all'interno della riga c'è il nome cercato.
            // string::npos significa "se la ricerca ha dato esito positivo".
            if (riga.find(cercaNome) != string::npos) {
                
                // Troviamo la posizione della virgola che divide nome e telefono
                size_t virgola = riga.find(',');
                
                if (virgola != string::npos) {
                    // Estraiamo il nome (da inizio riga fino alla virgola)
                    string nome = riga.substr(0, virgola);
                    // Estraiamo il telefono (dopo la virgola fino alla fine)
                    string tel = riga.substr(virgola + 1);
                    
                    // Stampiamo a schermo il risultato in modo bello e pulito
                    cout << "Trovato! -> Nome: " << nome << " | Tel: " << tel << endl;
                }
                // Segnamo che abbiamo trovato almeno un contatto corrispondente
                trovato = true;
            }
        }
        
        // Chiudiamo il file dopo aver finito la lettura
        file.close();

        // Se dopo aver letto tutto il file non abbiamo trovato nulla, avvisiamo l'utente
        if (!trovato) {
            cout << "Nessun contatto trovato con questo nome." << endl;
        }
        
    } else {
        // Se il file non esiste ancora (perché non è stato aggiunto nessun numero), lo segnaliamo
        cout << "La rubrica e' vuota o il file non esiste. Aggiungi prima un numero!" << endl;
    }
}

// ==========================================
// FUNZIONE PRINCIPALE (MAIN)
// ==========================================
int main() {
    // Variabile numerica per memorizzare la scelta del menu fatta dall'utente
    int scelta;

    // Usiamo un ciclo 'do-while': il blocco viene eseguito almeno una volta 
    // e si ripete finché l'utente non decide di uscire (premendo 3)
    do {
        // Mostriamo il menu a schermo
        cout << "\n=========================" << endl;
        cout << "   LA MIA RUBRICA C++    " << endl;
        cout << "=========================" << endl;
        cout << "1. Aggiungi numero" << endl;
        cout << "2. Cerca numero" << endl;
        cout << "3. Esci" << endl;
        cout << "Scegli un'opzione: ";
        
        // Leggiamo il numero scelto dall'utente
        cin >> scelta;

        // Struttura condizionale 'switch' per indirizzare l'utente in base alla sua scelta
        switch (scelta) {
            case 1:
                // Se l'utente preme 1, richiamiamo la funzione per aggiungere il contatto
                aggiungiContatto();
                break; // 'break' interrompe lo switch e non fa eseguire gli altri casi
                
            case 2:
                // Se l'utente preme 2, richiamiamo la funzione per cercare
                cercaContatto();
                break;
                
            case 3:
                // Se l'utente preme 3, usciamo dal programma
                cout << "Uscita dal programma. Ciao!" << endl;
                break;
                
            default:
                // 'default' scatta se l'utente inserisce un numero diverso da 1, 2 o 3 (es. 8 o 99)
                cout << "Scelta non valida! Usa 1 per aggiungere o 2 per cercare." << endl;
        }
        
    } while (scelta != 3); // Il ciclo continua finché la scelta è diversa da 3

    // Restituisce 0 per indicare che il programma è terminato senza errori
    return 0;
}// Includiamo la libreria standard per gestire l'input (cin) e l'output (cout) a schermo
#include <iostream>

// Includiamo la libreria 'fstream' che serve per creare, scrivere e leggere i file sul PC
#include <fstream>

// Includiamo la libreria 'string' per poter usare le parole e i testi
#include <string>

// Usiamo lo spazio dei nomi standard per evitare di scrivere sempre std:: prima di cout o cin
using namespace std;

// ==========================================
// FUNZIONE 1: Aggiunge un numero e lo salva sul PC
// ==========================================
void aggiungiContatto() {
    // Dichiariamo due variabili di tipo stringa per memorizzare nome e telefono inseriti dall'utente
    string nome, telefono;
    
    cout << "\n--- AGGIUNGI NUMERO ---" << endl;
    cout << "Inserisci il nome: ";
    cin >> nome; // Legge il nome da tastiera
    
    cout << "Inserisci il numero: ";
    cin >> telefono; // Legge il numero da tastiera

    // 'ofstream' serve per aprire un file in SCRITTURA. 
    // "rubrica.txt" è il nome del file che verrà creato sul computer.
    // 'ios::app' (append) è fondamentale: dice a C++ di aggiungere il nuovo contatto 
    // in fondo al file SENZA cancellare quelli vecchi che avevamo salvato prima!
    ofstream file("rubrica.txt", ios::app);

    // Controlliamo se il file si è aperto correttamente sul PC
    if (file.is_open()) {
        // Scriviamo nel file il nome e il telefono separati da una virgola (es: "Mario,3331234567")
        file << nome << "," << telefono << endl;
        
        // Chiudiamo il file per liberare la memoria del computer (buona abitudine)
        file.close();
        
        cout << "-> Numero salvato con successo sul tuo PC!" << endl;
    } else {
        // Se c'è un problema (es. disco pieno o permessi negati), avvisiamo l'utente
        cout << "Errore nell'apertura del file!" << endl;
    }
}

// ==========================================
// FUNZIONE 2: Cerca un numero salvato nel file
// ==========================================
void cercaContatto() {
    // Variabile per memorizzare il nome che l'utente vuole cercare
    string cercaNome;
    
    cout << "\n--- CERCA NUMERO ---" << endl;
    cout << "Inserisci il nome da cercare: ";
    cin >> cercaNome;

    // 'ifstream' serve per aprire un file in LETTURA (leggiamo dal PC)
    ifstream file("rubrica.txt");
    
    // Variabile che conterrà una riga alla volta del file
    string riga;
    
    // Un interruttore (flag) per ricordarci se abbiamo trovato il contatto o no
    bool trovato = false;

    // Verifichiamo che il file esista e si apra correttamente
    if (file.is_open()) {
        // Leggiamo il file riga per riga finché ci sono dati dentro (grazie a getline)
        while (getline(file, riga)) {
            
            // riga.find() cerca se all'interno della riga c'è il nome cercato.
            // string::npos significa "se la ricerca ha dato esito positivo".
            if (riga.find(cercaNome) != string::npos) {
                
                // Troviamo la posizione della virgola che divide nome e telefono
                size_t virgola = riga.find(',');
                
                if (virgola != string::npos) {
                    // Estraiamo il nome (da inizio riga fino alla virgola)
                    string nome = riga.substr(0, virgola);
                    // Estraiamo il telefono (dopo la virgola fino alla fine)
                    string tel = riga.substr(virgola + 1);
                    
                    // Stampiamo a schermo il risultato in modo bello e pulito
                    cout << "Trovato! -> Nome: " << nome << " | Tel: " << tel << endl;
                }
                // Segnamo che abbiamo trovato almeno un contatto corrispondente
                trovato = true;
            }
        }
        
        // Chiudiamo il file dopo aver finito la lettura
        file.close();

        // Se dopo aver letto tutto il file non abbiamo trovato nulla, avvisiamo l'utente
        if (!trovato) {
            cout << "Nessun contatto trovato con questo nome." << endl;
        }
        
    } else {
        // Se il file non esiste ancora (perché non è stato aggiunto nessun numero), lo segnaliamo
        cout << "La rubrica e' vuota o il file non esiste. Aggiungi prima un numero!" << endl;
    }
}

// ==========================================
// FUNZIONE PRINCIPALE (MAIN)
// ==========================================
int main() {
    // Variabile numerica per memorizzare la scelta del menu fatta dall'utente
    int scelta;

    // Usiamo un ciclo 'do-while': il blocco viene eseguito almeno una volta 
    // e si ripete finché l'utente non decide di uscire (premendo 3)
    do {
        // Mostriamo il menu a schermo
        cout << "\n=========================" << endl;
        cout << "   LA MIA RUBRICA C++    " << endl;
        cout << "=========================" << endl;
        cout << "1. Aggiungi numero" << endl;
        cout << "2. Cerca numero" << endl;
        cout << "3. Esci" << endl;
        cout << "Scegli un'opzione: ";
        
        // Leggiamo il numero scelto dall'utente
        cin >> scelta;

        // Struttura condizionale 'switch' per indirizzare l'utente in base alla sua scelta
        switch (scelta) {
            case 1:
                // Se l'utente preme 1, richiamiamo la funzione per aggiungere il contatto
                aggiungiContatto();
                break; // 'break' interrompe lo switch e non fa eseguire gli altri casi
                
            case 2:
                // Se l'utente preme 2, richiamiamo la funzione per cercare
                cercaContatto();
                break;
                
            case 3:
                // Se l'utente preme 3, usciamo dal programma
                cout << "Uscita dal programma. Ciao!" << endl;
                break;
                
            default:
                // 'default' scatta se l'utente inserisce un numero diverso da 1, 2 o 3 (es. 8 o 99)
                cout << "Scelta non valida! Usa 1 per aggiungere o 2 per cercare." << endl;
        }
        
    } while (scelta != 3); // Il ciclo continua finché la scelta è diversa da 3

    // Restituisce 0 per indicare che il programma è terminato senza errori
    return 0;
}// Includiamo la libreria standard per gestire l'input (cin) e l'output (cout) a schermo
#include <iostream>

// Includiamo la libreria 'fstream' che serve per creare, scrivere e leggere i file sul PC
#include <fstream>

// Includiamo la libreria 'string' per poter usare le parole e i testi
#include <string>

// Usiamo lo spazio dei nomi standard per evitare di scrivere sempre std:: prima di cout o cin
using namespace std;

// ==========================================
// FUNZIONE 1: Aggiunge un numero e lo salva sul PC
// ==========================================
void aggiungiContatto() {
    // Dichiariamo due variabili di tipo stringa per memorizzare nome e telefono inseriti dall'utente
    string nome, telefono;
    
    cout << "\n--- AGGIUNGI NUMERO ---" << endl;
    cout << "Inserisci il nome: ";
    cin >> nome; // Legge il nome da tastiera
    
    cout << "Inserisci il numero: ";
    cin >> telefono; // Legge il numero da tastiera

    // 'ofstream' serve per aprire un file in SCRITTURA. 
    // "rubrica.txt" è il nome del file che verrà creato sul computer.
    // 'ios::app' (append) è fondamentale: dice a C++ di aggiungere il nuovo contatto 
    // in fondo al file SENZA cancellare quelli vecchi che avevamo salvato prima!
    ofstream file("rubrica.txt", ios::app);

    // Controlliamo se il file si è aperto correttamente sul PC
    if (file.is_open()) {
        // Scriviamo nel file il nome e il telefono separati da una virgola (es: "Mario,3331234567")
        file << nome << "," << telefono << endl;
        
        // Chiudiamo il file per liberare la memoria del computer (buona abitudine)
        file.close();
        
        cout << "-> Numero salvato con successo sul tuo PC!" << endl;
    } else {
        // Se c'è un problema (es. disco pieno o permessi negati), avvisiamo l'utente
        cout << "Errore nell'apertura del file!" << endl;
    }
}

// ==========================================
// FUNZIONE 2: Cerca un numero salvato nel file
// ==========================================
void cercaContatto() {
    // Variabile per memorizzare il nome che l'utente vuole cercare
    string cercaNome;
    
    cout << "\n--- CERCA NUMERO ---" << endl;
    cout << "Inserisci il nome da cercare: ";
    cin >> cercaNome;

    // 'ifstream' serve per aprire un file in LETTURA (leggiamo dal PC)
    ifstream file("rubrica.txt");
    
    // Variabile che conterrà una riga alla volta del file
    string riga;
    
    // Un interruttore (flag) per ricordarci se abbiamo trovato il contatto o no
    bool trovato = false;

    // Verifichiamo che il file esista e si apra correttamente
    if (file.is_open()) {
        // Leggiamo il file riga per riga finché ci sono dati dentro (grazie a getline)
        while (getline(file, riga)) {
            
            // riga.find() cerca se all'interno della riga c'è il nome cercato.
            // string::npos significa "se la ricerca ha dato esito positivo".
            if (riga.find(cercaNome) != string::npos) {
                
                // Troviamo la posizione della virgola che divide nome e telefono
                size_t virgola = riga.find(',');
                
                if (virgola != string::npos) {
                    // Estraiamo il nome (da inizio riga fino alla virgola)
                    string nome = riga.substr(0, virgola);
                    // Estraiamo il telefono (dopo la virgola fino alla fine)
                    string tel = riga.substr(virgola + 1);
                    
                    // Stampiamo a schermo il risultato in modo bello e pulito
                    cout << "Trovato! -> Nome: " << nome << " | Tel: " << tel << endl;
                }
                // Segnamo che abbiamo trovato almeno un contatto corrispondente
                trovato = true;
            }
        }
        
        // Chiudiamo il file dopo aver finito la lettura
        file.close();

        // Se dopo aver letto tutto il file non abbiamo trovato nulla, avvisiamo l'utente
        if (!trovato) {
            cout << "Nessun contatto trovato con questo nome." << endl;
        }
        
    } else {
        // Se il file non esiste ancora (perché non è stato aggiunto nessun numero), lo segnaliamo
        cout << "La rubrica e' vuota o il file non esiste. Aggiungi prima un numero!" << endl;
    }
}

// ==========================================
// FUNZIONE PRINCIPALE (MAIN)
// ==========================================
int main() {
    // Variabile numerica per memorizzare la scelta del menu fatta dall'utente
    int scelta;

    // Usiamo un ciclo 'do-while': il blocco viene eseguito almeno una volta 
    // e si ripete finché l'utente non decide di uscire (premendo 3)
    do {
        // Mostriamo il menu a schermo
        cout << "\n=========================" << endl;
        cout << "   LA MIA RUBRICA C++    " << endl;
        cout << "=========================" << endl;
        cout << "1. Aggiungi numero" << endl;
        cout << "2. Cerca numero" << endl;
        cout << "3. Esci" << endl;
        cout << "Scegli un'opzione: ";
        
        // Leggiamo il numero scelto dall'utente
        cin >> scelta;

        // Struttura condizionale 'switch' per indirizzare l'utente in base alla sua scelta
        switch (scelta) {
            case 1:
                // Se l'utente preme 1, richiamiamo la funzione per aggiungere il contatto
                aggiungiContatto();
                break; // 'break' interrompe lo switch e non fa eseguire gli altri casi
                
            case 2:
                // Se l'utente preme 2, richiamiamo la funzione per cercare
                cercaContatto();
                break;
                
            case 3:
                // Se l'utente preme 3, usciamo dal programma
                cout << "Uscita dal programma. Ciao!" << endl;
                break;
                
            default:
                // 'default' scatta se l'utente inserisce un numero diverso da 1, 2 o 3 (es. 8 o 99)
                cout << "Scelta non valida! Usa 1 per aggiungere o 2 per cercare." << endl;
        }
        
    } while (scelta != 3); // Il ciclo continua finché la scelta è diversa da 3

    // Restituisce 0 per indicare che il programma è terminato senza errori
    return 0;
}
