#ifndef DSETTINGTOPIC_H
#define DSETTINGTOPIC_H

#include <QtGui>
#include <QtXml>
#include "../dsetting.h"

class dWindowFrame;
class dTopicWindow;

class dSettingTopic: public dSetting
{
    Q_OBJECT
    private:
        dTopicWindow *topicWindow;
        QFont font;
    public:
        bool isTableView();    
        dSettingTopic( const QString &_key, dSetting *_parent, dTopicWindow *_topicWindow );
        ~dSettingTopic();

        virtual QWidget *createWidget();
    
        QFont getFont(){ return font; };
    public slots:
        // Вызывается при нажатии кнопки выбора шрифта....
        void clickedFontButton();
        // Вызывается при нажатии кнопки сброса шрифта....
        void clickedStdFontButton();
};

#endif // DSETTINGTOPIC_H

