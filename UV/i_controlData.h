#ifndef I_CONTROLDATA_H
#define I_CONTROLDATA_H

#include "i_basicData.h"
#include "uv_state.h"
#include "uv_device.h"

class IControlData : public IBasicData {
public:
    IControlData();

    void setControlData(ControlData data);

    void setMarch(double march);
    void setLag(double lag);
    void setDepth(double depth);
    void setRoll(double roll);
    void setPitch(double pitch);
    void setYaw(double yaw);
    void setDeviceVelocity(e_Device device, double velocity);
};

#endif // I_CONTROLDATA_H