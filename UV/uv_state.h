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

enum e_Device {
    DEVICE_TILT,
    DEVICE_DEV,
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
};

struct Light {
    Light();

    uint8_t power_lower_light;
    uint8_t r_rgb_light;
    uint8_t g_rgb_light;
    uint8_t b_rgb_light;
};

struct ControlData {
    ControlData();

    float march;
    float lag;
    float depth;
    float roll;
    float pitch;
    float yaw;
};

class UV_State {
public:
    UV_State();
    ~UV_State();

    uint8_t connection_status;
    uint8_t reseived_connection_status;

    ControlData control;
    e_controlMode currentControlMode;
    e_packageMode currentPackageMode;

    Sensors sensors;
    Light light;
    Telemetry telemetry;
    UV_Device device[2];

    UV_Thruster thruster[8];
    void setThrusterNext();
    int currentThruster;

    UV_ControlCircuit controlCircuit[6];
    e_circuit currentCircuit;

    QString udpHostAddress;
    quint16 udpHostPort;

    // Flags
    bool thrusters_on;
    bool reset_imu;
    bool reset_depth;
    bool rgb_light_on;
    bool    ;

    bool stab_march;
    bool stab_lag;
    bool stab_depth;
    bool stab_roll;
    bool stab_pitch;
    bool stab_yaw;
};

#endif // UV_STATE_H
