#include "i_userInterfaceData.h"

IUserInterfaceData::IUserInterfaceData()
    : IBasicData() {

}

ControlData IUserInterfaceData::getControlData() {
    ControlData data;

    UVMutex.lock();
    data = UVState.control;
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

double IUserInterfaceData::getDeviceVelocity(e_Device device) {
    double data;

    UVMutex.lock();
    data = UVState.device[device].velocity;
    UVMutex.unlock();

    return data;
}

void IUserInterfaceData::setPackegeMode(e_packageMode packageMode) {
    UVMutex.lock();
    UVState.currentPackageMode = packageMode;
    UVMutex.unlock();
}

void IUserInterfaceData::setStabRoll(bool value) {
    UVMutex.lock();
    UVState.stab_roll = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setStabPitch(bool value) {
    UVMutex.lock();
    UVState.stab_pitch = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setStabYaw(bool value) {
    UVMutex.lock();
    UVState.stab_yaw = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setStabDepth(bool value) {
    UVMutex.lock();
    UVState.stab_depth = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setResetImu(bool value) {
    UVMutex.lock();
    UVState.reset_imu = value;
    UVMutex.unlock();
}

void IUserInterfaceData::setThrustersON(bool value) {
    UVMutex.lock();
    UVState.thrusters_on = value;
    UVMutex.unlock();
}

