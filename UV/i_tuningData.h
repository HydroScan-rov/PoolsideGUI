#ifndef I_TUNINGDATA_H
#define I_TUNINGDATA_H

#include "i_basicData.h"

#include <QDebug>
/** \brief Interface for accessing data in UV_State to alter specific thruster parameters
 *
 */
class ITuningData : public IBasicData {
public:
    ITuningData();

    void setThrusterAmount(int thrusterAmount);
    int getThrusterAmount();
    void setThrusterData(int slot, UV_Thruster data);
    UV_Thruster getThrusterData(int slot);
    void setThrusterPower(int slot, bool power);

    UV_CircuitStates getCircuitStates(e_circuit circuit);
    void setCircuitConstants(UV_CircuitConstants constants);
    void setCircuitConstants(UV_CircuitConstants constants, e_circuit circuit);
    void setCurrentCircuit(e_circuit circuit);
    void setSaveConstants(bool saveConstants);
};

#endif // I_TUNINGDATA_H
