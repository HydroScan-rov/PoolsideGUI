#ifndef I_USERINTERFACEDATA_H
#define I_USERINTERFACEDATA_H

#include "i_basicData.h"
#include "uv_state.h"
#include "uv_device.h"

class IUserInterfaceData : public IBasicData {
public:
    IUserInterfaceData();

    // get
    int getConnectionStatus();
    int getReseivedConnectionStatus();

    bool getThrustersOn();
    bool getStabilizeMarch();
    bool getStabilizeLag();
    bool getStabilizeDepth();
    bool getStabilizeRoll();
    bool getStabilizePitch();
    bool getStabilizeYaw();
    bool getLowerLightOn();
    bool getRGBLightOn();

    ControlData getControlData();
    uint16_t getDeviceVelocity(e_device device);
    Light getLight();
    Telemetry getTelemetry();
    Sensors getSensorsData();

    // set
    void setThrustersOn(bool value);
    void setControlMode(e_controlMode controlMode);
    void setPackegeMode(e_packageMode packageMode);
    void setStabFlage(e_circuit circuit, bool value);

    void setLowerLightOn(bool value);
    void setRgbLightOn(bool value);
    void setRgbToBlue();
    void setRgbToWhite();
    void setLowerLightPower(int value);
    void setRgbLightPower_R(int value);
    void setRgbLightPower_G(int value);
    void setRgbLightPower_B(int value);

    void setResetImu(bool value);
    void setResetDepth(bool value);
};

#endif // I_USERINTERFACEDATA_H
