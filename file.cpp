#include<fstream>
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QSaveFile>
#include <QFileDialog>
using namespace std;
//文件操作功能
//新建文件
void MainWindow::ShowNewFile ()
{
    MainWindow *newMainWindow = new MainWindow;
    newMainWindow->show ();
}
//打开文件
void MainWindow::ShowOpenFile ()
{
    fileName = QFileDialog::getOpenFileName(this, "打开");
    curFileName = fileName;
    if (!fileName.isEmpty ())       //文件名不为空
    {
        //原窗口内容为空，则直接加载该文件
        if (showWidget->text->document ()->isEmpty ())
        {
            loadFile (fileName);    //loadFile()函数实现在下方.
            //从文件都入到内存
        }
        //否则，打开新窗口加载文件
        else
        {
            MainWindow *newMainWindow = new MainWindow;
            newMainWindow->show ();
            newMainWindow->loadFile (fileName);
        }
    }
}

//loadFile()函数实现，利用QFile和QTextStream完成具体读取文件内容工作
void MainWindow::loadFile (QString filename)
{
    QFile f(filename);     //获取文件
    if (f.open (QIODevice::ReadOnly | QIODevice::Text))
    {
        //提供基于文本流的功能(对于ASCII文本）
        QTextStream textStream(&f);
        while (!textStream.atEnd ())      //判断是否到文件流或文件终点
        {
            //读取流中的一行,并返回包含文本的返回的字符串
            QString line = textStream.readLine();
            showWidget->text->append (line);
            printf("read line\n");
        }  
    }
    cl.ReadFile(filename);
}
void ChunkList::ReadFile(QString filename)//把文件读入内存
{
    int i,j;
    CPtr t;//行和块的指针
    t=heads[0];
    char* ch;
    QFile f(filename);
    QString str;
    QByteArray ba;
    if (f.open (QIODevice::ReadOnly | QIODevice::Text))
    {
        //提供基于文本流的功能(对于ASCII文本）
        QTextStream textStream(&f);

        while (!textStream.atEnd ())      //判断是否到文件流或文件终点
        {  
            //读取流中的一行,并返回包含文本的返回的字符串
            str = textStream.readLine();//读取一行
            ba = str.toLatin1();
            ch=ba.data();  //将Qstring转成char*
            i=0;
            j=0;
            while(i<100&&ch[j]!='\0')
            {
                while(i<100&&ch[j]!='\0')//块大小不足100且未至行尾
                {
                    t->data[i]=ch[j];
                    t->Total++;
                    j++;
                    i++;
                }
                if(i>=100)//此块满
                {
                    AddChunk(LineNum);//加一块
                    t=t->next;//指向下个块
                    i=0;
                }
            }
             if(ch[j]=='\0')
            {
               // t->data[i]='\0';
                AddLine();
                t=heads[LineNum-1];
                i=0;
                j=0;
            }
        }
    }
        f.close();
        pos.line=1;//为什么是这个？？打开后光标不是应该在最后一个位置了吗
        pos.num=0;
}
//保存文件
void MainWindow::ShowSaveFile ()
{
    int line,i;
    flag=1;
    QString str;
    char *cpline;
    if (curFileName.isEmpty ())    //原路径文件名
    {
       QString filename= QFileDialog::getSaveFileName (this, tr("保存文件"),QString(), tr("文本文件(*.txt);;c++文件(*h *cpp *hpp"));
        if (!filename.isEmpty ())
        {

            QFile f(filename);
            if (!f.open (QIODevice::Text | QIODevice::WriteOnly)) {
                QMessageBox::critical (this, tr("错误"), tr("不能打开文件"));
                return;
            }
            curFileName = filename;      //下次保存，默认同一条路径
            QTextStream outs(&f);
            for(line=1;line<=cl.LineNum;line++)
            {

                cl.LineString(line,cpline);
                str = QString(QLatin1String(cpline));
                outs<<str<<endl;
                outs.flush();
                delete cpline;
            }
            f.close ();
        }
    }
    else {     
        QFile f(curFileName);
        if (!f.open (QIODevice::Text | QIODevice::WriteOnly))
        {
            QMessageBox::critical (this, tr("错误"), tr("不能打开文件"));
            return;
        }
        QTextStream outs(&f);
        for(line=1;line<=cl.LineNum;line++)
        {

            cl.LineString(line,cpline);
            str = QString(QLatin1String(cpline));
            outs<<str<<endl;
            outs.flush();
            delete cpline;
        }
        f.close ();
    }
}
