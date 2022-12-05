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
	Mappa(float dimensione);

	float dim_cella();
	Cella crea_cella(float pos_x, float pos_y); //serve a creare delle posizioni Celle  partendo da coordinate cartesiane float
	void inserisci_ostacolo(Cella min, Cella max); //inserimento di ostacolo definito come da specifiche, si può implementare con array o cella
	void inserisci_robot(Cella posizione);
	void sposta_robot(Cella prima, Cella dopo);
	float distanza_cella_vicina(Cella cercata); //ritorna il valore della distanza euclidea tra la cella inserita e l'ostacolo-robot più vicino
	
private:
	std::set<Cella> pos_ostacoli;
	std::set<Cella> pos_robot;
	float dim_;
};

float distanza_euclidea(const Cella pos_1, const Cella pos_2);

bool operator==(const Cella& c1, const Cella& c2);

bool operator<(const Cella& c1, const Cella& c2);

#endif
