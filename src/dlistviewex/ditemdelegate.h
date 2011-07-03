#include <QItemDelegate>

class dListViewEx;

class UserItemDelegate : public QItemDelegate
{
    Q_OBJECT
    private:
        dListViewEx * listViewEx;
    public:
        UserItemDelegate( dListViewEx *_listViewEx );
    
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;

        void setEditorData(QWidget *editor, const QModelIndex &index) const;
 
        void setModelData(QWidget *editor, QAbstractItemModel *model,
                          const QModelIndex &index) const;

        virtual QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
        virtual void updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
   //     virtual bool editorEvent ( QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index );
    private slots:
   //     void emitCommitData();
    
};
