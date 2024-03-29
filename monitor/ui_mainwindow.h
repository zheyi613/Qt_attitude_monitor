/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mycombobox.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave_Data;
    QAction *actionSet_Axis_Range;
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_SerialPort;
    QGroupBox *groupBox_SerialPort;
    QHBoxLayout *horizontalLayout_SerialPortGroup;
    QVBoxLayout *verticalLayout_Label;
    QLabel *label_Port;
    QLabel *label_BaudRate;
    QLabel *label_PacketRate;
    QLabel *label_Coordinate;
    QVBoxLayout *verticalLayout_Parameter;
    MyComboBox *comboBox_Port;
    QComboBox *comboBox_BaudRate;
    QSpinBox *spinBox_PacketRate;
    QComboBox *comboBox_Coordinate;
    QPushButton *pushButton_Connect;
    QVBoxLayout *verticalLayout_3DCube;
    QVBoxLayout *verticalLayout_ChartView;
    QCustomPlot *customPlot_accel;
    QCustomPlot *customPlot_gyro;
    QCustomPlot *customPlot_attitude;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 720);
        MainWindow->setMinimumSize(QSize(720, 480));
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        MainWindow->setFont(font);
        actionSave_Data = new QAction(MainWindow);
        actionSave_Data->setObjectName(QString::fromUtf8("actionSave_Data"));
        actionSet_Axis_Range = new QAction(MainWindow);
        actionSet_Axis_Range->setObjectName(QString::fromUtf8("actionSet_Axis_Range"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_SerialPort = new QVBoxLayout();
        verticalLayout_SerialPort->setSpacing(6);
        verticalLayout_SerialPort->setObjectName(QString::fromUtf8("verticalLayout_SerialPort"));
        groupBox_SerialPort = new QGroupBox(centralwidget);
        groupBox_SerialPort->setObjectName(QString::fromUtf8("groupBox_SerialPort"));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Consolas")});
        font1.setPointSize(12);
        groupBox_SerialPort->setFont(font1);
        groupBox_SerialPort->setLayoutDirection(Qt::LeftToRight);
        groupBox_SerialPort->setFlat(false);
        groupBox_SerialPort->setCheckable(false);
        horizontalLayout_SerialPortGroup = new QHBoxLayout(groupBox_SerialPort);
        horizontalLayout_SerialPortGroup->setObjectName(QString::fromUtf8("horizontalLayout_SerialPortGroup"));
        verticalLayout_Label = new QVBoxLayout();
        verticalLayout_Label->setObjectName(QString::fromUtf8("verticalLayout_Label"));
        label_Port = new QLabel(groupBox_SerialPort);
        label_Port->setObjectName(QString::fromUtf8("label_Port"));
        label_Port->setFont(font1);

        verticalLayout_Label->addWidget(label_Port);

        label_BaudRate = new QLabel(groupBox_SerialPort);
        label_BaudRate->setObjectName(QString::fromUtf8("label_BaudRate"));
        label_BaudRate->setFont(font1);

        verticalLayout_Label->addWidget(label_BaudRate);

        label_PacketRate = new QLabel(groupBox_SerialPort);
        label_PacketRate->setObjectName(QString::fromUtf8("label_PacketRate"));

        verticalLayout_Label->addWidget(label_PacketRate);

        label_Coordinate = new QLabel(groupBox_SerialPort);
        label_Coordinate->setObjectName(QString::fromUtf8("label_Coordinate"));

        verticalLayout_Label->addWidget(label_Coordinate);


        horizontalLayout_SerialPortGroup->addLayout(verticalLayout_Label);

        verticalLayout_Parameter = new QVBoxLayout();
        verticalLayout_Parameter->setObjectName(QString::fromUtf8("verticalLayout_Parameter"));
        comboBox_Port = new MyComboBox(groupBox_SerialPort);
        comboBox_Port->setObjectName(QString::fromUtf8("comboBox_Port"));
        comboBox_Port->setMouseTracking(false);
        comboBox_Port->setEditable(false);
        comboBox_Port->setInsertPolicy(QComboBox::InsertAtBottom);

        verticalLayout_Parameter->addWidget(comboBox_Port);

        comboBox_BaudRate = new QComboBox(groupBox_SerialPort);
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->setObjectName(QString::fromUtf8("comboBox_BaudRate"));

        verticalLayout_Parameter->addWidget(comboBox_BaudRate);

        spinBox_PacketRate = new QSpinBox(groupBox_SerialPort);
        spinBox_PacketRate->setObjectName(QString::fromUtf8("spinBox_PacketRate"));
        spinBox_PacketRate->setMinimum(1);
        spinBox_PacketRate->setMaximum(1000);
        spinBox_PacketRate->setValue(100);

        verticalLayout_Parameter->addWidget(spinBox_PacketRate);

        comboBox_Coordinate = new QComboBox(groupBox_SerialPort);
        comboBox_Coordinate->addItem(QString());
        comboBox_Coordinate->addItem(QString());
        comboBox_Coordinate->setObjectName(QString::fromUtf8("comboBox_Coordinate"));
        comboBox_Coordinate->setEditable(false);

        verticalLayout_Parameter->addWidget(comboBox_Coordinate);


        horizontalLayout_SerialPortGroup->addLayout(verticalLayout_Parameter);

        horizontalLayout_SerialPortGroup->setStretch(0, 2);
        horizontalLayout_SerialPortGroup->setStretch(1, 3);

        verticalLayout_SerialPort->addWidget(groupBox_SerialPort);

        pushButton_Connect = new QPushButton(centralwidget);
        pushButton_Connect->setObjectName(QString::fromUtf8("pushButton_Connect"));
        pushButton_Connect->setFont(font1);

        verticalLayout_SerialPort->addWidget(pushButton_Connect);

        verticalLayout_3DCube = new QVBoxLayout();
        verticalLayout_3DCube->setObjectName(QString::fromUtf8("verticalLayout_3DCube"));

        verticalLayout_SerialPort->addLayout(verticalLayout_3DCube);

        verticalLayout_SerialPort->setStretch(0, 1);
        verticalLayout_SerialPort->setStretch(1, 1);
        verticalLayout_SerialPort->setStretch(2, 6);

        horizontalLayout->addLayout(verticalLayout_SerialPort);

        verticalLayout_ChartView = new QVBoxLayout();
        verticalLayout_ChartView->setObjectName(QString::fromUtf8("verticalLayout_ChartView"));
        customPlot_accel = new QCustomPlot(centralwidget);
        customPlot_accel->setObjectName(QString::fromUtf8("customPlot_accel"));

        verticalLayout_ChartView->addWidget(customPlot_accel);

        customPlot_gyro = new QCustomPlot(centralwidget);
        customPlot_gyro->setObjectName(QString::fromUtf8("customPlot_gyro"));

        verticalLayout_ChartView->addWidget(customPlot_gyro);

        customPlot_attitude = new QCustomPlot(centralwidget);
        customPlot_attitude->setObjectName(QString::fromUtf8("customPlot_attitude"));

        verticalLayout_ChartView->addWidget(customPlot_attitude);


        horizontalLayout->addLayout(verticalLayout_ChartView);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 3);

        formLayout->setLayout(0, QFormLayout::SpanningRole, horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        comboBox_Port->setCurrentIndex(-1);
        comboBox_BaudRate->setCurrentIndex(4);
        comboBox_Coordinate->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Monitor", nullptr));
        actionSave_Data->setText(QCoreApplication::translate("MainWindow", "Save Data", nullptr));
        actionSet_Axis_Range->setText(QCoreApplication::translate("MainWindow", "Set Axis Range", nullptr));
        groupBox_SerialPort->setTitle(QCoreApplication::translate("MainWindow", "Serial Port", nullptr));
        label_Port->setText(QCoreApplication::translate("MainWindow", "Port :", nullptr));
        label_BaudRate->setText(QCoreApplication::translate("MainWindow", "BaudRate :", nullptr));
        label_PacketRate->setText(QCoreApplication::translate("MainWindow", "PacketRate :", nullptr));
        label_Coordinate->setText(QCoreApplication::translate("MainWindow", "Coordinate  :", nullptr));
        comboBox_Port->setCurrentText(QString());
        comboBox_Port->setPlaceholderText(QString());
        comboBox_BaudRate->setItemText(0, QCoreApplication::translate("MainWindow", "9600", nullptr));
        comboBox_BaudRate->setItemText(1, QCoreApplication::translate("MainWindow", "19200", nullptr));
        comboBox_BaudRate->setItemText(2, QCoreApplication::translate("MainWindow", "38400", nullptr));
        comboBox_BaudRate->setItemText(3, QCoreApplication::translate("MainWindow", "57600", nullptr));
        comboBox_BaudRate->setItemText(4, QCoreApplication::translate("MainWindow", "115200", nullptr));
        comboBox_BaudRate->setItemText(5, QCoreApplication::translate("MainWindow", "230400", nullptr));
        comboBox_BaudRate->setItemText(6, QCoreApplication::translate("MainWindow", "460800", nullptr));
        comboBox_BaudRate->setItemText(7, QCoreApplication::translate("MainWindow", "921600", nullptr));

        comboBox_Coordinate->setItemText(0, QCoreApplication::translate("MainWindow", "NED (North-East-Down)", nullptr));
        comboBox_Coordinate->setItemText(1, QCoreApplication::translate("MainWindow", "ENU (East-North-Up)", nullptr));

        pushButton_Connect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
