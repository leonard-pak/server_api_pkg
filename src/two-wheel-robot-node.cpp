#include "server_api_pkg/two-wheel-robot-node.hpp"

#include "server_api_pkg/GoToPoint.h"
#include "server_api_pkg/TwoWheelRobotState.h"

#include "ros/ros.h"

namespace server_api_pkg
{
  TwoWheelRobotNode::TwoWheelRobotNode()
      : mTwoWheelRobot(
            std::make_unique<server_api_lib::TwoWheelRobotController>()),
        mNode("robots/two_wheel"),
        mPublisher(mNode.advertise<TwoWheelRobotState>("state", 1000)),
        mService(
            mNode.advertiseService<GoToPoint::Request, GoToPoint::Response>(
                "go_to_point",
                [this](GoToPoint::Request &req, GoToPoint::Response &res)
                {
                  ROS_INFO_STREAM("GoToPoint from two wheel robot call");
                  res.success = mTwoWheelRobot.GoToPoint({.x = req.target.x,
                                                          .y = req.target.y,
                                                          .z = req.target.z});
                  return true;
                })),
        mTimer(mNode.createTimer(
            ros::Duration(1),
            [this](const ros::TimerEvent &)
            {
              ROS_INFO_STREAM("GetStatus from two wheel robot call");
              auto state = mTwoWheelRobot.GetState();
              TwoWheelRobotState msg;
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
