#ifndef DLISTVIEWEX_H
#define DLISTVIEWEX_H

#include <QtGui>
class dItemWidget;

class dListViewEx : public QListView
{
    Q_OBJECT
    private:
        int column;
        QHash< int, dItemWidget* > hashItemWidget;
    protected:
        virtual void paintEvent ( QPaintEvent * event );

    public:
    // Возвращает виджет который представляет собой 1 пункт.    
        dItemWidget *getItemWidget(const QModelIndex &index);

        dListViewEx( QWidget *parent = 0 );
        ~dListViewEx();
        virtual QModelIndex indexAt ( const QPoint & p ) const;
        virtual void setModel ( QAbstractItemModel * _model );
        
    protected slots:
        virtual void rowsAboutToBeRemoved ( const QModelIndex & parent, int start, int end );
        virtual void rowsInserted ( const QModelIndex & parent, int start, int end );
        virtual void dataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight);
   //     virtual void currentChanged ( const QModelIndex & current, const QModelIndex & previous );
        virtual void selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected );
};

#endif // DLISTVIEWEX_H

