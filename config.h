#ifndef CONFIG_H
#define CONFIG_H

#include <QMap>
#include <QTextStream>
#include <QFile>
#include <QString>

class Config
{
public:
    static Config* instance();
    void openFile(const QString &fileName);
    void addPar(const QString &par, const QString &val="");
    void setVal(const QString &par, const QString &val);
    void setVal(const QString &par, const int &val);
    QString getVal(const QString &par);
    void save();
private:
    Config();
    QMap<QString, QString> hash;
    QFile file;
    static Config* m_pInstance;

};

#endif // CONFIG_H
