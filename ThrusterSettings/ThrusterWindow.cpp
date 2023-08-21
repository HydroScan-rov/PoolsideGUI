#include "ThrusterWindow.h"
#include "ui_ThrusterWindow.h"

ThrusterWindow::ThrusterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThrusterWindow) {
    ui->setupUi(this);

    jsonName = "thrusters.json";
    std::ifstream file(jsonName.toStdString());
    if (!file) {
        qDebug() << jsonName << " не открыт";
        createDefaultThrusterJson();
        std::ifstream file(jsonName.toStdString());
        qDebug() << jsonName << " создан";
        file >> allThrusterJson;
        file.close();
    } else {
        qDebug() << jsonName << " открыт";
        file >> allThrusterJson;
        file.close();
    }

    thrusters_amount = allThrusterJson["thrusters"].size();
    thrusters = new Thruster[thrusters_amount];
    for (int i = 0; i < thrusters_amount; ++i) {
        ui->horizontalLayout_Thrusters->addWidget(&thrusters[i], i);
        thrusters[i].setThruster(allThrusterJson["thrusters"][i]);
        interface.setThrusterData(i, thrusters[i].getUV_Thruster());

        connect(ui->CheckBox_AutoSave, SIGNAL(stateChanged(int)), &thrusters[i], SLOT(setAutoSave(int)));
        connect(ui->PushButton_Save, SIGNAL(clicked(bool)), &thrusters[i], SLOT(save(bool)));
        connect(&thrusters[i], SIGNAL(parametersChanged(json, UV_Thruster)), this, SLOT(thrusterEdited(json, UV_Thruster)));
        connect(ui->PushButton_Save, SIGNAL(pressed()), this, SLOT(saveDirectPressed()));
        connect(ui->PushButton_Save, SIGNAL(released()), this, SLOT(saveDirectReleased()));
    }
    ui->CheckBox_AutoSave->setCheckState(Qt::Checked);
}

ThrusterWindow::~ThrusterWindow() {
    delete[] thrusters;
    delete ui;
}

void ThrusterWindow::thrusterEdited(json thrusterJson, UV_Thruster thruster) {
    interface.setThrusterData(thruster.id, thruster);
    allThrusterJson["thrusters"][thruster.id] = thrusterJson;
}

void ThrusterWindow::saveDirectPressed() {
    interface.setSaveConstants(true);
}

void ThrusterWindow::saveDirectReleased() {
    qDebug() << "save direct json";
    std::ofstream o(jsonName.toStdString());
    o << std::setw(4) << allThrusterJson << std::endl;
    o.close();
    interface.setSaveConstants(false);
}

void ThrusterWindow::createDefaultThrusterJson() {
    std::ofstream o(jsonName.toStdString());
    json j = { {"thrusters", {
            {
                    {"name", "FrLowR"},
                    {"id", 0},
                    {"target_force", 0},
                    {"dPWM_backward", 75},
                    {"dPWM_forward", 75},
                    {"k_backward", 1},
                    {"k_forward", 1},
                    {"reverse", true}
            }, {
                    {"name", "FrLowL"},
                    {"id", 1},
                    {"target_force", 0},
                    {"dPWM_backward", 75},
                    {"dPWM_forward", 75},
                    {"k_backward", 1},
                    {"k_forward", 1},
                    {"reverse", false}
            }, {
                    {"name", "BackLowR"},
                    {"id", 2},
                    {"target_force", 0},
                    {"dPWM_backward", 75},
                    {"dPWM_forward", 75},
                    {"k_backward", 1},
                    {"k_forward", 1},
                    {"reverse", true}
            }, {
                    {"name", "BackLowL"},
                    {"id", 3},
                    {"target_force", 0},
                    {"dPWM_backward", 75},
                    {"dPWM_forward", 75},
                    {"k_backward", 1},
                    {"k_forward", 1},
                    {"reverse", true}
            }, {
                    {"name", "FrUpR"},
                    {"id", 4},
                    {"target_force", 0},
                    {"dPWM_backward", 75},
                    {"dPWM_forward", 75},
                    {"k_backward", 1},
                    {"k_forward", 1},
                    {"reverse", true}
            }, {
                    {"name", "FrUpL"},
                    {"id", 5},
                    {"target_force", 0},
                    {"dPWM_backward", 75},
                    {"dPWM_forward", 75},
                    {"k_backward", 1},
                    {"k_forward", 1},
                    {"reverse", true}
            }, {
                    {"name", "BackUpL"},
                    {"id", 6},
                    {"target_force", 0},
                    {"dPWM_backward", 75},
                    {"dPWM_forward", 75},
                    {"k_backward", 1},
                    {"k_forward", 1},
                    {"reverse", true}
            }, {
                    {"name", "BackUpR"},
                    {"id", 7},
                    {"target_force", 0},
                    {"dPWM_backward", 75},
                    {"dPWM_forward", 75},
                    {"k_backward", 1},
                    {"k_forward", 1},
                    {"reverse", true}
            },
    }} };
    o << std::setw(4) << j << std::endl;
    o.close();
}
