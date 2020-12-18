#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QCheckBox>

class AddWindow: public QWidget
{
    Q_OBJECT
public:
    AddWindow(QWidget *parent = 0);
private:
    //  This
    ~AddWindow();
    void configureThis();

    //  Buttons
    QPushButton *addButton;
    QPushButton *pasteAButton;
    QPushButton *pasteBButton;
    void createButtons();

    //  Chech box
    QCheckBox *onTop;
    void createChechBoxes();

    //  Layout
    void createLayout();

    //  Text fields
    QLineEdit *fieldA, *fieldB;
    void createTextFields();

    //  Config
    void loadCfg();
    void saveCfg();

private slots:
    void add();
    void pasteA();
    void pasteB();
    void toggleOnTop(int i);
};

#endif // ADDWINDOW_H
