#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>         //使能够输出中文
int main(int argc, char *argv[])
{
    //来设置中文字体编码
    //在读取文件时，才能不会读取中文为乱码
    QTextCodec::setCodecForLocale (QTextCodec::codecForName ("UTF8"));

    QApplication a(argc, argv);
    QFont f("ZYSong18030", 12);
    a.setFont (f);

    MainWindow w;
    w.show();
    return a.exec();
}
