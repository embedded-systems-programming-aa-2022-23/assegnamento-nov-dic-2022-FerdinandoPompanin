//robot.h
#ifndef robot_h
#define robot_h

#include "griglia.h"

#define DIST_MAX 10 //sarebbe il Q*, da esprimere i metri, per ora scelto questo in modo arbitrario
#define COEF_ATTRATTIVO 1.5 //coefficiente per calcolo potenziale attrattivo, chiedere alla prof valori verosimili
#define COEF_REPULSIVO 2 //coefficiente per calcolo potenziale repulsivo, chiedere alla prof valori verosimili

class Robot {
public:
	Robot(Cella pos, Cella goal);
	Robot(Cella pos);
	
	void cambia_goal(Cella goal);
	Cella valore_pos();
	bool goal_raggiunto(); 
	void cammina(Mappa& my_map);

private:
	//per ora puntiforme, da aggiungere poi il raggio e tutto quello che ne consegue
	Cella pos_;
	Cella goal_;

	void cambia_pos(Cella nuova_pos);
	float calcola_potenziale(Cella my_pos, float distanza);
};


#endif
