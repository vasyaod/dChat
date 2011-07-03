#include <QtGui>

#include "dchannelitemdelegate.h"
#include "dmessagetable.h"

#include "../dchatapplication.h"
#include "../netex/dmanagerex.h"

bool dTextEditMessageEx::event ( QEvent * _event )
{
    if( _event->type() == QEvent::FocusOut )
        messageItemWidget->setCurrentIndex(0);
    QTextEdit::event(_event);
}
void dMessageItemWidget::mousePressEvent ( QMouseEvent * _event )
{
    if( _event->button() ==Qt::LeftButton )
    {
        setCurrentIndex(1);
        editWidget->setFocus(Qt::MouseFocusReason);
        QStackedWidget::mousePressEvent(_event);
    }
}
QSize dMessageItemWidget::sizeHint () const
{
    return labelWidget->sizeHint();
}

dMessageItemWidget::dMessageItemWidget( const QString &_msg, QWidget * _parent):
        QStackedWidget(_parent)
{
    labelWidget  = new QLabel(_msg,this);
    labelWidget->setWordWrap(true);
    labelWidget->setScaledContents(true);
    addWidget(labelWidget);
    
    editWidget = new dTextEditMessageEx(this);    
    editWidget->setPlainText(_msg);
    editWidget->setReadOnly( true );
    addWidget(editWidget);
    
    setCurrentIndex(0);
};

//******************************************************************
//                          dMessageTable
//******************************************************************
dMessageTable::dMessageTable( QWidget * _parent ):QTableWidget(_parent)
{
    application = qobject_cast<dChatApplication*>(QApplication::instance());
    
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    maxString = 30;
    setItemDelegate( new dChannelItemDelegate(this) );
    setColumnCount(1);
    horizontalHeader()->hide();
    horizontalHeader()->setResizeMode(QHeaderView::Custom);
    verticalHeader()->setHighlightSections(false);
    setSelectionMode(QAbstractItemView::SingleSelection);
    connect(verticalHeader(), SIGNAL(sectionDoubleClicked(int)), this, SLOT(sectionClicked(int)));
        
    clearAct = new QAction(tr("Очистить"), this);
    clearAct->setIcon(QIcon(tr("pic/new32x32.png")));
    connect(clearAct, SIGNAL(triggered(bool)), this, SLOT(clearToggled(bool)));

    findToListAct = new QAction(tr("Найти в списке"), this);
    findToListAct->setIcon(QIcon(tr("pic/glass.png")));
    connect(findToListAct, SIGNAL(triggered(bool)), this, SLOT(findToListToggled(bool)));

    sendMessageAct = new QAction(tr("Послать сообщение"), this);
    sendMessageAct->setIcon(QIcon(tr("pic/feather64x64.png")));
    connect(sendMessageAct, SIGNAL(triggered(bool)), this, SLOT(sendMessageToggled(bool)));

    sendBeepAct = new QAction(tr("Послать зв. вызов"), this);
    sendBeepAct->setIcon(QIcon(tr("pic/sound32x32.png")));
    connect(sendBeepAct, SIGNAL(triggered(bool)), this, SLOT(sendBeepToggled(bool)));
 
//    userInfoAct = new QAction(tr("Информация о пользователе"), this);
//    userInfoAct->setIcon(QIcon(tr("pic/question64x64.png")));
//    connect(sendBeepAct, SIGNAL(triggered(bool)), this, SLOT(sendBeepToggled(bool)));

    addAction(clearAct);
    setContextMenuPolicy(Qt::ActionsContextMenu);

    verticalHeader()->addAction(clearAct);
    verticalHeader()->addAction(findToListAct);
    verticalHeader()->addAction(sendMessageAct);
    verticalHeader()->addAction(sendBeepAct);
//    verticalHeader()->addAction(userInfoAct);
    verticalHeader()->setContextMenuPolicy(Qt::ActionsContextMenu);
 
 //   connect(allParametersAct, SIGNAL(triggered()), application, SLOT(showPropertyWindow()));

   // allParametersAct = new QAction(tr("Параметры/Настройки"), this);
  //  allParametersAct->setShortcut(tr("Ctrl+P"));
   // allParametersAct->setIcon(QIcon(tr("pic/gear64x64.png")));
   // connect(allParametersAct, SIGNAL(triggered()), application, SLOT(showPropertyWindow()));
     
};

void dMessageTable::addMessage( dPUser _usr, const QString &_msg)
{
    int i;
    // Удалим строки если их больше нормы.
    if( maxString < rowCount()+1 )
    {
        for( i = rowCount(); i >= maxString; i-- )
            removeRow(0);
        for( i=rowCount(); i >= 0; i--)
            resizeRowToContents(i);
    }
    
    int _rowCount = rowCount();
    setRowCount(_rowCount+1);
   // tableMessage->insertRow(rowCount);

    QString name = _usr->get_name().left(maxName).leftJustified(maxName, ' ');
    QTime time(QTime::currentTime());
    // Укарачиваем или удлинняем имя... дабы оно не было слишком
    // коротким или длинным.
    QTableWidgetItem *item1 = new QTableWidgetItem(name+tr("\n")+time.toString());
    item1->setTextAlignment(Qt::AlignVCenter);
    item1->setIcon(QIcon(_usr->get_avatar()));
    setVerticalHeaderItem(_rowCount,item1);

    QTableWidgetItem *item0 = new QTableWidgetItem(_msg);
    dMessageItemWidget *itemWidget = new dMessageItemWidget(_msg);
    itemWidget->name = _usr->get_name();
    itemWidget->from = _usr;
    
    item0->setData(Qt::UserRole, QVariant ((int) itemWidget));
    setItem(_rowCount,0,item0); 
    openPersistentEditor( item0 );
    resizeRowToContents(_rowCount);
    
    int _width;
    _width = width() - verticalHeader()->sizeHint().width()-23;
    horizontalHeader()->resizeSection(0,_width); 
 
    scrollTimerID = startTimer (100);
}

void dMessageTable::timerEvent ( QTimerEvent * _event )
{
    if( _event->timerId() == scrollTimerID )
    {
        killTimer(scrollTimerID);
        verticalScrollBar()->setValue( verticalScrollBar()->maximum() );
    }
};

void dMessageTable::resizeEvent ( QResizeEvent * _event )
{
    int _width;
    _width = width() - verticalHeader()->sizeHint().width()-23;
    horizontalHeader()->resizeSection(0,_width); 
}

void dMessageTable::sectionClicked( int logicalIndex )
{
    if( logicalIndex != -1 )
    {
        dMessageItemWidget *itemWidget = (dMessageItemWidget*)item(logicalIndex,0)->data(Qt::UserRole).toInt();
        if( !itemWidget ) return;    
            emit addNameSignal(itemWidget->name);
    }
}

void dMessageTable::clearToggled( bool _clickable )
{
     int _rowCount = rowCount();
     for( int i=0; i < _rowCount; i++)
            removeRow( 0 );
}

void dMessageTable::findToListToggled( bool _clickable )
{
    dPUser usr = getUserInTable();
    if( !usr )
        return;
        
    QItemSelectionModel *selectionModel = application->get_managerEx()->get_selectionModel();
    QAbstractItemModel *model = application->get_managerEx()->get_model();

    QModelIndex index;
    for( int i = 0; i < model->rowCount(); i++ )
    {
        index = model->index(i,0);
        if( model->data(index,Qt::UserRole).value<dPUser>() == usr )
        {
            selectionModel->setCurrentIndex(index,QItemSelectionModel::Current|QItemSelectionModel::ClearAndSelect);
            break;
        }
    }                  
       
}

void dMessageTable::sendMessageToggled( bool _clickable )
{
    dPUser usr = getUserInTable();
    if( !usr )
        return;
    application->createMessageEditor( usr,usr->get_main_user(),tr(""),tr("Новое сообщение."));
}

void dMessageTable::sendBeepToggled( bool _clickable )
{
    dPUser usr = getUserInTable();
    if( !usr )
        return;
    usr->send_msg_beep(usr->get_main_user());
}

dPUser dMessageTable::getUserInTable()
{
    if( currentRow() == -1 )
        return dPUser();
        
    dMessageItemWidget *itemWidget = (dMessageItemWidget*)item(currentRow(),0)->data(Qt::UserRole).toInt();
    dPUser usr = itemWidget->from;
    QList<dPUser> users = application->get_managerEx()->get_users();
    if( users.contains(usr) )
        return usr;
    else
    {
        QMessageBox::information(0, tr("Пользователь не найден в списке."),
                                 tr("Пользователь либо уже вышел из сети, либо не занесен\n в список, попробуйте его обновить."),
                                 QMessageBox::Ok,0,0);    
        return dPUser();
    }
}

