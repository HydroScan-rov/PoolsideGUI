#include "uv_state.h"

Sensors::Sensors() {
    depth = 0;
    roll = 0;
    pitch = 0;
    yaw = 0;
}

ControlData::ControlData() {
    march = 0;
    lag = 0;
    depth = 0;
    roll = 0;
    pitch = 0;
    yaw = 0;
};

Light::Light() {
    power_lower_light = 0;
    r_rgb_light = 0;
    g_rgb_light = 0;
    b_rgb_light = 0;
}

Telemetry::Telemetry() {
    current_logic_electronics = 0;
    for (int i = 0; i < 8; i++) {
        current_vma[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        voltage_battery_cell[i] = 0;
    }
    voltage_battery = 0;
}

UV_State::UV_State() {
    udpHostAddress = "192.168.31.100";
    udpHostPort = 5000;

    connection_status = 0;
    reseived_connection_status = 0;

    thrusters_on = false;
    reset_imu = false;
    reset_depth = false;
    rgb_light_on = false;
    lower_light_on = false;

    stab_march = false;
    stab_lag = false;
    stab_depth = false;
    stab_roll = false;
    stab_pitch = false;
    stab_yaw = false;

    currentControlMode = MODE_HANDLE;
}

UV_State::~UV_State() {
    if (thruster != nullptr) {
        delete[] thruster;
    }
    if (controlCircuit != nullptr) {
        delete[] controlCircuit;
    }
}

void UV_State::setThrusterNext() {
    if (currentThruster < 8 - 1) {
        currentThruster++;
    } else {
        currentThruster = 0;
    }
}
