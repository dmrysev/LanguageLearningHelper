#ifndef ALLENTRIESTAB_H
#define ALLENTRIESTAB_H

#include <QWidget>
#include <QTableWidget>

class AllEntriesTab: public QWidget
{
    Q_OBJECT
public:
    AllEntriesTab(QWidget *parent = 0);

private:
    //  This
    ~AllEntriesTab();
    void configureThis();

    // Layout
    void createLayout();

    //  Table
    QTableWidget *table;
    QString before;
    void createTable();

public slots:
    void selectCell(QTableWidgetItem *item);

private slots:
    void fillTable();
    void saveOldEntry(QTableWidgetItem *item);
    void editEntry(QTableWidgetItem *item);
};

#endif // ALLENTRIESTAB_H
