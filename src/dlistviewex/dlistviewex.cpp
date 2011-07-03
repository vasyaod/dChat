#include "dlistviewex.h"
#include "ditemdelegate.h"
#include "ditemwidget.h"

dListViewEx::dListViewEx( QWidget *parent ):
             QListView( parent ),
             column(1)
{ 
    setItemDelegate( new UserItemDelegate(this) );

};
void dListViewEx::setModel( QAbstractItemModel * _model )
{
    QListView::setModel(_model);
    
    QModelIndex index;
    for( int i = 0; i < model()->rowCount(); i++ )
    {
        index = model()->index(i,0);
        openPersistentEditor(index);
    }
};
dListViewEx::~dListViewEx()
{
    QHashIterator<int, dItemWidget*> i(hashItemWidget);
    while (i.hasNext()) {
        i.next();
        delete (QWidget*)i.value();
    }    
};

QModelIndex dListViewEx::indexAt ( const QPoint & point ) const
{
    // Сделаем защиту от того что модель не будет указана для
    // dListViewEx.
    if( !model() )
        return QModelIndex();

    int wy = (point.y())/60;
    return model()->index(wy, 0, QModelIndex());
};

void dListViewEx::rowsAboutToBeRemoved ( const QModelIndex & parent, int start, int end )
{ 

    QModelIndex index = model()->index(start,column);
    int usr = model()->data(model()->index(index.row(),0),Qt::UserRole).toInt();
    
    dItemWidget *item = hashItemWidget.value(usr);
    if( item )
        delete item;        
    hashItemWidget.remove(usr);
    QListView::rowsAboutToBeRemoved(parent,start,end);
}

void dListViewEx::rowsInserted ( const QModelIndex & parent, int start, int end )
{ 
    QListView::rowsInserted(parent,start,end);
}

void dListViewEx::dataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
  //  hide();
  //  show();
    
    QModelIndex index = model()->index(topLeft.row(),column);
    dItemWidget *item = getItemWidget(index);

    // Тут можно внести изменения в работы дабы повысить скорость!!!
    // если малость переделать!
    if ( topLeft.column() == 0 )
    {
        QModelIndex index0 = model()->index(index.row(),0);
        
        item->set_name(model()->data(index0).toString());
        item->set_avatar( model()->data(index0,Qt::DecorationRole).value<QIcon>() );
        QColor selectColor = model()->data(index0,Qt::TextAlignmentRole).value<QColor>();
        if( selectColor == QColor() )
            selectColor = QApplication::palette().color(QPalette::Highlight);
        item->set_select_color(selectColor);
        
        QColor bgColor = model()->data(index0,Qt::BackgroundColorRole).value<QColor>();
        if( bgColor == QColor() )
            bgColor = QApplication::palette().color(QPalette::Highlight);
        item->set_background_color(bgColor);
    }
    if ( topLeft.column() == 1 ) item->set_ip(model()->data(model()->index(index.row(),1)).toString());
    if ( topLeft.column() == 2 ) item->set_host(model()->data(model()->index(index.row(),2)).toString());
    if ( topLeft.column() == 3 ) item->set_login(model()->data(model()->index(index.row(),3)).toString());
    if ( topLeft.column() == 4 ) item->set_version(model()->data(model()->index(index.row(),4)).toString());
    if ( topLeft.column() == 5 ) item->set_auto_answer(model()->data(model()->index(index.row(),5)).toString());

/*
    item->set_all( model()->data(index).toString() ,
                   model()->data(model()->index(index.row(),1)).toString(),
                   model()->data(model()->index(index.row(),2)).toString(),
                   model()->data(model()->index(index.row(),3)).toString(),
                   model()->data(model()->index(index.row(),4)).toString(),
                   model()->data(model()->index(index.row(),5)).toString(), 
                   model()->data(index,Qt::DecorationRole).value<QIcon>());
 */                  
    if ( topLeft.column() == 0 ) openPersistentEditor(topLeft);
    QListView::dataChanged(topLeft,bottomRight);

}
/*
void dListViewEx::currentChanged ( const QModelIndex & current, const QModelIndex & previous )
{
/*
    QModelIndex index;
    dItemWidget *item;
    if( current != QModelIndex())
    {
        index = model()->index(current.row(),column);
        item = getItemWidget(index);
        item->select();
    }
    if( previous != QModelIndex())
    {
        index = model()->index(previous.row(),column);
        item = getItemWidget(index);
        item->unselect();
    }

    QListView::currentChanged( current,  previous );
}
*/
void dListViewEx::selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected )
{
    dItemWidget *item;
    foreach( QModelIndex index, deselected.indexes() )
    {
        item = getItemWidget(index);
        item->unselect();    
    }

    foreach( QModelIndex index, selected.indexes() )
    {
        item = getItemWidget(index);
        item->select();    
    }
    
}

dItemWidget *dListViewEx::getItemWidget(const QModelIndex &index)
{
    int usr = model()->data(model()->index(index.row(),0),Qt::UserRole).toInt();
    dItemWidget *item;
    
    item = hashItemWidget.value(usr);
    if( !item )
    {
        item = new dItemWidget();

        item->set_name(model()->data(model()->index(index.row(),0)).toString());
        item->set_avatar( model()->data(model()->index(index.row(),0),Qt::DecorationRole).value<QIcon>() );
        item->set_ip(model()->data(model()->index(index.row(),1)).toString());
        item->set_host(model()->data(model()->index(index.row(),2)).toString());
        item->set_login(model()->data(model()->index(index.row(),3)).toString());
        item->set_version(model()->data(model()->index(index.row(),4)).toString());
        item->set_auto_answer(model()->data(model()->index(index.row(),5)).toString());

        QModelIndex index0 = model()->index(index.row(),0);
        QColor selectColor = model()->data(index0,Qt::TextAlignmentRole).value<QColor>();
        if( selectColor == QColor() )
            selectColor = QApplication::palette().color(QPalette::Highlight);
        item->set_select_color(selectColor);
        
        QColor bgColor = model()->data(index0,Qt::BackgroundColorRole).value<QColor>();
        if( bgColor == QColor() )
            bgColor = QApplication::palette().color(QPalette::Highlight);
        item->set_background_color(bgColor);

        hashItemWidget.insert(usr,item);
    }
    
    return item;
}

void dListViewEx::paintEvent ( QPaintEvent * event )
{
    QListView::paintEvent(event);
}
