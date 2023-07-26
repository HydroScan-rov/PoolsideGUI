#ifndef UV_THRUSTER_H
#define UV_THRUSTER_H

#include <QString>


class UV_Thruster {
public:
    UV_Thruster();

    bool power;

    int id;
    int adress; //  location on the ROV

    int8_t target_forse;

    bool reverse;

    // relative to the positive directions of the X and Z axes on the ROV
    int8_t kForward;
    int8_t kBackward;

    int8_t sForward;
    int8_t sBackward;
};

#endif // UV_THRUSTER_H
