#include "server_api_pkg/two-wheel-robot-node.hpp"

#include "common_msgs_srvs/GoToPoint.h"
#include "common_msgs_srvs/TwoWheelRobotState.h"

#include "ros/ros.h"

namespace server_api_pkg
{
  namespace m_s = common_msgs_srvs;
  TwoWheelRobotNode::TwoWheelRobotNode(std::string const &stateTopic,
                                       std::string const &goToPointSevice)
      : mTwoWheelRobot(
            std::make_unique<server_api_lib::TwoWheelRobotController>()),
        mNode("~"),
        mPublisher(mNode.advertise<m_s::TwoWheelRobotState>(stateTopic, 1000)),
        mService(mNode.advertiseService<m_s::GoToPoint::Request,
                                        m_s::GoToPoint::Response>(
            goToPointSevice,
            [this](m_s::GoToPoint::Request &req, m_s::GoToPoint::Response &res)
            {
              ROS_INFO_STREAM("[two wheel robot] GoToPoint call");
              res.success = mTwoWheelRobot.GoToPoint(
                  {.x = req.target.x, .y = req.target.y, .z = req.target.z});
              return true;
            })),
        mTimer(mNode.createTimer(
            ros::Duration(1),
            [this](const ros::TimerEvent &)
            {
              ROS_DEBUG_STREAM("[two wheel robot] GetState call");
              auto state = mTwoWheelRobot.GetState();
              m_s::TwoWheelRobotState msg;
              msg.leftWheelVelocity = state.leftWheelVelocity;
              msg.rightWheelVelocity = state.rightWheelVelocity;
              mPublisher.publish(msg);
            }))
  {
  }
} // namespace server_api_pkg

int main(int argc, char **argv)
{
  ros::init(argc, argv, "two_wheel_robot");
  server_api_pkg::TwoWheelRobotNode robot(
      ros::param::param<std::string>("state_topic", "state"),
      ros::param::param<std::string>("go_to_point_service", "go_to_point"));
  ros::spin();
  return 0;
}
