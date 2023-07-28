#include "i_serverData.h"

#include <QDebug>
#include <string>
#include <sstream>

IServerData::IServerData()
    : IBasicData() {
}

e_circuit IServerData::getCurrentCircuit() {
    e_circuit currentCircuit;

    UVMutex.lock();
    currentCircuit = UVState.currentCircuit;
    UVMutex.unlock();

    return currentCircuit;
}

e_packageMode IServerData::getCurrentPackageMode() {
    e_packageMode currentPackageMode;

    UVMutex.lock();
    currentPackageMode = UVState.currentPackageMode;
    UVMutex.unlock();

    return currentPackageMode;
}

QByteArray IServerData::generateMessage() {
    QByteArray formed;
    formed.clear();
    switch (getCurrentPackageMode()) {
        case PACKAGE_NORMAL:
            formed = generateNormalMessage();
            break;
        case PACKAGE_CONFIG:
            formed = generateConfigMessage();
            break;
        case PACKAGE_DIRECT:
            formed = generateDirectMessage();
            break;
    }
    return formed;
}

void IServerData::fillFlags(uint8_t& flags) {
    setBit(flags, 0, UVState.thrusters_on);
    setBit(flags, 1, UVState.reset_imu);
    setBit(flags, 2, UVState.reset_depth);
    setBit(flags, 3, UVState.rgb_light_on);
    setBit(flags, 4, UVState.lower_light_on);
}

void IServerData::fillStabFlags(uint8_t& stab_flags) {
    setBit(stab_flags, 0, UVState.stab_march);
    setBit(stab_flags, 1, UVState.stab_lag);
    setBit(stab_flags, 2, UVState.stab_depth);
    setBit(stab_flags, 3, UVState.stab_roll);
    setBit(stab_flags, 4, UVState.stab_pitch);
    setBit(stab_flags, 5, UVState.stab_yaw);
}

void IServerData::fillControlMode(uint8_t& control_mode) {
    for (int i = MODE_HANDLE; i < MODE_MANEUVERABLE; i++) {
        if (UVState.currentControlMode == i) { setBit(control_mode, i, true); };
    }
}

QByteArray IServerData::generateNormalMessage() {
    QByteArray msg;
    msg.clear();
    QDataStream stream(&msg, QIODeviceBase::Append);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    RequestNormalMessage req;
    fillStructure(req);

    stream << req.type;

    stream << req.flags;

    stream << req.march;
    stream << req.lag;
    stream << req.depth;
    stream << req.roll;
    stream << req.pitch;
    stream << req.yaw;

    stream << req.stab_flags;
    stream << req.control_mode;

    stream << req.power_lower_light;
    stream << req.r_rgb_light;
    stream << req.g_rgb_light;
    stream << req.b_rgb_light;

    uint16_t checksum = getCheckSumm16b(msg.data(), msg.size());
    stream << checksum;
    return msg;
}

void IServerData::fillStructure(RequestNormalMessage& req) {
    UVMutex.lock();

    fillFlags(req.flags);

    req.march = UVState.control.march;
    req.lag = UVState.control.lag;
    req.depth = UVState.control.depth;
    req.roll = UVState.control.roll;
    req.pitch = UVState.control.pitch;
    req.yaw = UVState.control.yaw;

    fillStabFlags(req.stab_flags);
    fillControlMode(req.control_mode);

    req.power_lower_light = UVState.light.power_lower_light;
    req.r_rgb_light = UVState.light.r_rgb_light;
    req.g_rgb_light = UVState.light.g_rgb_light;
    req.b_rgb_light = UVState.light.b_rgb_light;

    UVMutex.unlock();
}

QByteArray IServerData::generateConfigMessage() {
    QByteArray msg;
    msg.clear();
    QDataStream stream(&msg, QIODeviceBase::Append);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    RequestConfigMessage req;
    fillStructure(req);

    stream << req.type;

    stream << req.flags;
    stream << req.stab_flags;

    stream << req.current_circuit;

    stream << req.march;
    stream << req.lag;
    stream << req.depth;
    stream << req.roll;
    stream << req.pitch;
    stream << req.yaw;

    stream << req.dt;
    stream << req.k_joy;
    stream << req.k_tuning;

    stream << req.pid_kp;
    stream << req.pid_ki;
    stream << req.pid_kd;
    stream << req.pid_max_i;
    stream << req.pid_min_i;
    stream << req.pid_max;
    stream << req.pid_min;

    stream << req.posFilter_t;
    stream << req.posFilter_k;
    stream << req.speedFilter_y;
    stream << req.speedFilter_k;

    stream << req.out_max;
    stream << req.out_min;

    uint16_t checksum = getCheckSumm16b(msg.data(), msg.size());
    stream << checksum;
    return msg;
}

void IServerData::fillStructure(RequestConfigMessage& req) {
    UVMutex.lock();

    fillFlags(req.flags);
    fillFlags(req.stab_flags);

    for (int i = MARCH; i < YAW; i++) {
        if (UVState.currentCircuit == i) { setBit(req.current_circuit, i, true); };
    }

    req.march = UVState.control.march;
    req.lag = UVState.control.lag;
    req.depth = UVState.control.depth;
    req.roll = UVState.control.roll;
    req.pitch = UVState.control.pitch;
    req.yaw = UVState.control.yaw;

    req.dt = UVState.controlCircuit[UVState.currentCircuit].constants.dt;
    req.k_joy = UVState.controlCircuit[UVState.currentCircuit].constants.k_joy;
    req.k_tuning = UVState.controlCircuit[UVState.currentCircuit].constants.k_tuning;

    req.pid_kp = UVState.controlCircuit[UVState.currentCircuit].constants.pid_kp;
    req.pid_ki = UVState.controlCircuit[UVState.currentCircuit].constants.pid_ki;
    req.pid_kd = UVState.controlCircuit[UVState.currentCircuit].constants.pid_kd;
    req.pid_max_i = UVState.controlCircuit[UVState.currentCircuit].constants.pid_max_i;
    req.pid_min_i = UVState.controlCircuit[UVState.currentCircuit].constants.pid_min_i;
    req.pid_max = UVState.controlCircuit[UVState.currentCircuit].constants.pid_max;
    req.pid_min = UVState.controlCircuit[UVState.currentCircuit].constants.pid_min;

    req.posFilter_t = UVState.controlCircuit[UVState.currentCircuit].constants.posFilter_t;
    req.posFilter_k = UVState.controlCircuit[UVState.currentCircuit].constants.posFilter_k;
    req.speedFilter_y = UVState.controlCircuit[UVState.currentCircuit].constants.speedFilter_y;
    req.speedFilter_k = UVState.controlCircuit[UVState.currentCircuit].constants.speedFilter_k;

    req.out_max = UVState.controlCircuit[UVState.currentCircuit].constants.out_max;
    req.out_min = UVState.controlCircuit[UVState.currentCircuit].constants.out_min;

    UVMutex.unlock();
}

QByteArray IServerData::generateDirectMessage() {
    QByteArray msg;
    msg.clear();
    QDataStream stream(&msg, QIODeviceBase::Append);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    RequestDirectMessage req;
    fillStructure(req);

    stream << req.type;

    stream << req.flags;

    stream << req.id;
    stream << req.adress;

    stream << req.target_forse;

    stream << req.reverse;
    stream << req.k_forward;
    stream << req.k_backward;
    stream << req.s_forward;
    stream << req.s_backward;

    uint16_t checksum = getCheckSumm16b(msg.data(), msg.size());
    stream << checksum;
    return msg;
}

void IServerData::fillStructure(RequestDirectMessage& req) {
    UVMutex.lock();
    UVState.setThrusterNext();

    req.id = UVState.currentThruster;
    req.adress = UVState.thruster[UVState.currentThruster].adress;

    if (UVState.thruster[UVState.currentThruster].power == false) {
        req.target_forse = 0;
    } else {
        req.target_forse = UVState.thruster[UVState.currentThruster].target_forse;
    }

    req.reverse = UVState.thruster[UVState.currentThruster].reverse;
    req.k_forward = UVState.thruster[UVState.currentThruster].kForward;
    req.k_backward = UVState.thruster[UVState.currentThruster].kBackward;
    req.s_forward = UVState.thruster[UVState.currentThruster].sForward;
    req.s_backward = UVState.thruster[UVState.currentThruster].sBackward;

    UVMutex.unlock();
}

void IServerData::parseMessage(QByteArray message) {
    switch (getCurrentPackageMode()) {
        case PACKAGE_NORMAL:
            parseNormalMessage(message);
            break;
        case PACKAGE_CONFIG:
            parseConfigMessage(message);
            break;
        case PACKAGE_DIRECT:
            parseDirectMessage(message);
            break;
        default:
            throw std::invalid_argument("invalid PackageMode");
    }
}

void IServerData::parseNormalMessage(QByteArray msg) {
    ResponseNormalMessage res;
    uint16_t checksum_calc = getCheckSumm16b(msg.data(), msg.size() - 2);

    QDataStream stream(&msg, QIODeviceBase::ReadOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    stream >> res.depth;
    stream >> res.roll;
    stream >> res.pitch;
    stream >> res.yaw;

    stream >> res.distance_l;
    stream >> res.distance_r;

    stream >> res.speed_down;
    stream >> res.speed_right;

    stream >> res.current_logic_electronics;
    for (size_t i = 0; i < 8; i++) { stream >> res.current_vma[i]; }
    for (size_t i = 0; i < 4; i++) { stream >> res.voltage_battery_cell[i]; }
    stream >> res.voltage_battery;

    stream >> res.checksum;

    if (res.checksum != checksum_calc) {
        qDebug() << "Checksum NormalMessage is invalid";
        std::stringstream stream;
        stream << "[ISERVERDATA] Checksum is invalid. Calculated: [" <<
            std::ios::hex << checksum_calc << "] " <<
            "Received: [" <<
            std::ios::hex << res.checksum << "]";
        throw std::invalid_argument(stream.str());
    }

    pullFromStructure(res);
}

void IServerData::pullFromStructure(ResponseNormalMessage res) {
    UVMutex.lock();

    UVState.sensors.depth = res.depth;
    UVState.sensors.roll = res.roll;
    UVState.sensors.pitch = res.pitch;
    UVState.sensors.yaw = res.yaw;

    UVState.sensors.distance_l = res.distance_l;
    UVState.sensors.distance_r = res.distance_r;
    UVState.sensors.speed_down = res.speed_down;
    UVState.sensors.speed_right = res.speed_right;

    UVState.telemetry.current_logic_electronics = res.speed_right;
    for (size_t i = 0; i < 8; i++) { UVState.telemetry.current_vma[i] = res.current_vma[i]; }
    for (size_t i = 0; i < 4; i++) { UVState.telemetry.voltage_battery_cell[i] = res.voltage_battery_cell[i]; }
    UVState.telemetry.voltage_battery = res.voltage_battery;

    UVMutex.unlock();
}

void IServerData::parseConfigMessage(QByteArray msg) {
    ResponseConfigMessage res;
    uint16_t checksum_calc = getCheckSumm16b(msg.data(), msg.size() - 2);

    QDataStream stream(&msg, QIODeviceBase::ReadOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    stream >> res.depth;
    stream >> res.roll;
    stream >> res.pitch;
    stream >> res.yaw;

    stream >> res.input;
    stream >> res.pos_filtered;
    stream >> res.speed_filtered;

    stream >> res.joy_gained;
    stream >> res.target_integrator;

    stream >> res.pid_pre_error;
    stream >> res.pid_error;
    stream >> res.pid_integral;
    stream >> res.pid_Pout;
    stream >> res.pid_Iout;
    stream >> res.pid_Dout;
    stream >> res.pid_output;

    stream >> res.tuning_summator;
    stream >> res.speed_error;
    stream >> res.out_pre_saturation;
    stream >> res.out;

    stream >> res.current_logic_electronics;
    for (size_t i = 0; i < 8; i++) { stream >> res.current_vma[i]; }
    for (size_t i = 0; i < 4; i++) { stream >> res.voltage_battery_cell[i]; }
    stream >> res.voltage_battery;

    stream >> res.checksum;

    if (res.checksum != checksum_calc) {
        qDebug() << "Checksum ConfigMessage is invalid";
        std::stringstream stream;
        stream << "[ISERVERDATA] Checksum is invalid. Calculated: [" <<
            std::ios::hex << checksum_calc << "] " <<
            "Received: [" <<
            std::ios::hex << res.checksum << "]";
        throw std::invalid_argument(stream.str());
    }

    pullFromStructure(res);
}

void IServerData::pullFromStructure(ResponseConfigMessage res) {
    UVMutex.lock();

    UVState.sensors.depth = res.depth;
    UVState.sensors.roll = res.roll;
    UVState.sensors.pitch = res.pitch;
    UVState.sensors.yaw = res.yaw;

    UVState.controlCircuit[UVState.currentCircuit].states.input = res.input;
    UVState.controlCircuit[UVState.currentCircuit].states.pos_filtered = res.pos_filtered;
    UVState.controlCircuit[UVState.currentCircuit].states.speed_filtered = res.speed_filtered;

    UVState.controlCircuit[UVState.currentCircuit].states.joy_gained = res.joy_gained;
    UVState.controlCircuit[UVState.currentCircuit].states.target_integrator = res.target_integrator;

    UVState.controlCircuit[UVState.currentCircuit].states.pid_pre_error = res.pid_pre_error;
    UVState.controlCircuit[UVState.currentCircuit].states.pid_error = res.pid_error;
    UVState.controlCircuit[UVState.currentCircuit].states.pid_integral = res.pid_integral;
    UVState.controlCircuit[UVState.currentCircuit].states.pid_Pout = res.pid_Pout;
    UVState.controlCircuit[UVState.currentCircuit].states.pid_Iout = res.pid_Iout;
    UVState.controlCircuit[UVState.currentCircuit].states.pid_Dout = res.pid_Dout;
    UVState.controlCircuit[UVState.currentCircuit].states.pid_output = res.pid_output;

    UVState.controlCircuit[UVState.currentCircuit].states.tuning_summator = res.tuning_summator;
    UVState.controlCircuit[UVState.currentCircuit].states.speed_error = res.speed_error;
    UVState.controlCircuit[UVState.currentCircuit].states.out_pre_saturation = res.out_pre_saturation;
    UVState.controlCircuit[UVState.currentCircuit].states.out = res.out;

    UVState.telemetry.current_logic_electronics = res.current_logic_electronics;
    for (size_t i = 0; i < 8; i++) { UVState.telemetry.current_vma[i] = res.current_vma[i]; }
    for (size_t i = 0; i < 4; i++) { UVState.telemetry.voltage_battery_cell[i] = res.voltage_battery_cell[i]; }
    UVState.telemetry.voltage_battery = res.voltage_battery;

    UVMutex.unlock();
}

void IServerData::parseDirectMessage(QByteArray msg) {
    ResponseDirectMessage res;
    uint16_t checksum_calc = getCheckSumm16b(msg.data(), msg.size() - 2);

    QDataStream stream(&msg, QIODeviceBase::ReadOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    stream >> res.id;

    stream >> res.current_logic_electronics;
    for (size_t i = 0; i < 8; i++) { stream >> res.current_vma[i]; }
    for (size_t i = 0; i < 4; i++) { stream >> res.voltage_battery_cell[i]; }
    stream >> res.voltage_battery;

    stream >> res.checksum;

    if (res.checksum != checksum_calc) {
        std::stringstream stream;
        stream << "[ISERVERDATA] Checksum is invalid. Calculated: [" <<
            std::ios::hex << checksum_calc << "] " <<
            "Received: [" <<
            std::ios::hex << res.checksum << "]";
        throw std::invalid_argument(stream.str());
    }

    pullFromStructure(res);
}

void IServerData::pullFromStructure(ResponseDirectMessage res) {
    UVMutex.lock();

    UVState.telemetry.current_logic_electronics = res.current_logic_electronics;
    for (size_t i = 0; i < 8; i++) { UVState.telemetry.current_vma[i] = res.current_vma[i]; }
    for (size_t i = 0; i < 4; i++) { UVState.telemetry.voltage_battery_cell[i] = res.voltage_battery_cell[i]; }
    UVState.telemetry.voltage_battery = res.voltage_battery;

    UVMutex.unlock();
}

/* CRC16-CCITT algorithm */
uint16_t IServerData::getCheckSumm16b(char* pcBlock, int len) {
    uint16_t crc = 0xFFFF;
    //int crc_fix = reinterpret_cast<int*>(&crc);
    uint8_t i;

    while (len--) {
        crc ^= *pcBlock++ << 8;

        for (i = 0; i < 8; i++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}

void IServerData::setBit(uint8_t& byte, uint8_t bit, bool state) {
    uint8_t value = 1;
    if (state) {
        byte = byte | (value << bit);
    } else {
        byte = byte & ~(value << bit);
    }
}

bool IServerData::setBit(uint8_t& input, uint8_t bit) {
    return static_cast<bool>((input << (8 - bit)) >> 8);
}
