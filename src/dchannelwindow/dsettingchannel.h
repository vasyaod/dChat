#ifndef DSETTINGCHANNEL_H
#define DSETTINGCHANNEL_H

#include <QtGui>
#include <QtXml>
#include "../dsetting.h"

class dWindowFrame;
class dChannelWindow;

class dSettingChannel: public dSetting
{
    Q_OBJECT
    private:
        dChannelWindow *channelWindow;
    // Комбо с указание типа просмотра сообщений.
        QComboBox *viewTypeComboBox;
        
        QSpinBox *messageMaxSpinBox;
        QSpinBox *nameMaxSpinBox;
    public:
        bool isTableView();    
        dSettingChannel( const QString &_key, dSetting *_parent, dChannelWindow *_channelWindow );
        ~dSettingChannel();

        virtual QWidget *createWidget();
    
    public slots:
        void viewTypeActivated( int _index );
    // При изменении количества строк.
        void messageMaxChanged( int _value );
    // При изменении количества симвалов в имени.
        void nameMaxChanged( int _value );
};

#endif // DSETTINGCHANNEL_H

