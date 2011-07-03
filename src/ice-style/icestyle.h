#ifndef ICE_STYLE_H
#define ICE_STYLE_H

#include <QtGui>

class QPainterPath;

class IceStyle : public QWindowsStyle
{
    Q_OBJECT
    public:
        IceStyle() {}

        void polish(QPalette &palette);
    /*
        void polish(QWidget *widget);
        void unpolish(QWidget *widget);
        int pixelMetric(PixelMetric metric, const QStyleOption *option,
                        const QWidget *widget) const;
        int styleHint(StyleHint hint, const QStyleOption *option,
                      const QWidget *widget, QStyleHintReturn *returnData) const;
   */
        void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                           QPainter *painter, const QWidget *widget) const;
     
        void drawControl(ControlElement control, const QStyleOption *option,
                         QPainter *painter, const QWidget *widget) const;

    private:
        static void setTexture(QPalette &palette, QPalette::ColorRole role,
                               const QPixmap &pixmap);
        static QPainterPath roundRectPath(const QRect &rect);
};

#endif  //ICE_STYLE_H
