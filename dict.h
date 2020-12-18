#ifndef DICT_H
#define DICT_H

#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QObject>

class Dict: public QObject
{
    Q_OBJECT
public:
    static Dict* instance();
    void openDict(const QString &dictFilePath);
    void add(const QString &a, const QString &b);
    void save();
    void repeated(const QString &entry);
    void next(int step);
    QStringList getAllA();
    QStringList getAllB();
    QStringList getRepeatA();
    QStringList getRepeatB();
    QStringList getTempA();
    QStringList getTempB();
    void shuffleRepeat();
    void shuffleTemp();
    void clearTemp();
    void replace(const QString &before, const QString &after);

private:
    static Dict* m_pInstance;
    Dict();
    int nextEnd;
    void fillRepeat();
    QStringList A, B, repeatA, repeatB, tempA, tempB;
    QStringList added;
    QStringList lastRepeatDate;
    QList <int> nextRepeat;
    QFile file;

signals:
    void changed();
    void dublicate(int i);
};

#endif // DICT_H
