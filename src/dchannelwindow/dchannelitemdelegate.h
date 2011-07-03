#ifndef DCHANNELITEMDELEGATE_H
#define DCHANNELITEMDELEGATE_H

#include <QItemDelegate>

class dChannelItemDelegate : public QItemDelegate
{
  //  Q_OBJECT
    public:
        dChannelItemDelegate(QObject *parent = 0);
    
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model,
                          const QModelIndex &index) const;
        
      QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

};

#endif //DCHANNELITEMDELEGATE_H
