#include "appmanager.h"
#include "ui_appmanager.h"

AppManager::AppManager(QWidget *parent,QList<APP> apps) :
    QWidget(parent),
    ui(new Ui::AppManager)
{



    QPalette palette;
    palette.setBrush(QPalette::Background,QColor(Qt::lightGray));
    this->setPalette(palette);
    this->setAutoFillBackground(true);
    this->setFixedSize(1000,1000);
    ui->setupUi(this);

    setAppList(apps,apps.size());
    placeAppIcons();
    setSelfLayer();


}

AppManager::~AppManager()
{
    delete ui;
}
bool AppManager::placeAppIcons(void){
    APP *app;
    int i = 1;
    IconPushButton *button;


    qDebug()<<"apps size -> "<<this->apps.size();

    foreach(app,apps){
        app->max_run = i;
        button = new IconPushButton(this,app);
        connect(button,SIGNAL(buttonClick(void*)),this,SLOT(iconClick(void*)));

        button->setGeometry(120*i++,50,100,100);


    }
    foreach(app,apps){
        qDebug()<<"max_run"<<app->max_run <<"  cmd->"<<app->cmd;
    }

    return true;

}
bool AppManager::setAppList(QList<APP> apps ,int size)
{
    APP *tmp = NULL;
    if(size <= 0)
            return false;
    for(int i = 0;i<size;i++){
        tmp = new APP;
        *tmp = apps.at(i);

        tmp->max_run = 1;
        tmp->run_1.process = NULL;
        tmp->run_2.process = NULL;
        memset(&(tmp->run_1.info),0,sizeof(APP_COM));
        memset(&(tmp->run_2.info),0,sizeof(APP_COM));
        this->apps.append(tmp);
    }
    return true;
}
bool AppManager::iconClick(void *ptr)
{
    QString msg ;
    APP *appButton = (APP *)ptr;
    APP *app;
    msg.sprintf("from button ->%d",appButton->max_run);
    ui->label_status->setText(msg);

    if(appButton->run_1.process != NULL)
    {
        return false;
    }
    else
    {
        appButton->run_1.process = new QProcess();
        appButton->run_1.process->setProcessChannelMode(QProcess::MergedChannels);


        connect(appButton->run_1.process,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(appProcessChanged(QProcess::ProcessState)));
        appButton->run_1.process->start(appButton->cmd);
        qDebug()<<"create pid ->"<<appButton->run_1.process->pid();
        return true;
    }

}
bool AppManager::setSelfLayer(void)
{


}
bool AppManager::appProcessChanged(QProcess::ProcessState newState)
{
    QProcess *src = dynamic_cast<QProcess*>(sender());
    qDebug()<<"process new state"<<newState<<" src->"<<src->pid();
    switch(newState){
    case QProcess::NotRunning:
        src->kill();
        src->terminate();
        //qDebug()<<"fuck";
        qDebug()<<"process kill state"<<newState<<" src->"<<src->pid();
        //delete src;


        //delete ;
        break;
    case QProcess::Running:
        break;
    case QProcess::Starting:
        break;
    default :
        break;
    }

    return true;
}
