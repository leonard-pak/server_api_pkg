#include "server_api_lib/two-wheel-robot-ctrl.hpp"

#include <random>
#include <tuple>

namespace server_api_lib
{
  bool TwoWheelRobotController::GoToPointCall(dto::Point3D const &point)
  {
    // mock check and api call
    return point.z == 0;
  }

  dto::TwoWheelsRobotState TwoWheelRobotController::GetStateCall()
  {
    std::random_device r;
    dto::TwoWheelsRobotState state;
    state.leftWheelVelocity =
        static_cast<double>(r()) / static_cast<double>(r.max()) - 0.5;
    state.rightWheelVelocity =
        static_cast<double>(r()) / static_cast<double>(r.max()) - 0.5;
    return state;
  }
} // namespace server_api_lib
