# server_api_pkg
Package for controlling robots by api

## Launch

- `start-server.launch` - start server with robotic arm and two wheel robot

## Nodes
Nodes link the ros network with the implementation of controllers for robots
- `robotic-arm-node` - 6 dof robotic arm
- `two-wheel-robot-node` - robotic platform with two wheels

## Server api lib

Library contains interfaces, data-transfer objects and implementations for
call api of robotic arm and two wheel robot.
Robots can perform 2 functions:
```cpp
    // API call for going to point
    virtual bool GoToPointCall(dto::Point3D const &point) = 0;
    // API call for getting current robot state
    virtual C GetStateCall() = 0;
```
