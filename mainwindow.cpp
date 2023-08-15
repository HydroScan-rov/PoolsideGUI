#include "mainwindow.h"

//double X[2000][2];

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUi(this);

    // Menu:
    connect(action_SettingsThruster, SIGNAL(triggered()), &thrusterWindow, SLOT(show()));
    connect(action_SettingsControlSystem, SIGNAL(triggered()), &stabilizationWindow, SLOT(show()));

    udp_client = new UdpClient();
    connect(udp_client, SIGNAL(dataUpdated()), this, SLOT(updateUi()));

    QTimer* update_timer = new QTimer(this);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(updateUi()));

    gamepad = new Gamepad(20);

    connect(checkBox_ThrustersOn, SIGNAL(toggled(bool)), this, SLOT(setThrustersOn(bool)));

    connect(radioButton_ControModeHandle, SIGNAL(toggled(bool)), this, SLOT(setControModeHandle(bool)));
    connect(radioButton_ControModeAuto, SIGNAL(toggled(bool)), this, SLOT(setControModeAuto(bool)));
    connect(radioButton_ControModeManeuverable, SIGNAL(toggled(bool)), this, SLOT(setControModeManeuverable(bool)));
    connect(radioButton_PackageNormal, SIGNAL(toggled(bool)), this, SLOT(setPackageNormal(bool)));
    connect(radioButton_PackageConfig, SIGNAL(toggled(bool)), this, SLOT(setPackageConfig(bool)));
    connect(radioButton_PackageDirect, SIGNAL(toggled(bool)), this, SLOT(setPackageDirect(bool)));

    connect(checkBox_StabilizeMarch, SIGNAL(toggled(bool)), this, SLOT(setStabilizeMarch(bool)));
    connect(checkBox_StabilizeLag, SIGNAL(toggled(bool)), this, SLOT(setStabilizeLag(bool)));
    connect(checkBox_StabilizeDepth, SIGNAL(toggled(bool)), this, SLOT(setStabilizeDepth(bool)));
    connect(checkBox_StabilizeRoll, SIGNAL(toggled(bool)), this, SLOT(setStabilizeRoll(bool)));
    connect(checkBox_StabilizePitch, SIGNAL(toggled(bool)), this, SLOT(setStabilizePitch(bool)));
    connect(checkBox_StabilizeYaw, SIGNAL(toggled(bool)), this, SLOT(setStabilizeYaw(bool)));

    connect(checkBox_LowerLightOn, SIGNAL(toggled(bool)), this, SLOT(setLowerLightOn(bool)));
    connect(checkBox_RGBLightOn, SIGNAL(toggled(bool)), this, SLOT(setRGBLightOn(bool)));
    connect(pushButton_LightWhite, SIGNAL(released()), this, SLOT(setRGBtoWhite()));
    connect(pushButton_LightBlue, SIGNAL(released()), this, SLOT(setRGBtoBlue()));

    connect(spinBox_LightLowerPower, SIGNAL(valueChanged(int)), this, SLOT(setLowerLightPower(int)));
    connect(spinBox_LightR, SIGNAL(valueChanged(int)), this, SLOT(setRGBLightR(int)));
    connect(spinBox_LightG, SIGNAL(valueChanged(int)), this, SLOT(setRGBLightG(int)));
    connect(spinBox_LightB, SIGNAL(valueChanged(int)), this, SLOT(setRGBLightB(int)));

    connect(pushButton_ResetIMU, SIGNAL(pressed()), this, SLOT(resetImu()));
    connect(pushButton_ResetIMU, SIGNAL(released()), this, SLOT(clearResetImu()));
    connect(pushButton_ResetDepth, SIGNAL(pressed()), this, SLOT(resetDepth()));
    connect(pushButton_ResetDepth, SIGNAL(released()), this, SLOT(clearResetDepth()));

    // m_player = new QMediaPlayer(this);
    // m_player->play();
    // m_player->setSource(QUrl("gst-pipeline: udpsrc  port=8900 ! application/x-rtp, encoding-name=JPEG,payload=96 ! rtpjpegdepay ! jpegdec ! videoconvert ! autovideosink"));

    // m_videoWidget = new QVideoWidget(this);
    //     horizontalLayout_6->addWidget(m_videoWidget, 7);
    // m_videoWidget->resize(1280, 720);
    // m_player->setVideoOutput(m_videoWidget);



    //    const QString ConfigFile = "protocols.conf";
    //    const QString XI = "xi";
    //    const QString KI = "ki";
    //    //передача K
    //    Qkx_coeffs* kProtocol = new Qkx_coeffs(ConfigFile, KI);
    //    //передача X
    //    x_protocol* xProtocol = new x_protocol(ConfigFile, XI, X);

    updateUi();
    getDefaultSettings();
    update_timer->start(20);
}

void MainWindow::updateUi() {
    upUiConnectionStatus(uv_interface.getConnectionStatus(), uv_interface.getReseivedConnectionStatus());
    upUiImpact(uv_interface.getControlData(), uv_interface.getDeviceVelocity(DEVICE_TILT));
    upUiTelemetry(uv_interface.getTelemetry());
    upUiSensors(uv_interface.getSensorsData());
}

void MainWindow::upUiConnectionStatus(int connectionStatus, int reseivedConnectionStatus) {
    int sliderMax = horizontalSlider_connection->maximum();
    if (reseivedConnectionStatus <= sliderMax ||
        reseivedConnectionStatus >= 2 * sliderMax &&
        reseivedConnectionStatus <= 3 * sliderMax) {
        horizontalSlider_connection->setValue(reseivedConnectionStatus % sliderMax);
    } else {
        horizontalSlider_connection->setValue(sliderMax - reseivedConnectionStatus % sliderMax);
    }

    if (abs(reseivedConnectionStatus - connectionStatus) == 0) {
        colorConnectionStatus.setRgb(0, 255, 0);
    } else if (abs(reseivedConnectionStatus - connectionStatus) <= 1) {
        colorConnectionStatus.setRgb(100, 255, 0);
    } else if (abs(reseivedConnectionStatus - connectionStatus) <= 2) {
        colorConnectionStatus.setRgb(255, 255, 0);
    } else if (abs(reseivedConnectionStatus - connectionStatus) <= 4) {
        colorConnectionStatus.setRgb(255, 165, 0);
    } else {
        colorConnectionStatus.setRgb(255, 0, 0);
    }

    paletteConnectionStatus = horizontalSlider_connection->palette();
    paletteConnectionStatus.setColor(QPalette::ColorRole::Button, colorConnectionStatus);
    paletteConnectionStatus.setColor(QPalette::ColorRole::Highlight, colorConnectionStatus);
    horizontalSlider_connection->setPalette(paletteConnectionStatus);
}

void MainWindow::upUiImpact(ControlData control, uint16_t tilt) {
    label_ImpactMarch->setText(QString::number(control.march, 'f', 1));
    label_ImpactLag->setText(QString::number(control.lag, 'f', 1));
    label_ImpactDepth->setText(QString::number(control.depth, 'f', 1));
    label_ImpactRoll->setText(QString::number(control.roll, 'f', 1));
    label_ImpactPitch->setText(QString::number(control.pitch, 'f', 1));
    label_ImpactYaw->setText(QString::number(control.yaw, 'f', 1));
    label_DevicesTilt->setText(QString::number(tilt));
}

void MainWindow::upUiLight(Light light) {
    spinBox_LightLowerPower->setValue(light.power_lower_light);
    spinBox_LightR->setValue(light.r_rgb_light);
    spinBox_LightG->setValue(light.g_rgb_light);
    spinBox_LightB->setValue(light.b_rgb_light);
}

void MainWindow::upUiTelemetry(Telemetry telemetry) {
    doubleSpinBox_vma1->setValue(telemetry.current_vma[0]);
    doubleSpinBox_vma2->setValue(telemetry.current_vma[1]);
    doubleSpinBox_vma3->setValue(telemetry.current_vma[2]);
    doubleSpinBox_vma4->setValue(telemetry.current_vma[3]);
    doubleSpinBox_vma5->setValue(telemetry.current_vma[4]);
    doubleSpinBox_vma6->setValue(telemetry.current_vma[5]);
    doubleSpinBox_vma7->setValue(telemetry.current_vma[6]);
    doubleSpinBox_vma8->setValue(telemetry.current_vma[7]);

    progressBar_vma1->setValue(static_cast<int>(telemetry.current_vma[0] * 10));
    progressBar_vma2->setValue(static_cast<int>(telemetry.current_vma[1] * 10));
    progressBar_vma3->setValue(static_cast<int>(telemetry.current_vma[2] * 10));
    progressBar_vma4->setValue(static_cast<int>(telemetry.current_vma[3] * 10));
    progressBar_vma5->setValue(static_cast<int>(telemetry.current_vma[4] * 10));
    progressBar_vma6->setValue(static_cast<int>(telemetry.current_vma[5] * 10));
    progressBar_vma7->setValue(static_cast<int>(telemetry.current_vma[6] * 10));
    progressBar_vma8->setValue(static_cast<int>(telemetry.current_vma[7] * 10));

    doubleSpinBox_logicElectronics->setValue(telemetry.current_logic_electronics);

    doubleSpinBox_batteryCell1->setValue(telemetry.voltage_battery_cell[0]);
    doubleSpinBox_batteryCell2->setValue(telemetry.voltage_battery_cell[1]);
    doubleSpinBox_batteryCell3->setValue(telemetry.voltage_battery_cell[2]);
    doubleSpinBox_batteryCell4->setValue(telemetry.voltage_battery_cell[3]);
    doubleSpinBox_battery->setValue(telemetry.voltage_battery);
}

void MainWindow::upUiSensors(Sensors sensors) {
    label_TelemetryRoll->setText(QString::number(sensors.roll, 'f', 2));
    label_TelemetryPitch->setText(QString::number(sensors.pitch, 'f', 2));
    label_TelemetryYaw->setText(QString::number(sensors.yaw, 'f', 2));

    label_BarDepth->setText(QString::number(sensors.depth, 'f', 2));
    progressBar_Depth->setValue(static_cast<int>(sensors.depth * 10));
}

void MainWindow::setThrustersOn(bool value) {
    uv_interface.setThrustersOn(value);
}

void MainWindow::setControModeHandle(bool value) {
    if (value) { uv_interface.setControlMode(MODE_HANDLE); }
}

void MainWindow::setControModeAuto(bool value) {
    if (value) { uv_interface.setControlMode(MODE_AUTO); }
}

void MainWindow::setControModeManeuverable(bool value) {
    if (value) { uv_interface.setControlMode(MODE_MANEUVERABLE); }
}

void MainWindow::setPackageNormal(bool value) {
    if (value) { uv_interface.setPackegeMode(PACKAGE_NORMAL); }
}

void MainWindow::setPackageConfig(bool value) {
    if (value) { uv_interface.setPackegeMode(PACKAGE_CONFIG); }
}

void MainWindow::setPackageDirect(bool value) {
    if (value) { uv_interface.setPackegeMode(PACKAGE_DIRECT); }
}

void MainWindow::setStabilizeMarch(bool value) {
    uv_interface.setStabFlage(MARCH, value);
}

void MainWindow::setStabilizeLag(bool value) {
    uv_interface.setStabFlage(LAG, value);
}

void MainWindow::setStabilizeDepth(bool value) {
    uv_interface.setStabFlage(DEPTH, value);
}

void MainWindow::setStabilizeRoll(bool value) {
    uv_interface.setStabFlage(ROLL, value);
}

void MainWindow::setStabilizePitch(bool value) {
    uv_interface.setStabFlage(PITCH, value);
}

void MainWindow::setStabilizeYaw(bool value) {
    uv_interface.setStabFlage(YAW, value);
}

void MainWindow::setLowerLightOn(bool value) {
    uv_interface.setLowerLightOn(value);
}

void MainWindow::setRGBLightOn(bool value) {
    uv_interface.setRgbLightOn(value);
}

void MainWindow::setRGBtoWhite() {
    uv_interface.setRgbToWhite();
    spinBox_LightR->setValue(rgbPresetWhite.R);
    spinBox_LightG->setValue(rgbPresetWhite.G);
    spinBox_LightB->setValue(rgbPresetWhite.B);
}

void MainWindow::setRGBtoBlue() {
    uv_interface.setRgbToBlue();
    spinBox_LightR->setValue(rgbPresetBlue.R);
    spinBox_LightG->setValue(rgbPresetBlue.G);
    spinBox_LightB->setValue(rgbPresetBlue.B);
}

void MainWindow::setLowerLightPower(int value) {
    uv_interface.setLowerLightPower(value);
}

void MainWindow::setRGBLightR(int value) {
    uv_interface.setRgbLightPower_R(value);
}

void MainWindow::setRGBLightG(int value) {
    uv_interface.setRgbLightPower_G(value);
}

void MainWindow::setRGBLightB(int value) {
    uv_interface.setRgbLightPower_B(value);
}

void MainWindow::resetImu() {
    uv_interface.setResetImu(true);
}

void MainWindow::clearResetImu() {
    uv_interface.setResetImu(false);
}

void MainWindow::resetDepth() {
    uv_interface.setResetDepth(true);
}

void MainWindow::clearResetDepth() {
    uv_interface.setResetDepth(false);
}

void MainWindow::getDefaultSettings() {
    if (uv_interface.getThrustersOn()) { checkBox_ThrustersOn->setCheckState(Qt::Checked); };
    if (uv_interface.getStabilizeMarch()) { checkBox_StabilizeMarch->setCheckState(Qt::Checked); };
    if (uv_interface.getStabilizeLag()) { checkBox_StabilizeLag->setCheckState(Qt::Checked); };
    if (uv_interface.getStabilizeDepth()) { checkBox_StabilizeDepth->setCheckState(Qt::Checked); };
    if (uv_interface.getStabilizeRoll()) { checkBox_StabilizeRoll->setCheckState(Qt::Checked); };
    if (uv_interface.getStabilizePitch()) { checkBox_StabilizePitch->setCheckState(Qt::Checked); };
    if (uv_interface.getStabilizeYaw()) { checkBox_StabilizeYaw->setCheckState(Qt::Checked); };
    if (uv_interface.getLowerLightOn()) { checkBox_LowerLightOn->setCheckState(Qt::Checked); };
    if (uv_interface.getRGBLightOn()) { checkBox_RGBLightOn->setCheckState(Qt::Checked); };
}
