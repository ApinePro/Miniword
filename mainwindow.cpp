//界面设计
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QToolButton>
#include <QKeyEvent>
#include <QColor>
#include <QColorDialog>
#include <QCloseEvent>

class QIcon;  //类的前向声明
class ChunkList;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ChunkList cl;
     ui->setupUi(this);
     setWindowTitle(tr("Mini Word"));//设置窗口标题
     ui->statusBar->showMessage("Ready");

     showWidget = new ShowWidget(this);
     setCentralWidget (showWidget);
     showWidget->text->setLineWrapMode(QTextEdit::NoWrap);//横向滚动条

     OpenAction = new QAction(tr("&open"),this);
     OpenAction->setShortcut(QKeySequence::Open);//动作的快捷键
     OpenAction->setStatusTip(tr("open a file"));//添加状态栏的提示语句
     connect (OpenAction, SIGNAL(triggered(bool)), this, SLOT(ShowOpenFile()));
     NewAction = new QAction(tr("&new"),this);
     NewAction->setShortcut(QKeySequence::New);//动作的快捷键
     NewAction->setStatusTip(tr("new a file"));//添加状态栏的提示语句
     connect (NewAction, SIGNAL(triggered(bool)), this, SLOT(ShowNewFile()));
     SaveAction = new QAction(tr("&save"),this);
     SaveAction->setShortcut(QKeySequence::Save);//动作的快捷键
     SaveAction->setStatusTip(tr("save the file"));//添加状态栏的提示语句
     connect (SaveAction, SIGNAL(triggered(bool)), this, SLOT(ShowSaveFile()));
     QuitAction = new QAction(tr("&quit"),this);
     QuitAction->setStatusTip(tr("quit system"));//添加状态栏的提示语句
     connect (QuitAction, SIGNAL(triggered(bool)), this, SLOT(ShowQuit()));
     CutAction = new QAction(tr("&cut"),this);
     CutAction->setShortcut(QKeySequence::Cut);//动作的快捷键
     CutAction->setStatusTip(tr("cut words"));//添加状态栏的提示语句
     connect (CutAction, SIGNAL(triggered(bool)), this, SLOT(ShowCut()));
     CopyAction = new QAction(tr("&copy"),this);
     CopyAction->setShortcut(QKeySequence::Copy);//动作的快捷键
     CopyAction->setStatusTip(tr("copy words"));//添加状态栏的提示语句
     connect (CopyAction, SIGNAL(triggered(bool)), this, SLOT(ShowCopy()));
     PasteAction = new QAction(tr("&paste"),this);
     PasteAction->setShortcut(QKeySequence::Paste);//动作的快捷键
     PasteAction->setStatusTip(tr("paste words"));//添加状态栏的提示语句
     connect (PasteAction, SIGNAL(triggered(bool)), this, SLOT(ShowPaste()));
     FindAction = new QAction(tr("&find"),this);
     FindAction->setStatusTip(tr("find some word"));//添加状态栏的提示语句
     FindAction->setShortcut(QKeySequence::Find);//动作的快捷键
     connect (FindAction, SIGNAL(triggered(bool)), this, SLOT(ShowFindDialog()));
     ReplaceAction = new QAction(tr("&replace"),this);
     ReplaceAction->setStatusTip(tr("find and replace some word"));//添加状态栏的提示语句
     ReplaceAction->setShortcut(QKeySequence::Replace);//动作的快捷键
     connect (ReplaceAction, SIGNAL(triggered(bool)), this, SLOT(ShowReplaceDialog()));

     //添加图标
     OpenAction->setIcon(QIcon(":/open.png"));//添加这句代码，添加图标
     NewAction->setIcon(QIcon(":/new.png"));//添加这句代码，添加图标
     SaveAction->setIcon(QIcon(":/save.png"));//添加这句代码，添加图标
     CutAction->setIcon(QIcon(":/cut.png"));//添加这句代码，添加图标
     CopyAction->setIcon(QIcon(":/copy.png"));//添加这句代码，添加图标
     PasteAction->setIcon(QIcon(":/paste.png"));//添加这句代码，添加图标
//菜单栏
     File = menuBar()->addMenu(tr("&File"));
     File->addAction(OpenAction);
     File->addAction(NewAction);
     File->addAction(SaveAction);
     File->addAction(QuitAction);
     Edit = menuBar()->addMenu(tr("&Edit"));
     Edit->addAction(CutAction);
     Edit->addAction(CopyAction);
     Edit->addAction(PasteAction);
     Find = menuBar()->addMenu(tr("&Find"));
     Find->addAction(FindAction);
     Find->addAction(ReplaceAction);
//工具栏
     OpentoolBar = addToolBar(tr("&File"));
     OpentoolBar->addAction(OpenAction);
     NewtoolBar = addToolBar(tr("&File"));
     NewtoolBar->addAction(NewAction);
     SavetoolBar = addToolBar(tr("&File"));
     SavetoolBar->addAction(SaveAction);
     QuittoolBar = addToolBar(tr("&File"));
     QuittoolBar->addAction(QuitAction);
     CuttoolBar = addToolBar(tr("&Edit"));
     CuttoolBar->addAction(CutAction);
     CopytoolBar = addToolBar(tr("&Edit"));
     CopytoolBar->addAction(CopyAction);
     PastetoolBar = addToolBar(tr("&Edit"));
     PastetoolBar->addAction(PasteAction);
     FindtoolBar = addToolBar(tr("&Find"));
     FindtoolBar->addAction(FindAction);
     ReplacetoolBar = addToolBar(tr("&Find"));
     ReplacetoolBar->addAction(ReplaceAction);

     //在工具栏上嵌入控件:字体，大小，粗体，斜体，字体颜色
     fontLabel = new QLabel(tr("字体:"));
     fontComboBox = new QFontComboBox;
     //列出所有字体
     fontComboBox->setFontFilters (QFontComboBox::ScalableFonts);
     //字号
     fontLabel2 = new QLabel(tr("字号:"));
     sizeComboBox = new QComboBox;
     //QFontDatabase-实现在字号下拉列表框中填充各种不同的字号条目
     QFontDatabase db;

     foreach (int size, db.standardSizes ())
         sizeComboBox->addItem (QString::number (size)); //将它们插入到字号下拉框中

     //加粗
     BoldtooBar = new QToolButton;
     BoldtooBar->setIcon (QIcon(":/bold.png"));
     BoldtooBar->setStatusTip("加粗");
     //设置成是否是开关(toggle)按钮(true)---即可复选的
     BoldtooBar->setCheckable (true);

     //斜体
     ItalictooBar = new QToolButton;
     ItalictooBar->setIcon (QIcon(":/italic.png"));
     ItalictooBar->setStatusTip("斜体");
     ItalictooBar->setCheckable (true);

     //下划线
     UnderlinetooBar = new QToolButton;
     UnderlinetooBar->setIcon (QIcon(":/underline.png"));
     UnderlinetooBar->setStatusTip("下划线");
     UnderlinetooBar->setCheckable (true);

     //颜色
     ColortooBar = new QToolButton;
     ColortooBar->setIcon (QIcon(":/color.png"));
     ColortooBar->setStatusTip("颜色");
     ColortooBar->setCheckable (true);

     //字体工具条
     FonttoolBar = addToolBar ("Font");
     FonttoolBar->addWidget (fontLabel);
     FonttoolBar->addWidget (fontComboBox);
     FonttoolBar->addWidget (fontLabel2);
     FonttoolBar->addWidget (sizeComboBox);
     FonttoolBar->addSeparator ();
     FonttoolBar->addWidget (BoldtooBar);
     FonttoolBar->addWidget (ItalictooBar);
     FonttoolBar->addWidget (UnderlinetooBar);
     FonttoolBar->addSeparator ();
     FonttoolBar->addWidget (ColortooBar);

     //连接槽函数
      connect (fontComboBox, SIGNAL(activated(QString)), this, SLOT(ShowFontComboBox(QString)));
      connect (sizeComboBox, SIGNAL(activated(QString)), this, SLOT(ShowSizeSpinBox(QString)));
      connect (BoldtooBar, SIGNAL(clicked(bool)), this, SLOT(ShowBoldtooBar()));
      connect (ItalictooBar, SIGNAL(clicked(bool)), this, SLOT(ShowItalictooBar()));
      connect (UnderlinetooBar, SIGNAL(clicked(bool)), this, SLOT(ShowUnderlinetooBar()));
      connect (ColortooBar, SIGNAL(clicked(bool)), this , SLOT(ShowColortooBar()));

      //设置字符格式--之前的字符的字体，字号,仅仅是下拉列表框的改变, 还需要调用此函数改变文本字体
      //当光标所在字符格式发生变化时调用此槽函数，函数根据 新的字符格式 将工具栏各个格式的显示更新
      connect (showWidget->text, SIGNAL(currentCharFormatChanged(QTextCharFormat)),this, SLOT(ShowCurrentFormatChanged(QTextCharFormat)));
      connect(showWidget->text,SIGNAL(cursorPositionChanged()),this,SLOT(do_cursorChanged()));

 }

//设置字体格式
//字体
void MainWindow::ShowFontComboBox (QString comboStr)
{
    QTextCharFormat fmt;            //创建一个QTextCharFormat对象
    fmt.setFontFamily (comboStr);   //选择的字体名称设置给QTextCharFormat对象
    mergeFormat (fmt);              //将新格式应用到光标选区内的字符
}
//光标选区
void MainWindow::mergeFormat (QTextCharFormat fmt)
{
    QTextCursor cursor = showWidget->text->textCursor ();   //获得编辑框中的光标
    //若光标没有高亮区，则光标所在处的词为选区(由前后有空格，“，”，“、”，“."等标点分隔
    if (!cursor.hasSelection ())
        cursor.select (QTextCursor::WordUnderCursor);
    //将format所表示的格式应用到光标所在处的字符上
    cursor.mergeCharFormat (fmt);
    //调用QTextEdit的mergeCurrentCharFormat()将格式应用到选区的所有字符上
    showWidget->text->mergeCurrentCharFormat (fmt);
}
//设置字号
void MainWindow::ShowSizeSpinBox (QString spinValue)
{
    QTextCharFormat fmt;
    //设置字号
    fmt.setFontPointSize (spinValue.toFloat ());
    //直接调用QTextEdit的
    showWidget->text->mergeCurrentCharFormat (fmt);
}

//设置文字显示加粗
void MainWindow::ShowBoldtooBar ()
{
    QTextCharFormat fmt;
    //设置是否加粗
    fmt.setFontWeight (BoldtooBar->isChecked () ? QFont::Bold : QFont::Normal);
    showWidget->text->mergeCurrentCharFormat (fmt);
}

//设置文字倾斜
void MainWindow::ShowItalictooBar ()
{
    QTextCharFormat fmt;
    //设置是否倾斜 (true or false)
    fmt.setFontItalic (ItalictooBar->isChecked() );
    showWidget->text->mergeCurrentCharFormat (fmt);
}

//是否下划线
void MainWindow::ShowUnderlinetooBar ()
{
    QTextCharFormat fmt;
    //设置是否有下划线
    fmt.setFontUnderline (UnderlinetooBar->isChecked ());
    showWidget->text->mergeCurrentCharFormat (fmt);
}

//是否字体颜色
void MainWindow::ShowColortooBar ()
{
    QColor color = QColorDialog::getColor (Qt::red, this);
    if (color.isValid ())              //查看颜色是否有效
    {
        QTextCharFormat fmt;
        fmt.setForeground (color);     //设置前景颜色
        showWidget->text->mergeCurrentCharFormat (fmt);
    }
}

//设置字符格式
void MainWindow::ShowCurrentFormatChanged (const QTextCharFormat &fmt)
{
    //findText()返回(fmt.fontFamily()位置的索引)根据该索引得到ComboBox里面的元素
    sizeComboBox->setCurrentIndex (sizeComboBox->findText (QString::number (fmt.fontPointSize ())));
    BoldtooBar->setChecked(fmt.font ().bold ());
    ItalictooBar->setChecked (fmt.fontItalic ());
    UnderlinetooBar->setChecked (fmt.fontUnderline ());
}
//在状态栏实时显示当前光标所在行列
void MainWindow::do_cursorChanged()
{
    QTextCursor cursor;
    cursor = showWidget->text->textCursor();
    lineNumber = cursor.blockNumber()+1;//光标所在行
    rowNumber = cursor.columnNumber();//光标所在列
    // 在SatusBar中实时显示
    ui->statusBar->showMessage(tr("%1行，%2列").arg(lineNumber).arg(rowNumber));
}
//和编辑框本身的热键冲突了。。
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
        case Qt::Key_End : showWidget->text->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);//移动光标到此行末尾
        case Qt::Key_Home : showWidget->text->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);//移动光标到行首
        case Qt::Key_Backspace : cl.Delete();//向右删除一个字符
        case Qt::Key_Delete: cl.Back();//向左删除一个字符
        case Qt::Key_Return: cl.InsertLine();//插入换行符
    }
   if((e->key()>= int (Qt::Key_A))&&(e->key()<= int (Qt::Key_Z)))
        cl.Insert(e->key()-int (Qt::Key_A)+int('a'));
    if((e->key()>= int (Qt::Key_0))&&(e->key()<= int (Qt::Key_9)))
        cl.Insert(e->key()-int (Qt::Key_0)+int('0'));

    if((e->key()>= int (Qt::Key_A))&&(e->key()<= int (Qt::Key_Z)))
         cl.Insert(e->key()-int (Qt::Key_A)+int('a'));
     if((e->key()>= int (Qt::Key_0))&&(e->key()<= int (Qt::Key_9)))
         cl.Insert(e->key()-int (Qt::Key_0)+int('0'));
     if((e->key()>= int (Qt::Key_A))&&(e->key()<= int (Qt::Key_Z)))
          cl.Insert(e->key()-int (Qt::Key_A)+int('a'));
      if((e->key()>= int (Qt::Key_0))&&(e->key()<= int (Qt::Key_9)))
          cl.Insert(e->key()-int (Qt::Key_0)+int('0'));

    if (e->modifiers() ==Qt::ShiftModifier && (e->key()>= int (Qt::Key_A))&&(e->key()<= int (Qt::Key_Z)))
        cl.Insert(e->key()-int (Qt::Key_A)+int('A'));
    if(e->key()==Qt::Key_CapsLock)
    {
        if((e->key()>= int (Qt::Key_A))&&(e->key()<= int (Qt::Key_Z)))
             cl.Insert(e->key()-int (Qt::Key_A)+int('A'));
    }

}


/*void MainWindow::curselect()
{
    QTextCursor cur = showWidget->text->textCursor();//返回当前光标对象
    cur.setPosition(2, QTextCursor::MoveAnchor);//移到起始位置
    cur.movePosition(QTextCursor::NoMove, QTextCursor::KeepAnchor, 3);//移动结束位置
    cur.select(QTextCursor::WordUnderCursor);//选择
    showWidget->text->setTextCursor(cur);
}*/

//退出系统 确认退出对话框
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(flag==0)
    {
        QMessageBox::StandardButton button;
        button=QMessageBox::question(this,tr("退出程序"),QString(tr("文件未保存，确认退出？")),QMessageBox::Yes|QMessageBox::No);
        if(button==QMessageBox::No)
        {
            event->ignore(); // 忽略退出信号，程序继续进行
        }
        else if(button==QMessageBox::Yes)
        {
            event->accept(); // 接受退出信号，程序退出
        }
    }
}
//未保存就退出
void MainWindow::ShowQuit()
{
    if(flag==1) exit(0);
    else close();
}
MainWindow::~MainWindow()
{
    delete ui;
}
