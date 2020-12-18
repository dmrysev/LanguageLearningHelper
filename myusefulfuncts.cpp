#include "myusefulfuncts.h"

#include <time.h>

QStringList MyUsefulFuncts::shuffleList(QStringList list){
    QStringList tempList;
    qsrand(time(NULL));
    while(list.size() != 0){
        int rnd = qrand() % list.size();
        tempList << list.at(rnd);
        list.removeAt(rnd);
    }
    return tempList;
}
