#ifndef DSETTINGPLUGIN_H
#define DSETTINGPLUGIN_H

#include <QtGui>
#include "dsetting.h"

class dChatApplication;

class dSettingPlugin: public dSetting
{
    private:
        dChatApplication *application;
    public:
        dSettingPlugin( const QString &_key, dSetting *_parent );
        ~dSettingPlugin();

        virtual QWidget *createWidget();
};

#endif // DSETTINGPLUGIN_H

