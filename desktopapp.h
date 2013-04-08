#ifndef DESKTOPAPP_H
#define DESKTOPAPP_H

#include <QMainWindow>
#include "appmanager.h"
#include <QLineEdit>

namespace Ui {
    class DesktopApp;
}

class DesktopApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit DesktopApp(QWidget *parent = 0);
    ~DesktopApp();

private:
    Ui::DesktopApp *ui;
};

#endif // DESKTOPAPP_H
