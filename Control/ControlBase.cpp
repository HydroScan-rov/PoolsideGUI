#include "ControlBase.h"
#include <QDebug>

ControlBase::ControlBase(QString name) {
    device_name = name;
}

void ControlBase::sendAction(e_actionTypes type, float value) {
    switch (type) {
        case SET_MARCH:
            setMarch(value);
            break;

        case SET_LAG:
            setLag(value);
            break;

        case SET_DEPTH:
            setDepth(value);
            break;

        case SET_ROLL:
            setRoll(value);
            break;

        case SET_PITCH:
            setPitch(value);
            break;

        case SET_YAW:
            setYaw(value);
            break;

        case TILT:
            setTilt(value);
            break;
    }
}

void ControlBase::sendAction(e_actionTypes type) {
    switch (type) {
        case TOGGLE_THRUSTER_ON:
            toggleThrustersOn();
            break;
        case TOGGLE_LIGHT_ON:
            toggleLightOn();
            break;
        case LIGHT_TUNING_NEXT:
            setLightTuningNext();
            break;
        case LIGHT_POWER_UP:
            setLightPowerUp();
            break;
        case LIGHT_POWER_DOWN:
            setLightPowerDown();
            break;

        case CONTROL_MODE_NEXT:
            setControlModeNext();
            break;
        case CONTROL_SPEED_FAST:
            setControlSpeedFast();
            break;
        case CONTROL_SPEED_FINE:
            setControlSpeedFine();
            break;
    }
}

void ControlBase::setMarch(float value) {
    interface.setMarch(value);
}

void ControlBase::setLag(float value) {
    interface.setLag(value);
}

void ControlBase::setDepth(float value) {
    interface.setDepth(value);
}

void ControlBase::setRoll(float value) {
    interface.setRoll(value);
}

void ControlBase::setPitch(float value) {
    interface.setPitch(value);
}

void ControlBase::setYaw(float value) {
    interface.setYaw(value);
}

void ControlBase::setTilt(float value) {
    interface.setDeviceVelocity(e_device::DEVICE_TILT, value);
}

void ControlBase::toggleThrustersOn() {
    interface.toggleThrustersOn();
}

void ControlBase::toggleLightOn() {
    interface.toggleLightOn();
}

void ControlBase::setLightTuningNext() {
    interface.setLightTuningNext();
}

void ControlBase::setLightPowerUp() {
    interface.setLightPowerUp();
}

void ControlBase::setLightPowerDown() {
    interface.setLightPowerDown();
}

void ControlBase::setControlModeNext() {
    interface.setControlModeNext();
}

void ControlBase::setControlSpeedFast() {
    interface.setControlSpeedFast();
}

void ControlBase::setControlSpeedFine() {
    interface.setControlSpeedFine();
}
