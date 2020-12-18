#include "repeattab.h"

#include <QVBoxLayout>

#include "dict.h"
#include "config.h"

RepeatTab::RepeatTab(QWidget *parent): QWidget(parent){
    configureThis();
    createTable();
    createButtons();
    createLayout();
    fillTable();
}
void RepeatTab::configureThis(){
    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(Dict::instance(), SIGNAL(changed()), this, SLOT(fillTable()));
}
void RepeatTab::createTable(){
    table = new QTableWidget(this);
    QStringList labels;
    labels << "A" << "B";

    table->setColumnCount(2);
    table->setHorizontalHeaderLabels(labels);
    table->setMouseTracking(true);
    table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    table->setWordWrap(true);
    table->setColumnWidth(0, Config::instance()->getVal("RepTab/AW").toInt());
    table->setColumnWidth(1, Config::instance()->getVal("RepTab/BW").toInt());
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void RepeatTab::fillTable(){
    disconnect(table, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
            this, SIGNAL(itemDClicked(QTableWidgetItem*)));
    QStringList A = Dict::instance()->getRepeatA();
    QStringList B = Dict::instance()->getRepeatB();
    int size = A.size();
    table->setRowCount(size);
    for(int i = 0; i < size; i++){
        table->setItem(i, 0, new QTableWidgetItem);
        table->item(i, 0)->setText(A.at(i));
        table->setItem(i, 1, new QTableWidgetItem);
        table->item(i, 1)->setText(B.at(i));
    }
    table->resizeRowsToContents();
    table->scrollToBottom();
    connect(table, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
            this, SIGNAL(itemDClicked(QTableWidgetItem*)));
}
void RepeatTab::createButtons(){
    shuffleButton = new QPushButton("Shuffle");
    shuffleButton->setFixedWidth(100);
    connect(shuffleButton, SIGNAL(clicked()), this, SLOT(shuffle()));
}
void RepeatTab::createLayout(){
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(shuffleButton);
    mainLayout->addWidget(table);

    setLayout(mainLayout);
}
void RepeatTab::shuffle(){
    Dict::instance()->shuffleRepeat();
    fillTable();
}
RepeatTab::~RepeatTab(){
    Config::instance()->setVal("RepTab/AW", table->columnWidth(0));
    Config::instance()->setVal("RepTab/BW", table->columnWidth(1));
}
//void RepeatTab::itemDoubleClicked(QTableWidgetItem *item){
//    emit cellDoubleClicked(item->text());
//}
