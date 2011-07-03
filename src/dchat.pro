######################################################################
# Automatically generated by qmake (2.00a) ?? 14. ??? 21:21:23 2005
######################################################################

TEMPLATE = app
DESTDIR       = ./release/
TARGET        = dchat
QT           += xml\
		network
DEPENDPATH += . \
              dchannelwindow \
              dfriendswindow \
              dlistviewex \
              dlogwindow \
              dmessageeditor \
              dtopicwindow \
              dtrayicon \
              dudpsocket \
              duserinfowindow \
              dwarningwindow \
              dwindowframe \
              ice-style \
              net \
              netex
INCLUDEPATH += . \
               netex \
               net \
               dwindowframe \
               dchannelwindow \
               dtopicwindow \
               dmessageeditor \
               dwarningwindow \
               dlogwindow \
               duserinfowindow \
               dfriendswindow \
               dtrayicon \
               dlistviewex \
               dudpsocket \
               ice-style

# Input
HEADERS += dchatapplication.h \
           dpropertywindow.h \
           dsetting.h \
           dsettinggeneral.h \
           dsettinguserwin.h \
           dsettingwindow.h \
           duserwindow.h \
           dview.h \
           dwindow.h \
           dchannelwindow/dchannelitemdelegate.h \
           dchannelwindow/dchannelwindow.h \
           dchannelwindow/dmessagetable.h \
           dchannelwindow/dsettingchannel.h \
           dfriendswindow/dfriendswindow.h \
           dfriendswindow/dfriendview.h \
           dfriendswindow/dsettingfriends.h \
           dlistviewex/ditemdelegate.h \
           dlistviewex/ditemwidget.h \
           dlistviewex/dlistviewex.h \
           dlogwindow/dlogwindow.h \
           dmessageeditor/dmessageeditor.h \
           dtopicwindow/dsettingtopic.h \
           dtopicwindow/dtopicwindow.h \
           duserinfowindow/duserinfowindow.h \
           dwarningwindow/dsettingwarning.h \
           dwarningwindow/dwarningwindow.h \
           net/dabstractremoteusercreator.h \
           net/dlocaluser.h \
           net/dmanager.h \
           net/dremoteuser.h \
           net/dservice.h \
           net/duser.h \
           netex/dabstractusercreator.h \
           netex/diplistex.h \
           netex/dlocaluserex.h \
           netex/dmanagerex.h \
           netex/dsettinglocaluser.h \
           netex/dsettingnet.h \
           netex/dsettingusers.h \
           netex/duserex.h \
           netex/dusersfactory.h \
           netex\dusersfactory.h \
           netex\dlocaluserex.h \
           net\dlocaluser.h \
           netex\duserex.h \
           net\duser.h \
           netex\dabstractusercreator.h \
           netex\dmanagerex.h \
           net\dmanager.h \
           net\dservice.h \
           netex\dsettingusers.h \
           netex\dsettingnet.h \
           dchannelwindow\dchannelwindow.h \
           dtopicwindow\dtopicwindow.h \
           dmessageeditor\dmessageeditor.h \
           dwarningwindow\dwarningwindow.h \
           dlogwindow\dlogwindow.h \
           duserinfowindow\duserinfowindow.h \
           dfriendswindow\dfriendswindow.h \
           dfriendswindow\dfriendview.h \
           dlistviewex\dlistviewex.h \
           dchannelwindow\dchannelitemdelegate.h \
           dchannelwindow\dsettingchannel.h \
           dchannelwindow\dmessagetable.h \
           dfriendswindow\dsettingfriends.h \
           dlistviewex\ditemdelegate.h \
           dlistviewex\ditemwidget.h \
           dtopicwindow\dsettingtopic.h \
           dwarningwindow\dsettingwarning.h \
           net\dremoteuser.h \
           net\dabstractremoteusercreator.h \
           netex\diplistex.h \
           netex\dsettinglocaluser.h
SOURCES += dchatapplication.cpp \
           dpropertywindow.cpp \
           dsetting.cpp \
           dsettinggeneral.cpp \
           dsettinguserwin.cpp \
           dsettingwindow.cpp \
           duserwindow.cpp \
           dwindow.cpp \
           main.cpp \
           dchannelwindow/dchannelitemdelegate.cpp \
           dchannelwindow/dchannelwindow.cpp \
           dchannelwindow/dmessagetable.cpp \
           dchannelwindow/dsettingchannel.cpp \
           dfriendswindow/dfriendswindow.cpp \
           dfriendswindow/dsettingfriends.cpp \
           dlistviewex/ditemdelegate.cpp \
           dlistviewex/ditemwidget.cpp \
           dlistviewex/dlistviewex.cpp \
           dlogwindow/dlogwindow.cpp \
           dmessageeditor/dmessageeditor.cpp \
           dtopicwindow/dsettingtopic.cpp \
           dtopicwindow/dtopicwindow.cpp \
           duserinfowindow/duserinfowindow.cpp \
           dwarningwindow/dsettingwarning.cpp \
           dwarningwindow/dwarningwindow.cpp \
           net/dlocaluser.cpp \
           net/dmanager.cpp \
           net/dremoteuser.cpp \
           net/dservice.cpp \
           net/duser.cpp \
           netex/diplistex.cpp \
           netex/dlocaluserex.cpp \
           netex/dmanagerex.cpp \
           netex/dsettingnet.cpp \
           netex/dsettingusers.cpp \
           netex/duserex.cpp \
           netex/dusersfactory.cpp \
           netex\dusersfactory.cpp \
           netex\dlocaluserex.cpp \
           net\dlocaluser.cpp \
           netex\duserex.cpp \
           net\duser.cpp \
           netex\dmanagerex.cpp \
           net\dmanager.cpp \
           net\dservice.cpp \
           netex\dsettingusers.cpp \
           netex\dsettingnet.cpp \
           dchannelwindow\dchannelwindow.cpp \
           dtopicwindow\dtopicwindow.cpp \
           dmessageeditor\dmessageeditor.cpp \
           dwarningwindow\dwarningwindow.cpp \
           dlogwindow\dlogwindow.cpp \
           duserinfowindow\duserinfowindow.cpp \
           dfriendswindow\dfriendswindow.cpp \
           dlistviewex\dlistviewex.cpp \
           dchannelwindow\dchannelitemdelegate.cpp \
           dchannelwindow\dsettingchannel.cpp \
           dchannelwindow\dmessagetable.cpp \
           dfriendswindow\dsettingfriends.cpp \
           dlistviewex\ditemdelegate.cpp \
           dlistviewex\ditemwidget.cpp \
           dtopicwindow\dsettingtopic.cpp \
           dwarningwindow\dsettingwarning.cpp \
           net\dremoteuser.cpp \
           netex\diplistex.cpp
