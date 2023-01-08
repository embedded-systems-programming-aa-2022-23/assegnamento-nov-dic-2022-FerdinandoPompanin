#include "rclcpp/rclcpp.hpp"
#include "rover/publisher.h"
#include "rover_visualizer/msg/rover_position.hpp"

#include <iostream>
using std::cerr;
using std::cout;
#include <mutex>
using std::mutex;
#include <string>
#include <thread>
#include <fstream>

#include "rover/griglia.h"
#include "rover/robot.h"
#include "rover/monitor.h"

#define k 1
#define N 3
#define r 0.2

rclcpp::Node::SharedPtr g_node;
rclcpp::Publisher<rover_visualizer::msg::RoverPosition>::SharedPtr g_publisher;

Mappa my_map(1.0);//globali perchè condivisa dai processi

PC my_mon(k*N);

mutex mutex_mappa;//serve a far camminare un robot alla volta


void processo_robot(Cella pos, float raggio, int id)
{
	//creo robot
	Robot my_robot(pos, raggio, my_map);
	
	auto rover_ = Rover(id);
	
	rover_.set_pos(my_robot.x_value(), my_robot.y_value());
	
	while(!my_mon.order_to_stop()){
        	Cella value = my_mon.take(my_robot.valore_pos());
		my_robot.cambia_goal(value);
	
		while(!my_robot.goal_raggiunto())
		{
			mutex_mappa.lock(); //i lock si possono mettere anche fuori dal ciclo while, ma cosi si muove solo 1 robot alla volta.
			my_robot.cammina();
			
			rover_.set_pos(my_robot.x_value(), my_robot.y_value());
	
			mutex_mappa.unlock();
		}
		
		cout << "Robot: "<< id << "ha raggiunto il Goal in pos: " << my_robot.valore_pos() << " \n";
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

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  
  g_node = rclcpp::Node::make_shared("rover_publisher");
  g_publisher = g_node->create_publisher<rover_visualizer::msg::RoverPosition>("rover", 10);
  
 //lettura e inserimento degli ostacoli
	std::ifstream infile{"obstacle_positions.txt"};

	while(!infile.eof())
	{
		double x_min, y_min, x_max, y_max;
		infile >> x_min >> y_min >> x_max >> y_max;
		if (infile.eof() || infile.fail() || infile.bad()) {
            		std::cerr << "Error in input\n";
            		break;
       		}
       		
       		my_map.inserisci_ostacolo(my_map.crea_cella(x_min, y_min), my_map.crea_cella(x_max, y_max));
       	}	
       		
	Cella pos1 = Cella(-15, -15);
	Cella pos2 = Cella(-26, 32);
	Cella pos3 = Cella(7, 10);

	std::thread r1(processo_robot, pos1, r, 1);
	std::thread r2(processo_robot, pos2, r, 2);
	std::thread r3(processo_robot, pos3, r, 3);
	
	std::thread s1(processo_satellite, "../coordinate/stazione1.txt");
	std::thread s2(processo_satellite, "../coordinate/stazione2.txt");
	
	s1.join();
	s2.join();
	
	my_mon.finish();
	
	r1.join();
	r2.join();
	r3.join();
	
  rclcpp::shutdown();

  exit(EXIT_SUCCESS);
}
