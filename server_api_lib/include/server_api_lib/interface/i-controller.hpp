#ifndef SERVER_API_LIB_I_CONTROLLER_HPP
#define SERVER_API_LIB_I_CONTROLLER_HPP

#include "server_api_lib/dto/point3D.hpp"

#include <array>

namespace server_api_lib::interface
{

  template <typename C>
  concept Controller = requires(C x) {
    typename C::state_t;
    {
      x.GoToPointCall(dto::Point3D())
    } -> std::same_as<bool>;
    {
      x.GetStateCall()
    } -> std::same_as<typename C::state_t>;
  };

  template <typename C> class IController
  {
  public:
    typedef C state_t;
    // API call for going to point
    virtual bool GoToPointCall(dto::Point3D point) = 0;
    // API call for getting current robot state
    virtual C GetStateCall() = 0;
  };
} // namespace server_api_lib::interface

#endif // SERVER_API_LIB_I_CONTROLLER_HPP
