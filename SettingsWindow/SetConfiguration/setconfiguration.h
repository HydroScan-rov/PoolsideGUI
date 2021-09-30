#ifndef SETCONFIGURATION_H
#define SETCONFIGURATION_H

#include <QWidget>
#include <QFileInfo>
#include <QVBoxLayout>
#include "dialogcommit.h"

namespace Ui {
class setConfiguration;
}

class setConfiguration : public QWidget
{
    Q_OBJECT

public:
    explicit setConfiguration(QWidget *parent = nullptr);
    ~setConfiguration();

    void configGitBush(); //функция настройки гит клиента на пк
    void setElement_GroupBox(QFileInfo); //функция настройки отображения элементов из соответствующих папок репозитория

    bool file_flag = false; //переменная обработка .exe приложения

    QString filePath; //путь к действующему git-bash.exe
    QString fileName; //имя файла к которому указывает путь к действующему git-bash.exe
    QString dirConfig_Path; //путь к директории конфигураций

    DialogCommit* message = nullptr;
    QVBoxLayout* vbox_ThrusterSet = nullptr;
    QVBoxLayout* vbox_VehicleSetting = nullptr;
    QVBoxLayout* vbox_Devices = nullptr;

private slots:
    void on_pushButton_ThrusterSet_commit_clicked();

    void on_pushButton_VehicleSetting_commit_clicked();

    void on_pushButton_devices_commit_clicked();

    void on_pushButton_pull_clicked();

    void on_pushButton_push_clicked();

    void on_pushButton_Accept_Configurations_clicked();

private:
    Ui::setConfiguration *ui;
};

#endif // SETCONFIGURATION_H