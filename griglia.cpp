//griglia.cpp

#include <array>
using std::array;
#include <iostream>
using std::cerr;
#include <cmath>
using std::sqrt;
using std::pow;

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
		
		Cella my_cella(x, y);
		
		return my_cella;
	}

	//inserisco TUTTO l'ostacolo, si potrebbe anche inserire solo il contorno per risparmiare, pensaci in seguito
	void Mappa::inserisci_ostacolo(Cella min, Cella max)
	{
		for(int i{(min.pos())[0]}; i <= (max.pos())[0]; i++)
		{
			for(int j{(min.pos())[1]}; j <= (max.pos())[1]; j++)
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
	
	
	void Mappa::inserisci_robot(Cella posizione)
	{
		//controllo per evitare di inserire robot in cella già occupata
		if(pos_ostacoli.contains(posizione)||pos_robot.contains(posizione))
		{
			cerr <<"Errore in inserisci_robot(). Stai provando a inserire robot in posizione già occupata!\n";
			exit(EXIT_FAILURE);
		}
		
		pos_robot.insert(posizione);
	}
	
	
	void Mappa::sposta_robot(Cella prima, Cella dopo)
	{
		//controllo per evitare di inserire robot in cella già occupata
		if(pos_ostacoli.contains(dopo)||pos_robot.contains(dopo))
		{
			cerr <<"Errore in sposta_robot(). Stai provando a inserire robot in posizione già occupata!\n";
			exit(EXIT_FAILURE);
		}
		
		pos_robot.erase(prima);
		pos_robot.insert(dopo);
	}
	
	
	float Mappa::distanza_cella_vicina(Cella cercata)
	{
		float distanza_min = distanza_euclidea(cercata, *pos_ostacoli.cbegin());
		
		for(auto pos_corr = pos_ostacoli.begin(); pos_corr != pos_ostacoli.end(); pos_corr++)
		{
			float distanza = distanza_euclidea(cercata, *pos_corr);
			if(distanza < distanza_min)
				distanza_min = distanza;
		}
		
		for(auto pos_corr{pos_robot.begin()}; pos_corr != pos_robot.end(); pos_corr++)
		{
			float distanza = distanza_euclidea(cercata, *pos_corr);
			if(distanza < distanza_min)
				distanza_min = distanza;
		}
		
		return distanza_min;
	}
	
	
	float distanza_euclidea(const Cella pos_1, const Cella pos_2)//non serve per forza tenere conto delle dimensioni della cella...
	{
		float distanza = sqrt( pow(((pos_1.pos())[0] - (pos_2.pos())[0]), 2) + pow(((pos_1.pos())[1] - (pos_2.pos())[1]), 2))*DIM_CELLA;
		return distanza;
	}
	
	bool operator==(const Cella& c1, const Cella& c2)
	{
		return ((c1.pos())[0]==(c2.pos())[0])&&((c1.pos())[1]==(c2.pos())[1]);
	}


	bool operator<(const Cella& c1, const Cella& c2)
	{
		return ((((c1.pos())[0]==(c2.pos())[0])&&((c1.pos())[1]<(c2.pos())[1]))||((c1.pos())[0]<(c2.pos())[0]));
		
	}


