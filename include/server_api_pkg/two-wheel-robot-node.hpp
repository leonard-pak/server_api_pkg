#ifndef SERVER_API_PKG_TWO_WHEEL_ROBOT_NODE_HPP
#define SERVER_API_PKG_TWO_WHEEL_ROBOT_NODE_HPP

#include "ros/ros.h"

#include "server_api_lib/robot.hxx"
#include "server_api_lib/two-wheel-robot-ctrl.hpp"

namespace server_api_pkg
{
  class TwoWheelRobotNode
  {
  private:
    server_api_lib::Robot<server_api_lib::TwoWheelRobotController>
        mTwoWheelRobot;
    ros::NodeHandle mNode;
    ros::Publisher mPublisher;
    ros::ServiceServer mService;
    ros::Timer mTimer;

  public:
    TwoWheelRobotNode(std::string const &stateTopic,
                      std::string const &goToPointSevice);
    ~TwoWheelRobotNode() = default;
  };

} // namespace server_api_pkg

#endif // SERVER_API_PKG_TWO_WHEEL_ROBOT_NODE_HPP
