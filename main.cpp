#include <iostream>
using std::cerr;
using std::cout;
#include <mutex>
using std::mutex;
#include <string>
#include <thread>
#include <fstream>


#include "griglia.h"
#include "robot.h"
#include "monitor.h"

#define k 1
#define N 3
#define num_goal 3//questo è il numero di goal che ogni robot dovrà raggiungere

Mappa my_map(1.0);//globali perchè condivisa dai processi

PC my_mon(k*N);

mutex mutex_mappa;//serve a far camminare un robot alla volta


void processo_robot(Cella pos, float raggio)
{
	//creo robot
	Robot my_robot(pos, raggio, my_map);
	
	for(int i = 0; i < num_goal; i++){
        	Cella value = my_mon.take(my_robot.valore_pos());
		my_robot.cambia_goal(value);
	
		while(!my_robot.goal_raggiunto())
		{
			mutex_mappa.lock(); //i lock si possono mettere anche fuori dal ciclo while, ma cosi si muove solo 1 robot alla volta.
			my_robot.cammina();
			mutex_mappa.unlock();
		}
		
		cout << "Raggiunto il Goal in pos: " << my_robot.valore_pos() << " \n";
	}

}

void processo_satellite( const std::string& nome_file)
{
	std::ifstream infile{nome_file};

	while(!infile.eof())
	{
		double x, y;
		infile >> x >> y;
		if (infile.eof() || infile.fail() || infile.bad()) {
            		std::cerr << "Error in input\n";
            		break;
       		}
	
		Cella value = my_map.crea_cella(x, y);
		
		my_mon.append(value);
		
		cout << "Inserito valore: " << value << " nel buffer \n";
	}
}



int main()
{
	//inserimento degli ostacoli
	my_map.inserisci_ostacolo(my_map.crea_cella(15,20), my_map.crea_cella(40,40));
	my_map.inserisci_ostacolo(my_map.crea_cella(0,0), my_map.crea_cella(1,2));
	my_map.inserisci_ostacolo(my_map.crea_cella(-1000,-70), my_map.crea_cella(-50,-50));

	Cella pos1 = Cella(-15, -15);
	Cella pos2 = Cella(-26, 32);
	Cella pos3 = Cella(7, 10);
	
	std::thread s1(processo_satellite, "../coordinate/stazione1.txt");
	std::thread s2(processo_satellite, "../coordinate/stazione2.txt");

	std::thread r1(processo_robot, pos1, 1.5);
	std::thread r2(processo_robot, pos2, 0.6);
	std::thread r3(processo_robot, pos3, 3);
	
	s1.join();
	s2.join();
	r1.join();
	r2.join();
	r3.join();
	
	return 0;
	
}
