#ifndef DSETTING_H
#define DSETTING_H

#include <QtGui>
#include <QtXml>

class dSetting : public QObject
{
    Q_OBJECT
    private:
    // Название настроек.
        QString title;
        bool node;
    // Иконка символизирующая настройки.
        QIcon icon;
    protected:    
    // Элемент xml который содержит сия натройки.
        QDomElement element;
        QDomElement parentElement;
    public:
    // Получить элемент xml дерева
        QDomElement getXmlElement() const { return element; };
    //  элемент xml дерева
        QDomElement getChildXmlElement( const QString & _childName );
    //  элемент xml дерева
        QDomElement getParentXmlElement()const { return parentElement; };
    
    // Чтение и установка атрибутов дочерних элементов.]
    // Созданы исключительно для удобства.
        QString get(const QString &_elementName, const QString &_attributeName, const QString &_defValue = QString() );
        QString toString(const QString &_elementName, const QString &_attributeName, const QString &_defValue = QString() );
        int toInt(const QString &_elementName, const QString &_attributeName, int _defValue = 0 );
        QSize toSize( const QString &_elementName, const QSize &_defValue);
        QFont toFont( const QString &_elementName, const QFont &_defValue);
        QByteArray toByteArray( const QString &_elementName, const QByteArray &_defValue );
        void set(const QString &_elementName, const QString &_attributeName, const QString &_value);
        void set(const QString &_elementName, const QString &_attributeName, int _value);
        void set( const QString &_elementName, const QSize &_value);
        void set( const QString &_elementName, const QFont &_value);
        void set( const QString &_elementName, const QByteArray& _value);
    // Востанавливает размеры заголовков таблицы.
    // Параметр _header входящий....
        void getHeaderSize( const QString &_elementName, QHeaderView *_header );
    // Сохраняет размеры заголовков таблицы.
    // Параметр _header входящий....
        void setHeaderSize( const QString &_elementName, QHeaderView *_header );
        
    // key - ключь, надпись из латинских букв идендифицирующая текущие настройки.
    // Из ключа вырезается все кроме латинских букв.
        dSetting( const QString &_key, QDomElement &_element, dSetting *_parent = 0 );
        dSetting( const QString &_key, dSetting *_parent );
        ~dSetting();

    // Получить ключь.
        QString get_key() const;
    // Выдает родителя.
        dSetting *parent () const;
    // Выдет список детей.
        QList<dSetting*> children() const;
    // Поиск ребека в списке.
        dSetting* findChild ( const QString & name) const;
    // Получить(установить) заголовок настройки.
        QString &getTitle( void ){ return title; };
        void setTitle( QString _title ){ title = _title; };
    // Добавить ребенка в иерархию  по указанному пути.
        bool addChild( dSetting *_child, QString &_path = QString());

    // Это свойство указавет являются ли эти настройки новым узлом,
    // или являются добовлениями к старому узлу.
        bool isNode()const { return node; };
    // Метод устанавливет преведущее свойство.
        void setNode( const bool &_node ){ node = _node; };

    // Получить(установить) иконку символизирующщую настройки.
        const QIcon &getIcon() const { return icon; };
        void setIcon( const QIcon &_icon ){ icon = _icon; };
                            
    // ЧИСТО виртуальная функция. Возвращает указатель на виджет,
    // в котором будет распологаться управление настроек.
    //  virtual QWidget *getWidget() = 0;
        virtual QWidget *createWidget(){ return 0; };
    
    // ЧИСТО виртуальная функция. Активирует настройки.
    // virtual void activatingSetting() = 0;
    // Виртуальная функция. Сохраняет настройки.
        virtual void saveSetting();
    
    // ЧИСТО виртуальная функция. Восстанавливает настройки.
    // virtual void restoreSetting() = 0;
        
    // Нужно вызвать если надо перестроить дерево настроек.
        virtual void reParsing();
        
    signals:
    // Сигнал сигнал посылается если нужно перестроить дерево настроек.
        void reParsingSignal();
};
#endif // DSETTING_H
