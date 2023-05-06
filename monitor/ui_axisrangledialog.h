/********************************************************************************
** Form generated from reading UI file 'axisrangledialog.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AXISRANGLEDIALOG_H
#define UI_AXISRANGLEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label_timeInterval;
    QSpinBox *spinBox_timeInterval;
    QGroupBox *groupBox_YAxisRange;
    QLabel *label_acceleration;
    QLabel *label_angularVelocity;
    QLabel *label_attitude;
    QDoubleSpinBox *doubleSpinBox_accel;
    QDoubleSpinBox *doubleSpinBox_angularVecocity;
    QDoubleSpinBox *doubleSpinBox_attitude;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 300);
        Dialog->setMinimumSize(QSize(400, 300));
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_timeInterval = new QLabel(Dialog);
        label_timeInterval->setObjectName(QString::fromUtf8("label_timeInterval"));

        gridLayout->addWidget(label_timeInterval, 0, 0, 1, 1);

        spinBox_timeInterval = new QSpinBox(Dialog);
        spinBox_timeInterval->setObjectName(QString::fromUtf8("spinBox_timeInterval"));
        spinBox_timeInterval->setMinimum(1);
        spinBox_timeInterval->setMaximum(10);

        gridLayout->addWidget(spinBox_timeInterval, 0, 1, 1, 1);

        groupBox_YAxisRange = new QGroupBox(Dialog);
        groupBox_YAxisRange->setObjectName(QString::fromUtf8("groupBox_YAxisRange"));
        label_acceleration = new QLabel(groupBox_YAxisRange);
        label_acceleration->setObjectName(QString::fromUtf8("label_acceleration"));
        label_acceleration->setGeometry(QRect(10, 53, 118, 16));
        label_angularVelocity = new QLabel(groupBox_YAxisRange);
        label_angularVelocity->setObjectName(QString::fromUtf8("label_angularVelocity"));
        label_angularVelocity->setGeometry(QRect(10, 108, 139, 16));
        label_attitude = new QLabel(groupBox_YAxisRange);
        label_attitude->setObjectName(QString::fromUtf8("label_attitude"));
        label_attitude->setGeometry(QRect(10, 163, 82, 16));
        doubleSpinBox_accel = new QDoubleSpinBox(groupBox_YAxisRange);
        doubleSpinBox_accel->setObjectName(QString::fromUtf8("doubleSpinBox_accel"));
        doubleSpinBox_accel->setGeometry(QRect(194, 53, 52, 21));
        doubleSpinBox_angularVecocity = new QDoubleSpinBox(groupBox_YAxisRange);
        doubleSpinBox_angularVecocity->setObjectName(QString::fromUtf8("doubleSpinBox_angularVecocity"));
        doubleSpinBox_angularVecocity->setGeometry(QRect(194, 108, 52, 21));
        doubleSpinBox_attitude = new QDoubleSpinBox(groupBox_YAxisRange);
        doubleSpinBox_attitude->setObjectName(QString::fromUtf8("doubleSpinBox_attitude"));
        doubleSpinBox_attitude->setGeometry(QRect(194, 163, 52, 21));

        gridLayout->addWidget(groupBox_YAxisRange, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 2);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Dialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Dialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label_timeInterval->setText(QCoreApplication::translate("Dialog", "Time Interval:", nullptr));
        groupBox_YAxisRange->setTitle(QCoreApplication::translate("Dialog", "Y-Axis Range", nullptr));
        label_acceleration->setText(QCoreApplication::translate("Dialog", "Acceleration (g/s^2):", nullptr));
        label_angularVelocity->setText(QCoreApplication::translate("Dialog", "Angular Velocity (deg/s):", nullptr));
        label_attitude->setText(QCoreApplication::translate("Dialog", "Attitude (deg):", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AXISRANGLEDIALOG_H
