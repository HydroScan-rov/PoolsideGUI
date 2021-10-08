#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include "ControlBase.h"

#include "ui_ControlWindow.h"

#include "Keyboard.h"
#include "Mouse3d.h"
#include "Joystick.h"

namespace Ui {
    class ControlWindow;
}

class ControlWindow : public QWidget {
Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = nullptr);

    ~ControlWindow();

    ControlBase *controller = nullptr;

signals:

    void controlObject(ControlBase *);

    void controlObject_del();

private slots:

    void on_checkBox_KeyBoard_clicked(bool checked);

    void on_checkBox_3dMouse_clicked(bool checked);

    void on_checkBox_JoystickLogitech_clicked(bool checked);

private:
    Ui::ControlWindow *ui;
};

#endif // CONTROL_H
