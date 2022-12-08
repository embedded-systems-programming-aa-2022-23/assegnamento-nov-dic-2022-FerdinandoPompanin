//test_robot.cpp
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "griglia.h"
#include "robot.h"

int main()
{
	Mappa my_map(1.0);
	
	Cella c1(0,0);
	Cella c2(1,1);
	Cella c3(5,5);
	Cella c4(8,6);

	my_map.inserisci_ostacolo(c2, c3);

	Robot my_robot(c1, my_map);

	cout<<my_robot.valore_pos()<<"\n";
	cout<< my_robot<<"\n";
	
	my_robot.cambia_goal(c4);
	
	for(int i =0; i<20; i++)
	{
		my_robot.cammina();
		cout<<my_robot<<"\n";
	}	

return 0;
}
