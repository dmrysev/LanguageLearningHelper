#include "mainwindow.h"

#include <QVBoxLayout>
#include <QCoreApplication>

#include "addwindow.h"
#include "dict.h"
#include "config.h"
#include "argumentshandler.h"

MainWindow::MainWindow(QWidget *parent): QWidget(parent){ 
    configureThis();
    createTabs();
    createLayout();
    createWindows();
}
MainWindow::~MainWindow(){
    Config::instance()->setVal("MWinX", this->x());
    Config::instance()->setVal("MWinY", this->y());
    Config::instance()->setVal("MWinW", this->width());
    Config::instance()->setVal("MWinH", this->height());

    Dict::instance()->save();
    Config::instance()->save();
}
void MainWindow::openAllTab(){
    tabWidget->setCurrentWidget(all);
}
void MainWindow::createTabs(){
    all = new AllEntriesTab;
    rep = new RepeatTab;
    temp = new TempTab;

    tabWidget = new QTabWidget;
    tabWidget->addTab(all, tr("All entries"));
    tabWidget->addTab(rep, tr("Repeat"));
    tabWidget->addTab(temp, tr("Temp"));

    connect(rep, SIGNAL(itemDClicked(QTableWidgetItem*)), this, SLOT(openAllTab()));
    connect(rep, SIGNAL(itemDClicked(QTableWidgetItem*)), all, SLOT(selectCell(QTableWidgetItem*)));

    connect(temp, SIGNAL(itemDClicked(QTableWidgetItem*)), this, SLOT(openAllTab()));
    connect(temp, SIGNAL(itemDClicked(QTableWidgetItem*)), all, SLOT(selectCell(QTableWidgetItem*)));
}
void MainWindow::createLayout(){
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}
void MainWindow::configureThis(){
    ArgumentsHandler::instance()->setArguments(QCoreApplication::arguments());
//    Dict::instance()->openDict(ArgumentsHandler::instance()->getValue("--dict"));
    Dict::instance()->openDict(QCoreApplication::arguments().last());
    Config::instance()->openFile(QCoreApplication::applicationDirPath().append("/tdict.cfg"));

    this->setGeometry(Config::instance()->getVal("MWinX").toInt() + 8,
                      Config::instance()->getVal("MWinY").toInt() + 30,
                      Config::instance()->getVal("MWinW").toInt(),
                      Config::instance()->getVal("MWinH").toInt());
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle(tr("TabDict"));
}
void MainWindow::createWindows(){
    AddWindow *addWindow = new AddWindow;
    addWindow->show();
    connect(this, SIGNAL(destroyed()), addWindow, SLOT(close()));
}
