#ifndef DSETTINGPLCOMMAND_H
#define DSETTINGPLCOMMAND_H

#include "../dsetting.h"

class dPlCommand;

class dSettingPLCommand: public dSetting
{
    private:
         dPlCommand *plCommand;
    public:
        dSettingPLCommand( const QString &_key, dSetting *_parent, dPlCommand *_plCommand):dSetting(_key,_parent),plCommand(_plCommand){};
        virtual QWidget *createWidget();
        ~dSettingPLCommand(){};
};

#endif // DSETTINGPLCOMMAND_H
