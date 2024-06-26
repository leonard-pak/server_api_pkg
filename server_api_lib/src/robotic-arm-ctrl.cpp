#include "server_api_lib/robotic-arm-ctrl.hpp"

#include <random>
#include <ranges>
#include <thread>
#include <tuple>

namespace server_api_lib
{
  namespace vw = std::ranges::views;

  RoboticArmController::RoboticArmController(size_t dof) : kDOF(dof){};

  bool RoboticArmController::GoToPointCall(dto::Point3D const &point)
  {
    // mock check and api call
    return (point.x + point.y + point.z) > 1000.0 == 0;
  }

  dto::RoboticArmState RoboticArmController::GetStateCall()
  {
    std::random_device r;
    dto::RoboticArmState state;
    state.jointAngles.reserve(kDOF);
    for (auto &&_ : vw::iota(0u, kDOF))
    {
      state.jointAngles.push_back(
          360.0 * (static_cast<double>(r()) / static_cast<double>(r.max())) -
          180.0);
    }
    return state;
  }
} // namespace server_api_lib
