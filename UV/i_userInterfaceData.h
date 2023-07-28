#ifndef I_USERINTERFACEDATA_H
#define I_USERINTERFACEDATA_H

#include "i_basicData.h"
#include "uv_state.h"
#include "uv_device.h"

class IUserInterfaceData: public IBasicData {
public:
    IUserInterfaceData();

    ControlData getControlData();
    Sensors getSensorsData();
    double getDeviceVelocity(e_Device device);

    void setPackegeMode(e_packageMode packageMode);

    void setStabRoll(bool value);
    void setStabPitch(bool value);
    void setStabYaw(bool value);
    void setStabDepth(bool value);

    void setResetImu(bool value);
    void setThrustersON(bool value);

};

#endif // I_USERINTERFACEDATA_H
