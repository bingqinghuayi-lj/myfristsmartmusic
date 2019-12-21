#include "mywidget.h"
#include "ui_mywidget.h"
#include <QSlider>
#include <QSpinBox>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <qtextcodec.h>
#include <fcntl.h>
#include <sys/stat.h>
Mywidget::Mywidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mywidget)
{
    connect(ui->slider,&QSlider::valueChanged,[=]{
        char buff[128] ={0};
        sprintf(buff,"volume %d 1\n",ui->slider->value());
//        if(PuaesFlag == 0)
//        {
//         SendMsgToMplayer(buff);
//        }
    });
    ui->setupUi(this);
    connect(ui->slider,&QSlider::valueChanged,ui->spinBox,&QSpinBox::setValue);
    void (QSpinBox::*mysignal)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox,mysignal,ui->slider,&QSlider::setValue);


}

Mywidget::~Mywidget()
{
    delete ui;
}

void Mywidget::setValue(int num)
{
    ui->spinBox->setValue(num);
}

int Mywidget::getValue()
{
    return ui->spinBox->value();
}
