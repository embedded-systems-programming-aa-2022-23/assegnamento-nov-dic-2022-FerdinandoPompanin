//robot.cpp

#include <iostream>
using std::cerr;
#include <cmath>
using std::pow;

#include "robot.h"

//definisco classe robot
	Robot::Robot(Cella pos, Cella goal, Mappa& map)
		:pos_{pos},
		goal_{goal},
		map_{map}
		{
			if(map.contiene_obs(pos) || map.contiene_robot(pos) || map.contiene_obs(goal))
			{
				cerr<<"Errore il Robot::Robot(), stai inserendo robot o goal in posizioni proibite!!\n";
				exit(EXIT_FAILURE);
			}
		
			map.inserisci_robot(pos);
		}
		
	Robot::Robot(Cella pos, Mappa& map)
		:pos_{pos},
		goal_{pos}, //scelgo di mettere di default il goal nella posizione in cui si trova il robot, così se non ha un vero da raggiungere goal, risulta "non impegnato"
		map_{map}
		{
			if(map.contiene_obs(pos) || map.contiene_obs(pos))
			{
				cerr<<"Errore il Robot::Robot(), stai inserendo robot o goal in posizioni proibite!!\n";
				exit(EXIT_FAILURE);
			}
		
			map.inserisci_robot(pos);
		}
	
	
	void Robot::cambia_goal(Cella goal)
	{
		if(map_.contiene_obs(goal))
		{
			cerr<<"Errore in Robot::cambia_goal(), inserimento goal in pos proibita!\n";
			exit(EXIT_FAILURE);
		}
		
		goal_ = goal;
	}
	
	Cella Robot::valore_pos()
	{
		return pos_;
	}
	
	bool Robot::goal_raggiunto()
	{
		return pos_==goal_;
	}
	
	void Robot::cammina()
	{
		Cella prox_cella((pos_.pos())[0]-1, (pos_.pos())[1]-1);
		float potenziale_min = Robot::calcola_potenziale(prox_cella, map_.distanza_cella_vicina(prox_cella, pos_));
		
		//per ogni cella limitrofa fai il calcolo del potenziale
		for(int i = ((pos_.pos())[0]-1); i < (pos_.pos()[0]+2); i++)
		{
			for(int j = (pos_.pos())[1] -1; j < (pos_.pos()[1]+2); j++)
			{
				Cella candidato(i,j);
				if(candidato!=pos_)
				{
					float pot_cand = Robot::calcola_potenziale(candidato, map_.distanza_cella_vicina(candidato, pos_));
				
					if(pot_cand<potenziale_min)
					{
						potenziale_min = pot_cand;
						prox_cella = candidato;
					}
				}
			}
		}
		
		//il robot cambia la cella		
		Robot::cambia_pos(prox_cella);
	}
	
	void Robot::cambia_pos(Cella nuova_pos)
	{
		if(map_.contiene_obs(nuova_pos) || map_.contiene_robot(nuova_pos))
		{
			cerr<<"Errore in Robot::cambia_pos(), posizioni non valide!\n";
			exit(EXIT_FAILURE);
		}
		
		map_.sposta_robot(pos_, nuova_pos);
		pos_ = nuova_pos;
	}
	
	float Robot::calcola_potenziale(Cella my_pos, float distanza)
	{	
		float potenziale;
		//calcolo potenziale repulsivo
		if(distanza>DIST_MAX)
		{
			potenziale = 0;
		}else{
			potenziale = 0.5*COEF_REPULSIVO*pow((1/distanza)-(1/DIST_MAX),2);
		}
		
		
		//calcolo potenziale attrattivo
		potenziale = potenziale + 0.5*COEF_ATTRATTIVO*pow(distanza_euclidea(my_pos, goal_, map_.dim_cella()),2);
		
		return potenziale;
	}
	
	std::ostream& operator<<(std::ostream& os, Robot& r)
	{
		os << "Mio robot: "<< " posizione: " << r.valore_pos();
		return os;
	}
