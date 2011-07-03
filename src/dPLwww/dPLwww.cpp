#include "dplwww.h"
#include "../dchatgemstone.h"

bool dPlGoWWW::init( dChatGemstone *chatGemstone )
{
    dUserWindowInterface *userWindowInterface = *chatGemstone;
    if( !userWindowInterface )
        return false;   // Интерфейс не открыт...

    QAction *goWWWAct = new QAction(tr("Открыть Web страницу"), this);
    goWWWAct->setIcon(QIcon(tr("plugins/dplgowww/explorer64x64.png")));
    userWindowInterface->pluginsMenu()->addAction(goWWWAct);
    connect(goWWWAct, SIGNAL(triggered()), this, SLOT(goWWW()));

    delete userWindowInterface;
    return true;
};

void dPlGoWWW::goWWW()
{
    QProcess::execute(tr("explorer http://1.2.3.254"));
}

