#ifndef STABILIZATIONSETTINGS_H
#define STABILIZATIONSETTINGS_H

#include <QWidget>
#include <QDebug>
#include <QTimer>

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>

#include "Utilitis/json.h"
#include "UV/i_tuningData.h"

#include "KX_Pult/kx_protocol.h"
#include "KX_Pult/qkx_coeffs.h"

using json = nlohmann::json;

namespace Ui {
    class StabilizationWindow;
}

class StabilizationWindow : public QWidget {
    Q_OBJECT

public:
    explicit StabilizationWindow(QWidget* parent = nullptr);

    // ~StabilizationWindow();

private slots:
    void updateVariables_KX();

    void SetCircuitMarch();
    void SetCircuitLag();
    void SetCircuitDepth();
    void SetCircuitRoll();
    void SetCircuitPitch();
    void SetCircuitYaw();

    void CircuitEdited();
    void saveConfigPressed();
    void saveConfigReleased();
    void FillUiStates();

private:
    QTimer* updateTimer;
    Ui::StabilizationWindow* ui;
    ITuningData interface;

    QString jsonName;
    json allStabilizationJson;

    x_protocol* X_Protocol;
    e_circuit currentCircuit;
    UV_CircuitConstants circuitConstants[6];
    UV_CircuitStates circuitStates[6];

    void FillUiConstants();

    void getJsonFromFile();
    void getJsonFromConstants();
    void getConstantsFromJson();
    void createDefaultStabilizationJson();
    void saveToFile();
};

#endif // STABILIZATIONSETTINGS_H
