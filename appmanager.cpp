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
        tmp->run_main.process = new QProcess();
        //tmp->run_extend.process = new QProcess();
        //tmp->run_extend.process->setProcessChannelMode(QProcess::MergedChannels);
        tmp->run_main.process->setProcessChannelMode(QProcess::MergedChannels);
        //connect(tmp->run_extend.process,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(appProcessChanged(QProcess::ProcessState)));
        connect(tmp->run_main.process,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(appProcessChanged(QProcess::ProcessState)));
        memset(&(tmp->run_main.info),0,sizeof(APP_COM));
        memset(&(tmp->run_extend.info),0,sizeof(APP_COM));
        this->apps.append(tmp);
    }
    return true;
}
bool AppManager::iconClick(void *ptr)
{
    QString msg ;
    APP *app = (APP *)ptr;
    msg.sprintf("from button ->%d",app->max_run);
    ui->label_status->setText(msg);


    QProcess::ProcessState now =  app->run_main.process->state();
    switch(now)
    {
    case QProcess::Starting :
        qDebug()<<"just wait ....";
        break;
    case QProcess::Running :
        showRunningApp(app);
        break;
    case QProcess::NotRunning:
        startAppFromButton(app);
        break;

    }
}
bool AppManager::setSelfLayer(void)
{


}
bool AppManager::appProcessChanged(QProcess::ProcessState newState)
{
    QProcess *src = dynamic_cast<QProcess*>(sender());
    APP *app;
    qDebug()<<"process new state"<<newState<<" src->"<<src->pid();
    switch(newState){
    case QProcess::NotRunning:
        //src->kill();
        //src->terminate();
        //qDebug()<<"fuck";
        qDebug()<<"process kill state"<<newState<<" src->"<<src->pid();
        foreach(app,this->apps)
        {
            //if(app->run_main.process == src)
            //{
                //delete app->run_main.process;
                //app->run_main.process = NULL;
                //disconnect(src,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(appProcessChanged(QProcess::ProcessState)));
                //delete src;
                //qDebug()<<"delete process";
                return true;
            //}
        }

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
bool AppManager::showRunningApp(APP *app)
{

}

bool AppManager::startAppFromButton(APP *app)
{
    app->run_main.process->start(app->cmd);
    qDebug()<<"create pid ->"<<app->run_main.process->pid();
    app->run_main.info.pid = app->run_main.process->pid();
    return true;
}
bool AppManager::setHomeButton(void)
{


}
