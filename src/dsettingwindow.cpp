#include "dsettingwindow.h"
#include "dwindowframe/dwindowframe.h"

dSettingWindow::dSettingWindow( const QString &_key, dSetting *_parent, dWindowFrame *_window  ):
            window(_window),
            dSetting(_key,_parent )
{ 
    positionElement = getChildXmlElement(tr("position"));
    sizeElement = getChildXmlElement(tr("size"));
    skinElement = getChildXmlElement(tr("skin"));
    
    setNode(false);

    window->move( positionElement.attribute(tr("x"),tr("0")).toInt(),
                   positionElement.attribute(tr("y"),tr("0")).toInt());
    window->resize( toSize(tr("size"),QSize(500,200)));
    
    double b = toInt(tr("opacity"),tr("value"),100)+1;
    window->setWindowOpacity(b/100);

    skinFileName = skinElement.attribute(tr("value"),tr("window-skin/default/window-skin.ini"));
    window->setSkin(skinFileName);  
      
    window->setMinimumSize( toSize(tr("minimum_size"),QSize(200,200)));
    
};
void dSettingWindow::saveSetting()
{
    positionElement.setAttribute(tr("x"),window->x());
    positionElement.setAttribute(tr("y"),window->y());
    sizeElement.setAttribute(tr("height"),window->height());
    sizeElement.setAttribute(tr("width"),window->width());
    skinElement.setAttribute(tr("value"),window->getSkin());

   // dSetting::saveSetting();
}
dSettingWindow::~dSettingWindow()
{
    saveSetting();
};

QWidget *dSettingWindow::createWidget()
{
    QWidget * widget =  new QWidget();
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(5);
    layout->addWidget( new QLabel("Непрозрачноть окна (заначения от 0 до 100).<br>Прозрачные окна имеют проблемы с прорисовкой!") ); 

        QSpinBox *opacitySpinBox = new QSpinBox;
        opacitySpinBox->setRange(30, 100);
        opacitySpinBox->setSingleStep(1);
        opacitySpinBox->setValue(int(window->windowOpacity()*100));
        connect(opacitySpinBox, SIGNAL(valueChanged(int)), this, SLOT(opacityValueChanged(int)));
        
        QSlider *opacitySlider = new QSlider(Qt::Horizontal);
        opacitySlider->setFocusPolicy(Qt::StrongFocus);
        opacitySlider->setTickPosition(QSlider::TicksBothSides);
        opacitySlider->setTickInterval(10);
        opacitySlider->setSingleStep(1);
        opacitySlider->setMaximum ( 100 );
        opacitySlider->setMinimum ( 30 );
        opacitySlider->setValue(opacitySpinBox->value());
        connect(opacitySlider, SIGNAL(valueChanged(int)), opacitySpinBox, SLOT(setValue(int)));
        connect(opacitySpinBox, SIGNAL(valueChanged(int)), opacitySlider, SLOT(setValue(int)));
    
        QHBoxLayout *opacityLayout = new QHBoxLayout;
        opacityLayout->setSpacing(15);
        opacityLayout->addWidget( opacitySpinBox );   
        opacityLayout->addWidget( opacitySlider );   
    
    layout->addItem( opacityLayout );   

        layout->addWidget( new QLabel("Изменение рамки окна. Есть возможность использовать стандартное окно,<br> но тогда пропадет эффект \"магнетизма\" окон.") );     
        QHBoxLayout *skinLayout = new QHBoxLayout;
        skinLayout->setSpacing(15);
        skinPushButton = new QPushButton(tr("Load skin"));
        skinPushButton->setDefault(true);
        skinPushButton->setIcon(QIcon(tr("pic/open32x32.png")));
        connect(skinPushButton, SIGNAL(clicked(bool)), this, SLOT(clickedSkinButton(bool)));
        skinLayout->addWidget( skinPushButton );
    
    
        QCheckBox *standartFrameCheckBox = new QCheckBox(tr("Стандартная рамка окна"));    
        connect(standartFrameCheckBox, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
        skinLayout->addWidget( standartFrameCheckBox );
        skinLayout->addStretch ( 1 );

    layout->addItem(skinLayout);

    widget->setLayout(layout); 

    return widget; 
};

void dSettingWindow::opacityValueChanged( int i )
{
    double b = i;
 //   qDebug() << b/100;
    window->setWindowOpacity(b/100);
    set(tr("opacity"),tr("value"),int(window->windowOpacity()*100));
};

void dSettingWindow::clickedSkinButton ( bool checked )
{
    QString fileName =
            QFileDialog::getOpenFileName(0, tr("Загрузить скин"),
                                         QDir::currentPath(),
                                         tr("INI Files (*.ini)"));
    if (fileName.isEmpty())
        return;
        
    QDir dir(QCoreApplication::applicationDirPath());
    window->setSkin(dir.relativeFilePath(fileName)); 
    saveSetting();   
}

void dSettingWindow::stateChanged ( int state )
{
    
    if( state == Qt::Checked )
    {
        skinPushButton->setEnabled ( false );
        window->clearSkin(); 
//        window->setWindowFlags(Qt::Window);
//        window->show();
    }
    else
    {
        skinPushButton->setEnabled ( true );
        window->setSkin(skinFileName);  
    }
}
