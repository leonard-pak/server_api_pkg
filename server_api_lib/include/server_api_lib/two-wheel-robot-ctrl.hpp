#ifndef SERVER_API_LIB_TWO_WHEEL_ROBOT_CTRL_HPP
#define SERVER_API_LIB_TWO_WHEEL_ROBOT_CTRL_HPP

#include "server_api_lib/dto/state.hpp"
#include "server_api_lib/interface/i-controller.hpp"

namespace server_api_lib
{
  class TwoWheelRobotController
      : public interface::IController<dto::TwoWheelsRobotState>
  {
  private:
  public:
    bool GoToPointCall(dto::Point3D const &point) override;
    dto::TwoWheelsRobotState GetStateCall() override;
  };
} // namespace server_api_lib

#endif // SERVER_API_LIB_TWO_WHEEL_ROBOT_CTRL_HPP
