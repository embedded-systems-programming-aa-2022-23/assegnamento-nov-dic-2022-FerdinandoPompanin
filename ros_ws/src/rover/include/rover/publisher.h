#ifndef rover_Publisher_h
#define rover_Publisher_h

#include "rclcpp/rclcpp.hpp"
#include "rover_visualizer/msg/rover_position.hpp"

extern rclcpp::Node::SharedPtr g_node;
extern rclcpp::Publisher<rover_visualizer::msg::RoverPosition>::SharedPtr
    g_publisher;

class Rover {
 public:
  Rover(int id);
  ~Rover();

  void set_pos(double x_pos, double y_pos);

  void setX_pos(double x_pos);
  void setY_pos(double y_pos);

 private:
  rclcpp::TimerBase::SharedPtr timer_{};

  int id_{-1};
  double x_pos_{0.};
  double y_pos_{0.};
};

#endif
