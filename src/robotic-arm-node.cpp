#include "server_api_pkg/robot-arm-node.hpp"

#include "common_msgs_srvs/GoToPoint.h"

#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"

namespace server_api_pkg
{
  namespace m_s = common_msgs_srvs;
  RoboticArmNode::RoboticArmNode(std::string const &stateTopic,
                                 std::string const &goToPointSevice)
      : mRoboticArm(std::make_unique<server_api_lib::RoboticArmController>(6)),
        mNode("~"), mPublisher(mNode.advertise<std_msgs::Float64MultiArray>(
                        stateTopic, 1000)),
        mService(mNode.advertiseService<m_s::GoToPoint::Request,
                                        m_s::GoToPoint::Response>(
            goToPointSevice,
            [this](m_s::GoToPoint::Request &req, m_s::GoToPoint::Response &res)
            {
              ROS_DEBUG_STREAM("[robotic arm] GoToPoint call");
              res.success = mRoboticArm.GoToPoint(
                  {.x = req.target.x, .y = req.target.y, .z = req.target.z});
              return true;
            })),
        mTimer(mNode.createTimer(ros::Duration(1),
                                 [this](const ros::TimerEvent &)
                                 {
                                   ROS_DEBUG_STREAM(
                                       "[robotic arm] GetState call");
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

  server_api_pkg::RoboticArmNode robot(
      ros::param::param<std::string>("state_topic", "state"),
      ros::param::param<std::string>("go_to_point_service", "go_to_point"));
  ros::spin();
  return 0;
}
