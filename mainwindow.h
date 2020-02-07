#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "showwidgt.h"
#include <QMessageBox>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QTextEdit>      //文本编辑框
#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QCheckBox>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QTextCursor>
#include <QRadioButton>
#include <QFontComboBox>

using namespace std;
//数据结构部分
typedef struct chunk
{
    char data[100];
    chunk *pre,*next;
    int Total;//Total是当前Chunk有的字符数
} Chunk,*CPtr;

typedef struct
{
    int line;
    int num;
} Position; //position代表目前在第line行，光标以左有num个字符

//类部分

class ChunkList
{
private:

public:
    CPtr *heads;
    int LineNum;
    Position pos,pos2;//pos2只有块操作才用得上，不然为pos2.line=0,pos2.num=0;
    char *current;//待处理字符位置或者NULL，函数调用之前用方法更新
    CPtr currentchunk;


     ChunkList();
    void Delete();//还没写
    void Back();//向左回退
    void Insert(char);
    void InsertLine();

    void Merge(CPtr &,int);//合并所指的和下一个（若合并失败，则指针...)
    void MergeLine(int);//合并整行，其中调用了Merge函数

    void Locate();
    void AddLine();//加一行，并挂一个初始化的chunk
    void AddChunk(int);//在某一行挂一个chunk在结尾，并初始化它

    void LineTotal(int,int &);//可以知道一行里有多少个有效字符

    void OutputLine(int);//读出一行到屏幕

    //查找需要的某些函数
    void CopyLine(int,char *&);

    void ReadFile(QString filename);

    void LineString(int line, char *&cpline);
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ChunkList cl;
    explicit MainWindow(QWidget *parent = 0);
    void loadFile(QString  filename);          //加载文件
    void mergeFormat(QTextCharFormat);         //合并格式
    ~MainWindow();
    void keyPressEvent(QKeyEvent *);

    int flag=0;//是否保存
//光标位置，行数和列数
    int lineNumber;
    int rowNumber;
 //   void curselect();
private:
    Ui::MainWindow *ui;
    ShowWidget *showWidget;
    QLabel* first_statusLabel;
    QAction* OpenAction;
    QAction* NewAction;
    QAction* SaveAction;
    QAction* CutAction;
    QAction* CopyAction;
    QAction* PasteAction;
    QAction* QuitAction;
    QAction* FindAction;
    QAction* ReplaceAction;
//工具栏
    QToolBar* OpentoolBar;
    QToolBar* NewtoolBar;
    QToolBar* SavetoolBar;
    QToolBar* CuttoolBar;
    QToolBar* CopytoolBar;
    QToolBar* PastetoolBar;
    QToolBar* QuittoolBar;
    QToolBar* FindtoolBar;
    QToolBar* ReplacetoolBar;
//菜单栏
    QMenu* File;
    QMenu* Edit;
    QMenu* Find;
    //文本编辑
    QLabel *fontLabel;                          //字体设置项
    QFontComboBox *fontComboBox;                //字体选框
    QLabel *fontLabel2;                         //大小
    QComboBox *sizeComboBox;                    //大小选框
    QToolButton *BoldtooBar;                       //加粗按钮
    QToolButton *ItalictooBar;                     //斜体
    QToolButton *UnderlinetooBar;                  //下划线
    QToolButton *ColortooBar;                      //字体颜色
    QToolBar *FonttoolBar;                      //字体工具栏
    QString fileName;                          //打开文件名
    QString curFileName;                       //保存文件名
    //查找对话框
    QString str;
    QLabel *lineLabel;
    QLineEdit *lineEdit;
    QPushButton *findNextBtn;
    QPushButton *cancelBtn;
    QLabel *directLabel;
    QRadioButton *upBtn;
    QRadioButton *downBtn;
    QCheckBox *lowOrUpperBox;
    //替换对话框
    QString str2;
    QString str3;
    QLabel *lineLabel21;           //查找
    QLineEdit *lineEdit21;          //查找内容
    QLabel *lineLabel22;           //替换
    QLineEdit *lineEdit22;          //替换内容
    QPushButton *findNextBtn2;     //查找下一个
    QPushButton *subBtn2;          //替换按钮
    QPushButton *cancelBtn2;
    QLabel *directLabel2;
    QCheckBox *lowOrUpperBox2;
    bool findjudge;
protected slots:
    void ShowFindDialog();                      //查找对话框
    void ShowFindText();                        //查找
    void ShowFindStr();

    void ShowReplaceDialog();                       //替换对话框
    void ShowSubstitute();                      //替换
    void ShowSubText();
    void ShowSubText2();
    void ShowFindStr2 ();
    void ShowCut();
    void ShowCopy();
    void ShowPaste();
    void ShowSaveFile();
    void do_cursorChanged(); //获取光标位置信息
    void closeEvent(QCloseEvent *event);
    void ShowQuit();
    void ShowNewFile();                         //新建文件
    void ShowOpenFile();                        //打开文件
    void ShowFontComboBox(QString comboStr);    //显示字体框
    void ShowSizeSpinBox(QString spinValue);    //大小自旋盒
    void ShowBoldtooBar();                         //加粗功能
    void ShowItalictooBar();                       //显示斜体
    void ShowUnderlinetooBar();                    //下划线
    void ShowColortooBar();
    void ShowCurrentFormatChanged(const QTextCharFormat &fmt);//设置字符格式
};


#endif // MAINWINDOW_H
