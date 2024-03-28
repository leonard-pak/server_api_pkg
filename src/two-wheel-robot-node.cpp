#include "server_api_pkg/two-wheel-robot-node.hpp"

#include "common_msgs_srvs/GoToPoint.h"
#include "common_msgs_srvs/TwoWheelRobotState.h"

#include "ros/ros.h"

namespace server_api_pkg
{
  namespace m_s = common_msgs_srvs;
  TwoWheelRobotNode::TwoWheelRobotNode()
      : mTwoWheelRobot(
            std::make_unique<server_api_lib::TwoWheelRobotController>()),
        mNode("robots/two_wheel"),
        mPublisher(mNode.advertise<m_s::TwoWheelRobotState>("state", 1000)),
        mService(mNode.advertiseService<m_s::GoToPoint::Request,
                                        m_s::GoToPoint::Response>(
            "go_to_point",
            [this](m_s::GoToPoint::Request &req, m_s::GoToPoint::Response &res)
            {
              ROS_INFO_STREAM("GoToPoint from two wheel robot call");
              res.success = mTwoWheelRobot.GoToPoint(
                  {.x = req.target.x, .y = req.target.y, .z = req.target.z});
              return true;
            })),
        mTimer(mNode.createTimer(
            ros::Duration(1),
            [this](const ros::TimerEvent &)
            {
              ROS_INFO_STREAM("GetStatus from two wheel robot call");
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
  server_api_pkg::TwoWheelRobotNode robot;
  ros::spin();
  return 0;
}
