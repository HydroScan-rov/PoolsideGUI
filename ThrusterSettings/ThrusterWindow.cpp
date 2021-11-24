#include "ThrusterWindow.h"
#include "ui_ThrusterWindow.h"

ThrusterWindow::ThrusterWindow(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ThrusterWindow) {
    ui->setupUi(this);

    jsonName = "thrusterJson.json";
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
    thrustersPower = new ThrusterPower[thrusters_amount];
    for (int i = 0; i < thrusters_amount; ++i) {
        ui->horizontalLayout_Thrusters->addWidget(&thrusters[i], i);
        thrusters[i].setThruster(i, allThrusterJson["thrusters"][i]);
        thrustersPower[i] = {i, 0};
        connect(&thrusters[i], SIGNAL(parametorsChanged(json, UV_Thruster)), this, SLOT(thrusterEdited(json, UV_Thruster)));
        connect(&thrusters[i], SIGNAL(powerChanged(int)), this, SLOT()) //TODO вызов сизнала, который нужно реалтзовать
    }
    
}

ThrusterWindow::~ThrusterWindow() {
    delete[] thrusters;
    delete ui;
}

void ThrusterWindow::thrusterEdited(json thrusterJson, UV_Thruster thruster) {
    allThrusterJson["thrusters"][thruster.slot] = thrusterJson;
    std::ofstream o(jsonName.toStdString());
    o << std::setw(4) << allThrusterJson << std::endl;
    o.close();
    
}

void ThrusterWindow::createDefaultThrusterJson() {
    std::ofstream o(jsonName.toStdString());
    json j = {{"thrusters", {
            {
                    {"name", "HLB"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 6},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            }, {
                    {"name", "HLF"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 8},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", false}
            }, {
                    {"name", "HRB"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 1},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            }, {
                    {"name", "HRF"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 2},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            }, {
                    {"name", "VB"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 3},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            }, {
                    {"name", "VF"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 5},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            }, {
                    {"name", "VL"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 4},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            }, {
                    {"name", "VB"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 7},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            },
    }}};
    o << std::setw(4) << j << std::endl;
    o.close();
}