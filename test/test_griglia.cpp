//test_griglia.cpp
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "griglia.h"
#include "robot.h"

int main()
{
//testing di classe Cella
	Cella my_cella(1, 7);
	
	cout << "my_cella: "<< my_cella << "\n";
	cout << "my_cella.pos()[0]: "<< my_cella.pos()[0] << "\n";
	cout << "my_cella.pos()[1]: "<< my_cella.pos()[1] << "\n";


	cout << "\n";
	
//testing di classe Mappa
	Mappa my_mappa(2.0);
	
	//testing Mappa::crea_cella()
	cout << "my_mappa.crea_cella(0.0, 0.0): " << my_mappa.crea_cella(0.0, 0.0) << "\n";
	cout << "my_mappa.crea_cella(0, 0.5):" << my_mappa.crea_cella(0, 0.5) << "\n";
	cout << "my_mappa.crea_cella(0.0, 1.5):" << my_mappa.crea_cella(0.0, 1.5) << "\n";
	cout << "my_mappa.crea_cella(-0.5, 0.5):" << my_mappa.crea_cella(-0.5, 0.5) << "\n";
	cout << "my_mappa.crea_cella(-0.5, -0.5):" << my_mappa.crea_cella(-0.5, -0.5) << "\n";
	cout << "my_mappa.crea_cella(0.5, -0.5): "<< my_mappa.crea_cella(0.5, -0.5) << "\n";
	cout << "my_mappa.crea_cella(-1.5,-6.5): "<< my_mappa.crea_cella(-1.5,-6.5) << "\n";
	cout << "\n";

	//testing Mappa::inserisci_ostacolo()
	Cella c1 = my_mappa.crea_cella(1.3, 2.5); //cella (1,2)
	Cella c2 = my_mappa.crea_cella(5.6, 9.99); //cella (5,9)
	Cella c3 = my_mappa.crea_cella(-8.5, -7.2); //cella (-9,-8)
	Cella c4 = my_mappa.crea_cella(0.5, -1.2); //cella (0, -2)
	
	my_mappa.inserisci_ostacolo(c1, c2);
	my_mappa.inserisci_ostacolo(c3, c4);

	my_mappa.stampa_mappa();

	//testing Mappa::inserisci_robot()
	Cella c5(-10, -2);
	
	my_mappa.inserisci_robot(c5);
	
	my_mappa.stampa_mappa();
	
	//testing Mappa::sposta_robot()
	Cella c6(10, 10);
	
	my_mappa.sposta_robot(c5, c6);
	
	my_mappa.stampa_mappa();
	
	//testing Mappa:distanza_cella_vicina()

	Cella c0(0, 0);
	cout << "\nDistanza cella_vicina(): "<< my_mappa.distanza_cella_vicina(c0, my_cella); 
	
return 0;
}
