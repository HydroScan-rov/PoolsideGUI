#ifndef UV_CONTROLCIRCUIT_H
#define UV_CONTROLCIRCUIT_H

struct UV_CircuitConstants {
    float dt;
    float k_joy;
    float k_tuning;

    float pid_kp;
    float pid_ki;
    float pid_kd;
    float pid_max_i;
    float pid_min_i;
    float pid_max;
    float pid_min;

    float posFilter_t;
    float posFilter_k;
    float speedFilter_y;
    float speedFilter_k;

    float out_k;
    float out_max;
    float out_min;
};

struct UV_CircuitStates {
float input;
float pos_filtered;
float speed_filtered;

float joy_gained;
float target_integrator;

float pid_pre_error;
float pid_error;
float pid_integral;
float pid_Pout;
float pid_Iout;
float pid_Dout;
float pid_output;

float tuning_summator;
float speed_error;
float out_pre_saturation;
float out;
};

/** \brief Base class for stabilization contour of the underwater vehicle
 * UV can receive configuration messages and send back debug informations about contour
 */
class UV_ControlCircuit {
public:
    UV_ControlCircuit();

    UV_CircuitConstants constants;
    UV_CircuitStates states;
};

#endif // UV_CONTROLCIRCUIT_H
