#include "addwindow.h"

#include <QApplication>
#include <QClipboard>

#include "config.h"
#include "dict.h"

AddWindow::AddWindow(QWidget *parent): QWidget(parent){

    configureThis();
    createButtons();
    createTextFields();
    createChechBoxes();
    createLayout();
    loadCfg();
}
AddWindow::~AddWindow(){
    saveCfg();
}
void AddWindow::createLayout(){
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(onTop, 0, 0);
    mainLayout->addWidget(addButton, 0, 1);
    mainLayout->addWidget(pasteAButton, 1, 0);
    mainLayout->addWidget(pasteBButton, 2, 0);
    mainLayout->addWidget(fieldA, 1, 1);
    mainLayout->addWidget(fieldB, 2, 1);

    this->setLayout(mainLayout);
}
void AddWindow::loadCfg(){
    this->setGeometry(Config::instance()->getVal("AddWindowX").toInt() + 8,
                      Config::instance()->getVal("AddWindowY").toInt() + 30,
                      Config::instance()->getVal("AddWindowW").toInt(),
                      Config::instance()->getVal("AddWindowH").toInt());
}
void AddWindow::createButtons(){
    addButton = new QPushButton("Add");
    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    pasteAButton = new QPushButton(">>");
    connect(pasteAButton, SIGNAL(clicked()), this, SLOT(pasteA()));
    pasteBButton = new QPushButton(">>");
    connect(pasteBButton, SIGNAL(clicked()), this, SLOT(pasteB()));
}
void AddWindow::createTextFields(){
    fieldA = new QLineEdit;
    fieldB = new QLineEdit;
    connect(fieldA, SIGNAL(returnPressed()), this, SLOT(add()));
    connect(fieldB, SIGNAL(returnPressed()), this, SLOT(add()));
}
void AddWindow::add(){
    Dict::instance()->add(fieldA->text(), fieldB->text());
    fieldA->clear();
    fieldB->clear();
}
void AddWindow::saveCfg(){
    Config::instance()->setVal("AddWindowX", this->x());
    Config::instance()->setVal("AddWindowY", this->y());
    Config::instance()->setVal("AddWindowW", this->width());
    Config::instance()->setVal("AddWindowH", this->height());
    Config::instance()->save();
}
void AddWindow::pasteA(){
    QString text = QApplication::clipboard()->text();
    fieldA->setText(text);
}
void AddWindow::pasteB(){
    QString text = QApplication::clipboard()->text();
    fieldB->setText(text);
}
void AddWindow::createChechBoxes(){
    onTop = new QCheckBox("On top");
    connect(onTop, SIGNAL(stateChanged(int)), this, SLOT(toggleOnTop(int)));
}
void AddWindow::toggleOnTop(int i){
    if(i == 0)
        this->setWindowFlags(!Qt::WindowStaysOnTopHint);
    else if(i == 2)
        this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->show();
}
void AddWindow::configureThis(){
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("TabDict: add new entry");
}
