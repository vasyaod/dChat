#ifndef DFRIENDVIEW_H
#define DFRIENDVIEW_H

template<class ViewType>
class dFriendView: public ViewType
{
    private:
    // ”казатель на список друзей.
        QList<dFriend> *friends;
    public:
        dFriendView( QList<dFriend>*_friends, QWidget * _parent = 0 ): 
                    ViewType(_parent),friends(_friends){};
    
    protected slots:

        virtual void dataChanged ( const QModelIndex & _topLeft, const QModelIndex & _bottomRight)
        {   
            ViewType::dataChanged(_topLeft,_bottomRight);
            if ( _topLeft.column() == 1 )
            {
                dFriend _friend;
                _friend.name = this->model()->data(this->model()->index(_topLeft.row(),0)).toString(); 
                _friend.ip = this->model()->data(this->model()->index(_topLeft.row(),1)).toString(); 
                this->setRowHidden(_topLeft.row(),true);
                foreach(dFriend frd, *friends)
                    if( frd == _friend )
                        this->setRowHidden(_topLeft.row(),false);
            }
        };

        virtual void rowsInserted ( const QModelIndex &_parent, int _start, int _end )
        {   
            ViewType::rowsInserted(_parent,_start,_end );
            int _rowCount = this->model()->rowCount();

            for( int i=_rowCount-1; i>=_end+1; i-- )
            {
                if( this->isRowHidden(i-(_start-_end)-1) )
                    this->setRowHidden(i,true);
                else
                    this->setRowHidden(i,false);
            }
        };
        
        virtual void rowsAboutToBeRemoved( const QModelIndex &_parent, int _start, int _end )
        {   
            int _rowCount = this->model()->rowCount();

            for( int i=_end+1; i<_rowCount; i++)
            {
                if( this->isRowHidden(i) )
                    this->setRowHidden(i-(_start-_end)-1,true);
                else
                    this->setRowHidden(i-(_start-_end)-1,false);
            }
            ViewType::rowsInserted(_parent,_start,_end );
        };
};
#endif // DFRIENDVIEW_H

