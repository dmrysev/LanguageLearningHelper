#ifndef TEMPTAB_H
#define TEMPTAB_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>

class TempTab: public QWidget
{
    Q_OBJECT
public:
    TempTab(QWidget *parent = 0);

private:
    //  This
    ~TempTab();
    void configureThis();

    //  Table
    QTableWidget *table;
    QString oldEntry;
    bool isHiddenA;
    void createTable();
    void fillTable();

    //  Buttons
    QPushButton *nextButton;
    QPushButton *hideButton;
    QPushButton *shuffleButton;
    QPushButton *clearButton;
    void createButtons();

    //  Text fields
    QLineEdit *stepField;
    void createTextFields();

    //  Layout
    void createLayout();

private slots:
    void next();
    void hide();
    void shuffle();
    void clear();
    void repeated(QTableWidgetItem *item);

signals:
    void itemDClicked(QTableWidgetItem *item);
};

#endif // TEMPTAB_H
