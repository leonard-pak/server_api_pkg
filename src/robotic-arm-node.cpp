#include "server_api_pkg/robot-arm-node.hpp"

#include "server_api_pkg/GoToPoint.h"

#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"

namespace server_api_pkg
{
  RoboticArmNode::RoboticArmNode()
      : mRoboticArm(std::make_unique<server_api_lib::RoboticArmController>(6)),
        mNode("robots/arm"),
        mPublisher(mNode.advertise<std_msgs::Float64MultiArray>("state", 1000)),
        mService(
            mNode.advertiseService<GoToPoint::Request, GoToPoint::Response>(
                "go_to_point",
                [this](GoToPoint::Request &req, GoToPoint::Response &res)
                {
                  ROS_INFO_STREAM("GoToPoint from robotic arm call");
                  res.success = mRoboticArm.GoToPoint({.x = req.target.x,
                                                       .y = req.target.y,
                                                       .z = req.target.z});
                  return true;
                })),
        mTimer(mNode.createTimer(ros::Duration(1),
                                 [this](const ros::TimerEvent &)
                                 {
                                   ROS_INFO_STREAM(
                                       "GetStatus from robotic arm call");
                                   auto state = mRoboticArm.GetState();
                                   std_msgs::Float64MultiArray msg;
                                   msg.data = state.jointAngles;
                                   mPublisher.publish(msg);
                                 }))
  {
  }
} // namespace server_api_pkg

int main(int argc, char **argv)
{
  ros::init(argc, argv, "robotic_arm");
  server_api_pkg::RoboticArmNode robot;
  ros::spin();
  return 0;
}