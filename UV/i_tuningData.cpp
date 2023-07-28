#include "i_tuningData.h"

ITuningData::ITuningData() {
}


void ITuningData::setThrusterData(int slot, UV_Thruster data) {
    UVMutex.lock();
    UVState.thruster[slot] = data;
    UVMutex.unlock();
}

UV_Thruster ITuningData::getThrusterData(int slot) {
    UV_Thruster data;

    UVMutex.lock();
    data = UVState.thruster[slot];
    UVMutex.unlock();

    return data;
}

void ITuningData::setThrusterPower(int slot, bool power) {
        UVMutex.lock();
        UVState.thruster[slot].power = power;
        UVMutex.unlock();
}

UV_CircuitStates ITuningData::getCircuitStates(e_circuit countour) {
    UV_CircuitStates data;
    UVMutex.lock();
    data = UVState.controlCircuit[countour].states;
    UVMutex.unlock();
    return data;
}

void ITuningData::setCircuitConstants(UV_CircuitConstants constants) {
    UVMutex.lock();
    UVState.controlCircuit[UVState.currentCircuit].constants = constants;
    UVMutex.unlock();
}

void ITuningData::setCircuitConstants(UV_CircuitConstants constants, e_circuit countour) {
    UVMutex.lock();
    UVState.controlCircuit[countour].constants = constants;
    UVMutex.unlock();
}

void ITuningData::setCurrentCircuit(e_circuit contour) {
    UVMutex.lock();
    UVState.currentCircuit = contour;
    UVMutex.unlock();

}
