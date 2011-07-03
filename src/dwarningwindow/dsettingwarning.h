#ifndef DSETTINGTOPIC_H
#define DSETTINGTOPIC_H

#include <QtGui>
#include <QtXml>
#include "../dsetting.h"

class dWindowFrame;

class dSettingWarning: public dSetting
{
    Q_OBJECT
    private:
        static QString keys[9];
        QCheckBox *warningCheckBoxs[9];
        QCheckBox *soundCheckBoxs[9];
        QPushButton *soundPushButtons[9];
        QPushButton *warningPushButtons[9];
        QLabel *fileLabels[9];
        QLabel *colorLabels[9];
        
        int windowTimeOut;  //Время задержки всплывающего окна.
        int maxWindow;     //Максимальное количество окон на экране.

    public:
        dSettingWarning( const QString &_key, dSetting *_parent );
        ~dSettingWarning();

        virtual QWidget *createWidget();
        
    // Возвращает время задержки всплывающего окна.        
        int getWindowTimeOut(){ return windowTimeOut; };
    // Возвращает максимальное количество окон на экране.
        int getMaxWindow(){ return maxWindow; };
    
    public slots:
        void stateChangedWarning ( int state );
        void stateChangedSoundWarning ( int state );
        void fileSoundChange();
        void colorChange();
        void timeChanged(int _value);
        void maxWindowChanged(int _value);
};


#endif // DSETTINGTOPIC_H

