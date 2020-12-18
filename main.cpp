#include <QApplication>

//#include "addwindow.h"
#include "argumentshandler.h"
//#include "dict.h"
//#include "config.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    ArgumentsHandler::args = app.arguments();

    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();

    return app.exec();
}
