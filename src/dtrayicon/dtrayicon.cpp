#include <windows.h>
#include "dtrayicon.h"

#define WM_SYSTEM_TRAY_NOTIFY (WM_USER + 121)
char szClassName[ ] = "dChatTray";
dTrayIcon::dTrayIcon( QObject * _parent):
                QObject(_parent)
{
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = 0;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = 0;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        throw int(0);
      //  return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Code::Blocks Template Windows App",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           0,        /* The window is a child-window to desktop */
           0,                /* No menu */
           0,       /* Program Instance handler */
           0                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    //ShowWindow (hwnd, 1);
    if (!hwnd) {
        qWarning("Failed to create QEventDispatcherWin32 internal window: %d\n", (int)GetLastError());
    }
    
  //  qDebug("+");
};

dTrayIcon::~dTrayIcon()
{
     deleteIcon();
};

LRESULT CALLBACK dTrayIcon::WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    dTrayIcon *trayIcon;
    UINT uMouseMsg; 
  //  qDebug("+++");
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
        case WM_SYSTEM_TRAY_NOTIFY:
            trayIcon = (dTrayIcon*)wParam;
            uMouseMsg = (UINT) lParam; 
            if( WM_LBUTTONDOWN == uMouseMsg )
                emit trayIcon->leftButtonDown();
            if( WM_RBUTTONDOWN == uMouseMsg )
                emit trayIcon->rightButtonDown();
        break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

bool dTrayIcon::addIcon( const QString & _iconfile, const QString &_title )
{
    char *iconfile = _iconfile.toLocal8Bit().data();
    //HICON hicon = LoadIcon(NULL,IDI_APPLICATION);
    HICON hicon = (HICON)LoadImage(0, // small class icon 
                            iconfile,
                            IMAGE_ICON, 
                            GetSystemMetrics(SM_CXSMICON), 
                            GetSystemMetrics(SM_CYSMICON), 
                            LR_LOADFROMFILE); 
/*  
    QLabel label("test");
    if( !DrawIcon(label.getDC(),10,10,hicon) )
        qDebug("fsfadfsdfsdfsdfsdf");
*/
    UINT uID = int(this);
    BOOL res; 
    NOTIFYICONDATA tnid;
 
    tnid.cbSize = sizeof(NOTIFYICONDATA); 
    tnid.hWnd = hwnd; 
    tnid.uID = uID; 

    tnid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP; 
    tnid.uCallbackMessage = WM_SYSTEM_TRAY_NOTIFY; 
    tnid.hIcon = hicon; 
    
    lstrcpyn(tnid.szTip, _title.toLocal8Bit().data(), sizeof(tnid.szTip)); 

    res = Shell_NotifyIcon(NIM_ADD, &tnid); 
 
    if (hicon) 
        DestroyIcon(hicon);
    
    return res;
}

bool dTrayIcon::deleteIcon()
{
   NOTIFYICONDATA tnid; 
 
    tnid.cbSize = sizeof(NOTIFYICONDATA); 
    tnid.hWnd = hwnd; 
    tnid.uID = int(this); 
    Shell_NotifyIcon(NIM_DELETE, &tnid);
   // qDebug("-");
}

Q_EXPORT_PLUGIN(dTrayIcon)
/*
int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);
//    dTrayIcon trayIcon(QObject::tr("Text!!!"));
 //   return app.exec();
}
*/
