//数据结构部分的操作
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

//块操作
void MainWindow::ShowCopy()
{
    showWidget->text->copy();
}
void MainWindow::ShowCut()
{
    showWidget->text->cut();
}
void MainWindow::ShowPaste()
{
    showWidget->text->paste();
}

/*void ChunkList::GetNextVal(char *p,int next[])//求next数组
{
    int len=strlen(p);//长度
    int k=-1,j=0;
    next[0]=-1;

    while(j<len-1)
    {
        if(k==-1||p[j]==p[k])//p[k]表示前缀，p[j]表示后缀
        {
            j++;
            k++;
            if(p[j]!=p[k])
               next[j]=k;
            else
               next[j]=next[k];
        }
        else
        {
            k=next[k];
        }
    }
}
int ChunkList::KMP(char *p,char *s)//字符串匹配，成功则返回模式串第一次在文本串中出现的位置，失败则返回-1,s为文本串，p为模式串
{
    int i=0,j=0;
    int slen=strlen(s);
    int plen=strlen(p);

    while(i<slen&&j<plen)
    {
        if(j==-1||s[i]==p[j])//j=-1或当前字符匹配成功
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];
        }
    }
    if(j==plen)
       return i-j;//模式串第一次在文本串中出现的位置
    else
       return -1;//匹配失败
}

void ChunkList::search(char *p)//查找字符串，p为所查找的字符串,光标位置定位于第一次匹配的子串首字符
{
    int ln,ponum,flag=1,pnext[];//当前遍历到的行号,行中第几个位置
    char *cpline;//把每一行复制到这个数组
    GetNextVal(p,pnext);
    while(ln<=LineNum&&flag==1)
    {
        ln=1;//从第一行开始遍历
        CopyLine(ln,cpline);//把此行复制到这个数组
        if(KMP(p)==-1)//此行未找到
        {
            ln++;
            free(cpline);//释放
        }
        else
        {
            Position.line=ln;//当前的行号
            Position.num=KMP(p);//位置
            flag=0;//找到则跳出
        }
    }
}*/
//显示查找对话框
void MainWindow::ShowFindDialog ()
{
    QDialog *FindDialog = new QDialog(this);
    QGridLayout *mainLayout = new QGridLayout(FindDialog);

    lineLabel = new QLabel(tr("查找内容(N): "));
    lineEdit = new QLineEdit;

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget (lineLabel);
    inputLayout->addWidget (lineEdit);

    findNextBtn = new QPushButton(tr("查找下一个"));
    cancelBtn = new QPushButton(tr("取消"));
    connect (cancelBtn, SIGNAL(clicked(bool)), FindDialog, SLOT(reject()));

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget (findNextBtn);
    buttonLayout->addWidget (cancelBtn);

    directLabel = new QLabel(tr("方向"));
    upBtn = new QRadioButton(tr("向上"));

    upBtn->setChecked (true);

    downBtn = new QRadioButton(tr("向下"));

    mainLayout->addLayout (inputLayout, 0, 0, 1, 3);
    mainLayout->addLayout (buttonLayout, 0, 4, 2, 1);
    mainLayout->addWidget (directLabel, 1, 1);
    mainLayout->addWidget (upBtn, 2, 1);
    mainLayout->addWidget (downBtn, 2, 2);

    FindDialog->show ();
    str = "";
    connect (lineEdit, SIGNAL(textChanged(QString)), this, SLOT(ShowFindText()));
    connect (findNextBtn, SIGNAL(clicked(bool)), this, SLOT(ShowFindStr()));
}

void MainWindow::ShowFindText ()
{
    str = lineEdit->text ();
}

void MainWindow::ShowFindStr ()
{
//    qDebug() << str;
    bool judge;
    if (!str.isEmpty ()) {
        if (upBtn->isChecked () == Qt::Checked)
            judge = showWidget->text->find (str);
        else
            judge = showWidget->text->find (str, QTextDocument::FindBackward);
    }
    else return;
    if (!judge)
        QMessageBox::information (this, tr("结果"), tr("没找到查找内容"),QMessageBox::Yes);
}

//替换对话框
void MainWindow::ShowReplaceDialog ()
{
    QDialog *SubDialog = new QDialog(this);
    QGridLayout *mainLayout = new QGridLayout(SubDialog);

    lineLabel21 = new QLabel(tr("查找内容(N): "));
    lineEdit21 = new QLineEdit;

    lineLabel22 = new QLabel(tr("替换(P): "));
    lineEdit22 = new QLineEdit;

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget (lineLabel21);
    inputLayout->addWidget (lineEdit21);

    QHBoxLayout *inputLayout2 = new QHBoxLayout;
    inputLayout2->addWidget (lineLabel22);
    inputLayout2->addWidget (lineEdit22);

    findNextBtn2 = new QPushButton(tr("查找下一个"));
    subBtn2 = new QPushButton(tr("替换"));
    cancelBtn2 = new QPushButton(tr("取消"));
    connect (cancelBtn2, SIGNAL(clicked(bool)), SubDialog, SLOT(reject()));

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget (findNextBtn2);
    buttonLayout->addWidget (subBtn2);
    buttonLayout->addWidget (cancelBtn2);

    mainLayout->addLayout (inputLayout, 0, 0, 1, 3);
    mainLayout->addLayout (inputLayout2, 1, 0, 1, 3);
    mainLayout->addLayout (buttonLayout, 0, 4, 3, 1);

    SubDialog->show ();
    str2 = "";
    str3 = "";
    findjudge = false;
    connect (lineEdit21, SIGNAL(textChanged(QString)), this, SLOT(ShowSubText()));
    connect (lineEdit22, SIGNAL(textChanged(QString)), this, SLOT(ShowSubText2()));
    connect (findNextBtn2, SIGNAL(clicked(bool)), this, SLOT(ShowFindStr2()));
    connect (subBtn2, SIGNAL(clicked(bool)), this, SLOT(ShowSubstitute()));
}

void MainWindow::ShowSubText ()
{
    str2 = lineEdit21->text ();
}

void MainWindow::ShowSubText2 ()
{
    str3 = lineEdit22->text ();
}

void MainWindow::ShowFindStr2 ()
{
    bool judge2;
    if (!str2.isEmpty ())
         judge2 = showWidget->text->find (str2, QTextDocument::FindBackward);
    else return;
    if (!judge2)
        QMessageBox::information (this, tr("结果"), tr("没找到查找内容"),QMessageBox::Yes);
}
void MainWindow::ShowSubstitute ()
{
    QTextCursor textCur;
    int judge2;
    if (!str2.isEmpty ())
    {
        judge2 = showWidget->text->find (str2, QTextDocument::FindBackward);
        textCur = showWidget->text->textCursor ();
    }
    else return;
    if (!judge2)
        QMessageBox::information (this, tr("结果"), tr("没找到查找内容"),QMessageBox::Yes);
    else
        textCur.insertText (str3);
}
