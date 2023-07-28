#include "mainwindow.h"

//double X[2000][2];

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent) {
    setupUi(this);

    // Full screen and back
    QShortcut* keyCtrlF = new QShortcut(this);
    keyCtrlF->setKey(Qt::CTRL | Qt::Key_F);
    connect(keyCtrlF, &QShortcut::activated, this, &MainWindow::fullScreenKey);

    // Menu:
    connect(action_SettingsThruster, SIGNAL(triggered()), &thrusterWindow, SLOT(show()));
    connect(action_SettingsControlSystem, SIGNAL(triggered()), &stabilizationWindow, SLOT(show()));

    udp_client = new UdpClient();
    connect(udp_client, SIGNAL(dataUpdated()), this, SLOT(updateUi()));

    QTimer* update_timer = new QTimer(this);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(updateUi()));
    update_timer->start(10);

    gamepad = new Gamepad(10);

    connect(pushButton_ResetIMU, SIGNAL(pressed()), this, SLOT(resetImu()));
    connect(pushButton_ResetIMU, SIGNAL(released()), this, SLOT(clearResetImu()));

    //    const QString ConfigFile = "protocols.conf";
    //    const QString XI = "xi";
    //    const QString KI = "ki";
    //    //передача K
    //    Qkx_coeffs* kProtocol = new Qkx_coeffs(ConfigFile, KI);
    //    //передача X
    //    x_protocol* xProtocol = new x_protocol(ConfigFile, XI, X);

    updateUi();
}

void MainWindow::fullScreenKey() {
    if (QMainWindow::windowState() == Qt::WindowFullScreen) {
        QMainWindow::showNormal();
        QMainWindow::menuBar()->setVisible(true);
    } else {
        QMainWindow::showFullScreen();
        QMainWindow::menuBar()->setVisible(true);
    }
}

void MainWindow::updateUi() {
    // Get data from UVState object
    Sensors sensors = uv_interface.getSensorsData();

    // Update user interface
    progressBar_Depth->setValue(static_cast<int>(sensors.depth));

    label_BarDepth->setText(QString::number(sensors.depth, 'f', 2));

    label_TelemetryRoll->setText(QString::number(sensors.roll, 'f', 2));
    label_TelemetryPitch->setText(QString::number(sensors.pitch, 'f', 2));
    label_TelemetryYaw->setText(QString::number(sensors.yaw, 'f', 2));

    // Update drawing of a compass
    emit updateCompass(sensors.yaw);

    ControlData control = uv_interface.getControlData();
    label_ImpactMarch->setText(QString::number(control.march, 'f', 2));
    label_ImpactLag->setText(QString::number(control.lag, 'f', 2));
    label_ImpactDepth->setText(QString::number(control.depth, 'f', 2));
    label_ImpactYaw->setText(QString::number(control.yaw, 'f', 2));
    label_ImpactRoll->setText(QString::number(control.roll, 'f', 2));
    label_ImpactPitch->setText(QString::number(control.pitch, 'f', 2));

}

void MainWindow::resetImu() {
    uv_interface.setResetImu(true);
}

void MainWindow::clearResetImu() {
    uv_interface.setResetImu(false);
}

// void MainWindow::normalPackageClick() {
//     radioButton_PackageDirect->setChecked(false);
//     radioButton_PackageConfig->setChecked(false);
//     uv_interface.setPackegeMode(PACKAGE_NORMAL);
// }

// void MainWindow::configPackageClick() {
//     radioButton_PackageNormal->setChecked(false);
//     radioButton_PackageDirect->setChecked(false);
//     uv_interface.setPackegeMode(PACKAGE_CONFIG);
// }

// void MainWindow::directPackageClick() {
//     radioButton_PackageNormal->setChecked(false);
//     radioButton_PackageConfig->setChecked(false);
//     uv_interface.setPackegeMode(PACKAGE_DIRECT);
// }

// void MainWindow::stabilizeRollToggled(bool state) {
//     uv_interface.setStabRoll(state);
// }

// void MainWindow::stabilizePitchToggled(bool state) {
//     uv_interface.setStabPitch(state);
// }

// void MainWindow::stabilizeYawToggled(bool state) {
//     uv_interface.setStabYaw(state);
// }

// void MainWindow::stabilizeDepthToggled(bool state) {
//     uv_interface.setStabDepth(state);
// }
