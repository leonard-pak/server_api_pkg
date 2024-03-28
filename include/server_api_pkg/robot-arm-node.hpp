#ifndef SERVER_API_PKG_ROBOT_ARM_NODE_HPP
#define SERVER_API_PKG_ROBOT_ARM_NODE_HPP

#include "ros/ros.h"

#include "server_api_lib/robot.hxx"
#include "server_api_lib/robotic-arm-ctrl.hpp"

namespace server_api_pkg
{
  class RoboticArmNode
  {
  private:
    server_api_lib::Robot<server_api_lib::RoboticArmController> mRoboticArm;
    ros::NodeHandle mNode;
    ros::Publisher mPublisher;
    ros::ServiceServer mService;
    ros::Timer mTimer;

  public:
    RoboticArmNode();
    ~RoboticArmNode() = default;

    /* public members */
  };

} // namespace server_api_pkg

#endif // SERVER_API_PKG_ROBOT_ARM_NODE_HPP
