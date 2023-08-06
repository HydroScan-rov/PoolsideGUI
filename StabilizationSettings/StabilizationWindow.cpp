#include "StabilizationWindow.h"
#include "ui_StabilizationWindow.h"

// double X[2000][2];

StabilizationWindow::StabilizationWindow(QWidget* parent) :
    QWidget(parent), ui(new Ui::StabilizationWindow) {
    ui->setupUi(this);
    jsonName = "stabilizationJson.json";

    if (std::filesystem::exists(jsonName.toStdString())) {
        getJsonFromFile();
        qDebug() << jsonName << " открыт имеющийся";
    } else {
        createDefaultStabilizationJson();
        qDebug() << "createDefaultStabilizationJson done";
        saveToFile();
        qDebug() << jsonName << " создан новый";
    }
    getConstantsFromJson();

    connect(ui->pushButton_CS_saveConfig, SIGNAL(clicked()), this, SLOT(saveConfigClicked()));

    connect(ui->Const_k_joy, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_k_tuning, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_pid_kp, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_pid_ki, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_pid_kd, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_pid_max_i, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_pid_min_i, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_pid_max, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_pid_min, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_posFilter_t, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_posFilter_k, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_speedFilter_t, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_speedFilter_k, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_out_k, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_out_max, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));
    connect(ui->Const_out_min, SIGNAL(editingFinished()), this, SLOT(CircuitEdited()));

    connect(ui->radioButton_CS_MarchSelect, SIGNAL(clicked()), this, SLOT(SetCircuitMarch()));
    connect(ui->radioButton_CS_LagSelect, SIGNAL(clicked()), this, SLOT(SetCircuitLag()));
    connect(ui->radioButton_CS_DepthSelect, SIGNAL(clicked()), this, SLOT(SetCircuitDepth()));
    connect(ui->radioButton_CS_RollSelect, SIGNAL(clicked()), this, SLOT(SetCircuitRoll()));
    connect(ui->radioButton_CS_PitchSelect, SIGNAL(clicked()), this, SLOT(SetCircuitPitch()));
    connect(ui->radioButton_CS_YawSelect, SIGNAL(clicked()), this, SLOT(SetCircuitYaw()));

    // X_Protocol = new x_protocol("protocols.conf", "xi", X);

    emit ui->radioButton_CS_YawSelect->setChecked(true);
    emit SetCircuitYaw();

    FillUiConstants();
    FillUiStates();
}

void StabilizationWindow::SetCircuitMarch() {
    currentCircuit = MARCH;
    interface.setCurrentCircuit(MARCH);
    FillUiConstants();
}

void StabilizationWindow::SetCircuitLag() {
    currentCircuit = LAG;
    interface.setCurrentCircuit(LAG);
    FillUiConstants();
}

void StabilizationWindow::SetCircuitDepth() {
    currentCircuit = DEPTH;
    interface.setCurrentCircuit(DEPTH);
    FillUiConstants();
}

void StabilizationWindow::SetCircuitRoll() {
    currentCircuit = ROLL;
    interface.setCurrentCircuit(ROLL);
    FillUiConstants();
}

void StabilizationWindow::SetCircuitPitch() {
    currentCircuit = PITCH;
    interface.setCurrentCircuit(PITCH);
    FillUiConstants();
}

void StabilizationWindow::SetCircuitYaw() {
    currentCircuit = YAW;
    interface.setCurrentCircuit(YAW);
    FillUiConstants();
}

void StabilizationWindow::CircuitEdited() {
    circuitConstants[currentCircuit].k_joy = float(ui->Const_k_joy->value());
    circuitConstants[currentCircuit].k_tuning = float(ui->Const_k_tuning->value());
    circuitConstants[currentCircuit].pid_kp = float(ui->Const_pid_kp->value());
    circuitConstants[currentCircuit].pid_ki = float(ui->Const_pid_ki->value());
    circuitConstants[currentCircuit].pid_kd = float(ui->Const_pid_kd->value());
    circuitConstants[currentCircuit].pid_max_i = float(ui->Const_pid_max_i->value());
    circuitConstants[currentCircuit].pid_min_i = float(ui->Const_pid_min_i->value());
    circuitConstants[currentCircuit].pid_max = float(ui->Const_pid_max->value());
    circuitConstants[currentCircuit].pid_min = float(ui->Const_pid_min->value());
    circuitConstants[currentCircuit].posFilter_t = float(ui->Const_posFilter_t->value());
    circuitConstants[currentCircuit].posFilter_k = float(ui->Const_posFilter_k->value());
    circuitConstants[currentCircuit].speedFilter_t = float(ui->Const_speedFilter_t->value());
    circuitConstants[currentCircuit].speedFilter_k = float(ui->Const_speedFilter_k->value());
    circuitConstants[currentCircuit].out_k = float(ui->Const_out_k->value());
    circuitConstants[currentCircuit].out_max = float(ui->Const_out_max->value());
    circuitConstants[currentCircuit].out_min = float(ui->Const_out_min->value());

    interface.setCircuitConstants(circuitConstants[currentCircuit]);
}

void StabilizationWindow::saveConfigClicked() {
    getJsonFromConstants();
    saveToFile();
}

void StabilizationWindow::FillUiConstants() {
    ui->Const_k_joy->setValue(circuitConstants[currentCircuit].k_joy);
    ui->Const_k_tuning->setValue(circuitConstants[currentCircuit].k_tuning);
    ui->Const_pid_kp->setValue(circuitConstants[currentCircuit].pid_kp);
    ui->Const_pid_ki->setValue(circuitConstants[currentCircuit].pid_ki);
    ui->Const_pid_kd->setValue(circuitConstants[currentCircuit].pid_kd);
    ui->Const_pid_max_i->setValue(circuitConstants[currentCircuit].pid_max_i);
    ui->Const_pid_min_i->setValue(circuitConstants[currentCircuit].pid_min_i);
    ui->Const_pid_max->setValue(circuitConstants[currentCircuit].pid_max);
    ui->Const_pid_min->setValue(circuitConstants[currentCircuit].pid_min);
    ui->Const_posFilter_t->setValue(circuitConstants[currentCircuit].posFilter_t);
    ui->Const_posFilter_k->setValue(circuitConstants[currentCircuit].posFilter_k);
    ui->Const_speedFilter_t->setValue(circuitConstants[currentCircuit].speedFilter_t);
    ui->Const_speedFilter_k->setValue(circuitConstants[currentCircuit].speedFilter_k);
    ui->Const_out_k->setValue(circuitConstants[currentCircuit].out_k);
    ui->Const_out_max->setValue(circuitConstants[currentCircuit].out_max);
    ui->Const_out_min->setValue(circuitConstants[currentCircuit].out_min);
}

void StabilizationWindow::FillUiStates() {
    circuitStates[currentCircuit] = interface.getCircuitStates(currentCircuit);

    ui->State_input->setText(QString::number(circuitStates[currentCircuit].input));
    ui->State_pos->setText(QString::number(circuitStates[currentCircuit].pos));
    ui->State_pos_filtered->setText(QString::number(circuitStates[currentCircuit].pos_filtered));
    ui->State_speed->setText(QString::number(circuitStates[currentCircuit].speed));
    ui->State_speed_filtered->setText(QString::number(circuitStates[currentCircuit].speed_filtered));
    ui->State_joy_gained->setText(QString::number(circuitStates[currentCircuit].joy_gained));
    ui->State_target_integrator->setText(QString::number(circuitStates[currentCircuit].target_integrator));
    ui->State_pid_error->setText(QString::number(circuitStates[currentCircuit].pid_error));
    ui->State_pid_Pout->setText(QString::number(circuitStates[currentCircuit].pid_Pout));
    ui->State_pid_I_gained->setText(QString::number(circuitStates[currentCircuit].pid_I_gained));
    ui->State_pid_Iout->setText(QString::number(circuitStates[currentCircuit].pid_Iout));
    ui->State_pid_Dout->setText(QString::number(circuitStates[currentCircuit].pid_Dout));
    ui->State_pid_SumOut->setText(QString::number(circuitStates[currentCircuit].pid_SumOut));
    ui->State_pid_output->setText(QString::number(circuitStates[currentCircuit].pid_output));
    ui->State_tuning_summator->setText(QString::number(circuitStates[currentCircuit].tuning_summator));
    ui->State_speed_error->setText(QString::number(circuitStates[currentCircuit].speed_error));
    ui->State_out_pre_saturation->setText(QString::number(circuitStates[currentCircuit].out_pre_saturation));
    ui->State_out->setText(QString::number(circuitStates[currentCircuit].out));

    // updateVariables_KX();
}

void StabilizationWindow::getJsonFromFile() {
    std::ifstream file(jsonName.toStdString());
    allStabilizationJson = json::parse(file);
    // qDebug() << allStabilizationJson[std::to_string(1) +/ "_pJoyUnitCast"];
    file.close();
}

void StabilizationWindow::getJsonFromConstants() {
    for (int i = MARCH; i < YAW + 1; i++) {
        allStabilizationJson[std::to_string(i) + "_k_joy"] = circuitConstants[i].k_joy;
        allStabilizationJson[std::to_string(i) + "_k_tuning"] = circuitConstants[i].k_tuning;
        allStabilizationJson[std::to_string(i) + "_pid_kp"] = circuitConstants[i].pid_kp;
        allStabilizationJson[std::to_string(i) + "_pid_ki"] = circuitConstants[i].pid_ki;
        allStabilizationJson[std::to_string(i) + "_pid_kd"] = circuitConstants[i].pid_kd;
        allStabilizationJson[std::to_string(i) + "_pid_max_i"] = circuitConstants[i].pid_max_i;
        allStabilizationJson[std::to_string(i) + "_pid_min_i"] = circuitConstants[i].pid_min_i;
        allStabilizationJson[std::to_string(i) + "_pid_max"] = circuitConstants[i].pid_max;
        allStabilizationJson[std::to_string(i) + "_pid_min"] = circuitConstants[i].pid_min;
        allStabilizationJson[std::to_string(i) + "_posFilter_t"] = circuitConstants[i].posFilter_t;
        allStabilizationJson[std::to_string(i) + "_posFilter_k"] = circuitConstants[i].posFilter_k;
        allStabilizationJson[std::to_string(i) + "_speedFilter_t"] = circuitConstants[i].speedFilter_t;
        allStabilizationJson[std::to_string(i) + "_speedFilter_k"] = circuitConstants[i].speedFilter_k;
        allStabilizationJson[std::to_string(i) + "_out_k"] = circuitConstants[i].out_k;
        allStabilizationJson[std::to_string(i) + "_out_max"] = circuitConstants[i].out_max;
        allStabilizationJson[std::to_string(i) + "_out_min"] = circuitConstants[i].out_min;
    };
}

void StabilizationWindow::getConstantsFromJson() {
    for (int i = MARCH; i < YAW + 1; i++) {
        circuitConstants[i].k_joy = allStabilizationJson[std::to_string(i) + "_k_joy"];
        circuitConstants[i].k_tuning = allStabilizationJson[std::to_string(i) + "_k_tuning"];
        circuitConstants[i].pid_kp = allStabilizationJson[std::to_string(i) + "_pid_kp"];
        circuitConstants[i].pid_ki = allStabilizationJson[std::to_string(i) + "_pid_ki"];
        circuitConstants[i].pid_kd = allStabilizationJson[std::to_string(i) + "_pid_kd"];
        circuitConstants[i].pid_max_i = allStabilizationJson[std::to_string(i) + "_pid_max_i"];
        circuitConstants[i].pid_min_i = allStabilizationJson[std::to_string(i) + "_pid_min_i"];
        circuitConstants[i].pid_max = allStabilizationJson[std::to_string(i) + "_pid_max"];
        circuitConstants[i].pid_min = allStabilizationJson[std::to_string(i) + "_pid_min"];
        circuitConstants[i].posFilter_t = allStabilizationJson[std::to_string(i) + "_posFilter_t"];
        circuitConstants[i].posFilter_k = allStabilizationJson[std::to_string(i) + "_posFilter_k"];
        circuitConstants[i].speedFilter_t = allStabilizationJson[std::to_string(i) + "_speedFilter_t"];
        circuitConstants[i].speedFilter_k = allStabilizationJson[std::to_string(i) + "_speedFilter_k"];
        circuitConstants[i].out_k = allStabilizationJson[std::to_string(i) + "_out_k"];
        circuitConstants[i].out_max = allStabilizationJson[std::to_string(i) + "_out_max"];
        circuitConstants[i].out_min = allStabilizationJson[std::to_string(i) + "_out_min"];

        interface.setCircuitConstants(circuitConstants[i], static_cast<e_circuit>(i));
    };
}

void StabilizationWindow::createDefaultStabilizationJson() {
    for (int i = MARCH; i < YAW + 1; i++) {
        allStabilizationJson[std::to_string(i) + "_k_joy"] = 1;
        allStabilizationJson[std::to_string(i) + "_k_tuning"] = 0;
        allStabilizationJson[std::to_string(i) + "_pid_kp"] = 1;
        allStabilizationJson[std::to_string(i) + "_pid_ki"] = 1;
        allStabilizationJson[std::to_string(i) + "_pid_kd"] = 1;
        allStabilizationJson[std::to_string(i) + "_pid_max_i"] = 0;
        allStabilizationJson[std::to_string(i) + "_pid_min_i"] = 0;
        allStabilizationJson[std::to_string(i) + "_pid_max"] = 0;
        allStabilizationJson[std::to_string(i) + "_pid_min"] = 0;
        allStabilizationJson[std::to_string(i) + "_posFilter_t"] = 1;
        allStabilizationJson[std::to_string(i) + "_posFilter_k"] = 1;
        allStabilizationJson[std::to_string(i) + "_speedFilter_t"] = 1;
        allStabilizationJson[std::to_string(i) + "_speedFilter_k"] = 1;
        allStabilizationJson[std::to_string(i) + "_out_k"] = 1;
        allStabilizationJson[std::to_string(i) + "_out_max"] = 0;
        allStabilizationJson[std::to_string(i) + "_out_min"] = 0;
    }
}

void StabilizationWindow::saveToFile() {
    qDebug() << "saveToFile()";
    std::ofstream o(jsonName.toStdString());
    o << std::setw(4) << allStabilizationJson << std::endl;
    o.close();
}

// void StabilizationWindow::updateVariables_KX() {
//     X[0][0]  = static_cast<double>(circuitStates[currentCircuit].input);
//     X[1][0]  = static_cast<double>(circuitStates[currentCircuit].pos);
//     X[2][0]  = static_cast<double>(circuitStates[currentCircuit].pos_filtered);
//     X[5][0]  = static_cast<double>(circuitStates[currentCircuit].speed)
//     X[6][0]  = static_cast<double>(circuitStates[currentCircuit].speed_filtered)
//     X[7][0]  = static_cast<double>(circuitStates[currentCircuit].joy_gained)
//     X[8][0]  = static_cast<double>(circuitStates[currentCircuit].target_integrator)
//     X[9][0]  = static_cast<double>(circuitStates[currentCircuit].pid_error)
//     X[10][0] = static_cast<double>(circuitStates[currentCircuit].pid_Pout)
//     X[11][0] = static_cast<double>(circuitStates[currentCircuit].pid_I_gained)
//     X[12][0] = static_cast<double>(circuitStates[currentCircuit].pid_Iout)
//     X[13][0] = static_cast<double>(circuitStates[currentCircuit].pid_Dout)
//     X[14][0] = static_cast<double>(circuitStates[currentCircuit].pid_SumOut)
//     X[15][0] = static_cast<double>(circuitStates[currentCircuit].pid_output)
//     X[16][0] = static_cast<double>(circuitStates[currentCircuit].tuning_summator)
//     X[16][0] = static_cast<double>(circuitStates[currentCircuit].speed_error)
//     X[16][0] = static_cast<double>(circuitStates[currentCircuit].out_pre_saturation)
//     X[16][0] = static_cast<double>(circuitStates[currentCircuit].out)
// }
