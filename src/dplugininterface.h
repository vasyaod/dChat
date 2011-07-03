#ifndef DPLUGININTERFACE_H
#define DPLUGININTERFACE_H

#include <QtGui>

class dChatGemstone;

class dChatPluginInterface 
{
    public:
      //  virtual ~dChatPluginInterface(){};
        virtual bool init( dChatGemstone *chatGemstone ) = 0;
        virtual QString key() = 0;
        virtual QString title() = 0;
};
Q_DECLARE_INTERFACE(dChatPluginInterface,"dChatPluginInterface/1.0")

#endif // DPLUGININTERFACE_H

