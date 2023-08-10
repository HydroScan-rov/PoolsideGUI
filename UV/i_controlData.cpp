#include "i_controlData.h"

IControlData::IControlData() :
    IBasicData() {

}

void IControlData::setControlData(ControlData data) {
    UVMutex.lock();
    UVState.control = data;
    UVMutex.unlock();
}

void IControlData::setMarch(double march) {
    UVMutex.lock();
    UVState.control.march = march;
    UVMutex.unlock();
}

void IControlData::setLag(double lag) {
    UVMutex.lock();
    UVState.control.lag = lag;
    UVMutex.unlock();
}

void IControlData::setDepth(double depth) {
    UVMutex.lock();
    UVState.control.depth = depth;
    UVMutex.unlock();
}

void IControlData::setRoll(double roll) {
    UVMutex.lock();
    UVState.control.roll = roll;
    UVMutex.unlock();
}

void IControlData::setPitch(double pitch) {
    UVMutex.lock();
    UVState.control.pitch = pitch;
    UVMutex.unlock();
}

void IControlData::setYaw(double yaw) {
    UVMutex.lock();
    UVState.control.yaw = yaw;
    UVMutex.unlock();
}

void IControlData::setDeviceVelocity(e_device device, float velocity) {
    UVMutex.lock();
    UVState.device[device].pos += velocity;
    if (UVState.device[device].pos > 2000) {
        UVState.device[device].pos = 2000;
    } else if (UVState.device[device].pos < 1000) {
        UVState.device[device].pos = 1000;
    }
    UVMutex.unlock();
}
