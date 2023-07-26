#ifndef UV_STATE_H
#define UV_STATE_H

#include "stdint.h"

#include <QDebug>
#include <QUdpSocket>
#include "uv_device.h"
#include "uv_thruster.h"
#include "uv_controlCircuit.h"

enum e_packageMode : unsigned char {
    PACKAGE_NORMAL,
    PACKAGE_CONFIG,
    PACKAGE_DIRECT,
};

enum e_controlMode : unsigned char {
    MODE_HANDLE,
    MODE_AUTO,
    MODE_MANEUVERABLE,
};

enum e_circuit : unsigned char {
    MARCH,
    LAG,
    DEPTH,
    ROLL,
    PITCH,
    YAW,
};

struct Sensors {
    Sensors();

    float depth;
    float roll;
    float pitch;
    float yaw;

    float distance_l; // distance from laser rangefinder
    float distance_r;

    float speed_down; // speed signal from jetson
    float speed_right;
};

struct Telemetry {
    Telemetry();

    float current_logic_electronics; // from jetson + raspberry dc-dc
    float current_vma[8];
    float voltage_battery_cell[4];
    float voltage_battery; // 56
}

struct Light {
    Light();

    uint8_t power_lower_light;
    uint8_t r_rgb_light;
    uint8_t g_rgb_light;
    uint8_t b_rgb_light;
}

struct ControlData {
    ControlData();

    int16_t march;
    int16_t lag;
    int16_t depth;
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
};

class UV_State {
public:
    UV_State();
    ~UV_State();

    ControlData control;

    Sensors sensors;
    Light light;
    Telemetry telemetry;

    UV_Thruster thruster[8];
    void setThrusterNext();
    int currentThruster;

    UV_ControlCircuit controlCircuit[6];
    e_circuit currentCircuit;

    e_packageMode currentPackageMode;

    QString udpHostAddress;
    quint16 udpHostPort;

    // Flags
    bool thrusters_on;
    bool reset_imu;
    bool reset_depth;
    bool rgb_light_on;
    bool lower_light_on;

    bool stab_march;
    bool stab_lag;
    bool stab_depth;
    bool stab_roll;
    bool stab_pitch;
    bool stab_yaw;

    bool control_handle;
    bool control_auto;
    bool control_maneuverable;
};

#endif // UV_STATE_H
