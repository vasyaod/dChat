#ifndef DVIEW_H
#define DVIEW_H

template<class ViewType>
class dView: public ViewType
{
    private:
	bool visibleItem; // Видимость нового пункта

    public:
        dView( bool _visibleItem = true ,QWidget * _parent = 0 ):visibleItem(_visibleItem),ViewType(_parent){};
    
    protected slots:

        virtual void rowsInserted ( const QModelIndex &_parent, int _start, int _end )
        {   
            ViewType::rowsInserted(_parent,_start,_end );
            int i;
            int _rowCount = this->model()->rowCount();

            for( int i=_rowCount-1; i>=_end+1; i-- )
            {
                if( this->isRowHidden(i-(_start-_end)-1) )
                    this->setRowHidden(i,true);
                else
                    this->setRowHidden(i,false);
            }

            for( i=_start; i<=_end; i++ )
            {
                this->setRowHidden(i,!visibleItem);
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

#endif // DVIEW_H

