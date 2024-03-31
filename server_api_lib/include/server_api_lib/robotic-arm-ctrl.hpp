#ifndef SERVER_API_LIB_ROBOTIC_ARM_CTRL_HPP
#define SERVER_API_LIB_ROBOTIC_ARM_CTRL_HPP

#include "server_api_lib/dto/state.hpp"
#include "server_api_lib/interface/i-controller.hpp"

namespace server_api_lib
{
  class RoboticArmController
      : public interface::IController<dto::RoboticArmState>
  {
  private:
    size_t const kDOF;

  public:
    RoboticArmController(size_t dof);
    ~RoboticArmController() = default;

    bool GoToPointCall(dto::Point3D const &point) override;
    dto::RoboticArmState GetStateCall() override;
  };
} // namespace server_api_pkg

#endif // SERVER_API_LIB_ROBOTIC_ARM_CTRL_HPP
