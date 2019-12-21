/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *buttonafter;
    QPushButton *buttonstop;
    QLabel *labelrun;
    QComboBox *comboBox;
    QLabel *lablenow;
    QSlider *horizontalSlider;
    QPushButton *buttonbefore;
    QPushButton *buttonlrc;
    QPushButton *buttonheart;
    QPushButton *buttonsound;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *buttonskins;
    QLabel *label_3;
    QPushButton *buttonquit;
    QLabel *label_2;
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    QLabel *label_6;
    QLineEdit *lineEdit;
    QLabel *label_7;
    QLineEdit *lineEdit_2;
    QLabel *label_8;
    QLabel *label11;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_5;
    QWidget *page_2;
    QListWidget *listWidget_3;
    QWidget *page_3;
    QListWidget *listWidget3;
    QPushButton *buttonlrcback;
    QSpinBox *spinBox;
    QSlider *slider;
    QPushButton *buttonslot;
    QPushButton *buttonquitly;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1143, 807);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        buttonafter = new QPushButton(centralWidget);
        buttonafter->setObjectName(QStringLiteral("buttonafter"));
        buttonafter->setGeometry(QRect(360, 580, 81, 71));
        buttonafter->setStyleSheet(QStringLiteral("border-image: url(:/image/png/button-foward.png);"));
        buttonstop = new QPushButton(centralWidget);
        buttonstop->setObjectName(QStringLiteral("buttonstop"));
        buttonstop->setGeometry(QRect(210, 580, 81, 81));
        buttonstop->setStyleSheet(QStringLiteral("border-image: url(:/image/png/button-pause.png);"));
        labelrun = new QLabel(centralWidget);
        labelrun->setObjectName(QStringLiteral("labelrun"));
        labelrun->setGeometry(QRect(550, 650, 91, 41));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(920, 590, 86, 41));
        comboBox->setStyleSheet(QStringLiteral("background-color: rgb(239, 41, 41);"));
        lablenow = new QLabel(centralWidget);
        lablenow->setObjectName(QStringLiteral("lablenow"));
        lablenow->setGeometry(QRect(10, 660, 91, 31));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(70, 700, 501, 16));
        horizontalSlider->setOrientation(Qt::Horizontal);
        buttonbefore = new QPushButton(centralWidget);
        buttonbefore->setObjectName(QStringLiteral("buttonbefore"));
        buttonbefore->setGeometry(QRect(60, 580, 81, 71));
        buttonbefore->setStyleSheet(QStringLiteral("border-image: url(:/image/png/button-rewind.png);"));
        buttonlrc = new QPushButton(centralWidget);
        buttonlrc->setObjectName(QStringLiteral("buttonlrc"));
        buttonlrc->setGeometry(QRect(1020, 580, 111, 61));
        buttonlrc->setStyleSheet(QLatin1String("font: 26pt \"Ubuntu\";\n"
"background-image: url(:/image/png/78.png);"));
        buttonheart = new QPushButton(centralWidget);
        buttonheart->setObjectName(QStringLiteral("buttonheart"));
        buttonheart->setGeometry(QRect(830, 590, 71, 61));
        buttonheart->setStyleSheet(QStringLiteral("border-image: url(:/image/background/unheart.jpg);"));
        buttonsound = new QPushButton(centralWidget);
        buttonsound->setObjectName(QStringLiteral("buttonsound"));
        buttonsound->setGeometry(QRect(490, 580, 81, 71));
        buttonsound->setStyleSheet(QStringLiteral("border-image: url(:/image/png/Image-audio-volume-medium-panel.png);"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 10, 1131, 521));
        stackedWidget->setStyleSheet(QStringLiteral(""));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        buttonskins = new QPushButton(page);
        buttonskins->setObjectName(QStringLiteral("buttonskins"));
        buttonskins->setGeometry(QRect(890, 0, 101, 41));
        buttonskins->setStyleSheet(QLatin1String("font: 57 italic 11pt \"Ubuntu\";\n"
"background-color: rgb(245, 121, 0);"));
        label_3 = new QLabel(page);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(990, 0, 67, 41));
        label_3->setStyleSheet(QLatin1String("border-image: url(:/image/png/Image-gnome-netstatus-75-100.png);\n"
"background-color: rgb(78, 154, 6);"));
        buttonquit = new QPushButton(page);
        buttonquit->setObjectName(QStringLiteral("buttonquit"));
        buttonquit->setGeometry(QRect(1060, 0, 71, 41));
        buttonquit->setStyleSheet(QStringLiteral("border-image: url(:/image/png/nav-stop.png);"));
        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(-10, 0, 131, 81));
        label_2->setStyleSheet(QString::fromUtf8("border-image: url(:/image/Mplayer\347\205\247\347\211\207/picture.png);"));
        listWidget = new QListWidget(page);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(660, 80, 451, 441));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(10);
        sizePolicy.setVerticalStretch(10);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setStyleSheet(QLatin1String("font: 25 32pt \"Ubuntu\";\n"
"border-image: url(:/image/background/window.jpg);"));
        listWidget_2 = new QListWidget(page);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setGeometry(QRect(10, 80, 631, 441));
        listWidget_2->setStyleSheet(QLatin1String("font: 17pt \"Ubuntu\";\n"
"border-image: url(:/image/background/5.jpg);"));
        label_6 = new QLabel(page);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(120, 30, 51, 21));
        label_6->setStyleSheet(QStringLiteral("border-color: rgb(252, 233, 79);"));
        lineEdit = new QLineEdit(page);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(172, 30, 151, 25));
        lineEdit->setStyleSheet(QStringLiteral("background-color: rgb(114, 159, 207);"));
        label_7 = new QLabel(page);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(340, 30, 51, 21));
        label_7->setStyleSheet(QStringLiteral("border-color: rgb(252, 233, 79);"));
        lineEdit_2 = new QLineEdit(page);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(390, 30, 113, 25));
        lineEdit_2->setStyleSheet(QStringLiteral("background-color: rgb(114, 159, 207);"));
        label_8 = new QLabel(page);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(510, 10, 191, 51));
        label11 = new QLabel(page);
        label11->setObjectName(QStringLiteral("label11"));
        label11->setGeometry(QRect(720, 10, 141, 51));
        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 260, 401, 91));
        label->setStyleSheet(QLatin1String("font: 20pt \"Ubuntu\";\n"
"color: rgb(239, 41, 41);"));
        label_4 = new QLabel(page);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(130, 100, 401, 91));
        label_4->setStyleSheet(QLatin1String("font: 20pt \"Ubuntu\";\n"
""));
        label_5 = new QLabel(page);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(130, 370, 401, 91));
        label_5->setStyleSheet(QLatin1String("font: 20pt \"Ubuntu\";\n"
""));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        listWidget_3 = new QListWidget(page_2);
        listWidget_3->setObjectName(QStringLiteral("listWidget_3"));
        listWidget_3->setGeometry(QRect(0, 10, 1131, 541));
        listWidget_3->setStyleSheet(QLatin1String("font: 20pt \"Ubuntu\";\n"
"border-image: url(:/image/background/4.jpg);"));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        listWidget3 = new QListWidget(page_3);
        listWidget3->setObjectName(QStringLiteral("listWidget3"));
        listWidget3->setGeometry(QRect(340, 10, 431, 511));
        listWidget3->setStyleSheet(QLatin1String("font: 27pt \"Ubuntu\";\n"
"border-image: url(:/image/background/1.jpg);"));
        stackedWidget->addWidget(page_3);
        buttonlrcback = new QPushButton(centralWidget);
        buttonlrcback->setObjectName(QStringLiteral("buttonlrcback"));
        buttonlrcback->setGeometry(QRect(1020, 660, 111, 61));
        buttonlrcback->setStyleSheet(QLatin1String("font: 26pt \"Ubuntu\";\n"
"background-image: url(:/image/png/78.png);"));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(660, 690, 48, 26));
        slider = new QSlider(centralWidget);
        slider->setObjectName(QStringLiteral("slider"));
        slider->setGeometry(QRect(730, 590, 20, 131));
        slider->setOrientation(Qt::Vertical);
        buttonslot = new QPushButton(centralWidget);
        buttonslot->setObjectName(QStringLiteral("buttonslot"));
        buttonslot->setGeometry(QRect(150, 650, 51, 25));
        buttonslot->setStyleSheet(QString::fromUtf8("border-image: url(:/image/Mplayer\347\205\247\347\211\207/back.png);"));
        buttonquitly = new QPushButton(centralWidget);
        buttonquitly->setObjectName(QStringLiteral("buttonquitly"));
        buttonquitly->setGeometry(QRect(300, 650, 51, 25));
        buttonquitly->setStyleSheet(QString::fromUtf8("border-image: url(:/image/Mplayer\347\205\247\347\211\207/front.png);"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1143, 28));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        buttonafter->setText(QString());
        buttonstop->setText(QString());
        labelrun->setText(QString());
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\346\240\207\345\207\206\351\237\263\350\264\250", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\350\276\203\351\253\230\351\237\263\350\264\250", Q_NULLPTR)
         << QApplication::translate("MainWindow", "[vip]\346\227\240\346\215\237\351\237\263\350\264\250", Q_NULLPTR)
        );
        lablenow->setText(QString());
        buttonbefore->setText(QString());
        buttonlrc->setText(QApplication::translate("MainWindow", "\346\255\214 \350\257\215", Q_NULLPTR));
        buttonheart->setText(QString());
        buttonsound->setText(QString());
        buttonskins->setText(QApplication::translate("MainWindow", "\346\233\264\346\215\242\347\232\256\350\202\244", Q_NULLPTR));
        label_3->setText(QString());
        buttonquit->setText(QString());
        label_2->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "\350\211\272\346\234\257\345\256\266", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "\344\270\223\350\276\221", Q_NULLPTR));
        label_8->setText(QString());
        label11->setText(QString());
        label->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
        buttonlrcback->setText(QApplication::translate("MainWindow", "\350\277\224 \345\233\236", Q_NULLPTR));
        buttonslot->setText(QString());
        buttonquitly->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
