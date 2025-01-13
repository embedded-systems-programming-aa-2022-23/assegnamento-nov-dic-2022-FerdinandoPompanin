// Internal dependencies
#include "rover/publisher.h"

// ROS dependencies
#include "rover_visualizer/msg/rover_position.hpp"

// Standard dependencies
#include <iostream>

Rover::Rover(int id) : id_(id) {}

Rover::~Rover() {}

void Rover::set_pos(double x_pos, double y_pos) {
  auto message{rover_visualizer::msg::RoverPosition()};

  setY_pos(y_pos);
  setX_pos(x_pos);

  message.id = id_;
  message.position.x = x_pos_;
  message.position.y = y_pos_;

  g_publisher->publish(message);
}

void Rover::setY_pos(double y_pos) { y_pos_ = y_pos; }

void Rover::setX_pos(double x_pos) { x_pos_ = x_pos; }
