#ifndef DSETTINGWINDOW_H
#define DSETTINGWINDOW_H

#include <QtGui>
#include <QtXml>
#include "dsetting.h"

class dWindowFrame;

class dSettingWindow: public dSetting
{
    Q_OBJECT
    private:
    // Кнопка смены скина.
        QPushButton *skinPushButton;

    // Имя стиля.
        QString styleName;
    // Файл скина.
        QString skinFileName;
        
    // Разлиные элементы Хмл
        QDomElement positionElement;
        QDomElement sizeElement;
        QDomElement opacityElement;
        QDomElement skinElement;
        
    // Указатель на окно.     
        dWindowFrame *window;
    public:
    
        dSettingWindow( const QString &_key, dSetting *_parent, dWindowFrame *_window );
        ~dSettingWindow();
        virtual void saveSetting();
        virtual QWidget *createWidget();
    
    public slots:
    // Вызывается при изменении прозрачности.
        void opacityValueChanged ( int i );
    // При нажатии кнопки смены скина.
        void clickedSkinButton ( bool checked );
    // Использовать ст. рамку.
        void stateChanged ( int state );
};

#endif // DSETTINGWINDOW_H

