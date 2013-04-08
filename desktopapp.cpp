#include "desktopapp.h"
#include "ui_desktopapp.h"

DesktopApp::DesktopApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DesktopApp)
{

    QList<APP> apps;
    APP app;
    app.cmd = QString(tr("winid"));
    for(int i = 0;i<5;i++)
    {
        apps.append(app);
    }

    //appManager->show();
    //ui->formLayout->addWidget(appManager);
    //this->setLayout(ui->formLayout);



    ui->setupUi(this);
    AppManager *appManager = new AppManager(this,apps);
    appManager->setGeometry(500,500,1000,300);


}

DesktopApp::~DesktopApp()
{
    delete ui;
}
