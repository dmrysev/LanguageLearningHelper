#ifndef REPEATTAB_H
#define REPEATTAB_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>

class RepeatTab: public QWidget
{
    Q_OBJECT
public:
    RepeatTab(QWidget *parent = 0);

private:
    //  This
    ~RepeatTab();
    void configureThis();

    //  Table
    QTableWidget *table;
    void createTable();

    //  Button
    QPushButton *shuffleButton;
    void createButtons();

    //  Layout
    void createLayout();

private slots:
    void fillTable();
    void shuffle();

signals:
    void itemDClicked(QTableWidgetItem *item);
};

#endif // REPEATTAB_H
