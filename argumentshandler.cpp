#include "argumentshandler.h"

ArgumentsHandler::ArgumentsHandler(){

}
QString ArgumentsHandler::getValue(const QString &par){

    for(int i = 0; i < arguments.size(); i++){
        QString arg = arguments.at(i);
        if(arg.contains(par)){
            return arg.split("=").at(1);
        }
    }
}
ArgumentsHandler* ArgumentsHandler::m_pInstance = NULL;
ArgumentsHandler* ArgumentsHandler::instance(){
    if (!m_pInstance)
        m_pInstance = new ArgumentsHandler;
    return m_pInstance;
}
void ArgumentsHandler::setArguments(const QStringList &args){
    arguments = args;
}
