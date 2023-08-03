#include "i_userInterfaceData.h"

IUserInterfaceData::IUserInterfaceData()
    : IBasicData() {

}

int IUserInterfaceData::getConnectionStatus() {
    int data;
    UVMutex.lock();
    data = UVState.connection_status;
    UVMutex.unlock();
    return data;
}

int IUserInterfaceData::getReseivedConnectionStatus() {
    int data;
    UVMutex.lock();
    data = UVState.reseived_connection_status;
    UVMutex.unlock();
    return data;
}

ControlData IUserInterfaceData::getControlData() {
    ControlData data;
    UVMutex.lock();
    data = UVState.control;
    UVMutex.unlock();
    return data;
}

double IUserInterfaceData::getDeviceVelocity(e_Device device) {
    double data;
    UVMutex.lock();
    data = UVState.device[device].velocity;
    UVMutex.unlock();
    return data;
}

Light IUserInterfaceData::getLight() {
    Light data;
    UVMutex.lock();
    data = UVState.light;
    UVMutex.unlock();
    return data;
}

Telemetry IUserInterfaceData::getTelemetry() {
    Telemetry data;
    UVMutex.lock();
    data = UVState.telemetry;
    UVMutex.unlock();
    return data;
}

Sensors IUserInterfaceData::getSensorsData() {
    Sensors data;
    UVMutex.lock();
    data = UVState.sensors;
    UVMutex.unlock();
    return data;
}

void IUserInterfaceData::setThrustersON(bool value) {
    UVMutex.lock();
    UVState.thrusters_on = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setControlMode(e_controlMode controlMode) {
    UVMutex.lock();
    UVState.currentControlMode = controlMode;
    UVMutex.unlock();
}

void IUserInterfaceData::setPackegeMode(e_packageMode packageMode) {
    UVMutex.lock();
    UVState.currentPackageMode = packageMode;
    UVMutex.unlock();
}

void IUserInterfaceData::setStabFlage(e_circuit circuit, bool value) {
    UVMutex.lock();

    switch (circuit) {
        case MARCH:
            UVState.stab_march = value;
            break;

        case LAG:
            UVState.stab_lag = value;
            break;

        case DEPTH:
            UVState.stab_depth = value;
            break;

        case ROLL:
            UVState.stab_roll = value;
            break;

        case PITCH:
            UVState.stab_pitch = value;
            break;

        case YAW:
            UVState.stab_yaw = value;
            break;
    }

    UVMutex.unlock();
}

void IUserInterfaceData::setLowerLightOn(bool value) {
    UVMutex.lock();
    UVState.lower_light_on = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setRgbLightOn(bool value) {
    UVMutex.lock();
    UVState.rgb_light_on = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setRgbToBlue() {
    UVMutex.lock();
    UVState.light.r_rgb_light = 0;
    UVState.light.g_rgb_light = 255;
    UVState.light.b_rgb_light = 255;
    UVMutex.unlock();
}

void IUserInterfaceData::setRgbToWhite() {
    UVMutex.lock();
    UVState.light.r_rgb_light = 255;
    UVState.light.g_rgb_light = 255;
    UVState.light.b_rgb_light = 255;
    UVMutex.unlock();
}

void IUserInterfaceData::setLowerLightPower(int value) {
    UVMutex.lock();
    UVState.light.power_lower_light = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setRgbLightPower_R(int value) {
    UVMutex.lock();
    UVState.light.power_lower_light = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setRgbLightPower_G(int value) {
    UVMutex.lock();
    UVState.light.power_lower_light = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setRgbLightPower_B(int value) {
    UVMutex.lock();
    UVState.light.power_lower_light = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setResetImu(bool value) {
    UVMutex.lock();
    UVState.reset_imu = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setResetDepth(bool value) {
    UVMutex.lock();
    UVState.reset_depth = value;
    UVMutex.unlock();
}
