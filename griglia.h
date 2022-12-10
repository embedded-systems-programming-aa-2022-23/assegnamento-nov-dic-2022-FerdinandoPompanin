//griglia.h

#ifndef griglia_h
#define griglia_h

#include <array>
#include <set>
#include <map>

class Cella {
public:
	Cella(int pos_x, int pos_y);
	
	std::array<int,2> pos() const; //restituisce le coordinate della cella
	int posx() const;
	int posy() const;
	
private:
	//coordinate della posizione della cella
	int x_;
	int y_;
};	
	
	
class Mappa {
public:
	Mappa(float dimensione);

	float dim_cella();
	Cella crea_cella(float pos_x, float pos_y); //serve a creare delle posizioni Celle  partendo da coordinate cartesiane float, ho bisogno del dato delle dim cella per poter discretizzare
	void inserisci_ostacolo(Cella min, Cella max); //inserimento di ostacolo definito come da specifiche, si può implementare con array o cella
	void inserisci_robot(Cella posizione, float raggio);
	void sposta_robot(Cella prima, Cella dopo);
	float distanza_cella_vicina(Cella cercata, Cella my_r); //ritorna il valore della distanza euclidea tra la cella inserita e l'ostacolo-robot più vicino
	void stampa_mappa();
	bool contiene_obs(Cella pos, float raggio);
	bool contiene_robot(Cella pos, float raggio);
	bool spostamento_non_valido(Cella prima, Cella dopo, float raggio);
private:
	std::set<Cella> pos_ostacoli;
	std::map<Cella, float> pos_robot;
	float dim_;
};

float distanza_euclidea(const Cella pos_1, const Cella pos_2, float dim_cella);
float distanza_angolo(const Cella pos_1, const Cella pos_2, float dim_cella);

bool operator==(const Cella& c1, const Cella& c2);

bool operator!=(const Cella& c1, const Cella& c2);

bool operator<(const Cella& c1, const Cella& c2);

std::ostream& operator<<(std::ostream& os, const Cella& c);

#endif
