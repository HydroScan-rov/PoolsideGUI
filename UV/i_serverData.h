#ifndef I_SERVERDATA_H
#define I_SERVERDATA_H

#include <QDataStream>
#include <QByteArray>

#include "i_basicData.h"
#include "uv_state.h"

class IServerData : public IBasicData {
public:
    IServerData();

    QByteArray generateMessage();
    uint8_t getCurrentPackageRequestLenght(); // pult -> ROV
    uint8_t getCurrentPackageResponseLenght(); // ROV -> pult
    void parseMessage(QByteArray message);

    e_packageMode getCurrentPackageMode();
    e_circuit getCurrentCircuit();

private:
    QDataStream* port;

    // Normal pult -> ROV
    struct RequestNormalMessage {
        const static uint8_t lenght = 37;  // 1(type) + 34(message) + 2(checksum) = 37 dyte

        const static uint8_t type = 0xA5;
        uint8_t connection_status;

        uint8_t flags; // [0]thrusters_on, [1]reset_imu, [2]reset_depth, [3]rgb_light_on, [4]lower_light_on,
        uint8_t stab_flags; // [0]march, [1]lag, [2]depth, [3]roll, [4]pitch, [5]yaw
        uint8_t control_mode; // [0]handle , [1]auto (set depth and yaw, pitch and roll = 0), [2]maneuverable (set depth, yaw, pitch and roll)

        float march; // NED coordinate system
        float lag;
        float depth;
        float roll;
        float pitch;
        float yaw;

        uint16_t tilt; // 1000-2000

        uint8_t power_lower_light; // 0-255
        uint8_t r_rgb_light; // 0-255
        uint8_t g_rgb_light;
        uint8_t b_rgb_light;

        uint16_t checksum;
    };

    // Normal ROV -> pult
    struct ResponseNormalMessage {
        const static uint8_t lenght = 91; // 89(message) + 2(checksum) = 91 dyte

        uint8_t reseived_connection_status;

        float_t depth;
        float_t roll;
        float_t pitch;
        float_t yaw;

        float_t distance_l; // distance from laser rangefinder
        float_t distance_r;

        float_t speed_down; // speed signal from jetson
        float_t speed_right;

        float_t current_logic_electronics; // from jetson + raspberry dc-dc
        float_t current_vma[8];
        float_t voltage_battery_cell[4];
        float_t voltage_battery; // 56

        uint16_t checksum;
    };

    // Config pult -> ROV
    struct RequestConfigMessage {
        const static uint8_t lenght = 95; // 1(type) + 92(message) + 2(checksum) = 95 dyte

        const static uint8_t type = 0x55;
        uint8_t connection_status;

        uint8_t flags; // [0]thrusters_on, [1]reset_imu, [2]reset_depth, [3]rgb_light_on, [4]lower_light_on,
        uint8_t stab_flags; // stab [0]march, [1]lag, [2]depth, [3]roll, [4]pitch, [5]yaw, [6]thrusters_on, [6]reset_imu
        uint8_t current_circuit; // current contour: [0]march, [1]lag, [2]depth, [3]roll, [4]pitch, [5]yaw

        float_t march;
        float_t lag;
        float_t depth;
        float_t roll;
        float_t pitch;
        float_t yaw;

        float_t k_joy;
        float_t k_tuning;

        float_t pid_kp;
        float_t pid_ki;
        float_t pid_kd;
        float_t pid_max_i;
        float_t pid_min_i;
        float_t pid_max;
        float_t pid_min;

        float_t posFilter_t;
        float_t posFilter_k;
        float_t speedFilter_t;
        float_t speedFilter_k;

        float_t out_k;
        float_t out_max;
        float_t out_min;

        uint16_t checksum;
    };

    // Config ROV -> pult
    struct ResponseConfigMessage {
        const static uint8_t lenght = 141; // 139(message) + 2(checksum) = 139 dyte

        uint8_t reseived_connection_status;

        float_t depth;
        float_t roll;
        float_t pitch;
        float_t yaw;

        float_t input;
        float_t pos;
        float_t pos_filtered;
        float_t speed;
        float_t speed_filtered;

        float_t joy_gained;
        float_t target_integrator;

        float_t pid_pre_error;
        float_t pid_error;
        float_t pid_Pout;
        float_t pid_I_gained;
        float_t pid_Iout;
        float_t pid_Dout;
        float_t pid_SumOut;
        float_t pid_output;

        float_t tuning_summator;
        float_t speed_error;
        float_t out_pre_saturation;
        float_t out;

        float_t current_logic_electronics; // from jetson + raspberry dc-dc
        float_t current_vma[8];
        float_t voltage_battery_cell[4];
        float_t voltage_battery; // 56

        uint16_t checksum;
    };

    // Direct pult -> ROV
    struct RequestDirectMessage {
        const static uint8_t lenght = 24; // 1(type) + 21(message) + 2(checksum) = 24 dyte

        const static uint8_t type = 0xAA;
        uint8_t connection_status;

        uint8_t flags; // [0]thrusters_on, [1]reset_imu, [2]reset_depth, [3]rgb_light_on, [4]lower_light_on,

        uint8_t id; // 0..7
        uint8_t adress; // 0..7

        float_t target_forse; // newton

        uint8_t reverse;
        float_t k_forward;
        float_t k_backward;
        int16_t s_forward; // max PWM
        int16_t s_backward; // min PWM

        uint16_t checksum; // 1(type) + 20(message) + 2(checksum) = 23 dyte
    };

    // Direct ROV -> pult
    struct ResponseDirectMessage {
        const static uint8_t lenght = 59; // 57(message) + 2(checksum) = 59 dyte

        uint8_t reseived_connection_status;

        float_t current_logic_electronics; // from jetson + raspberry dc-dc
        float_t current_vma[8];
        float_t voltage_battery_cell[4];
        float_t voltage_battery; // 56

        uint16_t checksum;
    };

    QByteArray generateNormalMessage();
    QByteArray generateConfigMessage();
    QByteArray generateDirectMessage();
    void fillStructure(RequestNormalMessage& req);
    void fillStructure(RequestConfigMessage& req);
    void fillStructure(RequestDirectMessage& req);
    void fillFlags(uint8_t& flags);
    void fillStabFlags(uint8_t& stab_flags);
    void fillControlMode(uint8_t& control_mode);

    void parseNormalMessage(QByteArray msg);
    void parseConfigMessage(QByteArray msg);
    void parseDirectMessage(QByteArray msg);
    void pullFromStructure(ResponseNormalMessage res);
    void pullFromStructure(ResponseConfigMessage res);
    void pullFromStructure(ResponseDirectMessage res);

    uint16_t getCheckSumm16b(char* pcBlock, int len);
    uint8_t isCheckSumm16bCorrect(char* pcBlock, int len);
    void setBit(uint8_t& byte, uint8_t bit, bool state);
    bool setBit(uint8_t& input, uint8_t bit);
};

#endif // I_SERVERDATA_H
