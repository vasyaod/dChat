#include <QtGui>
#include "dpixmapbutton.h"

void dPixmapButton::setOverButton( const QPixmap &_pm_over_button )
{
    pm_over_button = _pm_over_button;
}

void dPixmapButton::setDisabledButton( const QPixmap &_pm_disabled_button )
{
    pm_disabled_button = _pm_disabled_button;
}
void dPixmapButton::setPressedButton( const QPixmap &_pm_pressed_button )
{
    pm_pressed_button = _pm_pressed_button;
}
void dPixmapButton::setButton( const QPixmap &_pm_button )
{
    pm_button = _pm_button;
    setActive( active );
}
QSize dPixmapButton::sizeHint() const
{   
    return pm_button.size();
}

dPixmapButton::dPixmapButton( const QPixmap &_pm_button,
                  QWidget *_parent):
                dPixmapView(_pm_button,_parent),
                pm_disabled_button(_pm_button),
                pm_button(_pm_button),
                pm_over_button(_pm_button),
                pm_pressed_button(_pm_button),
                active(true)
{        
    setActive( active );
};

void dPixmapButton::mousePressEvent( QMouseEvent * e )
{
    if( e->button() == Qt::LeftButton )
    {
        setPixmap(pm_pressed_button);
        update();
        emit pressed();
    }
};

void dPixmapButton::mouseReleaseEvent( QMouseEvent * e )
{
    if( e->button() == Qt::LeftButton )
    {
        setPixmap(pm_over_button);
        update();
        if(rect().contains(e->pos()))
           emit clicked();            
    }
};

bool dPixmapButton::event(QEvent * e )
{

    if( e->type() == QEvent::Leave && active)
    {
        if ( active == true )
            setPixmap(pm_button);
        else
            setPixmap(pm_disabled_button);
        update();
    }
    else if( e->type() == QEvent::Enter && active)
    {
        setPixmap(pm_over_button);
        update();
    }
    QWidget::event( e );
}

void dPixmapButton::setActive(bool _active)
{
    active = _active;
    if ( active == true )
        setPixmap(pm_button);
    else
        setPixmap(pm_disabled_button);
}
