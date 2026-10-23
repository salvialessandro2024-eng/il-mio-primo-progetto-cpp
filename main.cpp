#include <iostream>
#include <fstream>
#include <string>
using namespace std; 

int main() {
	
	int scelta;	
			 
	cout<<"---LA MIA RUBRICA ---"<<endl;	
	cout<<"1. AGGIUNGI CONTATTO"<<endl; 	
	cout<<"2. ESCI"<<endl;
	cout<<"scelta";	
	cin>>scelta;
	
	if (scelta==1){
	
	string nome,telefono; 
	
	cout<< "Inserisci nome e il numero di telefono ";
	cin>>nome>>telefono;
	//apre un file di testo e ci scrive dentro 
	ofstream file ("rubrica.txt",ios::app);
	file<<"Nome: "<<nome<<"-Tel: "<<telefono<<endl;
	file.close();
	
		
	cout<<"contatto salvato con successo su rubrica.txt"<<endl;	
		
	}
		
		
		
		
	return 0;
}