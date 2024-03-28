#ifndef SERVER_API_LIB_STATE_HPP
#define SERVER_API_LIB_STATE_HPP

#include <vector>

namespace server_api_lib::dto
{
  struct RoboticArmState
  {
    RoboticArmState() = default;
    explicit RoboticArmState(size_t dof) : jointAngles(dof, 0.0){};
    std::vector<double> jointAngles;
  };

  struct TwoWheelsRobot
  {
    double leftWheelVelocity;
    double rightWheelVelocity;
  };

} // namespace server_api_lib::dto

#endif // SERVER_API_LIB_STATE_HPP
