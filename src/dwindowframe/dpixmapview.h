#ifndef DPIXMAPVIEW_H
#define DPIXMAPVIEW_H

#include <QtGui>

class dPixmapView: public QWidget
{
    private:
        QPixmap pixmap;
        
        QString text;
        QPoint text_point;
        QFont text_font;
    
    public:
        dPixmapView( const QPixmap &_pixmap = QPixmap(), QWidget *_parent = 0 );

    // Перегрузка операций QWidget.
        virtual QSize sizeHint () const;
        virtual void paintEvent ( QPaintEvent * event );

    // Установка pixmap.
        virtual const QPixmap &getPixmap() const;
        virtual void setPixmap( const QPixmap &_pixmap );

    // Вывод текста.
        const QString &getText() const;
        void setText( const QString &_text );
        void setText( const QPoint &_point, const QString &_text );
        void setText( int x, int y, const QString &_text );
    // Установка шрифтов, при выводе текста.
        void setFont( const QFont &_text_font );
        const QFont &getFont() const;


};

#endif // DPIXMAPVIEW_H
