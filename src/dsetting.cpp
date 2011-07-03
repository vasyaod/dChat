#include "dsetting.h"

dSetting::dSetting( const QString &_key, QDomElement &_parentElement ,dSetting *_parent ):
        parentElement(_parentElement),
        QObject(_parent),
        node(true),
        title(_key)
{
    QDomElement temp_element =_parentElement.firstChildElement(title);
    element = temp_element;
    if( !element.isElement() )
    {
        element = _parentElement.ownerDocument().createElement(title);
        _parentElement.appendChild(element);
    }
    setObjectName ( _key );
}

dSetting::dSetting( const QString &_key, dSetting *_parent ):
        QObject(_parent),
        node(true),
        title(_key)
{
    parentElement = _parent->getXmlElement();
    QDomElement temp_element = parentElement.firstChildElement(title);
    element = temp_element;
        
    if( !element.isElement() )
    {
        element = parentElement.ownerDocument().createElement(title);
        parentElement.appendChild(element);
    }
    setObjectName ( _key );
}

dSetting::~dSetting()
{
    QList<dSetting*> _children = children();
    foreach( dSetting* child, _children )
        delete child;
};

// Получить ключь.
QString dSetting::get_key() const
{
    return objectName();
};
// Выдает родителя.
dSetting *dSetting::parent() const
{
    return qobject_cast<dSetting*>(QObject::parent());
};
// Returns the child.
dSetting* dSetting::findChild ( const QString & name) const
{
    return QObject::findChild<dSetting *>(name);
};

bool dSetting::addChild( dSetting *_child, QString &_path)
{
   _child->setParent(this);
}

QList<dSetting*> dSetting::children() const
{
    QList<dSetting*> list1 = QObject::findChildren<dSetting *>();
    QList<dSetting*> list2;
    dSetting *temp;
    
    QListIterator<dSetting*> i(list1);
    while (i.hasNext())
    {
        temp = i.next();
        if ( temp->parent () == this ) 
            list2.push_back ( temp );  
    }
     
    return list2;
};
void dSetting::saveSetting()
{
    QFile file(tr("setting.xml"));
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&file);
    element.ownerDocument().save(out, 5); 
};

QDomElement dSetting::getChildXmlElement( const QString & _childName )
{

    QDomElement childElement = element.firstChildElement(_childName);
    if( !childElement.isElement() )
    {
        childElement = element.ownerDocument().createElement(_childName);
        element.appendChild(childElement);
    }
    return childElement;
};

// Чтение и установка атрибутов дочерних элементов.
// Созданы исключительно для удобства.
QString dSetting::get( const QString &_elementName, const QString &_attributeName, const QString & _defValue)
{
    QDomElement childElement = getChildXmlElement(_elementName);
    return childElement.attribute(_attributeName,_defValue);
};

QString dSetting::toString( const QString &_elementName, const QString &_attributeName, const QString &_defValue )
{
    QDomElement childElement = getChildXmlElement(_elementName);
    return childElement.attribute(_attributeName,_defValue);
};

int dSetting::toInt( const QString &_elementName, const QString &_attributeName, int _defValue) 
{
    QDomElement childElement = getChildXmlElement(_elementName);
    return childElement.attribute(_attributeName,QString::number(_defValue)).toInt();
};

QSize dSetting::toSize( const QString &_elementName, const QSize &_defValue) 
{
    QDomElement childElement = getChildXmlElement(_elementName);
    QSize size;
    size.setHeight(childElement.attribute(tr("height"),QString::number(_defValue.height())).toInt());
    size.setWidth(childElement.attribute(tr("width"),QString::number(_defValue.width())).toInt());
    return size;
};
QFont dSetting::toFont( const QString &_elementName, const QFont &_defValue) 
{
    QDomElement childElement = getChildXmlElement(_elementName);
    QFont font;
    font.fromString(childElement.attribute(tr("discript"),_defValue.toString()));
    return font;
};

void dSetting::getHeaderSize( const QString &_elementName, QHeaderView *_header )
{
    for( int i=0; i<_header->count(); i++)
    {
        int size = toInt(_elementName,tr("column%1").arg(i),100);
        _header->resizeSection(i,size);
    }
}
void dSetting::setHeaderSize( const QString &_elementName, QHeaderView *_header )
{
    QDomElement childElement = getChildXmlElement(_elementName);
    for( int i=0; i<_header->count(); i++)
        childElement.setAttribute(tr("column%1").arg(i),_header->sectionSize(i));
}

QByteArray dSetting::toByteArray( const QString &_elementName, const QByteArray &_defValue ) 
{
    QDomElement childElement = getChildXmlElement(_elementName);
    if( !childElement.hasAttribute("array"))
        return _defValue;
        
    QByteArray temp;
    int size = toInt(_elementName,tr("size"),_defValue.size());
    QString str = childElement.attribute(tr("array"),tr(""));
    if( size > int(str.size()/2) )
        size = int(str.size()/2);
    for( int i = 0; i<size; i++ )
    {
        temp += str.left(2).toInt(0,16);
        str.remove(0,2);
    }
    
    return temp;
};

void dSetting::set( const QString &_elementName, const QSize &_value)
{
    QDomElement childElement = getChildXmlElement(_elementName);
    childElement.setAttribute(tr("height"),_value.height());
    childElement.setAttribute(tr("width"),_value.width());
}
void dSetting::set( const QString &_elementName, const QFont &_value)
{
    QDomElement childElement = getChildXmlElement(_elementName);
//    childElement.setAttribute(tr("family"),_value.family());
//    childElement.setAttribute(tr("point_size"),_value.pointSize());
    childElement.setAttribute(tr("discript"),_value.toString());
}
void dSetting::set( const QString &_elementName, const QString &_attributeName, const QString &_value)
{
    QDomElement childElement = getChildXmlElement(_elementName);
    childElement.setAttribute(_attributeName,_value);
}

void dSetting::set( const QString &_elementName, const QString &_attributeName, int _value)
{
    QDomElement childElement = getChildXmlElement(_elementName);
    childElement.setAttribute(_attributeName,_value);
}
void dSetting::set( const QString &_elementName, const QByteArray& _value)
{
    QDomElement childElement = getChildXmlElement(_elementName);
    childElement.setAttribute(tr("size"),_value.size());
    const char *pointer = _value.data();
    QString value_str;
    for( int i = 0; i<_value.size(); i++ )
    {
        unsigned char z = pointer[i];
        value_str += QString().setNum(z,16).rightJustified(2,'0');
    }
    childElement.setAttribute(tr("array"),value_str);        
}

void dSetting::reParsing()
{
    parent()->reParsing();
    emit reParsingSignal(); 
};
