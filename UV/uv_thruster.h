#ifndef UV_THRUSTER_H
#define UV_THRUSTER_H

#include <QString>


class UV_Thruster {
public:
    UV_Thruster();

    bool power; // sets target_force to 0 on pult

    int slot; //  location on the ROV
    int id;
    bool reverse;
    float_t target_force;
    // relative to the positive directions of thrusters on the ROV
    float_t k_forward;
    float_t k_backward;
    uint16_t dPWM_forward; // 0-500
    uint16_t dPWM_backward; // 0-500
};

#endif // UV_THRUSTER_H
