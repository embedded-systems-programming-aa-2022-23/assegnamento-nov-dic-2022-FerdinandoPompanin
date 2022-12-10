//griglia.cpp

#include <array>
using std::array;
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <cmath>
using std::sqrt;
using std::pow;
#include <map>
using std::map;
using std::pair;

#include "griglia.h"
//definisco classe cella
	Cella::Cella(int pos_x, int pos_y)
		:x_{pos_x},
		 y_{pos_y}
		 {}
	
	array<int,2> Cella::pos() const
	{
		array<int,2> posizione{x_, y_};
		return posizione;
	}

	int Cella::posx() const
	{
		return x_;
	}

	int Cella::posy() const
	{
		return y_;
	}

//definisco classe mappa
	Mappa::Mappa(float dimensione)
		:dim_{dimensione}
		{}

	float Mappa::dim_cella()
	{
		return dim_;
	}

	Cella Mappa::crea_cella(float pos_x, float pos_y)
	{
		int x = static_cast<int>(pos_x/dim_);
		int y = static_cast<int>(pos_y/dim_);
		
		if(pos_x<0)
			x--;
		if(pos_y<0)
			y--;
		
		Cella my_cella(x, y);
		
		return my_cella;
	}

	//inserisco TUTTO l'ostacolo, si potrebbe anche inserire solo il contorno per risparmiare, pensaci in seguito
	void Mappa::inserisci_ostacolo(Cella min, Cella max)
	{
		//inserire controllo dati in ingresso
		for(int i{min.posx()}; i <= max.posx(); i++)
		{
			for(int j{min.posy()}; j <= max.posy(); j++)
			{
				Cella posizione(i, j);
				//controlo per evitare di sovrapporre ostacoli
				if(pos_ostacoli.contains(posizione))
				{
					cerr <<"Errore in insericsci_ostacolo(). Sovrapposizione di ostacoli!\n";
					exit(EXIT_FAILURE);
				}
				pos_ostacoli.insert(posizione);
			}
		}
	}
	
	
	void Mappa::inserisci_robot(Cella posizione, float raggio)
	{
		//controllo per evitare di inserire robot in cella già occupata
		if(Mappa::contiene_obs(posizione, raggio)||Mappa::contiene_robot(posizione, raggio))
		{
			cerr <<"Errore in inserisci_robot(). Stai provando a inserire robot in posizione già occupata!\n";
			exit(EXIT_FAILURE);
		}
		
		pos_robot.insert(pair<Cella,float>(posizione,raggio));
	}
	
	
	void Mappa::sposta_robot(Cella prima, Cella dopo)
	{
		float prov{pos_robot[prima]};
		
		//controllo per evitare di spostare in celle gia occupate
		if(Mappa::spostamento_non_valido(prima, dopo, prov))
		{
			cerr <<"Errore in sposta_robot(). Stai provando a inserire robot in posizione già occupata!\n";
			exit(EXIT_FAILURE);
		}
		
		pos_robot.erase(prima);
		pos_robot.insert(pair<Cella,float>(dopo, prov));
	}
	
	
	float Mappa::distanza_cella_vicina(Cella cercata, Cella my_r)
	{
		float distanza_min;
		
		if(pos_ostacoli.size() != 0){
			distanza_min = distanza_euclidea(cercata, *pos_ostacoli.cbegin(), dim_);
		}else{
			distanza_min = distanza_euclidea(cercata, (pos_robot.cbegin())->first, dim_);
			if(pos_robot.size()==1)
				distanza_min=0;
			if(pos_robot.size()>1 && pos_robot.cbegin()->first==my_r)
				distanza_min = distanza_euclidea(cercata, (++pos_robot.cbegin())->first, dim_);
		}
		
		for(auto pos_corr = pos_ostacoli.begin(); pos_corr != pos_ostacoli.end(); pos_corr++)
		{
				float distanza = distanza_euclidea(cercata, *pos_corr, dim_);	
					if(distanza < distanza_min)
						distanza_min = distanza;
		}
		
		for(auto pos_corr{pos_robot.begin()}; pos_corr != pos_robot.end(); pos_corr++)
		{
			if(my_r != pos_corr->first)
			{
				float distanza = distanza_euclidea(cercata, pos_corr->first, dim_) - pos_corr->second;
				if(distanza < distanza_min)
					distanza_min = distanza;
			}
		}
		
		return distanza_min;
	}
	
	//utile unicamente al testing sta funzione
	void Mappa::stampa_mappa()
	{
		cout << "Gli ostacoli sono : \n";
		
		for(auto it = pos_ostacoli.begin(); it != pos_ostacoli.end(); it++)
		{
			cout << *it <<"\n";
		}
			
		cout <<"\nLa dim. delle cella è: "<< dim_<<"\n";
	}
	
	float distanza_euclidea(const Cella pos_1, const Cella pos_2, float dim_cella)
	{
		float distanza = sqrt( pow(((pos_1.pos())[0] - (pos_2.pos())[0]), 2) + pow(((pos_1.pos())[1] - (pos_2.pos())[1]), 2))*dim_cella;
		return distanza;
	}
	
	float distanza_angolo(const Cella pos_1, const Cella pos_2, float dim_cella)
	{
		float distanza = (sqrt( pow(((pos_1.pos())[0] - (pos_2.pos())[0]), 2) + pow(((pos_1.pos())[1] - (pos_2.pos())[1]), 2))-(sqrt(2)/2))*dim_cella;
		return distanza;
	}
	
	
	bool Mappa::contiene_obs(Cella pos, float raggio)
	{
		bool contiene{pos_ostacoli.contains(pos)};
		
		for(auto it{pos_ostacoli.cbegin()}; it != pos_ostacoli.cend(); it++)
		{
			if(distanza_angolo(pos, *it, dim_)<raggio)
				contiene=true;
		
		}
	
		return contiene;
	}
	
	bool Mappa::contiene_robot(Cella pos, float raggio)
	{
		bool contiene = false;
		
		for(auto it{pos_robot.cbegin()}; it != pos_robot.cend(); it++)
		{
				if(distanza_euclidea(pos, it->first, dim_)<(raggio+it->second))
					contiene=true;	
		}
	
		return contiene;
	}
	
	bool Mappa::spostamento_non_valido(Cella prima, Cella dopo, float raggio)
	{
		bool non_valido = Mappa::contiene_obs(dopo, raggio);
		
		for(auto it{pos_robot.cbegin()}; it != pos_robot.cend(); it++)
		{
			if(it->first != prima){
				if(distanza_euclidea(dopo, it->first, dim_)<(raggio+it->second))
					non_valido=true;
			}		
		}
		
		return non_valido;
	}
	
	Cella Mappa::prima_cella_valida(Cella pos, float raggio)
	{
		for(int i=-1; i<2; i++)
		{
			for(int j=-1; j<2; j++)
			{
				Cella valido(pos.posx()+i,pos.posy()+j);
				if(!spostamento_non_valido(pos, valido, raggio))
				{
					return valido;
				}
			}
		}
		return pos;
	}
	
	
	
//definisco operatori per tipo Cella
	bool operator==(const Cella& c1, const Cella& c2)
	{
		return ((c1.pos())[0]==(c2.pos())[0])&&((c1.pos())[1]==(c2.pos())[1]);
	}

	bool operator!=(const Cella& c1, const Cella& c2)
	{
		return !(c1==c2);
	}

	bool operator<(const Cella& c1, const Cella& c2)
	{
		return ((((c1.pos())[0]==(c2.pos())[0])&&((c1.pos())[1]<(c2.pos())[1]))||((c1.pos())[0]<(c2.pos())[0]));
		
	}

	std::ostream& operator<<(std::ostream& os, const Cella& c)
	{
		os << "X: " << (c.pos())[0] << " Y:  " << (c.pos())[1];
		return os;
	}
