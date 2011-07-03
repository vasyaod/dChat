#ifndef DPLWWW_H
#define DPLWWW_H

#include <QtGui>
#include "../dplugininterface.h"

class dPlGoWWW : public QObject, public dChatPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(dChatPluginInterface)

    public:
        dPlGoWWW( QObject * _parent = 0 ):QObject(_parent){};
        ~dPlGoWWW(){};
        
        virtual bool init( dChatGemstone *chatGemstone );
        virtual QString key(){ return tr("dPlGoWWW"); };
        virtual QString title(){ return  tr("Добавляет в меню кнопку, открывающую web-сайт чата."); };

    public slots:
        void goWWW();
};

#endif // DPLWWW_H



