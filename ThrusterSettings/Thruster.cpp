#include "Thruster.h"
#include "ui_Thruster.h"
#include "Thruster.moc"

Thruster::Thruster(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Thruster) {
    ui->setupUi(this);

    //change parameters
    connect(ui->CheckBox_ThrusterPower, SIGNAL(stateChanged(int)), this, SLOT(powerCheckBoxChanged(int)));
    connect(ui->SpinBox_ThrusterId, SIGNAL(valueChanged(int)), this, SLOT(idChanged(int)));
    connect(ui->doubleSpinBox_ThrusterSetTargetForce, SIGNAL(valueChanged(double)), this, SLOT(targetForceChanged(double)));
    connect(ui->DoubleSpinBox_SetForwardK, SIGNAL(valueChanged(double)), this, SLOT(forwardKChanged(double)));
    connect(ui->DoubleSpinBox_SetBackwardK, SIGNAL(valueChanged(double)), this, SLOT(backwardKChanged(double)));
    connect(ui->SpinBox_ThrusterSet_dPWM_forward, SIGNAL(valueChanged(int)), this, SLOT(forwardSaturationChanged(int)));
    connect(ui->SpinBox_ThrusterSet_dPWM_backward, SIGNAL(valueChanged(int)), this, SLOT(backwardSaturationChanged(int)));
    connect(ui->CheckBox_ThrusterReverse, SIGNAL(stateChanged(int)), this, SLOT(reverseChanged(int)));

    //speed
    connect(ui->PushButton_ThrusterSetForward, SIGNAL(clicked()), this, SLOT(speedSetForward()));
    connect(ui->PushButton_ThrusterSetStop, SIGNAL(clicked()), this, SLOT(speedSetStop()));
    connect(ui->PushButton_ThrusterSetBackward, SIGNAL(clicked()), this, SLOT(speedSetBackward()));
    connect(this, SIGNAL(speedSpinBoxChange(double)), ui->doubleSpinBox_ThrusterSetTargetForce, SLOT(setValue(double)));
}

Thruster::~Thruster() {
    delete ui;
}

UV_Thruster Thruster::getUV_Thruster() {
    return ThisThruster;
}

void Thruster::setThruster(json ThrusterJson) {
    this->ThrusterJson = ThrusterJson;
    setUV_Thruster();
    setUi();
}

void Thruster::setAutoSave(int autoSave) {
    this->autoSave = !!autoSave;
}

void Thruster::save(bool click) {
    ThrusterJson["id"] = ThisThruster.id;
    ThrusterJson["reverse"] = ThisThruster.reverse;
    ThrusterJson["target_force"] = ThisThruster.target_force;
    ThrusterJson["k_forward"] = ThisThruster.k_forward;
    ThrusterJson["k_backward"] = ThisThruster.k_backward;
    ThrusterJson["dPWM_forward"] = ThisThruster.dPWM_forward;
    ThrusterJson["dPWM_backward"] = ThisThruster.dPWM_backward;

    emit parametersChanged(ThrusterJson, ThisThruster);
}

void Thruster::setUV_Thruster() {
    ThisThruster.id = ThrusterJson["id"];
    ThisThruster.reverse = ThrusterJson["reverse"];
    ThisThruster.target_force = ThrusterJson["target_force"];
    ThisThruster.k_forward = ThrusterJson["k_forward"];
    ThisThruster.k_backward = ThrusterJson["k_backward"];
    ThisThruster.dPWM_forward = ThrusterJson["dPWM_forward"];
    ThisThruster.dPWM_backward = ThrusterJson["dPWM_backward"];
}

void Thruster::setUi() {
    ui->SpinBox_ThrusterId->setEnabled(!power);
    ui->SpinBox_ThrusterId->setValue(ThrusterJson["id"]);
    if (ThrusterJson["reverse"] == true) {
        ui->CheckBox_ThrusterReverse->setCheckState(Qt::Checked);
    } else {
        ui->CheckBox_ThrusterReverse->setCheckState(Qt::Unchecked);
    }
    ui->DoubleSpinBox_SetForwardK->setValue(ThrusterJson["k_forward"]);
    ui->DoubleSpinBox_SetBackwardK->setValue(ThrusterJson["k_backward"]);
    ui->SpinBox_ThrusterSet_dPWM_forward->setValue(ThrusterJson["dPWM_forward"]);
    ui->SpinBox_ThrusterSet_dPWM_backward->setValue(ThrusterJson["dPWM_backward"]);
}

void Thruster::powerCheckBoxChanged(int power) {
    ThisThruster.power = power;
    emit parametersChanged(ThrusterJson, ThisThruster);
}

void Thruster::idChanged(int id) {
    if (autoSave == true) ThrusterJson["id"] = id;
    ThisThruster.id = id;
    emit parametersChanged(ThrusterJson, ThisThruster);
}

void Thruster::targetForceChanged(double target_force) {
    ThisThruster.target_force = target_force;
    emit parametersChanged(ThrusterJson, ThisThruster);
}

void Thruster::forwardKChanged(double forwardK) {
    if (autoSave == true) ThrusterJson["k_forward"] = forwardK;
    ThisThruster.k_forward = forwardK;
    emit parametersChanged(ThrusterJson, ThisThruster);
}

void Thruster::backwardKChanged(double backwardK) {
    if (autoSave == true) ThrusterJson["k_backward"] = backwardK;
    ThisThruster.k_backward = backwardK;
    emit parametersChanged(ThrusterJson, ThisThruster);
}

void Thruster::forwardSaturationChanged(int forwardSaturation) {
    if (autoSave == true) ThrusterJson["forward_saturation"] = forwardSaturation;
    ThisThruster.dPWM_forward = forwardSaturation;
    emit parametersChanged(ThrusterJson, ThisThruster);
}

void Thruster::backwardSaturationChanged(int backwardSaturation) {
    if (autoSave == true) ThrusterJson["backward_saturation"] = backwardSaturation;
    ThisThruster.dPWM_backward = backwardSaturation;
    emit parametersChanged(ThrusterJson, ThisThruster);
}

void Thruster::reverseChanged(int state) {
    if (autoSave == true) ThrusterJson["reverse"] = !!state;
    ThisThruster.reverse = !!state;
    emit parametersChanged(ThrusterJson, ThisThruster);
}

void Thruster::speedSetForward() {
    emit speedSpinBoxChange(5);
}

void Thruster::speedSetStop() {
    emit speedSpinBoxChange(0);
}

void Thruster::speedSetBackward() {
    emit speedSpinBoxChange(-5);
}
