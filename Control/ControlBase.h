#ifndef CONTROLBASE_H
#define CONTROLBASE_H

#include <QTimer>
#include "UV/i_controlData.h"

class ControlBase: public QObject {
    Q_OBJECT

public:
    ControlBase(QString name);

protected:
    QString device_name;

    enum e_actionTypes {
        SET_MARCH,
        SET_LAG,
        SET_DEPTH,
        SET_ROLL,
        SET_PITCH,
        SET_YAW,
        TILT,

        TOGGLE_THRUSTER_ON,
        TOGGLE_LIGHT_ON,
        LIGHT_TUNING_NEXT,
        LIGHT_POWER_UP,
        LIGHT_POWER_DOWN,
        CONTROL_MODE_NEXT,
        CONTROL_SPEED_FAST,
        CONTROL_SPEED_FINE
    };

    void sendAction(e_actionTypes type, float value);
    void sendAction(e_actionTypes type, int value);
    void sendAction(e_actionTypes type);

    void setMarch(float value);
    void setLag(float value);
    void setDepth(float value);
    void setRoll(float value);
    void setPitch(float value);
    void setYaw(float value);
    void setTilt(float value);

    void toggleThrustersOn();
    void toggleLightOn();
    void setLightTuningNext();
    void setLightPowerUp(int value);
    void setLightPowerDown(int value);
    void setControlModeNext();
    void setControlSpeedFast();
    void setControlSpeedFine();

private:
    IControlData interface;
};

#endif // CONTROLBASE_H
