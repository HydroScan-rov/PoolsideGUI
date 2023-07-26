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

#include "UV/i_userInterfaceiata.h"
#include "Communication/UdpClient.h"
#include "Control/Joystick.h"
#include "Control/Gamepad.h"
#include "ThrusterSettings/ThrusterWindow.h"
#include "StabilizationSettings/StabilizationWindow.h"

class MainWindow: public QMainWindow, private Ui::MainWindow {
    Q_OBJECT

signals:
    //import from old interface
    void updateCompass(double yaw);

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    Joystick* joystick = nullptr;
    Gamepad* gamepad = nullptr;

    StabilizationWindow stabilizationWindow;
    ThrusterWindow thrusterWindow;

    UdpClient* udp_client;

    QTimer* update_timer;

    IUserInterfaceData uv_interface;

    bool yaw_plus180;
    double prev_yaw;

private slots:
    void updateUi();

    void resetImu();
    void clearResetImu();

    // full screen key combination
    void fullScreenKey();

    //Other buttons
    // void reconnectcROVclick();


};

#endif // MAINWINDOW_H
