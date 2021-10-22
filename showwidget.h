#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class showWidget : public QWidget
{
    Q_OBJECT
public:
    explicit showWidget(QWidget *parent = 0);
    ~showWidget();

signals:

public slots:
};

#endif // SHOWWIDGET_H
