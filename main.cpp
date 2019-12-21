#include "mainwindow.h"
#include <QApplication>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <qtextcodec.h>
#include <sys/stat.h>
#include <fcntl.h>

void *deal_fun(void *arg)
{

    long fd = (long)arg;
    while(1)
    {
        char buf[128]="";
        read(fd, buf,sizeof(buf));

        char cmd[128]="";
        sscanf(buf,"%[^=]",cmd);
        if(strcmp(cmd,"ANS_PERCENT_POSITION") == 0)//百分比
        {

            sscanf(buf,"%*[^=]=%d", &percent_pos);
        }
        else if(strcmp(cmd,"ANS_TIME_POSITION") == 0)//当前时间
        {

            sscanf(buf,"%*[^=]=%d", &time_pos);
        }
        else if(strcmp(cmd,"ANS_LENGTH")==0)
        {
            sscanf(buf,"%*[^=]=%d", &total_time);
        }
        else if(strcmp(cmd,"ANS_ARTIST")==0)//歌手
        {
            sscanf(buf,"%*[^']'%[^']",lrc_name);

        }
        else if(strcmp(cmd,"ANS_ALBUM")==0)//歌曲
        {

            sscanf(buf,"%*[^']'%[^']",song_name);

        }
    }
}
void *deal_fun2(void *arg)
{
    long fifo_fd = (long)arg;
    //不停的给fifo_cmd发送获取当前时间以及进度

    while(1)
    {
        pthread_mutex_lock(&mutex);
        usleep(500*100);//0.5秒发指令
        write(fifo_fd,"get_percent_pos\n", strlen("get_percent_pos\n"));
        usleep(500*100);//0.5秒发指令
        write(fifo_fd,"get_time_pos\n", strlen("get_time_pos\n"));
        usleep(500*100);//0.5秒发指令
        write(fifo_fd,"get_time_length\n", strlen("get_time_length\n"));
        pthread_mutex_unlock(&mutex);
        usleep(500*100);

    }
}
int main(int argc, char *argv[])
{
    //创建子父进程
    int fd[2];
    pipe(fd);
    pid_t pid=fork();
    if(pid < 0)
        perror("fork");
    else if(pid == 0)
    {
    //创建有名管道
    mkfifo("myfifo",0777);
    dup2(fd[1],1);
    execlp("mplayer","mplayer","-slave","-quiet","quit","-idle","-input",\
           "file=./myfifo","./爱上你很快乐.mp3",NULL);
    }
    else
    {
//    改成中文输入
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    //QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForCStrings(codec);


//    创建有名管道
      mkfifo("myfifo",0777);
      int fd1 = open("myfifo",O_WRONLY);
      write(fd1,"volume 50 1\n",strlen("volume 50 1\n"));;
      //创建一个接受mplayer回应的线程
      pthread_t mplayer_ack;
      pthread_create(&mplayer_ack,NULL,deal_fun , (void *)(fd[0]));
      pthread_detach(mplayer_ack);

      int fifo_fd = open("myfifo",O_WRONLY);
      //创建一个线程 给mplayer发送指令
      pthread_t send_mplayer;
      pthread_create(&send_mplayer,NULL,deal_fun2,(void *)fifo_fd);
      pthread_detach(send_mplayer);

      QApplication a(argc, argv);
      MainWindow w;
      w.show();

    return a.exec();
    }
}
