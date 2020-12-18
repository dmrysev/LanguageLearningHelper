#include "allentriestab.h"

#include <QVBoxLayout>

#include "dict.h"
#include "config.h"

AllEntriesTab::AllEntriesTab(QWidget *parent): QWidget(parent){

    configureThis();
    createTable();
    createLayout();
    fillTable();
}
void AllEntriesTab::createTable(){
    table = new QTableWidget(this);
    table->setColumnCount(2);
    QStringList labels;
    labels << "A" << "B";
    table->setHorizontalHeaderLabels(labels);
    table->setMouseTracking(true);
    table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    table->setWordWrap(true);
    table->setColumnWidth(0, Config::instance()->getVal("AllTab/AW").toInt());
    table->setColumnWidth(1, Config::instance()->getVal("AllTab/BW").toInt());
}
void AllEntriesTab::fillTable(){
    disconnect(table, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(saveOldEntry(QTableWidgetItem*)));
    disconnect(table, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(editEntry(QTableWidgetItem*)));
    QStringList A = Dict::instance()->getAllA();
    QStringList B = Dict::instance()->getAllB();
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
    connect(table, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(saveOldEntry(QTableWidgetItem*)));
    connect(table, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(editEntry(QTableWidgetItem*)));
}
AllEntriesTab::~AllEntriesTab(){
    Config::instance()->setVal("AllTab/AW", table->columnWidth(0));
    Config::instance()->setVal("AllTab/BW", table->columnWidth(1));
}
void AllEntriesTab::saveOldEntry(QTableWidgetItem *item){
    before = item->text();
}
void AllEntriesTab::editEntry(QTableWidgetItem *item){
    QString after = item->text();
    Dict::instance()->replace(before, after);
}
void AllEntriesTab::selectCell(QTableWidgetItem *item){
    QString cellText = item->text();
    for(int i = 0; i < table->rowCount(); i++){
        QString curCellText = table->item(i, 0)->text();
        if(cellText == curCellText){
            saveOldEntry(table->item(i, 0));
            table->editItem(table->item(i, 0));
            break;
        }

        curCellText = table->item(i, 1)->text();
        if(cellText == curCellText){
            saveOldEntry(table->item(i, 1));
            table->editItem(table->item(i, 1));
            break;
        }
    }
}
void AllEntriesTab::configureThis(){

    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(Dict::instance(), SIGNAL(changed()), this, SLOT(fillTable()));
}
void AllEntriesTab::createLayout(){

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(table);

    setLayout(mainLayout);
}
