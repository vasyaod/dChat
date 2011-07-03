#include <QtGui>

#include "icestyle.h"

class MyStylePlugin : public QStylePlugin
{
    public:
        QStringList keys() const {
            return QStringList() << "ICEStyle";
        }

        QStyle *create(const QString &key) {
            if (key == "icestyle")
            {
                return new IceStyle();
            }
            qDebug()<<key;
            return 0;
        }
};

Q_EXPORT_PLUGIN(MyStylePlugin)


