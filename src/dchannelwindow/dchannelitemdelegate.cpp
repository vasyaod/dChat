#include <QtGui>

#include "dchannelitemdelegate.h"

dChannelItemDelegate::dChannelItemDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *dChannelItemDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem & /* option */,
                                     const QModelIndex &index) const
{
 //   QTextEdit *textEdit = new QTextEdit(parent);
    QWidget *textEdit = (QWidget*)index.model()->data(index,Qt::UserRole).toInt();
    if( !textEdit)
        return 0;
    textEdit->setParent(parent);
//    connect(comboBox, SIGNAL(activated(int)), this, SLOT(emitCommitData()));
 //   index.model()->setData(index, textEdit->height(),Qt::UserRole);
   // return new QLabel("dfsfsf",parent);
    return textEdit;
}

void dChannelItemDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
/*
    QWidget *textEdit = qobject_cast<QWidget *>(editor);
    if (!textEdit)
        return;

    textEdit->setPlainText(index.model()->data(index).toString());
*/
}

void dChannelItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
/*  
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    if (!comboBox)
        return;

    model->setData(index, comboBox->currentText());
*/
}

QSize dChannelItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{

    if( QModelIndex() != index )
    {
        QWidget *textEdit = (QWidget*)index.model()->data(index,Qt::UserRole).toInt();
    //    qDebug() << textEdit->size().height();
        return QSize(800,textEdit->sizeHint().height()+5);
    }
    else return QSize(800,50);
}

/*
void dChannelItemDelegate::emitCommitData()
{
    emit commitData(qobject_cast<QWidget *>(sender()));
}
*/

