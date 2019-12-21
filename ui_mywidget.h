/********************************************************************************
** Form generated from reading UI file 'mywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWIDGET_H
#define UI_MYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mywidget
{
public:
    QSlider *slider;
    QSpinBox *spinBox;

    void setupUi(QWidget *Mywidget)
    {
        if (Mywidget->objectName().isEmpty())
            Mywidget->setObjectName(QStringLiteral("Mywidget"));
        Mywidget->resize(400, 300);
        slider = new QSlider(Mywidget);
        slider->setObjectName(QStringLiteral("slider"));
        slider->setGeometry(QRect(180, 30, 20, 131));
        slider->setOrientation(Qt::Vertical);
        spinBox = new QSpinBox(Mywidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(110, 130, 48, 26));

        retranslateUi(Mywidget);

        QMetaObject::connectSlotsByName(Mywidget);
    } // setupUi

    void retranslateUi(QWidget *Mywidget)
    {
        Mywidget->setWindowTitle(QApplication::translate("Mywidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Mywidget: public Ui_Mywidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWIDGET_H
