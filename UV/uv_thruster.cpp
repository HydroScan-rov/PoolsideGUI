#include "uv_thruster.h"

UV_Thruster::UV_Thruster() {
    power = false;

    id = 0;
    adress = 0;

    target_forse = 0;

    reverse = false;
    kForward = 1;
    kBackward = 1;

    sForward = 100;
    sBackward = 100;
}
