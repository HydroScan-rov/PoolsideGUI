#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QSettings>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QFileInfo>
#include <QDebug>
#include <QShortcut>
#include <QApplication>
#include <QThread>
#include <QTimer>
#include <QPixmap>

#include "KX_Pult/kx_protocol.h"
#include "KX_Pult/qkx_coeffs.h"

#include "ui_mainwindow.h"

#include "UV/i_userInterfaceData.h"
#include "Communication/UdpClient.h"
#include "Control/Gamepad.h"
#include "ThrusterSettings/ThrusterWindow.h"
#include "StabilizationSettings/StabilizationWindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    QWidget* getVideoWidget();

private:

    void upUiConnectionStatus(int connectionStatus, int reseivedConnectionStatus);
    void upUiImpact(ControlData control, uint16_t tilt);
    void upUiLight(Light light);
    void upUiTelemetry(Telemetry telemetry);
    void upUiSensors(Sensors sensors);

    void getDefaultSettings();

    Gamepad* gamepad = nullptr;
    StabilizationWindow stabilizationWindow;
    ThrusterWindow thrusterWindow;
    UdpClient* udp_client;
    QTimer* update_timer;
    IUserInterfaceData uv_interface;

    QColor colorConnectionStatus;
    QPalette paletteConnectionStatus;

private slots:
    void updateUi();

    void setThrustersOn(bool value);

    void setControModeHandle(bool value);
    void setControModeAuto(bool value);
    void setControModeManeuverable(bool value);
    void setPackageNormal(bool value);
    void setPackageConfig(bool value);
    void setPackageDirect(bool value);

    void setStabilizeMarch(bool value);
    void setStabilizeLag(bool value);
    void setStabilizeDepth(bool value);
    void setStabilizeRoll(bool value);
    void setStabilizePitch(bool value);
    void setStabilizeYaw(bool value);

    void setLowerLightOn(bool value);
    void setRGBLightOn(bool value);
    void setRGBtoWhite();
    void setRGBtoBlue();
    void setLowerLightPower(int value);
    void setRGBLightR(int value);
    void setRGBLightG(int value);
    void setRGBLightB(int value);

    void resetImu();
    void clearResetImu();
    void resetDepth();
    void clearResetDepth();
};

#endif // MAINWINDOW_H
