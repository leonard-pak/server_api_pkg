#ifndef SERVER_API_LIB_ROBOT_HPP
#define SERVER_API_LIB_ROBOT_HPP

#include "server_api_lib/dto/state.hpp"
#include "server_api_lib/interface/i-controller.hpp"

#include "server_api_lib/robotic-arm-ctrl.hpp"

#include <atomic>
#include <thread>

namespace server_api_lib
{

  template <interface::Controller C> class Robot
  {
  private:
    std::unique_ptr<C> mController;
    C::state_t mState;
    std::atomic_flag mContinueRecv;
    mutable std::mutex mStateMut;
    std::thread mRecvStateThread;

  public:
    Robot(std::unique_ptr<C> ctrl)
        : mController(std::move(ctrl)),
          mRecvStateThread(
              [this]()
              {
                mContinueRecv.test_and_set();
                while (mContinueRecv.test(std::memory_order_acquire))
                {
                  std::lock_guard lock(mStateMut);
                  mState = mController->GetStateCall();
                }
              })
    {
    }

    ~Robot()
    {
      mContinueRecv.clear();
      mRecvStateThread.join();
    }

    bool GoToPoint(dto::Point3D const &point)
    {
      return mController->GoToPointCall(point);
    }

    C::state_t GetState() const
    {
      std::lock_guard lock(mStateMut);
      return mState;
    }
  };
} // namespace server_api_pkg

#endif // SERVER_API_LIB_ROBOT_HPP
