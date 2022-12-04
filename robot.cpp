//robot.cpp

#include <iostream>
using std::cerr;
#include <cmath>
using std::pow;

#include "robot.h"

//definisco classe robot
	Robot::Robot(Cella pos, Cella goal)
		:pos_{pos},
		goal_{goal}
		{}
		
	Robot::Robot(Cella pos)
		:pos_{pos},
		goal_{pos} //scelgo di mettere di default il goal nella posizione in cui si trova il robot, così se non ha un vero da raggiungere goal, risulta "non impegnato"
		{}
	
	
	void Robot::cambia_goal(Cella goal)
	{
		//non viene fatto alcun controllo se il goal è raggiungibile o meno, bisognerà poi pensare a questo quando gli si passa un valore di goal
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
	
	void Robot::cammina(Mappa& my_map)
	{
		Cella prox_cella((pos_.pos())[0], (pos_.pos())[1]);
		float potenziale_min = Robot::calcola_potenziale(pos_, 0.0);
		
		//per ogni cella limitrofa fai il calcolo del potenziale
		for(int i = ((pos_.pos())[0]-1); i < (pos_.pos()[0]+2); i++)
		{
			for(int j = (pos_.pos())[1] -1; i < (pos_.pos()[1]+2); i++)
			{
				Cella candidato(i,j);
				float pot_cand = Robot::calcola_potenziale(candidato, my_map.distanza_cella_vicina(candidato));
				
				if(pot_cand<potenziale_min)
				{
					potenziale_min = pot_cand;
					prox_cella = candidato;
				}
				
			}
		}
		//trovata la cella a potenziale minore, cambia la cella		
		Robot::cambia_pos(prox_cella);
	}
	
	void Robot::cambia_pos(Cella nuova_pos)
	{
		pos_ = nuova_pos;
	}
	
	//passagli la cella e la distanza dall'ostacolo più vicino
	float Robot::calcola_potenziale(Cella my_pos, float distanza)
	{	
		float potenziale;
		//calcolo potenziale repulsivo
		if(distanza<DIST_MAX)
		{
			potenziale = 0.5*COEF_REPULSIVO*pow((1/distanza)-(1/DIST_MAX),2);
		}else{
			potenziale = 0;
		}
		//calcolo potenziale attrattivo
		potenziale = potenziale + 0.5*COEF_ATTRATTIVO*pow(distanza_euclidea(my_pos, goal_),2);
		
		return potenziale;
	}
	
	
