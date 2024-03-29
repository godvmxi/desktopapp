#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QWidget>
#include <QPalette>
#include <QRect>
#include <QString>
#include "filetype.h"
#include <QDebug>
#include <QPushButton>
#include "iconpushbutton.h"
#include <QMessageBox>

typedef struct{
    QList<APP *> running;
    QList<APP *>top;
    QList<APP *>bottom;
    QStack<APP *>stack;
}SCREEN;

namespace Ui {
    class AppManager;
}

class AppManager : public QWidget
{
    Q_OBJECT

public:
    explicit AppManager(QWidget *parent,QList<APP> apps);

    ~AppManager();
    bool setAppList(QList<APP> apps,int size);
    bool placeAppIcons(void);
    QList<APP_COM> getAppLists(void);
   //APP_COM execObCmd();

public slots:
    //bool update_app(APP_COM app);
    //bool update_apps_list(QList<APP_COM> apps);
    bool iconClick(void *ptr);
    bool appProcessChanged(QProcess::ProcessState newState);
signals:
    //execObCmd(APP_COM app);

    //Appxxx xxx = ObCall::call(app)

private:
    Ui::AppManager *ui;
    SCREEN main;
    SCREEN extend;
    QList<APP *> apps;

    QWidget *home;

    bool setSelfLayer(void);
    bool showRunningApp(APP *app);
    bool startAppFromButton(APP *app);
};

#endif // APPMANAGER_H
