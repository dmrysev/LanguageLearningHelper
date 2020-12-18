#include "temptab.h"

#include <QVBoxLayout>

#include "dict.h"
#include "config.h"

TempTab::TempTab(QWidget *parent): QWidget(parent){
    configureThis();
    createTable();
    createButtons();
    createTextFields();
    createLayout();
    fillTable();
}
void TempTab::createTable(){
    table = new QTableWidget(this);
    QStringList labels;
    labels << "A" << "B";

    table->setColumnCount(2);
    table->setHorizontalHeaderLabels(labels);
    table->setMouseTracking(true);
    table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    table->setWordWrap(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnWidth(0, Config::instance()->getVal("TempTab/AW").toInt());
    table->setColumnWidth(1, Config::instance()->getVal("TempTab/BW").toInt());

    isHiddenA = false;
}
void TempTab::fillTable(){
    disconnect(table, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
            this, SIGNAL(itemDClicked(QTableWidgetItem*)));
    disconnect(table, SIGNAL(itemClicked(QTableWidgetItem*)),
            this, SLOT(repeated(QTableWidgetItem*)));

    QStringList A = Dict::instance()->getTempA();
    QStringList B = Dict::instance()->getTempB();

    int size = A.size();
    table->setRowCount(size);

    for(int i = 0; i < size; i++){
        table->setItem(i, 0, new QTableWidgetItem);
        table->item(i, 0)->setText(A.at(i));
        table->setItem(i, 1, new QTableWidgetItem);
        table->item(i, 1)->setText(B.at(i));
        if(isHiddenA)
            table->item(i, 0)->setTextColor(Qt::white);
        else
            table->item(i, 1)->setTextColor(Qt::white);
    }

    table->resizeRowsToContents();
    table->scrollToBottom();

    connect(table, SIGNAL(itemClicked(QTableWidgetItem*)),
            this, SLOT(repeated(QTableWidgetItem*)));
    connect(table, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
            this, SIGNAL(itemDClicked(QTableWidgetItem*)));
}
void TempTab::createLayout(){
    QHBoxLayout *upperLayout = new QHBoxLayout;
    upperLayout->addWidget(stepField, 0, Qt::AlignRight);
    upperLayout->addWidget(nextButton);
    upperLayout->addWidget(hideButton);
    upperLayout->addWidget(shuffleButton);
    upperLayout->addWidget(clearButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(upperLayout);
    mainLayout->addWidget(table);

    setLayout(mainLayout);
}
void TempTab::createTextFields(){
    stepField = new QLineEdit;
    stepField->setValidator(new QIntValidator());
    stepField->setFixedWidth(50);
    stepField->setText("5");
}

void TempTab::createButtons(){

    nextButton = new QPushButton("Next");
    nextButton->setFixedHeight(35);
    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));

    hideButton = new QPushButton("Toggle hide\n and shuffle");
    hideButton->setFixedHeight(35);
    connect(hideButton, SIGNAL(clicked()), this, SLOT(hide()));

    shuffleButton = new QPushButton("Shuffle");
    shuffleButton->setFixedHeight(35);
    connect(shuffleButton, SIGNAL(clicked()), this, SLOT(shuffle()));

    clearButton = new QPushButton("Clear");
    clearButton->setFixedHeight(35);
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));

}
void TempTab::next(){
    isHiddenA = false;
    Dict::instance()->next(stepField->text().toInt());
    fillTable();
}
void TempTab::hide(){
    isHiddenA = !isHiddenA;
    Dict::instance()->shuffleTemp();
    fillTable();
}
void TempTab::shuffle(){
    Dict::instance()->shuffleTemp();
    fillTable();
}
void TempTab::clear(){
    Dict::instance()->clearTemp();
    fillTable();
}
TempTab::~TempTab(){
    Config::instance()->setVal("TempTab/AW", table->columnWidth(0));
    Config::instance()->setVal("TempTab/BW", table->columnWidth(1));
}
void TempTab::repeated(QTableWidgetItem *item){
    Dict::instance()->repeated(item->text());
}
void TempTab::configureThis(){
    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(Dict::instance(), SIGNAL(changed()), this, SLOT(clear()));
}
