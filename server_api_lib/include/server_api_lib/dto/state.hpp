#ifndef SERVER_API_LIB_DTO_STATE_HPP
#define SERVER_API_LIB_DTO_STATE_HPP

#include <vector>

namespace server_api_lib::dto
{
  struct RoboticArmState
  {
    std::vector<double> jointAngles;
  };

  struct TwoWheelsRobotState
  {
    double leftWheelVelocity;
    double rightWheelVelocity;
  };

} // namespace server_api_lib::dto

#endif // SERVER_API_LIB_DTO_STATE_HPP
