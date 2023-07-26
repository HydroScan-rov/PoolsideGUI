#ifndef UV_STABILIZATION_H
#define UV_STABILIZATION_H

struct UV_StabilizationConstants {
    float march;
    float lag;
    float depth;
    float roll;
    float pitch;
    float yaw;

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

    float out_max;
    float out_min;
};

struct UV_StabilizationState {
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

    UV_StabilizationConstants constant;
    UV_StabilizationState state;
};

#endif // UV_STABILIZATION_H
