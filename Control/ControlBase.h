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
    };

    void sendAction(e_actionTypes type, float value);
    void sendAction(e_actionTypes type, int8_t value);

    void setMarch(float value);
    void setLag(float value);
    void setDepth(float value);
    void setRoll(float value);
    void setPitch(float value);
    void setYaw(float value);

    void setTilt(double value);

private:
    IControlData interface;
};

#endif // CONTROLBASE_H
