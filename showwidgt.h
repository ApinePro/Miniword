#ifndef SHOWWIDGT_H
#define SHOWWIDGT_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>      //文本编辑框

class ShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWidget(QWidget *parent = 0);

    QTextEdit *text;

signals:

public slots:
};

#endif // SHOWWIDGT_H
