#ifndef ARGUMENTSHANDLER_H
#define ARGUMENTSHANDLER_H

#include <QStringList>

class ArgumentsHandler
{
public:  
    static ArgumentsHandler* instance();
    void setArguments(const QStringList &args);
    QString getValue(const QString &par);
private:
    ArgumentsHandler();
    static ArgumentsHandler* m_pInstance;
    QStringList arguments;
};

#endif // ARGUMENTSHANDLER_H
