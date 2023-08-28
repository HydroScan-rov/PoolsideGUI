#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "ControlBase.h"
#include "SFML/Window.hpp"

class Gamepad: public ControlBase {
    Q_OBJECT

public:
    Gamepad(int updateTimeMs);

public slots:

    void updateDevice();

private:
    int id = 0;
    QTimer* update_timer;

    struct control_axis {
        sf::Joystick::Axis axis;
        e_actionTypes action;
        float multiplier;
    };

    struct control_buttons {
        unsigned int button_id;
        e_actionTypes action;
        bool previousState;
    };

    const static control_axis axis_table[];
    static control_buttons buttons_table[];
};

#endif // GAMEPAD_H
