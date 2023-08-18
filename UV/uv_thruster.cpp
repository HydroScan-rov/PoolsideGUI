#include "uv_thruster.h"

UV_Thruster::UV_Thruster() {
    power = true;

    slot = 0;
    id = 0;
    reverse = false;
    target_force = 0;
    k_forward = 1;
    k_backward = 1;
    dPWM_forward = 500;
    dPWM_backward = 500;
}
