#ifndef DTRAYICON_H
#define DTRAYICON_H

#include <QtGui>

class dTrayIcon;
Q_DECLARE_INTERFACE(dTrayIcon,"dTrayIcon/1.0")

class dTrayIcon : public QObject
{
#ifdef BUILD_DLL
    Q_OBJECT
#endif    
    Q_INTERFACES(dTrayIcon)
    private:
        HWND hwnd;               /* This is the handle for our window */
        static LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    public:
        dTrayIcon( QObject * _parent = 0 );
        ~dTrayIcon();

    // Добавляет иконку в трей...
        virtual bool addIcon( const QString & _iconfile, const QString &_title = tr("") );
        virtual bool deleteIcon();
        
    signals:
    // Сигнал подается, при нажатии левой кнопки мыши.
        void leftButtonDown();
    // Сигнал подается, при нажатии левой правой мыши.
        void rightButtonDown();
};

#endif // DTRAYICON_H


