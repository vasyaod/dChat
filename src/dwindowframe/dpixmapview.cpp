#include <QtGui>
#include "dpixmapview.h"

dPixmapView::dPixmapView( const QPixmap &_pixmap, 
                          QWidget *_parent ):
        QWidget(_parent),
        pixmap(_pixmap)
{ 
  //  resize(pixmap.size());

};

void dPixmapView::paintEvent ( QPaintEvent * event )
{
    QPainter painter(this);
    painter.fillRect(event->rect() ,QBrush(pixmap));
    painter.setFont(text_font);
    painter.drawText(text_point,text);
            //painter.drawRect(10,10,50,50);
}
const QPixmap &dPixmapView::getPixmap() const
{ 
    return pixmap; 
};
void dPixmapView::setPixmap( const QPixmap &_pixmap )
{ 
    pixmap = _pixmap;
  //  resize(pixmap.size()); 
    update(); 
};
/************* Вывод текста на экран. *****************/
const QString &dPixmapView::getText() const
{ 
    return text; 
};
void dPixmapView::setText( const QString &_text )
{ 
    text = _text; 
    update();
};
void dPixmapView::setText( const QPoint &_point, const QString &_text ) 
{   
    text_point = _point; 
    text = _text; 
    update();
};
void dPixmapView::setText( int x, int y, const QString &_text ) 
{   
    text_point.rx() = x;
    text_point.ry() = y;    
    text = _text;
    update();
};
QSize dPixmapView::sizeHint () const
{
    return pixmap.size();
};

/************ Установка шрифтов, при выводе текста. ***********/
void dPixmapView::setFont( const QFont &_text_font )
{
    text_font = _text_font;
    update();
};

const QFont &dPixmapView::getFont() const
{
    return text_font;
};
        

