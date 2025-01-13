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
	
	Cella c1(-1,-1);
	Cella c2(1,1);
	Cella c3(5,5);
	Cella c4(8,6);
	Cella o1(13,20);
	Cella o2(20,23);
	Cella g1(27,23);

	my_map.inserisci_ostacolo(c2, c3);
	my_map.inserisci_ostacolo(o1, o2);

	Robot my_robot(c1, 1.0, my_map);

	cout<<my_robot.valore_pos()<<"\n";
	cout<< my_robot<<"\n";
	
	my_robot.cambia_goal(c4);
	
	while(!my_robot.goal_raggiunto())
	{
		my_robot.cammina();
		cout<<my_robot<<"\n";
	}	

	Cella c5(11,7);
	Cella c6(1,8);

	Robot my_robot2(c5, c6, 1.5, my_map);
		
	cout<<my_robot2.valore_pos()<<"\n";
	cout<< my_robot2<<"\n";

	while(!my_robot2.goal_raggiunto())
	{
		my_robot2.cammina();
		cout<<my_robot2<<"\n";
	}
	
	cout<<my_robot.valore_pos()<<"\n";
	cout<< my_robot<<"\n";
	
	my_robot.cambia_goal(g1);
	while(!my_robot.goal_raggiunto())
	{
		my_robot.cammina();
		cout<<my_robot<<"\n";
	}
	
return 0;
}
