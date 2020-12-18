#include "dict.h"

#include <QDate>
#include <time.h>

#include "myusefulfuncts.h"

Dict::Dict(): QObject(){
    nextEnd = 0;
}
void Dict::add(const QString &a, const QString &b){
    A << a;
    B << b;
    repeatA << a;
    repeatB << b;
    QDate c = QDate::currentDate();
//    added << c.toString("dd.MM.yyyy");
    lastRepeatDate << c.toString("dd.MM.yyyy");
    nextRepeat << 0;
    emit changed();
}
void Dict::save(){
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    for(int i = 0; i < A.size(); i++){

        stream << A.at(i) << "|"
               << B.at(i) << "|"
//               << added.at(i) << "|"
               << lastRepeatDate.at(i) << "|"
               << nextRepeat.at(i);

        if(i < A.size()-1)
            stream << "\n";
    }
    file.close();
}
void Dict::repeated(const QString &entry){
    int i = A.indexOf(entry);
    if(i == -1)
        i = B.indexOf(entry);

    QList <int> nextRepeatList;
    nextRepeatList << 0 << 1 << 2 << 4 << 8 << 16 << 32 << 64;
    QDate c = QDate::currentDate();
//    QDate a = QDate::fromString(added.at(i), "dd.MM.yyyy");
//    QDate a = QDate::fromString(lastRepeatDate.at(i), "dd.MM.yyyy");
//    int daysPassed = a.daysTo(c);

//    if(daysPassed >= nextRepeat.at(i)){
        int k = nextRepeatList.indexOf(nextRepeat.at(i));
        nextRepeat.replace(i, nextRepeatList.at(k + 1));

        lastRepeatDate.replace(i, c.toString("dd.MM.yyyy"));

//        emit changed();
//    }
}
QStringList Dict::getAllA(){
    return A;
}
QStringList Dict::getAllB(){
    return B;
}
QStringList Dict::getRepeatA(){
    return repeatA;
}
QStringList Dict::getRepeatB(){
    return repeatB;
}QStringList Dict::getTempA(){
    return tempA;
}
QStringList Dict::getTempB(){
    return tempB;
}
void Dict::openDict(const QString &dictFilePath){
    //  Open file.
    file.setFileName(dictFilePath);
    file.open(QFile::ReadWrite | QFile::Text);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream.seek(0);
    while(!stream.atEnd()){
        QString line=stream.readLine();
        if(line.contains("|")){
            A << line.split("|").at(0);
            B << line.split("|").at(1);
//            added << line.split("|").at(2);
            lastRepeatDate << line.split("|").at(2);
            nextRepeat << line.split("|").at(3).toInt();
        }
    }
    file.close();

    fillRepeat();
}
Dict* Dict::m_pInstance = NULL;

Dict* Dict::instance(){

    if (!m_pInstance)
        m_pInstance = new Dict;
    return m_pInstance;
}
void Dict::shuffleRepeat(){

    repeatA = MyUsefulFuncts::shuffleList(repeatA);
    repeatB = MyUsefulFuncts::shuffleList(repeatB);

    emit changed();
}
void Dict::fillRepeat(){

    repeatA.clear();
    repeatB.clear();

    QDate c = QDate::currentDate();

    for(int i = 0; i < A.size(); i++){

//        QDate a = QDate::fromString(added.at(i), "dd.MM.yyyy");
        QDate a = QDate::fromString(lastRepeatDate.at(i), "dd.MM.yyyy");
        int daysPassed = a.daysTo(c);

        if(daysPassed >= nextRepeat.at(i)){
            repeatA << A.at(i);
            repeatB << B.at(i);
        }
    }
}
void Dict::next(int step){

    tempA = repeatA.mid(nextEnd, step);
    tempB = repeatB.mid(nextEnd, step);

    nextEnd += step;
    if(nextEnd > repeatA.size())
        nextEnd = 0;
}
void Dict::shuffleTemp(){

    tempA = MyUsefulFuncts::shuffleList(tempA);
    tempB = MyUsefulFuncts::shuffleList(tempB);
}
void Dict::clearTemp(){

    tempA.clear();
    tempB.clear();
    nextEnd = 0;
}
void Dict::replace(const QString &before, const QString &after){

    A.replaceInStrings(before, after);
    B.replaceInStrings(before, after);
    fillRepeat();
    emit changed();
}
