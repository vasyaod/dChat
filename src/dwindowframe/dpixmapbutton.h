#ifndef DPIXMAPBUTTON_H
#define DPIXMAPBUTTON_H

#include <QtGui>
#include "dpixmapview.h"

class dPixmapButton: public dPixmapView
{
    Q_OBJECT
    private:
    // Состояние активности кнопки.
        bool active;
        
    // Картинки для клавиш.
        QPixmap pm_disabled_button;         
        QPixmap pm_button;
        QPixmap pm_over_button;
        QPixmap pm_pressed_button;

    protected:
    // Перегрузка событий QWidget.
        virtual void mousePressEvent( QMouseEvent * e );
        virtual void mouseReleaseEvent( QMouseEvent * e );
        virtual void mouseMoveEvent( QMouseEvent * e ){};   // Просто перегрузим.
        virtual bool event(QEvent * e );
    
    public:
        dPixmapButton( const QPixmap &_pm_button = QPixmap(),
                 QWidget *_parent = 0 );
    // Добавление других состояний клавиши.
        void setOverButton( const QPixmap &_pm_over_button ); 
        void setButton( const QPixmap &_pm_button ); 
        void setDisabledButton( const QPixmap &_pm_disabled_button ); 
        void setPressedButton( const QPixmap &_pm_pressed_button ); 
        
        virtual QSize sizeHint () const;

    // Установка состояний клавиши.
        void setActive( bool _active);

// ОПРЕДЕЛИМ СИГНАЛЫ.
    signals:
        void clicked();
        void pressed();
};

#endif // DPIXMAPBUTTON_H
