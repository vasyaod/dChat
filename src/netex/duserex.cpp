#include "duserex.h"

//#include "../dlistviewex/dlistviewex.h"
//#include "../dlistviewex/ditemwidget.h"

#include "../dchatapplication.h"
#include "../duserwindow.h"

#include "dmanagerex.h"

//***************************************************************
// Набор конструкторов.
dUserEx::dUserEx( dManager * _manager, const QHostAddress &_ip, const QString &_name):
                dUser(_manager,_ip,_name)
{
    application = qobject_cast<dChatApplication*>(QApplication::instance());
    addItemToList();
};

void dUserEx::addItemToList()
{
    int i = 0;
    QModelIndex index;    
    model = get_manager()->get_model();

    // Здесь происходит сортировка и ищется место куда нужно вставить
    // новые данные.
    int row_count = model->rowCount();

    // Выискиваем место в сооответствии с алфавитом.
    for( i = 0; i < row_count; i++ )
    {
        index = model->index(i,0);
        if ( model->data(index).toString() > get_name() )
        {
//             if ( model->data(model->index(i,1)).toString() > get_ip().toString() )
                  break; 
        }
    }
   
    if( !row_count )
        i = 0;
    model->insertRows(i, 1, QModelIndex());

    model->setData(model->index(i, 0, QModelIndex()), QVariant::fromValue(get_pointer()),Qt::UserRole);
    model->setData(model->index(i, 0, QModelIndex()), QIcon("avatar/noavatar.png"),Qt::DecorationRole);
    model->setData(model->index(i, 0, QModelIndex()), get_name());
    model->setData(model->index(i, 1, QModelIndex()), get_ip().toString());
    
    // Мне так не хотелось делать этот вызов.... но пришлось,
    // так как других вариантов я не нашел.
  //  application->user_window->searchWidgetUpdate();
    
    set_tool_tip(model->index(i,0));
};

dUserEx::~dUserEx()
{
    QModelIndex index = find_index();
    if( index != QModelIndex() )
        model->removeRow(index.row());
}; 

QModelIndex dUserEx::find_index()
{
    QModelIndex index;
    QAbstractItemModel *model = get_manager()->get_model();
    
    dPUser usr = get_pointer();
    int row_count = model->rowCount();
    for( int i = 0; i < row_count; i++ )
    {
        index = model->index(i,0);
        if ( model->data(index, Qt::UserRole).value<dPUser>() ==  usr )
            return index;
    }
/*    
    QModelIndexList indexes = model->match ( model->index(0,0), Qt::UserRole, QVariant::fromValue(get_pointer()) );
    if ( indexes.size() > 0 )
        return model->index(indexes[0].row(),0);
*/
    return QModelIndex();
};

void dUserEx::set_avatar(const QPixmap &_avatar)
{

    QAbstractItemModel *model = get_manager()->get_model();
    QModelIndex index = find_index();
    if( index == QModelIndex() )
        return;
        
    dUser::set_avatar(_avatar);
    model->setData(model->index(index.row(),0), QIcon(_avatar),Qt::DecorationRole);
};

bool dUserEx::set_name(const QString &_name)
{
    if( get_name() == _name )
         return true;
    QModelIndex index = find_index();
    dUser::set_name(_name);

    if( index == QModelIndex() )
        return true;

    model->setData(model->index(index.row(),0),_name);
    set_tool_tip(index);
};

void dUserEx::set_host(const QString & _host)
{
    if( get_host() == _host)
         return;
    QModelIndex index = find_index();
     if( index == QModelIndex() )
        return;

    dUser::set_host(_host);
    model->setData(model->index(index.row(),2),_host);
    set_tool_tip(index);
};
void dUserEx::set_login(const QString & _login)
{
    if( get_login() == _login)
         return;
    QModelIndex index = find_index();
    if( index == QModelIndex() )
        return;
    dUser::set_login(_login);
    model->setData(model->index(index.row(),3),_login);
};
void dUserEx::set_version( const QString & _version )
{
    if( get_version() == _version)
         return;
    QModelIndex index = find_index();
    if( index == QModelIndex() )
        return;
    dUser::set_version(_version);
    model->setData(model->index(index.row(),4),_version);
    set_tool_tip(index);
};

void dUserEx::set_auto_answer( const QString & _auto_answer )
{
    if( get_auto_answer() == _auto_answer)
         return;
    QModelIndex index = find_index();
    if( index == QModelIndex() )
        return;
    dUser::set_auto_answer(_auto_answer);
    model->setData(model->index(index.row(),5),_auto_answer);
    model->setData(model->index(index.row(),5),int(Qt::AlignLeft|Qt::AlignTop),Qt::TextAlignmentRole);
//    set_tool_tip(index);
};

void dUserEx::set_activity(const bool & _activity)
{
    if( get_activity() == _activity)
         return;
    QModelIndex index = find_index();
    if( index == QModelIndex() )
        return;
    dUser::set_activity(_activity);

    if( get_xml_protocol() == 0 )
    {
        if( _activity == true )
        {
            for( int i = 0; i < 8;i++ )
                model->setData(model->index(index.row(),i),QColor(0xF5C6DC),Qt::BackgroundColorRole);
        }
        else
        {
            for( int i = 0; i < 8;i++ )
                model->setData( model->index(index.row(),i),
                                QApplication::palette().color(QPalette::Base),
                                Qt::BackgroundColorRole);
        }
    }
    model->setData(model->index(index.row(),6),_activity);
};

void dUserEx::set_xml_protocol( uint _xml_protocol) 
{
    if( get_xml_protocol() == _xml_protocol)
         return;
    
    QModelIndex index = find_index();
    if( index == QModelIndex() )
        return;
    
    dUser::set_xml_protocol(_xml_protocol);
    if( _xml_protocol >= 1 )
    {
        // 0x72B972
        for( int i = 0; i < 8;i++ )
            model->setData(model->index(index.row(),i),QColor(0x85B985),Qt::BackgroundColorRole);
    }
};   

void dUserEx::set_mode(const uint & _mode)
{
    if( get_mode() == _mode)
         return;
    QModelIndex index = find_index();
    if( index == QModelIndex() )
        return;
    dUser::set_mode(_mode);
    model->setData(model->index(index.row(),7),_mode);
};

void dUserEx::set_sex(const uint & _sex)
{
    if( get_sex() == _sex)
         return;
    QModelIndex index = find_index();
    if( index == QModelIndex() )
        return;
    dUser::set_sex(_sex);
    model->setData(model->index(index.row(),8),_sex);
};

void dUserEx::set_tool_tip( QModelIndex index )
{
    QString tool_tip = tr("<b>Имя:</b> %1<br><b>IP:</b> %2<br><b>Host:</b> %3<br><b>Version:</b> %5")
                               .arg(get_name())
                               .arg(get_ip().toString())
                               .arg(get_host())
                               .arg(get_version());
    model->setData(model->index(index.row(),0),tool_tip,Qt::ToolTipRole);
    model->setData(model->index(index.row(),1),tool_tip,Qt::ToolTipRole);
    model->setData(model->index(index.row(),2),tool_tip,Qt::ToolTipRole);
};