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

