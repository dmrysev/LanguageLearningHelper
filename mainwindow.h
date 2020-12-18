#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTabWidget>

#include "allentriestab.h"
#include "repeattab.h"
#include "temptab.h"

class MainWindow: public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

private:
    // This
    ~MainWindow();
    void configureThis();

    //  Tabs
    QTabWidget *tabWidget;
    AllEntriesTab *all;
    RepeatTab *rep;
    TempTab *temp;
    void createTabs();

    //  Layout
    void createLayout();

    // Windows
    void createWindows();

private slots:
    void openAllTab();

};

#endif // MAINWINDOW_H
