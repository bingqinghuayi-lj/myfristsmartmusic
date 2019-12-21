#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QPixmap>
#include <QPushButton>
#include <qpalette.h>
#include <QMessageBox>
#include <QIcon>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <qtextcodec.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <qstringlist.h>
#include <QString>
#include <dirent.h>
#include <QMouseEvent>
#include <list>
#include <algorithm>
#include <iostream>
#include <qlistwidget.h>
#include <QListWidget>
#include <QSlider>
#include <QSpinBox>
#include <QMap>
#include <QTimer>
#include <QObject>
#include <QDateTime>
#include <pthread.h>
#include <QSize>
#include <string>
#include <QDebug>
#include <string.h>

namespace Ui {
class MainWindow;
}

extern void Close(int fd);
extern int Open(char *fifo);
extern char buf[128];
extern int total_time ;//总时间
extern int percent_pos ;//百分比
extern int time_pos ;//实时时间
extern char song_name[32] ;//歌曲名字
extern char *lrc_name ;
//extern  int time1 ; //歌曲实时时间
extern int time_new ;
extern int time_now;
extern int i ;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer *mytimer;
public slots:
    void shoucanglrc(void);//收藏歌曲提示
    void changephoto(void);//改变图片暂停播放
    void quitmplayer(void);//关闭音乐播放器
    void changeskins(void);//换皮肤
    void buttonsunds(void);//静音
    void buttonfront(void);//上一首
    void buttonbeore(void);//下一首
    void switchPage();//全屏歌词
    void setValue(int num);//调节音量大小
    int getValue();//调节音量大小
    void Getdatetime();//显示当前日期时间
    //void on_btn_Del_clicked();//删除我的喜欢
    void timeout_slot();//时间进度条
    void heartback();//我的喜欢改变图片
    void buttonquilt();//快进
    void buttonslot();//快退
private:
    Ui::MainWindow *ui;
};
extern void *deal_fun(void *arg);
extern void *deal_fun2(void *arg);
extern pthread_mutex_t mutex;
#endif // MAINWINDOW_H
