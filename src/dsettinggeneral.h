#ifndef DSETTINGGENERAL_H
#define DSETTINGGENERAL_H

#include <QtGui>
#include "dsetting.h"

class dSettingGeneral: public dSetting
{
    private:
        QWidget * widget;
    public:
    
        dSettingGeneral( QDomElement &_element );
        ~dSettingGeneral();
        virtual QWidget *createWidget();
        virtual void reParsing();
};
#endif // DSETTINGGENERAL_H

