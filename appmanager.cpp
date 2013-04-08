#include "appmanager.h"
#include "ui_appmanager.h"

AppManager::AppManager(QWidget *parent,QList<APP> apps) :
    QWidget(parent),
    ui(new Ui::AppManager)
{



    QPalette palette;
    palette.setBrush(QPalette::Background,QColor(Qt::yellow));
    this->setPalette(palette);
    this->setAutoFillBackground(true);
    this->setFixedSize(1000,1000);
    ui->setupUi(this);

    setAppList(apps,apps.size());
    placeAppIcons();


}

AppManager::~AppManager()
{
    delete ui;
}
bool AppManager::placeAppIcons(void){
    APP *app;
    int i = 1;
    QPushButton *button;


    qDebug()<<"apps size -> "<<this->apps.size();

    foreach(app,apps){
        app->max_run = 1;
        button = new QPushButton(this);
        //ui->gridLayout->addWidget(button);
        //button->setFixedSize(60,60);
       // button-
        button->setGeometry(100*i++,50,60,60);


    }
    foreach(app,apps){
        qDebug()<<"max_run"<<app->max_run <<"  cmd->"<<app->cmd;
    }



}
bool AppManager::setAppList(QList<APP> apps ,int size)
{
    APP *tmp = NULL;
    for(int i = 0;i<size;i++){
        tmp = new APP;
        *tmp = apps.at(i);
        this->apps.append(tmp);
    }
}
