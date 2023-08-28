#include "i_controlData.h"

IControlData::IControlData() :
    IBasicData() {

}

float IControlData::getControlSpeed() {
    double data;
    UVMutex.lock();
    data = UVState.controlSpeed;
    UVMutex.unlock();
    return data;
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

void IControlData::toggleThrustersOn() {
    UVMutex.lock();
    UVState.thrusters_on = !UVState.thrusters_on;
    UVMutex.unlock();
}

void IControlData::toggleLightOn() {
    UVMutex.lock();
    UVState.rgb_light_on = !UVState.rgb_light_on;
    UVState.lower_light_on = UVState.rgb_light_on;
    UVMutex.unlock();
}

void IControlData::setLightTuningNext() {
    UVMutex.lock();
    if (UVState.currentTunningLight == LIGHT_B)
        UVState.currentTunningLight = LIGHT_LOWER;
    else if (UVState.currentTunningLight == LIGHT_LOWER)
        UVState.currentTunningLight = LIGHT_R;
    else if (UVState.currentTunningLight == LIGHT_R)
        UVState.currentTunningLight = LIGHT_G;
    else if (UVState.currentTunningLight == LIGHT_G)
        UVState.currentTunningLight = LIGHT_B;
    UVMutex.unlock();
}

void IControlData::setLightPowerUp() {
    UVMutex.lock();
    switch (UVState.currentTunningLight) {
        case LIGHT_LOWER:
            if (UVState.light.power_lower_light < 210)
                UVState.light.power_lower_light++;
            break;
        case LIGHT_R:
            if (UVState.light.r_rgb_light < 210)
                UVState.light.r_rgb_light++;
            break;
        case LIGHT_G:
            if (UVState.light.g_rgb_light < 210)
                UVState.light.g_rgb_light++;
            break;
        case LIGHT_B:
            if (UVState.light.b_rgb_light < 210)
                UVState.light.b_rgb_light++;
            break;
    }
    UVMutex.unlock();
}

void IControlData::setLightPowerDown() {
    UVMutex.lock();
    switch (UVState.currentTunningLight) {
        case LIGHT_LOWER:
            if (UVState.light.power_lower_light > 0)
                UVState.light.power_lower_light--;
            break;
        case LIGHT_R:
            if (UVState.light.r_rgb_light > 0)
                UVState.light.r_rgb_light--;
            break;
        case LIGHT_G:
            if (UVState.light.g_rgb_light > 0)
                UVState.light.g_rgb_light--;
            break;
        case LIGHT_B:
            if (UVState.light.b_rgb_light > 0)
                UVState.light.b_rgb_light--;
            break;
    }
    UVMutex.unlock();
}

void IControlData::setControlModeNext() {
    UVMutex.lock();
    if (UVState.currentControlMode == MODE_MANEUVERABLE)
        UVState.currentControlMode = MODE_HANDLE;
    else if (UVState.currentControlMode == MODE_HANDLE)
        UVState.currentControlMode = MODE_AUTO;
    else if (UVState.currentControlMode == MODE_AUTO)
        UVState.currentControlMode = MODE_MANEUVERABLE;
    qDebug() << "UVState.currentControlMode: " << UVState.currentControlMode;

    UVMutex.unlock();
}

void IControlData::setControlSpeedFast() {
    UVMutex.lock();
    UVState.controlSpeed = controlSpeedPreset.fast;
    UVMutex.unlock();
}

void IControlData::setControlSpeedFine() {
    UVMutex.lock();
    UVState.controlSpeed = controlSpeedPreset.slow;
    UVMutex.unlock();
}
