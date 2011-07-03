#include <QtGui>

#include "ditemdelegate.h"
#include "ditemwidget.h"
#include "dlistviewex.h"

UserItemDelegate::UserItemDelegate( dListViewEx * _listViewEx ):
        QItemDelegate(_listViewEx),
        listViewEx(_listViewEx)
{
}

QWidget *UserItemDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem & /* option */,
                                     const QModelIndex &index) const
{
   // dItemWidget *item = new dItemWidget();
//    const QAbstractItemModel * model = index.model();
//    dItemWidget *item = (dItemWidget*)model->data(index,Qt::UserRole).toInt();
    QWidget *item = listViewEx->getItemWidget(index);
    item->setParent(parent);
    
    return item;
}

void UserItemDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
//  ИЗЪЯТО ЗА НЕНАДОБНОСТЬЮ
  /*
    qDebug() << "+" << endl;
    dItemWidget *item = qobject_cast<dItemWidget *>(editor);
    const QAbstractItemModel * model = index.model();

    if (!item)
        return;
        
    item->set_name(model->data(index).toString());

    item->set_avatar( model->data(index,Qt::DecorationRole).value<QIcon>() );
    item->set_ip(model->data(model->index(index.row(),1)).toString());
    item->set_host(model->data(model->index(index.row(),2)).toString());
    // Сохраним указатель на виджет пункта во второй колонке, 
    // как данные пользователя.
  //  model->setData(index, QVariant ((int) item),Qt::UserRole);
 */
}

void UserItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
   //  qDebug() << "1" ;
  //  dItemWidget *item = qobject_cast<dItemWidget *>(editor);
 //   if (!item)
  //      return;

  // model->setData(index, comboBox->currentText());

}

QSize UserItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QWidget *item = listViewEx->getItemWidget(index);
    return item->sizeHint();
}
/*
bool UserItemDelegate::editorEvent ( QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index )
{

};

*/

void UserItemDelegate::updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
   // dItemWidget *item = qobject_cast<dItemWidget *>(editor);
   // item->unselect();
    QItemDelegate::updateEditorGeometry ( editor, option, index );
  //  qDebug() << "+++++++++++++++++++++++++++++" << endl;
};

/*
void UserItemDelegate::emitCommitData()
{
   // emit commitData(qobject_cast<QWidget *>(sender()));
}
//*/
