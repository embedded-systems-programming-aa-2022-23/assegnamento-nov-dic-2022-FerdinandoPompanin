//robot.cpp

#include <iostream>
using std::cerr;
#include <cmath>
using std::pow;
using std::sqrt;
using std::ceil;

#include "robot.h"

//definisco classe robot
	Robot::Robot(Cella pos, Cella goal, float raggio, Mappa& mappa)
		:pos_{pos},
		goal_{goal},
		map_{mappa},
		raggio_{raggio}
		{
			//controllo me lo fa già inserisci_robot()
			mappa.inserisci_robot(pos, raggio);
		}
		
	Robot::Robot(Cella pos, float raggio, Mappa& mappa)
		:pos_{pos},
		goal_{pos}, //scelgo di mettere di default il goal nella posizione in cui si trova il robot, così se non ha un vero da raggiungere goal, risulta "non impegnato"
		map_{mappa},
		raggio_{raggio}
		{
			//controllo me lo fa gia inserisci_robot()
			mappa.inserisci_robot(pos, raggio);
		}
	
	
	void Robot::cambia_goal(Cella goal)
	{
		if(map_.contiene_obs(goal, raggio_))
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
		Cella prox_cella((pos_.posx()-1), (pos_.posy()-1));
		float potenziale_min = Robot::calcola_potenziale(prox_cella, map_.distanza_cella_vicina(prox_cella, pos_));
		
		//per ogni cella limitrofa fai il calcolo del potenziale
		for(int i{(pos_.posx()-1)}; i < (pos_.posx()+2); i++)
		{
			for(int j{pos_.posy() -1}; j < (pos_.posy()+2); j++)
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
		//il controllo me lo fa gia sposta_robot()
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
