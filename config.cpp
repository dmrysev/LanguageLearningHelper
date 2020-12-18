#include "config.h"

#include <QStringList>

Config::Config(){
}
void Config::addPar(const QString &par, const QString &val){
    hash.insert(par, val);
}
void Config::setVal(const QString &par, const QString &val){
    hash.insert(par, val);
}
void Config::setVal(const QString &par, const int &val){
    QString str;
    QTextStream(&str) << val;
    hash.insert(par, str);
}
QString Config::getVal(const QString &par){
    return hash.value(par);
}
void Config::save(){
    file.open(QFile::WriteOnly);
    QTextStream stream(&file);
    stream.seek(0);
    QStringList parList, valList;
    parList = hash.keys();
    valList = hash.values();
    for(int i = 0; i < hash.size(); i++){
        stream << parList.at(i) << '=' << valList.at(i) << '\n';
    }
    file.close();
}
void Config::openFile(const QString &fileName){
    file.setFileName(fileName);
    //    QFile file(cfgFile);
    file.open(QFile::ReadOnly);
    QTextStream txtStrm(&file);
    QStringList list = txtStrm.readAll().split("\n");
    //    strLst.removeLast();
    list.removeAll("");
    for(int i = 0; i < list.size(); i++){
        hash.insert(list.at(i).split("=").at(0), list.at(i).split("=").at(1));
    }
    file.close();
}
Config* Config::m_pInstance = NULL;
Config* Config::instance(){
    if (!m_pInstance)
        m_pInstance = new Config;
    return m_pInstance;
}
