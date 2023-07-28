#include "uv_controlCircuit.h"

UV_ControlCircuit::UV_ControlCircuit() {
    constants.dt = 0;
    constants.k_joy = 0;
    constants.k_tuning = 0;
    constants.pid_kp = 0;
    constants.pid_ki = 0;
    constants.pid_kd = 0;
    constants.pid_max_i = 0;
    constants.pid_min_i = 0;
    constants.pid_max = 0;
    constants.pid_min = 0;
    constants.posFilter_t = 0;
    constants.posFilter_k = 0;
    constants.speedFilter_y = 0;
    constants.speedFilter_k = 0;
    constants.out_max = 0;
    constants.out_min = 0;

    states.input = 0;
    states.pos_filtered = 0;
    states.speed_filtered = 0;
    states.joy_gained = 0;
    states.target_integrator = 0;
    states.pid_pre_error = 0;
    states.pid_error = 0;
    states.pid_integral = 0;
    states.pid_Pout = 0;
    states.pid_Iout = 0;
    states.pid_Dout = 0;
    states.pid_output = 0;
    states.tuning_summator = 0;
    states.speed_error = 0;
    states.out_pre_saturation = 0;
    states.out = 0;
}
