//griglia.h

#ifndef griglia_h
#define griglia_h

#include <array>
#include <set>

#define DIM_CELLA 1 //[m] dimensione della cella, da essere multiplo o sottomultiplo del metro

class Cella {
public:
	Cella(int pos_x, int pos_y);
	
	std::array<int,2> pos() const; //restituisce le coordinate della cella
	
private:
	//coordinate della posizione della cella
	int x_;
	int y_;
};	
	
	
class Mappa {
public:
	void inserisci_ostacolo(int min_x, int min_y, int max_x, int max_y); //inserimento di ostacolo definito come da specifiche, si può implementare con array o cella
	void inserisci_robot(Cella posizione);
	void sposta_robot(Cella prima, Cella dopo);
	float distanza_cella_vicina(Cella cercata); //ritorna il valore della distanza euclidea tra la cella inserita e l'ostacolo-robot più vicino
	
private:
	std::set<Cella> pos_ostacoli;
	std::set<Cella> pos_robot;
};

float distanza_euclidea(const Cella pos_1, const Cella pos_2);

bool operator==(const Cella& c1, const Cella& c2);

bool operator<(const Cella& c1, const Cella& c2);

#endif
