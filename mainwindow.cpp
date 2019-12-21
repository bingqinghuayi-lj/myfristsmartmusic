#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<string>
class lrcsong{
public:
    lrcsong (QString lrcl,int lrc_time)
    {
        this->lrc_time = lrc_time;
        this->lrclrc = lrcl;
    }

    int lrc_time;
    QString  lrclrc;

};
int songssum = 0;
int time_now = 0;
int flag = 0;
using namespace std;
QStringList l;
QStringList songs;
list<lrcsong> lrcis;
pthread_mutex_t mutex;
char buf[128] = "爱上你很快乐.mp3";
int total_time = 0;//总时间
int percent_pos = 0;//百分比
int time_pos = 0;//实时时间
char song_name[32] = "";//歌曲名字
char *lrc_name = new char[32];
static int time1 = 0; //歌曲实时时间
int time_new = 0;
int i = 0.1;
int as = 0;

void PrintListInt(QString &value)
{
    qDebug() << value<<endl;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //创建一个定时器
    QTimer *time = new QTimer(this);
    time->start(100);//        int diffvalue = slidervalue - time_pos; //差值
    connect(time,SIGNAL(timeout()),this,SLOT(timeout_slot()));
    //显示时间和日期//        int diffvalue = slidervalue - time_pos; //差值
    mytimer = new QTimer(this);
    mytimer->start(100);
    connect(mytimer,SIGNAL(timeout()),this,SLOT(Getdatetime()));
    //背景图片
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/bizhi1.jpg")));
    setPalette(pal);
    //收藏歌曲提示信息
    connect(ui->buttonheart, SIGNAL(clicked()), this, SLOT(shoucanglrc()));

    //暂停与开始图片切换
    connect(ui->buttonstop,SIGNAL(clicked()),this,SLOT(changephoto()));

    //退出音乐播放器
    connect(ui->buttonquit,SIGNAL(clicked()),this,SLOT(quitmplayer()));

    //换皮肤
    connect(ui->buttonskins,SIGNAL(clicked()),this,SLOT(changeskins()));

    //静音
    connect(ui->buttonsound,SIGNAL(clicked()),this,SLOT(buttonsunds()));

    //上一首
    connect(ui->buttonbefore,SIGNAL(clicked()),this,SLOT(buttonfront()));

    //下一首
    connect(ui->buttonafter,SIGNAL(clicked()),this,SLOT(buttonbeore()));

    //快进
    connect(ui->buttonquitly,SIGNAL(clicked()),this,SLOT(buttonquilt()));

    //快退
    connect(ui->buttonslot,SIGNAL(clicked()),this,SLOT(buttonslot()));

    //返回时改变我的喜欢图片
    connect(ui->buttonlrcback,SIGNAL(clicked()),this,SLOT(heartback()));

    //歌词全屏
    connect(ui->buttonlrc,SIGNAL(clicked()),this,SLOT(switchPage()));
    connect(ui->buttonlrcback,SIGNAL(clicked()),this,SLOT(switchPage()));
    connect(ui->buttonheart,SIGNAL(clicked()),this,SLOT(switchPage()));

    //进度条拖拽
    connect(ui->horizontalSlider,&QSlider::sliderReleased,[=]()
    {
        mkfifo("myfifo",0777);
        int fd = open("myfifo",O_WRONLY);
        pthread_mutex_lock(&mutex);
        time->stop();
        int slidervalue = ui->horizontalSlider->value(); //移动后
        time_pos = slidervalue; //给时间赋值
        char buf[32] = "";
        sprintf(buf,"seek %d 1\n",slidervalue);
        write(fd,buf,strlen(buf));
        time->start();
        pthread_mutex_unlock(&mutex);
    });

    //双击切换歌曲
    connect(ui->listWidget,&QListWidget::doubleClicked,[=]{
        mkfifo("myfifo",0777);
        int fd = open("myfifo",O_WRONLY);
        char buff[128]= "loadfile \"";
        QByteArray ba = ui->listWidget->currentItem()->text().toUtf8();
        //ui->listWidget->setCurrentRow;//设置列表变化
        strcpy(buf,ba.data());
        strcat(buff,buf);
        strcat(buff,"\"");
        strcat(buff,"\n");
        write(fd,buff,strlen(buff));
        printf("%s\n",buff);
        //显示歌词
        //清空labe内容
        lrcis.clear();
        songs.clear();
        ui->label->clear();
        ui->label_4->clear();
        ui->label_5->clear();
        ui->listWidget_3->clear();
        char buff1[128] = "";
        char Site[128] = "";
        strcpy(buff1,buf);
        strcpy(&(buff1[strlen(buff1)-4]),".lrc");
//        printf("%s\n",buff1);
        sprintf(Site,"./lyrics/%s",buff1);
//        printf("%s\n",Site);
        fflush(stdout);
        FILE *fp;
        if ((fp = fopen(Site,"r+")) == NULL)
        {
            perror("fail to fopen");
            return;
        }
        fseek(fp, 0, SEEK_END);
        long int len = ftell(fp);
        char *lrc = (char *)malloc(len + 1);
        fseek(fp, 0, SEEK_SET);
        fread(lrc, len, 1, fp);
        char *str[256] = {NULL};
        int l = 0;
        str[l] = strtok(lrc,"\n");
        fclose(fp);
        while(str[l] != NULL)
        {
            l++;
            str[l] = strtok(NULL,"\n");

        }
        int j = 0;
        int min,sec;
        for(j = 0;j<l;j++)
        {
            char *p_lrc = str[j];
            char *p_s = str[j];
            while(*p_lrc == '[')
            {
                sscanf(p_s,"[%d:%d",&min,&sec);
                time_now = min*60+sec;
                p_lrc += 10;
                QString p_lrc1 = (QString)p_lrc;
                lrcis.push_back(lrcsong(p_lrc1,time_now));
                //全屏
                songs.push_back(p_lrc1);
                QListWidgetItem *item1 = new QListWidgetItem;

                item1->setTextAlignment(Qt::AlignCenter);
                item1->setText(p_lrc1);
                ui->listWidget_3->addItem(item1);
                ui->listWidget_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //垂直滚动条
            }
        }
        fflush(stdout);
    });
    //双击切换歌曲在我的喜欢中
    connect(ui->listWidget3,&QListWidget::doubleClicked,[=]{
        mkfifo("myfifo",0777);
        int fd = open("myfifo",O_WRONLY);
        char buff[128]= "loadfile \"";
        QByteArray ba = ui->listWidget3->currentItem()->text().toUtf8();
        //ui->listWidget->setCurrentRow;//设置列表变化
        strcpy(buf,ba.data());
        strcat(buff,buf);
        strcat(buff,"\"");
        strcat(buff,"\n");
        write(fd,buff,strlen(buff));
        printf("%s\n",buff);
        //显示歌词
        //清空labe内容
        lrcis.clear();
        songs.clear();
        ui->label->clear();
        ui->label_4->clear();
        ui->label_5->clear();
        ui->listWidget_3->clear();
        char buff1[128] = "";
        char Site[128] = "";
        strcpy(buff1,buf);
        strcpy(&(buff1[strlen(buff1)-4]),".lrc");
//        printf("%s\n",buff1);
        sprintf(Site,"./lyrics/%s",buff1);
//        printf("%s\n",Site);
        fflush(stdout);
        FILE *fp;
        if ((fp = fopen(Site,"r+")) == NULL)
        {
            perror("fail to fopen");
            return;
        }
        fseek(fp, 0, SEEK_END);
        long int len = ftell(fp);
        char *lrc = (char *)malloc(len + 1);
        fseek(fp, 0, SEEK_SET);
        fread(lrc, len, 1, fp);
        char *str[256] = {NULL};
        int l = 0;
        str[l] = strtok(lrc,"\n");
        fclose(fp);
        while(str[l] != NULL)
        {
            l++;
            str[l] = strtok(NULL,"\n");

        }
        int j = 0;
        int min,sec;
        for(j = 0;j<l;j++)
        {
            char *p_lrc = str[j];
            char *p_s = str[j];
            while(*p_lrc == '[')
            {
                sscanf(p_s,"[%d:%d",&min,&sec);
                time_now = min*60+sec;
                p_lrc += 10;
                QString p_lrc1 = (QString)p_lrc;
                lrcis.push_back(lrcsong(p_lrc1,time_now));
                //全屏
                songs.push_back(p_lrc1);
                QListWidgetItem *item1 = new QListWidgetItem;

                item1->setTextAlignment(Qt::AlignCenter);
                item1->setText(p_lrc1);
                ui->listWidget_3->addItem(item1);
                ui->listWidget_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //垂直滚动条
            }
        }
        fflush(stdout);
    });
    //打印歌单并将歌单放入到容器里面
    DIR *dir = opendir("./song");
    int i = 0;
    ui->listWidget->clear();
    while (1) {
        struct dirent* dirp = readdir(dir);

        if(dirp == NULL){
            break;
        }
        else if(dirp->d_type == DT_REG){
            //sscanf(dirp->d_name,"%[^.]",buf);
            ui->listWidget->addItem(new QListWidgetItem(dirp->d_name));
            ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //垂直滚动条
            l.push_back(dirp->d_name);
            songssum ++;
            //strcpy(buf,ret[i]);
        }
        i++;
    }
    closedir(dir);
    printf("songssum = %d\n",songssum);
    //调节音量大小
    ui->spinBox->setValue(50);
    ui->slider->setValue(50);
    connect(ui->slider,&QSlider::valueChanged,[=]{
        char buff[128] ={0};
        sprintf(buff,"volume %d 1\n",ui->spinBox->value());
        int fd_v = open("myfifo",O_WRONLY);
        write(fd_v,buff,strlen(buff));
    });

    connect(ui->slider,&QSlider::valueChanged,ui->spinBox,&QSpinBox::setValue);
    void (QSpinBox::*mysignal)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox,mysignal,ui->slider,&QSlider::setValue);
    //清空容器
    lrcis.clear();
    songs.clear();
    ui->label->clear();
    ui->label_4->clear();
    ui->label_5->clear();
    ui->listWidget_3->clear();
    //显示歌词

    char buff[128] = "";
    char Site[128] = "";
    strcpy(buff,buf);
    strcpy(&(buff[strlen(buff)-4]),".lrc");
    printf("%s\n",buff);
    sprintf(Site,"./lyrics/%s",buff);
    printf("%s\n",Site);
    fflush(stdout);
    FILE *fp;
    if ((fp = fopen(Site,"r+")) == NULL)
    {
        perror("fail to fopen");
        return;
    }
    fseek(fp, 0, SEEK_END);
    long int len = ftell(fp);
    char *lrc = (char *)malloc(len + 1);
    fseek(fp, 0, SEEK_SET);
    fread(lrc, len, 1, fp);
    char *str[256] = {NULL};
    int l = 0;
    str[l] = strtok(lrc,"\n");
    fclose(fp);
    while(str[l] != NULL)
    {
        l++;
        str[l] = strtok(NULL,"\n");

    }
    int j = 0;
    int min,sec;
    for(j = 0;j<l;j++)
    {
        char *p_lrc = str[j];
        char *p_s = str[j];
        while(*p_lrc == '[')
        {
            sscanf(p_s,"[%d:%d",&min,&sec);
            time_now = min*60+sec;
            p_lrc += 10;
            QString p_lrc1 = (QString)p_lrc;
            lrcis.push_back(lrcsong(p_lrc1,time_now));
            songs.push_back(p_lrc);
            //全屏
            QListWidgetItem *item1 = new QListWidgetItem;
            item1->setTextAlignment(Qt::AlignCenter);
            item1->setText(p_lrc1);
            ui->listWidget_3->addItem(item1);
            ui->listWidget_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //垂直滚动条
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::shoucanglrc()//收藏喜欢
{
    if(flag == 0)
    {
        QMessageBox::information(this,"成功","已添加到我的喜欢");
        QIcon button_stop(":/image/png/favorites.png");
        ui->buttonheart->setMinimumSize(60,60);
        ui->buttonheart->setMaximumSize(80,80);
        ui->buttonheart->setIcon(button_stop);
        ui->buttonheart->setIconSize(QSize(80,80));
        ui->listWidget3->addItem(new QListWidgetItem(buf));
        flag++;
    }
    else if(flag == 1)
    {
        QMessageBox::information(this,"成功","已添加到我的喜欢");
        QIcon button_stop(":/image/png/favorites.png");
        ui->buttonheart->setMinimumSize(60,60);
        ui->buttonheart->setMaximumSize(80,80);
        ui->buttonheart->setIcon(button_stop);
        ui->buttonheart->setIconSize(QSize(80,80));
        ui->listWidget3->addItem(new QListWidgetItem(buf));
        flag++;
    }
    else if(flag == 2)
    {
        QMessageBox::information(this,"取消","取消喜欢成功");
        QIcon button_stop(":/image/unheart.jpg");
        ui->buttonheart->setMinimumSize(60,60);
        ui->buttonheart->setMaximumSize(80,80);
        ui->buttonheart->setIcon(button_stop);
        ui->buttonheart->setIconSize(QSize(80,80));
        flag = 0;
    }
}

void MainWindow::changephoto()//暂停播放
{
    mkfifo("myfifo",0777);

    if(flag == 0)
    {
        pthread_mutex_lock(&mutex);
        QIcon button_stop(":/image/png/button-play.png");

        ui->buttonstop->setMinimumSize(80,80);
        ui->buttonstop->setMaximumSize(80,80);
        ui->buttonstop->setIcon(button_stop);
        ui->buttonstop->setIconSize(QSize(80,80));
        int fd1 = open("myfifo",O_WRONLY);
        write(fd1,"pause\n",strlen("pause\n"));
        flag++;
    }
    else if(flag == 1)
    {
        QIcon button_start(":/image/png/button-pause.png");

        ui->buttonstop->setIcon(button_start);
        int fd1 = open("myfifo",O_WRONLY);
        write(fd1,"pause\n",strlen("pause\n"));
        pthread_mutex_unlock(&mutex);
        flag--;
    }
}

void MainWindow::quitmplayer()//关闭音乐播放器
{
    this->close();
    mkfifo("myfifo",0777);
    int fd1 = open("myfifo",O_WRONLY);
    write(fd1,"quit\n",strlen("quit\n"));
}

void MainWindow::changeskins()//换皮肤
{
    if(flag == 0)
    {
        QPalette pal = this->palette();
        pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/bizhi2.jpg")));
        setPalette(pal);
        flag++;
    }
    else if(flag == 1)
    {
        QPalette pal = this->palette();
        pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/background/3.jpg")));
        setPalette(pal);
        flag++;
    }
    else if(flag == 2)
    {
        QPalette pal = this->palette();
        pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/dongtai1.gif")));
        setPalette(pal);
        flag++;
    }
    else if(flag == 3)
    {
        QPalette pal = this->palette();
        pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/bizhi1.jpg")));
        setPalette(pal);
        flag = 0;
    }
}

void MainWindow::buttonsunds()//静音
{

    if(flag == 0)
    {
        QIcon button_stop(":/image/png/Image-audio-volume-muted-blocking-panel.png");
        ui->buttonsound->setMinimumSize(80,80);
        ui->buttonsound->setMaximumSize(80,80);
        ui->buttonsound->setIcon(button_stop);
        ui->buttonsound->setIconSize(QSize(80,80));
        mkfifo("myfifo",0777);
        int fd1 = open("myfifo",O_RDWR);
        write(fd1,"mute 1\n",strlen("mute 1\n"));
        flag++;
    }
    else if(flag == 1)
    {
        QIcon button_start(":/image/png/Image-audio-volume-medium-panel.png");
        ui->buttonsound->setIcon(button_start);
        mkfifo("myfifo",0777);
        int fd1 = open("myfifo",O_RDWR);
        write(fd1,"mute 0\n",strlen("mute 0\n"));
        flag--;
    }
}

void MainWindow::switchPage()//全屏歌词
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(button==ui->buttonlrc)
        ui->stackedWidget->setCurrentIndex(1);
    if(button==ui->buttonlrcback)
        ui->stackedWidget->setCurrentIndex(0);
    if(button==ui->buttonheart)
        ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::setValue(int num)//调节音量大小
{
    ui->spinBox->setValue(num);

}

int MainWindow::getValue()//调节音量大小
{
    return ui->spinBox->value();
}

void MainWindow::Getdatetime()//显示当前时间日期
{
    QTime timeNow = QTime::currentTime();
    ui->label_8->setText(tr("日期:")+(QDate::currentDate().toString(tr("yyyy年MM月dd日 ddd" ))));
    ui->label11->setText(tr("时间:%1").arg(timeNow.toString()));
}

void MainWindow::timeout_slot()
{
    char buf_tmp[32] = "";
    sprintf(buf_tmp,"%02d:%02d",time_pos/60, time_pos%60);
    QString str(buf_tmp);
    ui->lablenow->setText(str); //自定义实时时间
    as++;
    if(as%10 == 0)
        ui->horizontalSlider->setValue(percent_pos);//进度条进度
    //显示总时间
    char buf_tmp1[32] = "";
    sprintf(buf_tmp1,"%02d:%02d", (int)(total_time)/60, (int)(total_time)%60);

    QString str1(buf_tmp1);
    ui->labelrun->setText(str1);
    //显示歌手和专辑
    ui->lineEdit->setText(buf);
    char buf_artist[32]="";
    sprintf(buf_artist,"%s",lrc_name);
    ui->lineEdit_2->setText(buf_artist);

    //显示歌词
    //顺序播放
    mkfifo("myfifo",0777);
    int fd = Open("myfifo");
    int a = l.indexOf(QString(buf));
    if(time_pos == total_time-3)
    {
        mkfifo("myfifo",0777);
        int fd = Open("myfifo");
        int a = l.indexOf(QString(buf));
        if(a == songssum-1)
        {
            char*  ch;
            QByteArray ba = l[0].toUtf8();
            ch=ba.data();
            strcpy(buf,ch);
            char buff[128];
            sprintf(buff,"loadfile %s\n",buf);
            write(fd,buff,strlen(buff));
        }
        else
        {
            //打开当前歌词文件
            char*  ch;
            QByteArray ba = l[a+1].toUtf8();
            ch=ba.data();
            strcpy(buf,ch);
            char buff[128];
            sprintf(buff,"loadfile %s\n",buf);
            write(fd,buff,strlen(buff));
            Close(fd);
        }

        //显示歌词
        lrcis.clear();
        songs.clear();
        ui->label->clear();
        ui->label_4->clear();
        ui->label_5->clear();
        ui->listWidget_3->clear();
        char buff1[128] = "";
        char Site[128] = "";
        strcpy(buff1,buf);
        strcpy(&(buff1[strlen(buff1)-4]),".lrc");
    //    printf("%s\n",buff1);
        sprintf(Site,"./lyrics/%s",buff1);
    //    printf("%s\n",Site);
        fflush(stdout);
        FILE *fp;
        if ((fp = fopen(Site,"r+")) == NULL)
        {
            perror("fail to fopen");
            return;
        }
        fseek(fp, 0, SEEK_END);
        long int len = ftell(fp);
        char *lrc = (char *)malloc(len + 1);
        fseek(fp, 0, SEEK_SET);
        fread(lrc, len, 1, fp);
        char *str[256] = {NULL};
        int l = 0;
        str[l] = strtok(lrc,"\n");
        fclose(fp);
        while(str[l] != NULL)
        {
            l++;
            str[l] = strtok(NULL,"\n");

        }
        int j = 0;
        int min,sec;
        for(j = 0;j<l;j++)
        {
            char *p_lrc = str[j];
            char *p_s = str[j];
            while(*p_lrc == '[')
            {
                sscanf(p_s,"[%d:%d",&min,&sec);
                time_now = min*60+sec;
                p_lrc += 10;
                QString p_lrc1 = (QString)p_lrc;
                lrcis.push_back(lrcsong(p_lrc1,time_now));
                songs.push_back(p_lrc);
                //全屏

                QListWidgetItem *item1 = new QListWidgetItem;

                item1->setTextAlignment(Qt::AlignCenter);
                item1->setText(p_lrc1);
                ui->listWidget_3->addItem(item1);
                ui->listWidget_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //垂直滚动条
            }
        }
        fflush(stdout);
    }
    else
    {
        for_each(lrcis.begin(),lrcis.end(),[=](lrcsong p)
        {
            if(p.lrc_time == time_pos)
            {

                {
                    char bufff[64] = "";
                    int a = songs.indexOf(p.lrclrc);
                    char*  ch;
                    QByteArray ba = songs[a].toUtf8();
                    ch=ba.data();
                    strcpy(bufff,ch);
                    ui->label->setText(songs[a]);
                    ui->listWidget_3->setCurrentRow(a+8);
                    ui->listWidget_3->setCurrentRow(a);
                }

            }
        });
    }


}

void MainWindow::heartback()//返回按钮改变我的喜欢
{
    QIcon button_stop(":/image/unheart.jpg");
    ui->buttonheart->setMinimumSize(60,60);
    ui->buttonheart->setMaximumSize(80,80);
    ui->buttonheart->setIcon(button_stop);
    ui->buttonheart->setIconSize(QSize(80,80));
}

void MainWindow::buttonquilt()//快进
{
    mkfifo("myfifo",0777);
    int fd = open("myfifo",O_WRONLY);
    write(fd,"seek 10",strlen("seek 10"));
}

void MainWindow::buttonslot()//快退
{
    mkfifo("myfifo",0777);
    int fd = open("myfifo",O_WRONLY);
    write(fd,"seek -10",strlen("seek -10"));
}

//void MainWindow::on_btn_Del_clicked()//取消我的喜欢
//{
//    if(ui->listWidget3->takeItem()!=Q_NULLPTR)
//    {
//        QListWidgetItem * item = ui->listWidget3->takeItem()(ui->listWidget3->currentRow());
//        delete item;
//    }
//}

void MainWindow::buttonfront()//上一首
{
    mkfifo("myfifo",0777);
    int fd = open("myfifo",O_WRONLY);
    int a = l.indexOf(QString(buf));
    if(a == songssum - 14 )
    {
        char*  ch;
        QByteArray ba = l[13].toUtf8();
        ch=ba.data();
        strcpy(buf,ch);
        char buff[128];
        sprintf(buff,"loadfile %s\n",buf);
        write(fd,buff,strlen(buff));
    }
    else
    {
        char*  ch;
        QByteArray ba = l[a-1].toUtf8();
        ch=ba.data();
        strcpy(buf,ch);
        char buff[128];
        sprintf(buff,"loadfile %s\n",buf);
        write(fd,buff,strlen(buff));
    }
    //显示歌词
    lrcis.clear();
    songs.clear();
    ui->label->clear();
    ui->label_4->clear();
    ui->label_5->clear();
    ui->listWidget_3->clear();
    char buff1[128] = "";
    char Site[128] = "";
    strcpy(buff1,buf);
    strcpy(&(buff1[strlen(buff1)-4]),".lrc");
//    printf("%s\n",buff1);
    sprintf(Site,"./lyrics/%s",buff1);
//    printf("%s\n",Site);
    fflush(stdout);
    FILE *fp;
    if ((fp = fopen(Site,"r+")) == NULL)
    {
        perror("fail to fopen");
        return;
    }
    fseek(fp, 0, SEEK_END);
    long int len = ftell(fp);
    char *lrc = (char *)malloc(len + 1);
    fseek(fp, 0, SEEK_SET);
    fread(lrc, len, 1, fp);
    char *str[256] = {NULL};
    int l = 0;
    str[l] = strtok(lrc,"\n");
    fclose(fp);
    while(str[l] != NULL)
    {
        l++;
        str[l] = strtok(NULL,"\n");

    }
    int j = 0;
    int min,sec;
    for(j = 0;j<l;j++)
    {
        char *p_lrc = str[j];
        char *p_s = str[j];
        while(*p_lrc == '[')
        {
            sscanf(p_s,"[%d:%d",&min,&sec);
            time_now = min*60+sec;
            p_lrc += 10;
            QString p_lrc1 = (QString)p_lrc;
            lrcis.push_back(lrcsong(p_lrc1,time_now));
            songs.push_back(p_lrc);
            //全屏

            QListWidgetItem *item1 = new QListWidgetItem;

            item1->setTextAlignment(Qt::AlignCenter);
            item1->setText(p_lrc1);
            ui->listWidget_3->addItem(item1);
            ui->listWidget_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //垂直滚动条
        }
    }
    fflush(stdout);
}

void MainWindow::buttonbeore()//下一首
{
    mkfifo("myfifo",0777);
    int fd = Open("myfifo");
    int a = l.indexOf(QString(buf));
    if(a == songssum-1)
    {
        char*  ch;
        QByteArray ba = l[0].toUtf8();
        ch=ba.data();
        strcpy(buf,ch);
        char buff[128];
        sprintf(buff,"loadfile %s\n",buf);
        write(fd,buff,strlen(buff));
    }
    else
    {
        //打开当前歌词文件
        char*  ch;
        QByteArray ba = l[a+1].toUtf8();
        ch=ba.data();
        strcpy(buf,ch);
        char buff[128];
        sprintf(buff,"loadfile %s\n",buf);
        write(fd,buff,strlen(buff));
        Close(fd);
    }

    //显示歌词
    lrcis.clear();
    songs.clear();
    ui->label->clear();
    ui->label_4->clear();
    ui->label_5->clear();
    ui->listWidget_3->clear();
    char buff1[128] = "";
    char Site[128] = "";
    strcpy(buff1,buf);
    strcpy(&(buff1[strlen(buff1)-4]),".lrc");
//    printf("%s\n",buff1);
    sprintf(Site,"./lyrics/%s",buff1);
//    printf("%s\n",Site);
    fflush(stdout);
    FILE *fp;
    if ((fp = fopen(Site,"r+")) == NULL)
    {
        perror("fail to fopen");
        return;
    }
    fseek(fp, 0, SEEK_END);
    long int len = ftell(fp);
    char *lrc = (char *)malloc(len + 1);
    fseek(fp, 0, SEEK_SET);
    fread(lrc, len, 1, fp);
    char *str[256] = {NULL};
    int l = 0;
    str[l] = strtok(lrc,"\n");
    fclose(fp);
    while(str[l] != NULL)
    {
        l++;
        str[l] = strtok(NULL,"\n");

    }
    int j = 0;
    int min,sec;
    for(j = 0;j<l;j++)
    {
        char *p_lrc = str[j];
        char *p_s = str[j];
        while(*p_lrc == '[')
        {
            sscanf(p_s,"[%d:%d",&min,&sec);
            time_now = min*60+sec;
            p_lrc += 10;
            QString p_lrc1 = (QString)p_lrc;
            lrcis.push_back(lrcsong(p_lrc1,time_now));
            songs.push_back(p_lrc);
            //全屏

            QListWidgetItem *item1 = new QListWidgetItem;

            item1->setTextAlignment(Qt::AlignCenter);
            item1->setText(p_lrc1);
            ui->listWidget_3->addItem(item1);
            ui->listWidget_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //垂直滚动条
        }
    }
    fflush(stdout);
}

int Open(char *fifo)
{
    return  open(fifo,O_WRONLY);
}
void Close(int fd)
{
    close(fd);
}
